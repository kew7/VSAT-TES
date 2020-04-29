// VSAT_TESDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VSAT_TES.h"
#include "VSAT_TESDlg.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVSAT_TESDlg dialog

CVSAT_TESDlg::CVSAT_TESDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVSAT_TESDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVSAT_TESDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	flWork=FALSE;
}

void CVSAT_TESDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVSAT_TESDlg)
	DDX_Control(pDX, IDC_TAB, m_Cards);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVSAT_TESDlg, CDialog)
	//{{AFX_MSG_MAP(CVSAT_TESDlg)
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnSelchangeTab)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB, OnSelchangingTab)
	ON_BN_CLICKED(ID_PUSK, OnPusk)
	ON_BN_CLICKED(ID_STOP, OnStop)
	ON_MESSAGE(MES_COUNT2, OnMesCount2)
	ON_MESSAGE(MES_VKL, OnMesVkl)
	ON_MESSAGE(MES_OTKL, OnMesOtkl)
	ON_MESSAGE(MES_SHOW_DISK,OnShowDisk )
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_COMMAND(ID_DIR_OPEN, OnDirOpen)
	ON_COMMAND(ID_FILE_FREQ, OnFileFreq)
	ON_COMMAND(ID_TEMP_DIR, OnDirOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVSAT_TESDlg message handlers

BOOL CVSAT_TESDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	TC_ITEM TabCtrlItem;
	TabCtrlItem.mask = TCIF_TEXT;
    TabCtrlItem.pszText = " Терминалы ";
	m_Cards.InsertItem( 0, &TabCtrlItem );
	TabCtrlItem.pszText = " Установки ";
	m_Cards.InsertItem( 1, &TabCtrlItem );
    TabCtrlItem.pszText = " Отбор ";
	m_Cards.InsertItem( 2, &TabCtrlItem );
    
	m_TerminalDlg.Create(CTerminalDlg::IDD,this);
	m_OtborDlg.Create(COtborDlg::IDD,this);
	m_ConfigDlg.Create(CConfigDlg::IDD,this);

    m_Cards.SetCurSel(0);
	m_TerminalDlg.ShowWindow(SW_SHOW);

	m_ConfigDlg.m_MinSize.SetRange(10,100);
	m_ConfigDlg.m_MaxSize.SetRange(1000,10000);

    GetDlgItem(ID_STOP)->EnableWindow(FALSE);	
    m_TargetDirSave="C:\\";
	m_ConfigDlg.SetDlgItemText(IDC_PATH," "+m_TargetDirSave);
	m_TargetDirTemp="C:\\";

    Com.AbonDlg=new CAbonentDlg;          // создаем объект абонентского диалогового окна
	Com.AbonDlg->inhWnd=this->m_hWnd;
	Com.AbonDlg->Create(CAbonentDlg::IDD);

	Com.AbonDlg->EndDialog(0);
	SetTimer(1,1000,NULL);

	m_TerminalDlg.m_ColorIden=RGB(32,32,128);
    m_TerminalDlg.m_ColorIden2=RGB(32,32,128);
		                                   
	return TRUE;  // return TRUE  unless you set the focus to a control

// If you add a minimize button to your dialog, you will need the code below

//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
}

void CVSAT_TESDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		if((m_ConfigDlg.m_Radio==1)&&(flWork==TRUE)&&(Com.AbonDlg->SynFlag==1))
			Com.AbonDlg->ShowWindow(SW_SHOW);
		CDialog::OnPaint();
    }
	
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVSAT_TESDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CVSAT_TESDlg::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	switch (m_Cards.GetCurSel()){
	case 0: m_TerminalDlg.ShowWindow(SW_SHOW);   break;
	case 1: m_ConfigDlg.ShowWindow(SW_SHOW);     break;
	case 2: m_OtborDlg.ShowWindow(SW_SHOW);	     break;
	}
	*pResult = 0;
}

void CVSAT_TESDlg::OnSelchangingTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
 	switch (m_Cards.GetCurSel()){
	case 0: m_TerminalDlg.ShowWindow(SW_HIDE);   break;
	case 1: m_ConfigDlg.ShowWindow(SW_HIDE);     break;
	case 2: m_OtborDlg.ShowWindow(SW_HIDE);		 break;
	}
	*pResult = 0;
}

void CVSAT_TESDlg::OnPusk() 
{
	// TODO: Add your control notification handler code here

   GetDlgItem(ID_PUSK)->EnableWindow(FALSE);
   GetDlgItem(ID_STOP)->EnableWindow(TRUE);	
//   Ocean.fout.Open("fileOcc.dat",CFile::modeCreate|CFile::modeWrite);
  
   m_ConfigDlg.GetDlgItem(IDC_RADIO)->EnableWindow(FALSE);
   m_ConfigDlg.GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
   m_ConfigDlg.GetDlgItem(IDC_RADIO_4HHz)->EnableWindow(FALSE);
   m_ConfigDlg.GetDlgItem(IDC_RADIO_11HHz)->EnableWindow(FALSE);
   m_ConfigDlg.GetDlgItem(IDC_SPEED)->EnableWindow(FALSE);
   m_ConfigDlg.GetDlgItem(IDC_SPEED2)->EnableWindow(FALSE);

   Ocean.Process.FlagZes=FALSE;
   m_TerminalDlg.m_Zes="";

   if(m_ConfigDlg.m_Radio==0)
   {
       m_ConfigDlg.GetDlgItem(IDC_TXT_PATH)->EnableWindow(FALSE);
       m_ConfigDlg.GetDlgItem(IDC_PATH)->EnableWindow(FALSE);

	   Ocean.Process.Radio=0;
	   Ocean.Process.ObsluvFlag=0;
	   Ustan_Razw();
	   m_TerminalDlg.SetDlgItemText(IDC_VKL,"");
   }

   if(m_ConfigDlg.m_Radio==1) 
   {

	     if(m_FileFreqName=="") 
		  {
		   GetDlgItem(ID_PUSK)->EnableWindow(TRUE);
 	       GetDlgItem(ID_STOP)->EnableWindow(FALSE);

           m_ConfigDlg.GetDlgItem(IDC_RADIO)->EnableWindow(TRUE);
           m_ConfigDlg.GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE);
           m_ConfigDlg.GetDlgItem(IDC_RADIO_4HHz)->EnableWindow(TRUE);
           m_ConfigDlg.GetDlgItem(IDC_RADIO_11HHz)->EnableWindow(TRUE);
	       m_ConfigDlg.GetDlgItem(IDC_SPEED)->EnableWindow(TRUE);
		   m_ConfigDlg.GetDlgItem(IDC_SPEED2)->EnableWindow(TRUE);
		   MessageBox("Выберите файл с кодами частот",NULL,MB_ICONERROR);
		   return;
		  }
	Ocean.Process.finFREQ.Open(m_FileFreqName,CFile::modeRead);
	GetMenu()->EnableMenuItem(ID_FILE_FREQ,MF_GRAYED);
	Ocean.Process.Radio=1;
	Ocean.Process.ObsluvFlag=0;
	Ocean.Process.Vkl_Done=0;

	Ocean.Process.inhWnd=this->m_hWnd; //указываем дискриптору класса HDLC 
                                      //на дискриптор этого диалогового окна 
	
  	Ustan_Priem();
	m_TerminalDlg.SetDlgItemText(IDC_VKL,"Ожидание...");
	m_ConfigDlg.SetDlgItemText(IDC_NumSeans,"0");
	Com.AbonDlg->NumFile=0;
	Com.AbonDlg->m_FilesDone=0;
	Com.AbonDlg->SynFlag=0;
	Com.AbonDlg->Ocean.Num_kan=3;
	Com.AbonDlg->Ocean2.Num_kan=3;

   }

   flWork=TRUE;     
   if(!Mirag.Create(0,this->m_hWnd))
	{	
	  OnStop();
	::MessageBox(NULL,"НЕТ СИГНАЛА НА ВХОДЕ Mirage 0 !!!","Сообщение",MB_OK|MB_ICONERROR);    
	  return;
	}

   if(!Mirag.OpenTread(0)) // функция создания потока
	{
		MessageBox("Не могу открыть поток для Mirage 0");
		exit(0);
	}

  if(m_ConfigDlg.m_Radio==1) 
   	if(!(Com.AbonDlg->Mirag.Create(1,Com.AbonDlg->m_hWnd)))
	{	
	  OnStop();
	::MessageBox(NULL,"НЕТ СИГНАЛА НА ВХОДЕ Mirage 0!!!","Сообщение",MB_OK|MB_ICONERROR);    
	  return;
	}
}

void CVSAT_TESDlg::OnStop() 
{
	// TODO: Add your control notification handler code here

	flWork=FALSE;
//	Ocean.fout.Close();
    GetDlgItem(ID_PUSK)->EnableWindow(TRUE);
 	GetDlgItem(ID_STOP)->EnableWindow(FALSE);

    m_ConfigDlg.GetDlgItem(IDC_RADIO)->EnableWindow(TRUE);
    m_ConfigDlg.GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE);
    m_ConfigDlg.GetDlgItem(IDC_RADIO_4HHz)->EnableWindow(TRUE);
    m_ConfigDlg.GetDlgItem(IDC_RADIO_11HHz)->EnableWindow(TRUE);

	m_ConfigDlg.UpdateData(TRUE);
	m_TerminalDlg.UpdateData(TRUE);
	m_TerminalDlg.SetDlgItemText(IDC_SYN,""); 

 if(m_ConfigDlg.m_Radio==0)
 {
	int i;
	CString str_id,str_freq;
	char buf_EOL[2]={13,10};
	// TODO: Add your control notification handler code here
    m_ConfigDlg.GetDlgItem(IDC_TXT_PATH)->EnableWindow(TRUE);
	m_ConfigDlg.GetDlgItem(IDC_ZANOS)->EnableWindow(TRUE);
    m_ConfigDlg.GetDlgItem(IDC_PATH)->EnableWindow(TRUE);
    SetDlgItemText(IDC_PAUSE,"ЖДИТЕ...");
	
    if(Mirag.WorkFlag[0]==TRUE) //сбрасываем все что можно в Mirage0 и закрываем поток
	{
    Mirag.WorkFlag[0]=FALSE;
	}
	CloseHandle(Mirag.m_hDevice[0]);

	for(i=0;i<65535;i++) 
	if(Ocean.Process.buf_freq[i]!=0)
	{   
		str_freq.Format("%5d",Ocean.Process.buf_freq[i]);;
		foutFREQ.WriteString(str_freq); // записываем код частоты
		if(m_ConfigDlg.m_Zanos==TRUE) ConvertCod_Freq(Ocean.Process.buf_freq[i]);
		foutFREQ.Write(buf_EOL,2);
	}
	
    for(i=0;i<Ocean.Process.ChisloID;i++)
	{
        str_id.Format("%s",Ocean.Process.bufID[i]);
		foutID.Write(str_id,str_id.GetLength());   // записываем идентификатор
		foutID.Write(buf_EOL,2);
	}

    foutFREQ.Close();
	foutID.Close();
 }

 if(m_ConfigDlg.m_Radio==1)
 {
	
	GetMenu()->EnableMenuItem(ID_FILE_FREQ,MF_ENABLED);
	m_ConfigDlg.GetDlgItem(IDC_SPEED)->EnableWindow(TRUE);
    m_ConfigDlg.GetDlgItem(IDC_SPEED2)->EnableWindow(TRUE);

    m_OtborDlg.GetDlgItem(IDC_IDEN_OTBOR)->EnableWindow(TRUE);
	m_OtborDlg.GetDlgItem(IDC_COD_OTBOR)->EnableWindow(TRUE);

	Com.AbonDlg->OnStop();
	CloseHandle(Com.AbonDlg->Mirag.m_hDevice[1]);
	Com.AbonDlg->Ocean.Num_kan=3;
	Com.AbonDlg->Ocean2.Num_kan=3;
	Com.AbonDlg->NumFile=0;
	m_TerminalDlg.SetDlgItemText(IDC_VKL,"");
	Ocean.Process.finFREQ.Close();

	if(Mirag.WorkFlag[0]==TRUE) //сбрасываем все что можно в Mirage0 и закрываем поток
	{
    Mirag.WorkFlag[0]=FALSE;
	}
	CloseHandle(Mirag.m_hDevice[0]);

	for(int i=0;i<2;i++)  //сбрасываем все что можно в COM и закрываем их потоки 
	{
     if(Com.ComFlag[i]==TRUE)
	 {
     Com.WorkFlag[i]=FALSE;
   	 Com.ComFlag[i]=FALSE;
	 CloseHandle(Com.osRead[i].hEvent); CloseHandle(Com.osWrite[i].hEvent);
	 CloseHandle(Com.hCom[i]);
	 }
	}
	Ocean.Process.ObsluvFlag=0;
 }

	SetDlgItemText(IDC_PAUSE," ");
    memset(Ocean.Process.buf_id,0,8);
    memset(Ocean.Process.buf_kod[0],0,6);
    memset(Ocean.Process.buf_kod[1],0,6);
	Ocean.Process.strFREQ[0]="";
	Ocean.Process.strFREQ[1]="";

}


void CVSAT_TESDlg::zagruzka_cod()
{
	CString str;
		   
    
    for(int i=0;i<65535;i++) Ocean.Process.buf_freq[i]=0;

	if(m_ConfigDlg.m_Radio==1)
	{
     while(foutCodOtb.ReadString(str))
	 {
	  Ocean.Process.buf_freq[atoi(str)]=atoi(str);
	 }
	}
    else 
	{
     while(foutFREQ.ReadString(str))
	 {
     Ocean.Process.buf_freq[atoi(str)]=atoi(str);
	 }
	}
}

void CVSAT_TESDlg::zagruzka_iden()
{
    CString str;

    Ocean.Process.ChisloID=0;

	if(m_ConfigDlg.m_Radio==1)
	{
     while(foutIdenOtb.ReadString(str))
	 {
	  str.TrimRight();
	  memcpy(Ocean.Process.bufID[Ocean.Process.ChisloID],str,str.GetLength());
	  Ocean.Process.ChisloID++;
	 }
	}
    else 
	{
     while(foutID.ReadString(str))
	 {
      str.TrimRight();
	  strncpy(Ocean.Process.bufID[Ocean.Process.ChisloID],str,str.GetLength());
	  Ocean.Process.ChisloID++;
	 }
	}

}

      //функция вычисления значения частоты для кода Kod
void CVSAT_TESDlg::ConvertCod_Freq(unsigned short Kod)
{
  static int k=0;
  CString FFF;
  static double Freq;
  if(k==2) k=0;
  m_ConfigDlg.UpdateData(TRUE);

  if(m_ConfigDlg.m_Cod!="")
  {
	  k++;
      if(k==1) 
	  {
		  if(atoi(m_ConfigDlg.m_Cod)>=Kod) 
		  {                                  //  диапазон 4 ГГц
		   if(m_ConfigDlg.m_Radio4Hhz==1) 
		   {         
                Freq=atof(m_ConfigDlg.m_Freq)-abs(Kod-atoi(m_ConfigDlg.m_Cod))/(2*Ocean.Process.d_kod)
	         	     *2*atof(m_ConfigDlg.m_Step);
		   }
		   if(m_ConfigDlg.m_Radio4Hhz==0)     //  диапазон 11 ГГц
		   {            
			
				Freq=atof(m_ConfigDlg.m_Freq)+abs(Kod-atoi(m_ConfigDlg.m_Cod))/(2*Ocean.Process.d_kod)
		             *2*atof(m_ConfigDlg.m_Step);
		   }
		  }
    	  else 
		  {
		   if(m_ConfigDlg.m_Radio4Hhz==1) 
		   {            
				Freq=atof(m_ConfigDlg.m_Freq)+abs(Kod-atoi(m_ConfigDlg.m_Cod))/(2*Ocean.Process.d_kod)
		             *2*atof(m_ConfigDlg.m_Step);
		   }
           if(m_ConfigDlg.m_Radio4Hhz==0)
		   {
                Freq=atof(m_ConfigDlg.m_Freq)-abs(Kod-atoi(m_ConfigDlg.m_Cod))/(2*Ocean.Process.d_kod)
		             *2*atof(m_ConfigDlg.m_Step);
		   }
		  }
	  }
	  if(k==2) 
	  {
		if(m_ConfigDlg.m_Radio4Hhz==1)  Freq=Freq+atof(m_ConfigDlg.m_Step); 
		if(m_ConfigDlg.m_Radio4Hhz==0)  Freq=Freq-atof(m_ConfigDlg.m_Step);
	  }
      FFF.Format("%15.3f",Freq); 
	  foutFREQ.WriteString(" ");
	  foutFREQ.WriteString(FFF);
  }
}

void CVSAT_TESDlg::Ustan_Razw()
{
	m_ConfigDlg.UpdateData(FALSE);
	m_ConfigDlg.UpdateData(TRUE);
	CString FileName;
    if(m_TargetDirTemp=="") m_TargetDirTemp="C:";
	FileName=m_TargetDirTemp+"\\freq.txt";
	if(foutFREQ.Open(FileName,CFile::modeRead|CFile::typeBinary)) 
		{
	     zagruzka_cod(); // загружаем из файла в память коды частот и частоты(если есть)
	     if(m_ConfigDlg.m_Zanos==TRUE)
		 {
		  m_ConfigDlg.GetDlgItem(IDC_COD)->EnableWindow(TRUE);
		  m_ConfigDlg.GetDlgItem(IDC_FREQ)->EnableWindow(TRUE);
		  m_ConfigDlg.GetDlgItem(IDC_STEP)->EnableWindow(TRUE);
		 }
		 else m_ConfigDlg.GetDlgItem(IDC_ZANOS)->EnableWindow(FALSE);
	     foutFREQ.Close();
		}
	    

    foutFREQ.Open(m_TargetDirTemp+"\\freq.txt",CFile::modeCreate|CFile::modeWrite|CFile::typeBinary);

		 Ocean.Process.ChisloID=0;
	     if(foutID.Open(m_TargetDirTemp+"\\identif.txt",CFile::modeRead|CFile::typeBinary))
		 {
         zagruzka_iden();
	     foutID.Close();
		 }
foutID.Open(m_TargetDirTemp+"\\identif.txt",CFile::modeCreate|CFile::modeWrite|CFile::typeBinary);
}


void CVSAT_TESDlg::Ustan_Priem()
{
     CString Text,
		    Numer,
			strEOL; 
	int i;
    strEOL.Format("\r\n");                       
	if(m_OtborDlg.m_Cod_Otbor==TRUE)             //файл отбора по кодам частот
	{
		foutCodOtb.Open(m_OtborDlg.m_FileCodOtb,CFile::modeRead);
		Ocean.Process.FlagOtbCod=TRUE;
		zagruzka_cod();
        foutCodOtb.Close();
	} else Ocean.Process.FlagOtbCod=FALSE;
    if(m_OtborDlg.m_Iden_Otbor==TRUE)             //файл отбора по идентификаторам
	{
		foutIdenOtb.Open(m_OtborDlg.m_FileIdenOtb,CFile::modeRead);
		Ocean.Process.FlagOtbIden=TRUE;
		zagruzka_iden();
		foutIdenOtb.Close();
	} else Ocean.Process.FlagOtbIden=FALSE;

    m_OtborDlg.GetDlgItem(IDC_IDEN_OTBOR)->EnableWindow(FALSE);
	m_OtborDlg.GetDlgItem(IDC_COD_OTBOR)->EnableWindow(FALSE);


	m_ConfigDlg.SetDlgItemText(IDC_PATH," "+m_TargetDirSave);

	Com.AbonDlg->m_TargetDir=m_TargetDirSave;
   	if(m_ConfigDlg.m_Chek_Del) 	Com.AbonDlg->MinSizeFile=m_ConfigDlg.m_MinSize.GetPos(); 
	               else (Com.AbonDlg->MinSizeFile)=0;
    if(m_ConfigDlg.m_Chek_Max) (Com.AbonDlg->MaxSizeFile)=m_ConfigDlg.m_MaxSize.GetPos(); 
                   else (Com.AbonDlg->MaxSizeFile)=0;

 for(int i=0;i<2;i++)
 {
	 if(Com.Proverka(i));
	 else
	 {
		 Text="                                            НЕТ СВЯЗИ С СОМ";
         Numer.Format("%d",i+1);
		 Text+=Numer;
		 Text+=" !!!\r\nНет физического соединения или неправильно установлены параметры обмена.";
		 MessageBox(Text,"Сообщение",MB_ICONERROR);
	 }
	 
 }

 if((Com.ComFlag[0]==FALSE)&&(Com.ComFlag[1]==FALSE)) 
 {
	 OnStop();
     return;
 }

 for(int i=0;i<2;i++)
 {
	 if(Com.ComFlag[i]==TRUE) 
	 {
		 if(!Com.Create(i))
		 {
		  Text="Не могу открыть драйвер СОМ";
          Numer.Format("%d",i+1);
		  Text+=Numer;
			 MessageBox(Text,NULL,MB_ICONERROR) ;
			 exit(0);
		 }
	 }
 }

 m_InitComDlg=new CInitComDlg;
 m_InitComDlg->Create(CInitComDlg::IDD);

                 // инициализация модемов
 for(i=0;i<2;i++)
 {
	 if(Com.ComFlag[i]) 
	 {
	 Text="Инициализация МОДЕМА ";
     Numer.Format("%d",i+1);
	 Text="     ЖДИТЕ...\r\n"+Text+Numer;
     m_InitComDlg->SetDlgItemText(IDC_TXT,Text);
  
         m_InitComDlg->m_Progress.SetPos(0);
		 Com.WriteCommBlock("EE 0\r\n",i);  // отключаем Эхо модемов
         m_InitComDlg->m_Progress.StepIt();
		 Com.WriteCommBlock("EST 1\r\n",i); //питание
		 m_InitComDlg->m_Progress.StepIt();
		 if(m_ConfigDlg.m_Radio4Hhz==1) 
			 Com.WriteCommBlock("DI 0\r\n",i);  // отключение инверсии спектра
		 else Com.WriteCommBlock("DI 1\r\n",i);  // включение инверсии спектра
		 m_InitComDlg->m_Progress.StepIt();
		 Com.WriteCommBlock("RC 0\r\n",i);  // отключение кодера
		 m_InitComDlg->m_Progress.StepIt();
		 Com.WriteCommBlock("RM 1\r\n",i);  // вид модуляции (QPSK)
		 m_InitComDlg->m_Progress.StepIt();
		 Com.WriteCommBlock("DD 0\r\n",i);  //отключение дифдекодера
		 m_InitComDlg->m_Progress.StepIt();
		 Com.WriteCommBlock("AQ 1\r\n",i);  //NORMAL
		 m_InitComDlg->m_Progress.StepIt();
		 Com.WriteCommBlock("AR 5000\r\n",i); // подстройка +(-) 5 кГц
		 m_InitComDlg->m_Progress.StepIt();
		 Com.WriteCommBlock("SD 0\r\n",i);  // отключаем скремблер
		 m_InitComDlg->m_Progress.StepIt();
		 Com.WriteCommBlock("DFS 0\r\n",i); // фильтр COMSTREAM
		 m_InitComDlg->m_Progress.StepIt();
		 Text="RR "+m_ConfigDlg.m_Speed+strEOL;	 
		 m_InitComDlg->m_Progress.StepIt();
		 m_InitComDlg->m_Progress.StepIt();
		 Com.WriteCommBlock(Text,i); // символьная скорость в абонентских каналах
	 }
 }

m_InitComDlg->EndDialog(0);
m_InitComDlg->DestroyWindow();
delete [] m_InitComDlg;

SetDlgItemText(IDC_PAUSE," ");
    
}


LRESULT CVSAT_TESDlg::OnMesCount2(WPARAM def, LPARAM Block ) 
{
	BYTE*buf;
	int len_block,i;
    static BOOL SynFlag=FALSE;
 
 if(flWork==TRUE)
  { 
	len_block=def;
	buf=new BYTE[len_block];
    Ocean.buf_out=new BYTE[len_block];
    Ocean.buf_temp=new BYTE[len_block];
    Ocean.buf_deper=new BYTE[len_block];
    Ocean.buf_dec=new BYTE[len_block];
    Ocean.buf_dif=new BYTE[len_block>>1];
    Ocean.buf_dskr=new BYTE[len_block>>1];

	Mirag.GetBlock(buf,len_block,0);
    //Ocean.fout.Write(buf,len_block);
   
 if(SynFlag==FALSE)
 {
	    for(i=0;i<48;i++) 
		if((Ocean.massiv[i]=new BYTE[LENG_SHAB])==NULL) 
		{
    	  ::MessageBox(NULL,"Не хватает памяти!!!",NULL,MB_OK|MB_ICONERROR);
		    exit(0);
			return 0;
		}
	
		
		
    if(Ocean.synchro_search(buf,len_block)==TRUE)
	{
		if(m_ConfigDlg.m_Radio==0)
		{
	   	  Ocean.Process.NEW1="";
		  Ocean.Process.NEW2="";
		  Ocean.Process.NEW3="";
		  Ocean.Process.NEW4="";
		}else
        if(m_ConfigDlg.m_Radio==1)
		{
          Ocean.Process.strFREQ[0]="          ";
		  Ocean.Process.strFREQ[1]="          ";
		}
          for(i=0;i<48;i++) delete [] Ocean.massiv[i];
		  m_TerminalDlg.m_ColorSinOcc=RGB(0,128,32);;
          m_TerminalDlg.SetDlgItemText(IDC_SYN,"Есть"); 
          SynFlag=TRUE;	
          if(Ocean.Obrabotka(buf,len_block)==TRUE) 
		  {
			if(m_ConfigDlg.m_Radio==0)
			{
			  	
			  m_TerminalDlg.SetDlgItemText(IDC_ID_CALL,Ocean.Process.buf_id);
			  m_TerminalDlg.SetDlgItemText(IDC_ID_ANSWER,Ocean.Process.buf_id2);
			  m_TerminalDlg.SetDlgItemText(IDC_FREQ_C,Ocean.Process.buf_kod[0]);
			  m_TerminalDlg.SetDlgItemText(IDC_FREQ_A,Ocean.Process.buf_kod[1]);
              m_TerminalDlg.SetDlgItemInt(IDC_ISDONE, Ocean.Process.Vkl_Done,TRUE);
			  m_TerminalDlg.SetDlgItemText(ID_CALL_NEW,Ocean.Process.NEW1);
			  m_TerminalDlg.SetDlgItemText(ID_ANSWER_NEW,Ocean.Process.NEW4);
			  m_TerminalDlg.SetDlgItemText(IDC_FREQ_Cnew,Ocean.Process.NEW2);
			  m_TerminalDlg.SetDlgItemText(IDC_FREQ_Anew,Ocean.Process.NEW3);
			}
			else
			{
			  m_TerminalDlg.SetDlgItemInt(IDC_ISDONE, Ocean.Process.Vkl_Done);
	          m_TerminalDlg.SetDlgItemText(IDC_ID_CALL,Ocean.Process.buf_id);
			  m_TerminalDlg.SetDlgItemText(IDC_ID_ANSWER,Ocean.Process.buf_id2);
			  m_TerminalDlg.SetDlgItemText(IDC_FREQ_C,Ocean.Process.buf_kod[0]);
			  m_TerminalDlg.SetDlgItemText(IDC_FREQ_A,Ocean.Process.buf_kod[1]);
			  m_TerminalDlg.SetDlgItemText(ID_CALL_NEW,"");
			  m_TerminalDlg.SetDlgItemText(ID_ANSWER_NEW,"Частота, кГц:");
              m_TerminalDlg.SetDlgItemText(IDC_FREQ_Cnew,Ocean.Process.strFREQ[0]);
			  m_TerminalDlg.SetDlgItemText(IDC_FREQ_Anew,Ocean.Process.strFREQ[1]);

			}
		  }
		  else 
		  {
		    if(m_ConfigDlg.m_Radio==1)
            if(Com.AbonDlg->SynFlag==1)
			{
	        OnStop();
            MessageBox("Сбой синхронизации в канале OCC\r\n.Необходим перезапуск",
                       NULL,MB_ICONERROR);
			}
			  m_TerminalDlg.SetDlgItemText(IDC_SYN,"Нет");
			  m_TerminalDlg.m_ColorSinOcc=RGB(128,32,0);
				
		  }		 
	} 

       else
	   {  
          Ocean.Process.firstFlag=0;
          memset(Ocean.Process.buf_id,0,6);
		  memset(Ocean.Process.buf_kod[0],0,6);
          memset(Ocean.Process.buf_kod[1],0,6);
		  for(i=0;i<48;i++) delete [] Ocean.massiv[i];
		  m_TerminalDlg.m_ColorSinOcc=RGB(128,32,0);;
          m_TerminalDlg.SetDlgItemText(IDC_SYN,"Нет"); 
	   }
 }
	 else
	 {
		  
		 if(Ocean.Obrabotka(buf,len_block)==TRUE)
		 {
			 m_TerminalDlg.m_ColorSinOcc=RGB(0,128,32);;
			 m_TerminalDlg.SetDlgItemText(IDC_SYN,"Есть");
		    if(m_ConfigDlg.m_Radio==0)
			{
			 m_TerminalDlg.SetDlgItemText(IDC_ID_CALL,Ocean.Process.buf_id);
			 m_TerminalDlg.SetDlgItemText(IDC_ID_ANSWER,Ocean.Process.buf_id2);
			 m_TerminalDlg.SetDlgItemText(IDC_FREQ_C,Ocean.Process.buf_kod[0]);
			 m_TerminalDlg.SetDlgItemText(IDC_FREQ_A,Ocean.Process.buf_kod[1]);
			 m_TerminalDlg.SetDlgItemInt (IDC_ISDONE, Ocean.Process.Vkl_Done,TRUE);   
           	 m_TerminalDlg.SetDlgItemText(ID_CALL_NEW,Ocean.Process.NEW1);
			 m_TerminalDlg.SetDlgItemText(ID_ANSWER_NEW,Ocean.Process.NEW4);
			 m_TerminalDlg.SetDlgItemText(IDC_FREQ_Cnew,Ocean.Process.NEW2);
			 m_TerminalDlg.SetDlgItemText(IDC_FREQ_Anew,Ocean.Process.NEW3);
			}
			else
			{
           	  m_TerminalDlg.SetDlgItemInt(IDC_ISDONE, Ocean.Process.Vkl_Done,TRUE);
	          m_TerminalDlg.SetDlgItemText(IDC_ID_CALL,Ocean.Process.buf_id);
			  m_TerminalDlg.SetDlgItemText(IDC_ID_ANSWER,Ocean.Process.buf_id2);
			  m_TerminalDlg.SetDlgItemText(IDC_FREQ_C,Ocean.Process.buf_kod[0]);
			  m_TerminalDlg.SetDlgItemText(IDC_FREQ_A,Ocean.Process.buf_kod[1]);
			  m_TerminalDlg.SetDlgItemText(ID_CALL_NEW,"");
			  m_TerminalDlg.SetDlgItemText(ID_ANSWER_NEW,"Частота, кГц:");
              m_TerminalDlg.SetDlgItemText(IDC_FREQ_Cnew,Ocean.Process.strFREQ[0]);
			  m_TerminalDlg.SetDlgItemText(IDC_FREQ_Anew,Ocean.Process.strFREQ[1]);
			  Com.AbonDlg->FileNameA.Format("%s",Ocean.Process.buf_id2);

			}
		  }
		  else 
		  {
            if(m_ConfigDlg.m_Radio==1)
            if(Com.AbonDlg->SynFlag==1)
			{
	        OnStop();
            MessageBox("Сбой синхронизации в канале OCC\r\n.Необходим перезапуск",
                       NULL,MB_ICONERROR);
			}
		    SynFlag=FALSE;
			m_TerminalDlg.m_ColorSinOcc=RGB(128,32,0);;
			m_TerminalDlg.SetDlgItemText(IDC_SYN,"Нет");
          } 	  
	 }
      delete [] Ocean.buf_out;
      delete [] Ocean.buf_temp;
      delete [] Ocean.buf_deper;
      delete [] Ocean.buf_dec;
      delete [] Ocean.buf_dif;
      delete [] Ocean.buf_dskr;
      delete [] buf;
  }
return 0; 
}

LRESULT CVSAT_TESDlg::OnMesVkl(WPARAM Num,LPARAM Vkl) // функция обработки сообщения о прохождении
{                                                 // пакета назначения частот
 CString strEOL,strRS,strFREQ[2],strTemp;
 
 strRS.Format("RS ");
 strEOL.Format("\r\n");

              m_TerminalDlg.m_ColorIden=RGB(32,32,128);

		/*	  m_TerminalDlg.SetDlgItemInt(IDC_ISDONE, Ocean.Process.Vkl_Done,TRUE);
	          m_TerminalDlg.SetDlgItemText(IDC_ID_CALL,Ocean.Process.buf_id);
			  m_TerminalDlg.SetDlgItemText(IDC_FREQ_C,Ocean.Process.buf_kod[0]);
			  m_TerminalDlg.SetDlgItemText(IDC_FREQ_A,Ocean.Process.buf_kod[1]);
			  m_TerminalDlg.SetDlgItemText(ID_CALL_NEW,"Частота, кГц:");
              m_TerminalDlg.SetDlgItemText(IDC_FREQ_Cnew,Ocean.Process.strFREQ[0]);
			  m_TerminalDlg.SetDlgItemText(IDC_FREQ_Anew,Ocean.Process.strFREQ[1]);*/

			  // Задаем частоты для настройки

 strFREQ[0].Format("%d",atoi(Ocean.Process.strFREQ[0]));
 strTemp.Format("%s",strpbrk(Ocean.Process.strFREQ[0],".")+1);
 strFREQ[0]=strFREQ[0]+strTemp;
 strFREQ[0]=strRS+strFREQ[0]+strEOL;
 Com.strFREQ[0]=strFREQ[0];              

 strFREQ[1].Format("%d",atoi(Ocean.Process.strFREQ[1]));
 strTemp.Format("%s",strpbrk(Ocean.Process.strFREQ[1],".")+1);
 strFREQ[1]=strFREQ[1]+strTemp;
 strFREQ[1]=strRS+strFREQ[1]+strEOL;
 Com.strFREQ[1]=strFREQ[1];

 Com.AbonDlg->FileNameC.Format("%s",Ocean.Process.buf_id); // имя файла для абонентов

 m_TerminalDlg.SetDlgItemText(IDC_VKL,"Включение...");

 /*for(int i=0;i<2;i++)
 {	 
   if(Com.ComFlag[i]) Com.WriteCommBlock(strFREQ[i],i);
 } */
  
 if(Com.OpenThreadSyn(strFREQ[0],0)) return 1;
 else 
	{
    ::MessageBox(NULL,"Не могу открыть поток для Synchro!!!",NULL,MB_OK);
      exit(0);
	}
}

LPARAM CVSAT_TESDlg::OnMesOtkl(WPARAM rr,LPARAM Vkl) // функция обработки сообщения о прохождении
{                                               // пакета выключения


 // дело в том,что эту функцию могут использовать одновременно 
 //два потока (канала управления и абонентских каналов)
 // поэтому необходимо синхронизировать потоки
::WaitForSingleObject
  (HMutex,
  INFINITE);

if(Ocean.Process.ObsluvFlag==0) return 1; // возвращаемся если здесь уже
                                        // был какой-нибудь поток 

 Mirag.hTHR[0]->SuspendThread();  // приостанавливаем поток ОСС

 m_TerminalDlg.SetDlgItemText(IDC_VKL,"Выключение...");
 m_TerminalDlg.SetDlgItemText(IDC_VKL,"Ожидание...");
 Com.AbonDlg->OnStop();
 m_ConfigDlg.m_NumSeans.Format("%d",Com.AbonDlg->m_FilesDone);
 m_ConfigDlg.UpdateData(FALSE);
 m_ConfigDlg.UpdateData(TRUE);
 for(int i=0;i<2;i++)
 if(Com.ComFlag[i])
  {
    Com.WorkFlag[i]=FALSE; 

  }
 Ocean.Process.ObsluvFlag=0;

 Mirag.hTHR[0]->ResumeThread(); // повторный запуск потока ОСС
 ::ReleaseMutex(HMutex); //устанавливаем мьютекс  в свободное состояние
return 0;
}

void CVSAT_TESDlg::OnCancel()
{
	SendMessage(WM_SYSCOMMAND,SC_ICON);
	return;
}



void CVSAT_TESDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(1);
	if(flWork==TRUE) OnStop();
	EndDialog(0);
	Com.AbonDlg->DestroyWindow();
	m_ConfigDlg.UpdateData(TRUE);
	m_TerminalDlg.DestroyWindow();
	m_OtborDlg.DestroyWindow();
	m_ConfigDlg.DestroyWindow();
	CDialog::OnClose();
	return;
}

void CVSAT_TESDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
  m_ConfigDlg.UpdateData(TRUE);
  if(m_ConfigDlg.m_Radio==1) 
  {
    SendMessage(MES_SHOW_DISK,0,0);
  }
  CDialog::OnTimer(nIDEvent); 
}

void CVSAT_TESDlg::OnDirOpen() 
{
	// TODO: Add your command handler code here
	m_ConfigDlg.UpdateData(TRUE);
	CDirOpenDialog DirDlg;
	if (DirDlg.DoModal()==IDOK){
	if(m_ConfigDlg.m_Radio==0)
		m_TargetDirTemp=DirDlg.GetPath();
	else if(m_ConfigDlg.m_Radio==1) 
	{
		m_TargetDirSave=DirDlg.GetPath();
	    m_ConfigDlg.SetDlgItemText(IDC_PATH," "+m_TargetDirSave);
		if(flWork==TRUE)
		{
			Com.AbonDlg->m_TargetDir=m_TargetDirSave;
		}
	}
	}
	return;
}

void CVSAT_TESDlg::OnFileFreq() 
{
	// TODO: Add your command handler code here
   CFileDialog fdd(TRUE,NULL,NULL,OFN_HIDEREADONLY,
					"Текстовые файлы (*.txt)|*.txt|All Files (*.*)|*.*||",NULL);

   if(fdd.DoModal()==IDOK)
   {
    m_FileFreqName=fdd.GetPathName();

   }
   else
   {
    MessageBox("Выберите файл с кодами частот","Сообщение",MB_ICONERROR);
	m_FileFreqName="";
	return;
   } 
return;	
}

LRESULT CVSAT_TESDlg::OnShowDisk(WPARAM wParam, LPARAM lParam) //функция определения
{                                                           //своб.места на диске
	CString RootStr;
	ULARGE_INTEGER Stab;
	ULARGE_INTEGER Stab1;
	ULARGE_INTEGER Total;
	DWORD Volume;
	
	if(GetDiskFreeSpaceEx(LPCSTR(m_TargetDirSave),&Stab,&Stab1,&Total)){
	Volume=(ULONG(Total.LowPart)>>10)|(Total.HighPart<<22);	
		RootStr.Format("%d K",Volume);

		if(Volume>3000)
		{
		  m_ConfigDlg.m_ColorFreeDisk=RGB(32,128,64)	;
		}
		else m_ConfigDlg.m_ColorFreeDisk=RGB(128,32,0)	;
		m_ConfigDlg.SetDlgItemText(IDC_FreeDisk,LPCSTR(RootStr));
		if(Volume<1000) 
		{
			OnStop();
			MessageBox("Нет места на диске",NULL,MB_ICONERROR);
		}
	}else{
		RootStr="";
		m_ConfigDlg.SetDlgItemText(IDC_FreeDisk,LPCSTR(RootStr));
	}
	return 0;
}
