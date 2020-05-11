// HDLC.cpp: implementation of the CHDLC class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VSAT_TES.h"
#include "HDLC.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CVSAT_TESApp theApp;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHDLC::CHDLC()
{
 strFREQ[0]=""; strFREQ[1]="";
 Vkl_Done=0; 
 int i;
 ChisloID=0;
 for(i=0;i<65535;i++) buf_freq[i]=0;
 for(i=0;i<1000;i++) memset(bufID[i],0,6);
// for(i=0;i<65535;i++) buf_id1[i]=0;
 memset(buf_id,0,6);
 memset(buf_id2,0,6);
 memset(buf_kod[0],0,6);
 memset(buf_kod[1],0,6);
 ObsluvFlag=0;
}

CHDLC::~CHDLC()
{
 ObsluvFlag=0;
 int i;
 Vkl_Done=0; 
 ChisloID=0;
 for(i=0;i<65535;i++) buf_freq[i]=0;
 for(i=0;i<1000;i++) memset(bufID[i],0,6);
 memset(buf_id,0,6);
 memset(buf_id2,0,6);
 memset(buf_kod[0],0,6);
 memset(buf_kod[1],0,6);
}

void CHDLC::FirstFlag(BYTE*buf_inp,int lenb)
{  
   static unsigned short int kod1,kod2;
   static UINT iden;
   int i,j,k;
   static BYTE
	      freq_kod[2][2],
	      NN,ed_5,l,sum_ed,
	      flag=0,
		  buf_name[4],buf_name2[4],
		  buf_EOL[2]={13,10},
		  buf_save[3000];  

 if(firstFlag) i=0;
 if(!firstFlag)
 {
	 NN=0;
	 l=0;
	 sum_ed=0;
	 flag=0;
  for(i=0;i<lenb;i++)
  {
    for(j=0;j<8;j++)
	{
	(buf_inp[i]&(1<<j))?(reg=((reg>>1)|0x80)):(reg>>=1);

	  if(reg==0x7E) 
	  {
       	firstFlag=1;
		for(reg=0;j<8;j++)
		{
         (buf_inp[i]&(1<<j))?(reg=(reg>>1)|0x80):(reg>>=1);
		 if(reg&0x80) sum_ed++; else sum_ed=0;
		 ++NN;
		}
		i++;
	    break;
	  }
	}
  if(firstFlag) break;
   }
 }

    for(;i<lenb;i++)
    for(j=0;j<8;j++)
    { 
	 (buf_inp[i]&(1<<j))?(reg=(reg>>1)|0x80):(reg>>=1);
       
     if(flag) 
	 {
         reg=0; flag=0; 

    if(!FlagZes)              // определяем идентификатор ЦЗС
		if(l==106)
		  if(buf_save[0]==0xFD) // Запомни что первый байт в пакете имени ЦЗС 
		  {                     // должен в 16-ой системе иметь значение FD
           FlagZes=TRUE;
		   for(int n=87;n<103;n++)   // с 88-го по 103 байты содержится имя ЦЗС(105 и 106 - проверка CRC)
           theApp.dlg->m_TerminalDlg.m_Zes+=buf_save[n];
		   theApp.dlg->m_TerminalDlg.UpdateData(FALSE);
		  } 

  if(ObsluvFlag!=1)
  {
   if((l>20)&&(l<40))
   if((buf_save[4]==0x40)&&(buf_save[5]==0x00)&&(buf_save[6]==0x19))
   {
                             
                Vkl_Done++;
 	            memset(buf_id,0,6);
				memset(buf_id2,0,6);
				memset(buf_kod[0],0,6);
                memset(buf_kod[1],0,6);
				NEW4.Format("%s","      ");

		   // Определяем идентификатор вызывающего терминала

			  iden=0;
              for(k=0;k<3;k++) buf_name[k]=buf_save[k]; 
			  for(k=0;k<3;k++) iden=((buf_name[k]<<(8*k))|iden);
			  ltoa(iden,buf_id,16);  

		      for(k=0;k<3;k++) buf_name2[k]=0x00;              

		  // Определяем коды частот приемника и передатчика

			      freq_kod[0][0]=buf_save[15];
				  freq_kod[0][1]=buf_save[16];
				  kod1=freq_kod[0][1];
				  kod1=freq_kod[0][0]|(kod1<<8);   // код частоты приемника
				  itoa(kod1,buf_kod[0],10);  

				  freq_kod[1][0]=buf_save[17];
				  freq_kod[1][1]=buf_save[18];
                  kod2=freq_kod[1][1];
				  kod2=freq_kod[1][0]|(kod2<<8);   //код частоты передатчика
				  itoa(kod2,buf_kod[1],10);  

				  d_kod=kod2-kod1;  //интервал кода в паре 
   if(Radio==0)
   {
	          ObsluvFlag=1;
	          for(k=0;k<ChisloID;k++)
			  {
                   if(memcmp(bufID[k],buf_id,strlen(buf_id))==0) break;
			  }
			  if((k==ChisloID)) 
			  {
               NEW1.Format("%s","NEW !!!");                      //новый идентификатор   
			   memcpy(bufID[ChisloID],buf_id,strlen(buf_id));
			   ChisloID++;
			  }
			  else NEW1.Format("%s","      ");

			  if(buf_freq[kod1]==0) NEW2.Format("%s","NEW !!!"); //новая частота
			  else NEW2.Format("%s","      ");
			  buf_freq[kod1]=kod1;

              if(buf_freq[kod2]==0) NEW3.Format("%s","NEW !!!"); //новая частота
			  else NEW3.Format("%s","      ");
			  buf_freq[kod2]=kod2;              
   }		       

  if(Radio==1)
  {
   char buf[100];
   CString strKod;

   ObsluvFlag=1;   // заявка на обслуживание абонентов
   WPARAM rr=2;
   LPARAM nn=0;

      // Определяем вид кодирования (12 байт в пакете назначения частот)		
            if(buf_save[11]==0x02){
				
				theApp.dlg->Com.AbonDlg->Flag3_4=TRUE;                   // НСК 3/4
				theApp.dlg->Com.AbonDlg->Flag1_2=FALSE; 
			}
			else {
				theApp.dlg->Com.AbonDlg->Flag1_2=TRUE;                   // НСК 1/2
				theApp.dlg->Com.AbonDlg->Flag3_4=FALSE;
			}

	// Определяем вид модуляции (13 байт в пакете назначения частот)		
			if(buf_save[12]==0x00) {
				theApp.dlg->Com.FlagQPSK=TRUE;    // QPSK
				theApp.dlg->Com.FlagBPSK=FALSE;
			}
			else {
			    theApp.dlg->Com.FlagBPSK=TRUE;    // BPSK
				theApp.dlg->Com.FlagQPSK=FALSE;
			}

    // Определяем скорость (14 байт в пакете назначения частот)
			if(buf_save[13]==0x04) {
				theApp.dlg->Com.AbonDlg->Ocean.FlagG728=TRUE;
				theApp.dlg->Com.AbonDlg->Ocean.FlagG726=FALSE;
			}
			else 
			if(buf_save[13]=0x05)
			{
			    theApp.dlg->Com.AbonDlg->Ocean.FlagG728=FALSE;
				theApp.dlg->Com.AbonDlg->Ocean.FlagG726=TRUE;
			}
			else
			{
                theApp.dlg->Com.AbonDlg->Ocean.FlagG728=FALSE;
				theApp.dlg->Com.AbonDlg->Ocean.FlagG726=FALSE;
			}


   finFREQ.SeekToBegin();//на начало файла
    while(finFREQ.ReadString(buf,100))
	{
	   strKod.Format("%d",atoi(buf));
	   if(strcmp(strKod,buf_kod[0])==0) 
	   {
		   
         strFREQ[0].Format("%.3f",atof(strstr(buf,strKod)
			                        +strKod.GetLength())); //хитрый способ считывания 
       	                                                   // номинала чатсоты
		 rr=0;              //на СОМ1
//		 SendMessage(inhWnd,MES_VKL,rr,nn); // формируем сообщение о включении для диалогового окна

		 finFREQ.ReadString(buf,100);           // считываем следующую строку
		 strKod.Format("%d",atoi(buf));         //считываем код частоты
         strFREQ[1].Format("%.3f",atof(strstr(buf,strKod)+strKod.GetLength())); //получаем номинал частоты
		 rr=1;              //на СОМ2

		 FlagOtb=0;

		 if((FlagOtbIden==TRUE)||(FlagOtbCod==TRUE)) //если задан отбор приема
		 {
			 if(FlagOtbIden==TRUE)
			 {
			  for(k=0;k<ChisloID;k++)
			  {
                   if(memcmp(bufID[k],buf_id,strlen(buf_id))==0) 
				   {
                   FlagOtb=1;
                   SendMessage(inhWnd,MES_VKL,rr,nn); // формируем сообщение о включении для диалогового окна
				   break;
				   }
		 	  }
			  if(FlagOtb==1) break;
			 }
			 if(FlagOtbCod==TRUE)
			 {
			     if(buf_freq[kod1]==kod1)
				 {
                   FlagOtb=1;
                   SendMessage(inhWnd,MES_VKL,rr,nn); // формируем сообщение о включении для диалогового окна
				   break;
				 }
			  if(FlagOtb==1) break;
			 }
		 }
		 else                   //если отбора нет
			 SendMessage(inhWnd,MES_VKL,rr,nn); // формируем сообщение о включении для диалогового окна
		 break; 
	   }
	   else { strFREQ[0]=" "; strFREQ[1]=" "; }
	}
   if(rr==2) ObsluvFlag=0;
  }
	
		}
      }
	 else 
      if(ObsluvFlag==1)
	  {
		   if((l>10)&&(l<20))
		   {
			  if((buf_save[4]==0x40)&&(buf_save[5]==0x00)) // пакет отключения частот
		      if(((buf_save[0]==buf_name[0])&&(buf_save[1]==buf_name[1])
					 &&(buf_save[2]==buf_name[2]))||
					 		      ((buf_save[0]==buf_name2[0])&&(buf_save[1]==buf_name2[1])
			                		 &&(buf_save[2]==buf_name2[2])))   
			  {
					if(Radio==1) SendMessage(inhWnd,MES_OTKL,0,0);
					if(Radio==0) ObsluvFlag=0;
			  }
		   }
		  else
		  if((l>20)&&(l<50))
		  {
		   if((buf_save[4]==0x40)&&(buf_save[5]==0x00)&& // возможно пакет назначения 
			  (buf_save[6]==0x1A))
                                                         // отвечающему терминалу
		   {
            	  freq_kod[0][0]=buf_save[15];
				  freq_kod[0][1]=buf_save[16];
		      if((freq_kod[0][0]|(freq_kod[0][1]<<8))==kod1)
			  {
                   iden=0;
                   for(k=0;k<3;k++) buf_name2[k]=buf_save[k]; 
			       for(k=0;k<3;k++) iden=((buf_name2[k]<<(8*k))|iden);
			       ltoa(iden,buf_id2,16);  

                   if(Radio==1)
				   {
					 if(FlagOtbIden==TRUE)
					  if(FlagOtb==0)
			          for(k=0;k<ChisloID;k++)
					  {
                       if(memcmp(bufID[k],buf_id2,strlen(buf_id2))==0) 
					   {
                        FlagOtb=1;
                        SendMessage(inhWnd,MES_VKL,0,0); // формируем сообщение о включении для диалогового окна
				        break;
					   }
					  }
				   }

                   if(Radio==0)
				   {
			         for(k=0;k<ChisloID;k++)
					 {
                      if(memcmp(bufID[k],buf_id2,strlen(buf_id2))==0) break;
					 }

			         if((k==ChisloID)) 
					 {
                       NEW4.Format("%s","NEW !!!");                      //новый идентификатор   
			           memcpy(bufID[ChisloID],buf_id2,strlen(buf_id2));
			           ChisloID++;
					 }
			         else NEW4.Format("%s","      ");
					 ObsluvFlag=0;
				   }
			  }
			  else 
			  {
			  if(Radio==0) ObsluvFlag=0;
			  if(Radio==1) 
				if(FlagOtbIden==TRUE)
			      if(FlagOtb==0) ObsluvFlag=0;
			  }
		   }
    		  if(Radio==1) 
				if(FlagOtbIden==TRUE)
			      if(FlagOtb==0) ObsluvFlag=0;	  
			   if(Radio==0) ObsluvFlag=0;
		   
		  }

	  }

	       l=0; continue;
    }
		   
	   if(sum_ed==5)
	   {
		 if(reg&0x80) {flag=1; NN=0;} else reg<<=1;
	     sum_ed=0;
		 continue;
	   }

	   if(reg&0x80) sum_ed++; else sum_ed=0;
 	   ++NN;

	   if(NN==8)
		  if(!flag)
		  {
			   buf_save[l]=reg;
			   l++;
			   NN=0;
		  }
    }

}

