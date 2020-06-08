// AbonentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VSAT_TES.h"
#include "AbonentDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAbonentDlg dialog


CAbonentDlg::CAbonentDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAbonentDlg::IDD, pParent)
{
	SynFlag=0;
		
	//{{AFX_DATA_INIT(CAbonentDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

}


void CAbonentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAbonentDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAbonentDlg, CDialog)
	//{{AFX_MSG_MAP(CAbonentDlg)
	ON_WM_CTLCOLOR()
	ON_MESSAGE(MES_COUNT, OnMesCount)
	ON_MESSAGE(MES_SYN, OnMesSyn)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAbonentDlg message handlers

LRESULT CAbonentDlg::OnMesSyn(WPARAM Num,LPARAM Vkl)
{   

	 ::WaitForSingleObject(HMutexDir,INFINITE); // если вдруг в этот момент пользователь 
												 // захочет выбрать другую директорию
	 if(SynFlag!=1)
	   {
		 WorkFlag=TRUE;
		 SynFlag=1;	
	 
	   ShowWindow(SW_SHOW);

	   SetDlgItemText(IDC_QUAL1,"");     
	   SetDlgItemText(IDC_QUAL2,"");     
	   SetDlgItemText(IDC_SYN1,""); 
	   SetDlgItemText(IDC_SYN2,""); 
  
	   CString FileName1,FileName2,strTemp;
	   strTemp.Format("%d",NumFile++);
	   FileName1=m_TargetDir+"\\"+"_"+FileNameC+"_C"+strTemp;

	   if(Flag3_4==TRUE)
	   {
	   Ocean.buf_in1=new BYTE[2000];
	   Ocean.buf_in2=new BYTE[2000];
	   Ocean.buf_out=new BYTE[2000];
	   Ocean.buf_temp=new BYTE[2000];
	   Ocean.buf_deper=new BYTE[2000];
	   Ocean.buf_dec=new BYTE[2000];
	   Ocean.buf_dif=new BYTE[2000];
	   Ocean.buf_dskr=new BYTE[2000];
	   for(int i=0;i<48;i++) 
	   {
    			if((Ocean.massiv[i]=new BYTE[400])==NULL) 
				{
    		  ::MessageBox(NULL,"Не хватает памяти!!!",NULL,MB_OK);
				exit(0);
				return 0;
				}

	   }

	   if(Ocean.fout1.Open(FileName1,CFile::modeCreate|CFile::modeWrite)); else exit(0);	
	   }
	   else
		if(Flag1_2==TRUE)
		{
	   Ocean2.buf_in1=new BYTE[2000];
	   Ocean2.buf_in2=new BYTE[2000];
	   Ocean2.buf_out=new BYTE[2000];
	   Ocean2.buf_temp=new BYTE[2000];
	   Ocean2.buf_deper=new BYTE[2000];
	   Ocean2.buf_dec=new BYTE[2000];
	   Ocean2.buf_dif=new BYTE[2000];
	   Ocean2.buf_dskr=new BYTE[2000];
	   for(int i=0;i<48;i++) 
	   {
    			if((Ocean2.massiv[i]=new BYTE[100])==NULL) 
				{
    		  ::MessageBox(NULL,"Не хватает памяти!!!",NULL,MB_OK);
				exit(0);
				return 0;
				}

	   }

	   if(Ocean2.fout1.Open(FileName1,CFile::modeCreate|CFile::modeWrite)); else exit(0);	
		}
		  else
		  { 
			MessageBox("Не могу установить вид НСК (12 байт в пакете назначения частот)",0,0);
			OnStop();
		  } 

	   SetDlgItemText(IDC_FileName1,FileNameC+"_C"+strTemp);

	   if(FileNameA!="")
	   {
		   FileName2=m_TargetDir+"\\"+"_"+FileNameA+"_A"+strTemp;
		   if(Flag3_4==TRUE)
		   {
			 if(Ocean.fout2.Open(FileName2,CFile::modeCreate|CFile::modeWrite));
			 else exit(0);  
		   }
		   if(Flag1_2==TRUE)
		   {
			 if(Ocean2.fout2.Open(FileName2,CFile::modeCreate|CFile::modeWrite));
			 else exit(0);  
		   }
		   SetDlgItemText(IDC_FileName2,FileNameA+"_A"+strTemp);
	   }
	   else 
	   {
		   FileName2=m_TargetDir+"\\"+"_"+FileNameC+"_A"+strTemp;
		   if(Flag3_4==TRUE)
		   {
			 if(Ocean.fout2.Open(FileName2,CFile::modeCreate|CFile::modeWrite));
			 else exit(0);  
		   }
		   if(Flag1_2==TRUE)
		   {
			 if(Ocean2.fout2.Open(FileName2,CFile::modeCreate|CFile::modeWrite));
			 else exit(0);  
		   }
		   SetDlgItemText(IDC_FileName2,FileNameC+"_A"+strTemp);
	   }
   

		if(!Mirag.OpenTread(1)) // функция создания потока
		{
			MessageBox("Не могу открыть поток для Mirage 1");
			exit(0);
		}
	   NumBlock[0]=0;
	   NumBlock[1]=0;
	   m_Quality[0]=0; m_Quality[1]=0;
	   BytesDone1=0; BytesDone2=0;
	   }

   ::ReleaseMutex(HMutexDir); // освобождаем мьютекс  
   return 0;
}


LRESULT CAbonentDlg::OnMesCount(WPARAM def, LPARAM Block ) 
{
	BYTE buf[4000];
	static 	BOOL Syn1=FALSE,Syn2=FALSE;
	CString Text;
	int len_block;

	if(WorkFlag==TRUE)
	{
	  while(1)
	  {
	   len_block=Mirag.GetBlock(buf,sizeof(buf),1);   //вызываем функцию GetBlock,чтобы
													  //не очищать буфер,если запрошенной длины                                            
													  // еще не накоплено
	   if(len_block==sizeof(buf)) break; else Sleep(1);        //задержка для заполнения буфера

	  }


	  if(NumBlock[0]==20)
			   { 
				   Text.Format("%d",m_Quality[0]*5);
				   Text+=" %";
				   SetDlgItemText(IDC_QUAL1,Text);
				   m_Quality[0]=0;
				   NumBlock[0]=0;
			   }
	  if(NumBlock[1]==20)
			   { 
			   
				   Text.Format("%d",m_Quality[1]*5);
				   Text+=" %";
				   SetDlgItemText(IDC_QUAL2,Text);
				   m_Quality[1]=0;
				   NumBlock[1]=0;
			   }

	   // Здесь необходимо учесть какой вид кодирования используется во включившихся
								// абонентских кналах (1/2 или 3/4)


	//////////////////////////////////////// Вот блок для обработки 3/4//////////////////////////////////////////////////////
	  if(Flag3_4==TRUE)
	  {

	   if(Ocean.Demultiplex(buf,len_block)==TRUE)
	   if(Ocean.SizeBuf_kan>100)
	   {

		if((Ocean.Num_kan==2)||(Ocean.Num_kan==0))
		if(SynFlag1==TRUE)
		{
		 NumBlock[0]++;
		 if(Syn1==FALSE)  // если нет синхронизации в первом канале
		 {

		  Ocean.buf_saveG726[0]=0; 
		  Ocean.buf_saveG728[0][0]=0; 
		  Ocean.SynchroG728[0]=FALSE;
		  Ocean.SynchroG726[0]=FALSE;
		
   		   if(Ocean.synchro_search(Ocean.buf_in1,30,0)==TRUE)
		   {
          
			  Syn1=TRUE;                  //устанавливаем флаг синхронизации в единицу

			  if(Ocean.Obrabotka(Ocean.buf_in1,Ocean.SizeBuf_kan,0))
			  {
				  BytesDone1+=Ocean.SizeBuf_kan*3/4;		
				  m_Quality[0]++;
			  }
			  m_ColorSyn1=RGB(0,128,32);
			  SetDlgItemText(IDC_SYN1,"Есть"); 
		   } 
		   else
		   {
			  m_ColorSyn1=RGB(128,32,0);
			  SetDlgItemText(IDC_SYN1,"Нет"); 
		   }
       
		 }
		 else                                  // если есть синхронизация
		 {
			if(Ocean.Obrabotka(Ocean.buf_in1,Ocean.SizeBuf_kan,0)==TRUE)
			{
			   m_Quality[0]++;
           
			   m_ColorSyn1=RGB(0,128,32);
			   SetDlgItemText(IDC_SYN1,"Есть"); 
			   BytesDone1+=Ocean.SizeBuf_kan*3/4;		   
			}
			else 
			{
			  m_ColorSyn1=RGB(128,32,0);
			  SetDlgItemText(IDC_SYN1,"Нет");  
    		  Syn1=FALSE;
			}
		 }
		}
    
	   if((Ocean.Num_kan==2)||(Ocean.Num_kan==1))
	   if(SynFlag2==TRUE)
	   {
		NumBlock[1]++;
		if(Syn2==FALSE)  // если нет синхронизации во втором канале
		{
	    
		 Ocean.buf_saveG726[1]=0;
		 Ocean.buf_saveG728[1][0]=0; 
		 Ocean.SynchroG728[1]=FALSE;

		   if(Ocean.synchro_search(Ocean.buf_in2,30,1)==TRUE)
		   {
          
        
			  Syn2=TRUE;                  //устанавливаем флаг синхронизации в единицу
			  if(Ocean.Obrabotka(Ocean.buf_in2,Ocean.SizeBuf_kan,1))
			  {
				  BytesDone2+=Ocean.SizeBuf_kan*3/4;
				  m_Quality[1]++;
			  }
			  m_ColorSyn2=RGB(0,128,32);
			  SetDlgItemText(IDC_SYN2,"Есть"); 
		   } 
		   else
		   {
			  m_ColorSyn2=RGB(128,32,0);
			  SetDlgItemText(IDC_SYN2,"Нет"); 
		   }
       
		}
		else                                  // если есть синхронизация
		{
			if(Ocean.Obrabotka(Ocean.buf_in2,Ocean.SizeBuf_kan,1)==TRUE)
			{
			   m_Quality[1]++;
			   m_ColorSyn2=RGB(0,128,32);
			   SetDlgItemText(IDC_SYN2,"Есть"); 
			   BytesDone2+=Ocean.SizeBuf_kan*3/4;		
			}
			else 
			{
			  m_ColorSyn2=RGB(128,32,0);
			  SetDlgItemText(IDC_SYN2,"Нет");  
			  Syn2=FALSE;
			}
		}
	   }
	  }

	   SetDlgItemInt(IDC_ISDONE1, BytesDone1/1024);
	   SetDlgItemInt(IDC_ISDONE2, BytesDone2/1024);

	 }
	/////////////////////////////////// Конец блока обработки 3/4////////////////////////////////

	else                                 
	/////////////////////////////////// Вот блок для обработки 1/2///////////////////////////////
	  if(Flag1_2==TRUE)
	  {
    

	//  SetDlgItemInt(IDC_SIZ_BBUF,len_block);
	//  SetDlgItemInt(IDC_SIZE_BUF,Ocean.SizeBuf_kan);

	  if(Ocean2.Demultiplex(buf,len_block)==TRUE)
	  if(Ocean2.SizeBuf_kan>100)
	  {

	   if((Ocean2.Num_kan==2)||(Ocean2.Num_kan==0))
	   if(SynFlag1==TRUE)
	   {
		NumBlock[0]++;
		if(Syn1==FALSE)  // если нет синхронизации в первом канале
		{

	 //   Ocean2.buf_saveG726[0]=0; 
	 //	  Ocean2.buf_saveG728[0][0]=0; 
	 //	  Ocean2.SynchroG728[0]=FALSE;
		
   		   if(Ocean2.synchro_search(Ocean2.buf_in1,100,0)==TRUE)
		   {
          
			  Syn1=TRUE;                  //устанавливаем флаг синхронизации в единицу

			  if(Ocean2.Obrabotka(Ocean2.buf_in1,Ocean2.SizeBuf_kan,0))
			  {
				  BytesDone1+=Ocean2.SizeBuf_kan/2;		
				  m_Quality[0]++;
			  }
			  m_ColorSyn1=RGB(0,128,32);
			  SetDlgItemText(IDC_SYN1,"Есть"); 
		   } 
		   else
		   {
			  m_ColorSyn1=RGB(128,32,0);
			  SetDlgItemText(IDC_SYN1,"Нет"); 
		   }
       
		}
		else                                  // если есть синхронизация
		{
			if(Ocean2.Obrabotka(Ocean2.buf_in1,Ocean2.SizeBuf_kan,0)==TRUE)
			{
			   m_Quality[0]++;
           
			   m_ColorSyn1=RGB(0,128,32);
			   SetDlgItemText(IDC_SYN1,"Есть"); 
			   //SetDlgItemInt(ID_C_SdwigG728,Ocean.m_MaxSynIndex[0]);
			   BytesDone1+=Ocean2.SizeBuf_kan/2;		   
			}
			else 
			{
			  m_ColorSyn1=RGB(128,32,0);
			  SetDlgItemText(IDC_SYN1,"Нет");  
    		  Syn1=FALSE;
			}
		}
	   }
    
	   if((Ocean2.Num_kan==2)||(Ocean2.Num_kan==1))
	   if(SynFlag2==TRUE)
	   {
		NumBlock[1]++;
		if(Syn2==FALSE)  // если нет синхронизации во втором канале
		{

		 //Ocean2.buf_saveG726[1]=0;
		 //Ocean2.buf_saveG728[1][0]=0; 
		 //Ocean2.SynchroG728[1]=FALSE;

		   if(Ocean2.synchro_search(Ocean2.buf_in2,100,1)==TRUE)
		   {
          
			  Syn2=TRUE;                  //устанавливаем флаг синхронизации в единицу
			  if(Ocean2.Obrabotka(Ocean2.buf_in2,Ocean2.SizeBuf_kan,1))
			  {
				  BytesDone2+=Ocean2.SizeBuf_kan/2;
				  m_Quality[1]++;
			  }
			  m_ColorSyn2=RGB(0,128,32);
			  SetDlgItemText(IDC_SYN2,"Есть"); 
		   } 
		   else
		   {
			  m_ColorSyn2=RGB(128,32,0);
			  SetDlgItemText(IDC_SYN2,"Нет"); 
		   }
       
		}
		else                                  // если есть синхронизация
		{
			if(Ocean2.Obrabotka(Ocean2.buf_in2,Ocean2.SizeBuf_kan,1)==TRUE)
			{
			   m_Quality[1]++;
			   m_ColorSyn2=RGB(0,128,32);
			   SetDlgItemText(IDC_SYN2,"Есть"); 
			   BytesDone2+=Ocean2.SizeBuf_kan/2;		
			}
			else 
			{
			  m_ColorSyn2=RGB(128,32,0);
			  SetDlgItemText(IDC_SYN2,"Нет");  
			  Syn2=FALSE;
			}
		}
	   }
	  }

	SetDlgItemInt(IDC_ISDONE1, BytesDone1/1024);
	SetDlgItemInt(IDC_ISDONE2, BytesDone2/1024);

	}
	///////////////////////////////////Конец блока обработки 1/2////////////////////////////////

	  UpdateData(FALSE);

	  ::WaitForSingleObject(HMutexMax,INFINITE); // если вдруг в этот момент пользователь 
												 // захочет изменить ограничение на размеры
	  if(MaxSizeFile!=0) // ограничение размера файла
	   {
		  if(Flag3_4==TRUE)
		  {
		   if((Ocean.fout1.GetPosition()>=(MaxSizeFile*1024))||
			 (Ocean.fout2.GetPosition()>=(MaxSizeFile*1024)))
		   {
		   ::SendMessage(inhWnd,MES_OTKL,0,0);
		   }
		  }
		  if(Flag1_2==TRUE)
		  {
		   if((Ocean2.fout1.GetPosition()>=(MaxSizeFile*1024))||
			 (Ocean2.fout2.GetPosition()>=(MaxSizeFile*1024)))
		   {
		   ::SendMessage(inhWnd,MES_OTKL,0,0);
		   }
		  }
	   }
	  ::ReleaseMutex(HMutexMax);


	  }
  return 0;
}

void CAbonentDlg::OnStop()
{

	CString FileName[2];
	int i;
	BOOL FlagDel[2]={ FALSE,FALSE };

	  WorkFlag=FALSE;


	  if(SynFlag==1)
	  {
	   Mirag.WorkFlag[1]=FALSE;
	   EndDialog(0);

	 ::WaitForSingleObject(HMutexMin,INFINITE); // если вдруг в этот момент пользователь 
												 // захочет изменить ограничение на размеры
	 if(Flag3_4==TRUE)
	 {
	   FileName[0]=Ocean.fout1.GetFilePath(); // полный путь к файлу
	   FileName[1]=Ocean.fout2.GetFilePath(); // полный путь к файлу

	   if(Ocean.fout1.GetPosition()<=MinSizeFile*1024)
	   {
	 		   FlagDel[0]=TRUE;
	   
	   }
	   if(Ocean.fout2.GetPosition()<=MinSizeFile*1024)
	   {
     		   FlagDel[1]=TRUE;
	   }

		m_FilesDone+=2;

	   Ocean.fout1.Close();	
	   Ocean.fout2.Close();
	   Ocean.Num_kan=3;
				delete [] Ocean.buf_in1;
				delete [] Ocean.buf_in2;
				delete [] Ocean.buf_out;
				delete [] Ocean.buf_temp;
				delete [] Ocean.buf_deper;
				delete [] Ocean.buf_dec;
				delete [] Ocean.buf_dif;
				delete [] Ocean.buf_dskr;
			 for(i=0;i<48;i++) delete [] Ocean.massiv[i];

	 }
	 else   
	 if(Flag1_2==TRUE)
	 {
	   FileName[0]=Ocean2.fout1.GetFilePath(); // полный путь к файлу
	   FileName[1]=Ocean2.fout2.GetFilePath(); // полный путь к файлу

	   if(Ocean2.fout1.GetPosition()<=MinSizeFile*1024)
	   {
	 		   FlagDel[0]=TRUE;
	   
	   }
	   if(Ocean2.fout2.GetPosition()<=MinSizeFile*1024)
	   {
     		   FlagDel[1]=TRUE;
	   }

		m_FilesDone+=2;

	   Ocean2.fout1.Close();	
	   Ocean2.fout2.Close();
	   Ocean2.Num_kan=3;
				delete [] Ocean2.buf_in1;
				delete [] Ocean2.buf_in2;
				delete [] Ocean2.buf_out;
				delete [] Ocean2.buf_temp;
				delete [] Ocean2.buf_deper;
				delete [] Ocean2.buf_dec;
				delete [] Ocean2.buf_dif;
				delete [] Ocean2.buf_dskr;
			 for(i=0;i<48;i++) delete [] Ocean2.massiv[i];

	 }
  

	   for(i=0;i<2;i++)
	   {
		if(!MoveFile(FileName[i],FileName[i]+".dat")) 
			MessageBox("NO RENAME",0,0);
		FileName[i]+=".dat";
   		if(FlagDel[i]==TRUE)
		{
			 DeleteFile(FileName[i]);
			 --m_FilesDone;
		}
	   }
   
		if((FlagDel[0])&&(FlagDel[1])) if(NumFile>0) --NumFile;

		SynFlag=0;
	        
	   ::ReleaseMutex(HMutexMin);
	  }
}

HBRUSH CAbonentDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
    int TargetControl=pWnd->GetDlgCtrlID();
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	switch(TargetControl){
	case IDC_SYN1:	pDC->SetTextColor(m_ColorSyn1);		break;
	case IDC_SYN2:	pDC->SetTextColor(m_ColorSyn2);		break;
	}	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}


/*void CAbonentDlg::OnPaint() 
{

		CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}*/


BOOL CAbonentDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	HMutexDir=::CreateMutex(NULL,
		                    FALSE,
							NULL);
	HMutexMax=::CreateMutex(NULL,
		                    FALSE,
							NULL);
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

