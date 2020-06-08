// ComPort.cpp: implementation of the CComPort class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VSAT_TES.h"
#include "ComPort.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CVSAT_TESApp theApp;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPortCom::CPortCom()
{
   // AbonDlg=new CAbonentDlg;          // // создаем объект абонентского диалового окна
	
    //AbonDlg->Create(CAbonentDlg::IDD);
    //AbonDlg->EndDialog(0);
}

CPortCom::~CPortCom()
{
 
}


UINT ComThreadSyn1(void*Com1)
{
COMSTAT ComStat;
int NumDev=0;
int i=0;
int Flag=0;
DWORD dwEvtMask,dwError,ReturnByte=0;
char BufRead[300];

  cClass cd=(cClass)Com1;

  cd->AbonDlg->SynFlag1=FALSE;

                // Задаем модему вид модуляции и скорость
  if(cd->FlagBPSK==TRUE) {
	  cd->WriteCommBlock("RM 0\r\n",0);
	  cd->WriteCommBlock("RR "+theApp.dlg->m_ConfigDlg.m_Speed2+"\r\n",0);
  }
  else 
  {
	  cd->WriteCommBlock("RM 1\r\n",0);
	  cd->WriteCommBlock("RR "+theApp.dlg->m_ConfigDlg.m_Speed+"\r\n",0);
  }
  cd->WriteCommBlock(cd->strFREQ[0],0);
  //WriteFile(hCom[Num],BufWrite,BufWrite.GetLength(),&Returned,&osWrite[Num]);
  SetCommMask(cd->hCom[NumDev],EV_RXCHAR);
     do
	 {
	  if(!(cd->WorkFlag[0])) return 0;
      dwEvtMask=0;
	  WaitCommEvent(cd->hCom[NumDev], &dwEvtMask,NULL);
      if ((dwEvtMask & EV_RXCHAR)==EV_RXCHAR) 
	  {
      	 ReturnByte=0;
    	 ClearCommError(cd->hCom[NumDev],&dwError,&ComStat);
         if(ReadFile(cd->hCom[NumDev],BufRead+i,ComStat.cbInQue,&ReturnByte,
			                                 &(cd->osRead[NumDev])))
                                                                       	 i+=ReturnByte;
	  }	 
	  
	 }
	 while(ReturnByte>0);

	 if(strstr(BufRead,"ST")!=NULL)     //ждем синхронизации модема
	 {
		  cd->AbonDlg->SynFlag1=TRUE;
		  cd->AbonDlg->PostMessage(MES_SYN,0,0);
	 }
    else 
	{

	}
return 0;
}


UINT ComThreadSyn2(void*Com2)
{
COMSTAT ComStat;
int Num=1;
int i=0;
int Flag=0;
DWORD dwEvtMask,dwError,ReturnByte=0;
char BufRead[300];

  cClass cd=(cClass)Com2;

  cd->AbonDlg->SynFlag2=FALSE;

	// Задаем модему вид модуляции
  if(cd->FlagBPSK==TRUE) {
	  cd->WriteCommBlock1("RM 0\r\n",1);
	  cd->WriteCommBlock1("RR "+theApp.dlg->m_ConfigDlg.m_Speed2+"\r\n",1);
  }
  else 
  {
	  cd->WriteCommBlock1("RM 1\r\n",1);
	  cd->WriteCommBlock1("RR "+theApp.dlg->m_ConfigDlg.m_Speed+"\r\n",1);
  }
  cd->WriteCommBlock1(cd->strFREQ[1],1);
//  WriteFile(hCom[Num],BufWrite,BufWrite.GetLength(),&Returned,&osWrite[Num]);

  SetCommMask(cd->hCom[Num],EV_RXCHAR);
     do
	 { 
	  if(!(cd->WorkFlag[1])) return 0;
      dwEvtMask=0;
	  WaitCommEvent(cd->hCom[Num], &dwEvtMask,NULL);
      if ((dwEvtMask & EV_RXCHAR)==EV_RXCHAR) 
	  {
      	 ReturnByte=0;
    	 ClearCommError(cd->hCom[Num],&dwError,&ComStat);
         if(ReadFile(cd->hCom[Num],BufRead+i,ComStat.cbInQue,&ReturnByte,
			                                 &(cd->osRead[Num]))) i+=ReturnByte;
	  }	 
	 }
	 while(ReturnByte>0);

	 if(strstr(BufRead,"ST")!=NULL)     //ждем синхронизации модема
	 {
         cd->AbonDlg->SynFlag2=TRUE;
		 cd->AbonDlg->PostMessage(MES_SYN,0,0);
	 }
	 else 
	 {

	 }
return 0;
}


BOOL CPortCom::Proverka(int Num)    //функция проверки соединения модема с СОМ-порт
{
	CString DeviceName="COM",PortNum;
	OVERLAPPED os; 

	PortNum.Format("%d",Num+1);
	DeviceName+=PortNum;
	
	hCom[Num] = CreateFile( DeviceName,
	GENERIC_READ | GENERIC_WRITE,
    0,    // exclusive access 
    NULL, // no security attributes 
    OPEN_EXISTING,
    FILE_ATTRIBUTE_NORMAL
	|FILE_FLAG_OVERLAPPED, 
    NULL
	);

	memset(&os,0,sizeof(OVERLAPPED));
	os.hEvent = CreateEvent( NULL,    // no security
								TRUE,    // explicit reset req
								FALSE,   // initial event reset
								NULL ) ; // no name
		if (os.hEvent == NULL)
		{
		   MessageBox(NULL, "Failed to create event for thread!", "TTY Error!",
			   MB_ICONEXCLAMATION | MB_OK);
		   return (FALSE);
		 }

		if (hCom[Num] == INVALID_HANDLE_VALUE) 
		{
			// Handle the error. 
			return FALSE;
		}

		if (!OpenConnection(hCom[Num])) return FALSE;

		WriteFile(hCom[Num], "EB\r\n", 8, &Returned, &os);
		if (!OpenThread(Num))
		{
			if (Num == 0) { CloseHandle(hTHR[0]);  CloseHandle(hCom[0]); }
			else { CloseHandle(hTHR[1]); CloseHandle(hCom[1]); }
			CloseHandle(os.hEvent);
			return FALSE;
		}
		else
		{
			if (Num == 0) {
				CloseHandle(hTHR[0]);
				CloseHandle(hCom[0]);
			}
			else { CloseHandle(hTHR[1]);	 CloseHandle(hCom[1]); }
			CloseHandle(os.hEvent);
			return TRUE;
		}
}


BOOL CPortCom::Create(int Num) //функция открытия и инициализации портов 
{

	CString DeviceName="COM",PortNum;

	PortNum.Format("%d",Num+1);
	DeviceName+=PortNum;

	hCom[Num] = CreateFile( DeviceName,  
		GENERIC_READ | GENERIC_WRITE,    
		0,    // exclusive access 
		NULL, // no security attributes 
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL
		|FILE_FLAG_OVERLAPPED,
		NULL
		);

		if (hCom[Num] == INVALID_HANDLE_VALUE) 
		{
			// Handle the error. 
			return FALSE;
		}

		for(int i=0; i<2;i++)
		{
		memset(&osRead[Num],0,sizeof(OVERLAPPED));
		memset(&osWrite[Num],0,sizeof(OVERLAPPED));
		osRead[Num].Offset=0;   osRead[Num].OffsetHigh=0;
		osWrite[Num].Offset=0;    osWrite[Num].OffsetHigh=0;
		}

		if(!OpenConnection(hCom[Num])) return FALSE;

		if((osRead[Num].hEvent=CreateEvent(NULL,
									TRUE,
									FALSE,
									NULL))==NULL)  return FALSE;

		if((osWrite[Num].hEvent=CreateEvent(NULL,
									TRUE,
									FALSE,
									NULL))==NULL) return FALSE;
return TRUE;
}


BOOL CPortCom::SetupConnection(HANDLE h)		// параметры соединения с COM
{
		DCB dcb;
		BOOL fSuccess;

		fSuccess = GetCommState(h, &dcb);

		if (!fSuccess) 
		{
			return FALSE;  // Handle the error. 
		}

		// Fill in the DCB: baud=9600, 8 data bits, no parity, 1 stop bit. 
		dcb.BaudRate = 9600;
		dcb.ByteSize = 8;
		dcb.Parity = NOPARITY;
		dcb.StopBits = ONESTOPBIT;
		dcb.XonChar = ASCII_XON ;
		dcb.XoffChar = ASCII_XOFF ;
		dcb.XonLim = 100 ;
		dcb.XoffLim = 100 ;
		fSuccess = SetCommState(h, &dcb);

		if (!fSuccess) 
		{
		  return FALSE;    // Handle the error. 
		}
 
return TRUE;
}

BOOL CPortCom::OpenConnection(HANDLE h) // устанавливаем параметры обмена
{
	COMMTIMEOUTS CommTimeOuts;
 
      SetupComm(h, 4096, 4096 ) ;

      // purge any information in the buffer

      PurgeComm( h, PURGE_TXABORT | PURGE_RXABORT |
                                      PURGE_TXCLEAR | PURGE_RXCLEAR ) ;

      // set up for overlapped I/O

      CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;
      CommTimeOuts.ReadTotalTimeoutMultiplier = 0 ;
      CommTimeOuts.ReadTotalTimeoutConstant = 1000 ;
      // CBR_9600 is approximately 1byte/ms. For our purposes, allow
      // double the expected time per character for a fudge factor.
      CommTimeOuts.WriteTotalTimeoutMultiplier = 0 ;
      CommTimeOuts.WriteTotalTimeoutConstant = 0 ;
      SetCommTimeouts(h, &CommTimeOuts ) ;

   if(SetupConnection(h)) return TRUE ; else return FALSE;
}


BOOL CPortCom::OpenThread(int Num)		// создание потока
{
	  NumDevice=Num;
	//  for(int i=0;i<2;i++) ComFlag[i]=FALSE;
	  if(!(hTHR[Num]=CreateThread(NULL,0,ComThreadFunc,(void*)this,0,NULL))) return FALSE;
	  else
	  {
		  SetThreadPriority(hTHR[Num],THREAD_PRIORITY_NORMAL);
		  Sleep(500);
		  if(ComFlag[Num]==TRUE) return TRUE; 
		  else 	return FALSE;
	  
	  }
}


DWORD WINAPI ComThreadFunc(void*Com)	// функция потока
{
	DWORD dwEvtMask;

	 cClass cd=(cClass)Com;
	 SetCommMask(cd->hCom[cd->NumDevice],EV_RXCHAR) ;
	 dwEvtMask=0;
	 {
	 WaitCommEvent(cd->hCom[cd->NumDevice],&dwEvtMask,NULL);
	 if((dwEvtMask&EV_RXCHAR)==EV_RXCHAR)
	 {
		 cd->ComFlag[cd->NumDevice]=TRUE;
	 }
	 else {cd->ComFlag[cd->NumDevice]=FALSE;}
	 }
	return 0;
 
}


BOOL CPortCom::WriteCommBlock(CString BufWrite,int Num)		// отправка данных настройки модему
{
		COMSTAT ComStat;
		int i=0;
		int Flag=0;
		DWORD dwEvtMask,dwError;
		CString BRead="";
		char BufRead[300];

		WriteFile(hCom[Num],BufWrite,BufWrite.GetLength(),&Returned,&osWrite[Num]);

		SetCommMask(hCom[Num],EV_RXCHAR);
				do
				{
					  dwEvtMask=0;
					  WaitCommEvent(hCom[Num], &dwEvtMask, NULL);
					  if ((dwEvtMask & EV_RXCHAR)==EV_RXCHAR) 
					  {
      					 Returned=0;
    					 ClearCommError(hCom[Num],&dwError,&ComStat);
						 if(ReadFile(hCom[Num],BufRead+i,ComStat.cbInQue,&Returned,&osRead[Num])) i+=Returned;
						 for(int n=0;n<i;n++) if(BufRead[n]=='>'){       //ждем ответа модема
							 Flag=1;
							 if(Flag==1) break;
						 }
					  }
				}
				while(Flag!=1);
		if(Flag==1) return TRUE; else return FALSE;
}

BOOL CPortCom::WriteCommBlock1(CString BufWrite,int Num)
{
		COMSTAT ComStat;
		int i=0;
		int Flag=0;
		DWORD dwEvtMask,dwError;
		CString BRead="";
		char BufRead[300];

		WriteFile(hCom[Num],BufWrite,BufWrite.GetLength(),&Returned,&osWrite[Num]);

		SetCommMask(hCom[Num],EV_RXCHAR);
			do
			{
			  dwEvtMask=0;
			  WaitCommEvent(hCom[Num], &dwEvtMask, NULL);
			  if ((dwEvtMask & EV_RXCHAR)==EV_RXCHAR) 
			  {
      			 Returned=0;
    			 ClearCommError(hCom[Num],&dwError,&ComStat);
				 if(ReadFile(hCom[Num],BufRead+i,ComStat.cbInQue,&Returned,&osRead[Num])) i+=Returned;
				 for(int n=0;n<i;n++) if(BufRead[n]=='>'){      
					 Flag=1;
					 if(Flag==1) break;
				 }
			  }
			}
			while(Flag!=1);
		if(Flag==1) return TRUE; else return FALSE;
}


BOOL CPortCom::OpenThreadSyn(CString Str,int Num)   //функция открытия потока для отлавливания синхронизации
{
		if (ComFlag[0])
		{
			if (!(hTHRSyn[0] = AfxBeginThread(ComThreadSyn1, (void*)this, THREAD_PRIORITY_NORMAL, 0, 0, NULL)))
			{
				WorkFlag[0] = FALSE;
				return FALSE;
			}
			else
			{
				WorkFlag[0] = TRUE;

			}
		}
		if (ComFlag[1])
		{
			if (!(hTHRSyn[1] = AfxBeginThread(ComThreadSyn2, (void*)this, THREAD_PRIORITY_NORMAL, 0, 0, NULL)))

			{
				WorkFlag[1] = FALSE;
				return FALSE;
			}
			else
			{
				WorkFlag[1] = TRUE;
			}
		}
		if ((!ComFlag[0]) && (!ComFlag[0])) return FALSE;
	return TRUE;
}







