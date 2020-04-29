// Mirage.cpp: implementation of the CMirage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Resource.h"
#include "VSAT_TES.h"
#include "Mirage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CVSAT_TESApp theApp;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMirage::CMirage()
{
//	AbonDlg=new CAbonentDlg;

}

CMirage::~CMirage()
{

}


UINT LL=2048;
UINT ThreadFunc( void* Mir)
{
	WPARAM re=0;
	LPARAM nn=0;

	pClass md = (pClass)Mir;
	nn=md->LengthUsBuf[0];
	md->FlushData(0,0);    Sleep(100);
	while(md->WorkFlag[0])
	{	re=md->GetDataCount(0,0);
		if	((UINT)re > LL)
		{
		::SendMessage(md->inhwnd[0], MES_COUNT2, re, (LPARAM)nn);
		Sleep(1); 
		}
		else	Sleep(1);
	}
	return 0;
}	

UINT MM=3000;
UINT ThreadFunc2( void* Mir)
{
	WPARAM re=0;
	LPARAM nn=0;

	pClass md = (pClass)Mir;
	nn=md->LengthUsBuf[1];
	md->FlushData(0,1);    Sleep(100);
	while(md->WorkFlag[1])
	{	re=md->GetDataCount(0,1);
		if	((UINT)re > MM)
		{
		::SendMessage(md->inhwnd[1], MES_COUNT, re, (LPARAM)nn);
		Sleep(1); 
		}
		else	Sleep(1);
	}
	return 0;
}	

BOOL CMirage::Create(int DeviceNumber,HWND pParentWnd)
{
	HRSRC hRes;
	HGLOBAL hglbData;
	LPVOID pData=NULL;
	DWORD cb=0;

	inhwnd[DeviceNumber] = pParentWnd;
  	CString DeviceName;
	CString strDeviceNumber;
	strDeviceNumber.Format("%d",DeviceNumber);
	DeviceName="//./MirageDevice";
	DeviceName+=strDeviceNumber;
	DeviceNum=DeviceNumber;
	m_hDevice[DeviceNum]=CreateFile(DeviceName,GENERIC_READ|GENERIC_WRITE,
		                 0,NULL,
					     OPEN_EXISTING,
					     FILE_ATTRIBUTE_NORMAL,
					     NULL);

	if (m_hDevice[DeviceNum]==INVALID_HANDLE_VALUE) 
	{
		MessageBox(NULL,"Проверьте установку драйвера на Mirage"+strDeviceNumber,NULL,MB_OK|MB_ICONERROR);
		exit(1);
		return FALSE;
	}

 if(DeviceNum==1)      //прогружаем плату абонентских каналов
 {
    hRes=FindResource(theApp.hm,(LPCSTR)IDR_YyyBit,"ZAGRFILE");
	hglbData=LoadResource(theApp.hm,hRes);
	pData=LockResource(hglbData);
	cb=*((DWORD*)(hRes+1));// Хитрый способ получить длину данных ресурса
//    (*(PULONG)pData)=0;

    if(!(DeviceIoControl(m_hDevice[DeviceNum],IOCTL_LoadUnit,//Грузим Плис
						pData,cb,
						NULL,0,
						&cb,NULL)))
	{
      ::MessageBox(NULL,"Устройство не отвечает на загрузку LCA","Очень плохая новость",MB_OK|MB_ICONERROR);
        FreeResource(hglbData);
	    return FALSE;
	}
	FreeResource(hglbData);

	hRes=FindResource(theApp.hm,(LPCSTR)IDR_YyyBin,"ZAGRFILE");
	cb=*((DWORD*)(hRes+1));// Хитрый способ получить длину данных ресурса
	hglbData=LoadResource(theApp.hm,hRes);
	pData=LockResource(hglbData);
//    *((PULONG)pData)=0;

    if(!(DeviceIoControl(m_hDevice[DeviceNum],IOCTL_LoadUnit,//Грузим TMS
						pData,cb,
						NULL,0,
						&cb,NULL)))
	{
	   ::MessageBox(NULL,"Устройство не отвечает на загрузку DSP","Очень плохая новость",MB_OK|MB_ICONERROR);
	     FreeResource(hglbData);
	     return FALSE;
	}
	FreeResource(hglbData);
 }

 if(DeviceNum==0)    //прогружаем плату канала управления
 {
    hRes=FindResource(theApp.hm,(LPCSTR)IDR_FullBit,"ZAGRFILE");
	hglbData=LoadResource(theApp.hm,hRes);
	pData=LockResource(hglbData);
	cb=*((DWORD*)(hRes+1));// Хитрый способ получить длину данных ресурса
//    *((PULONG)pData)=0;

    if(!(DeviceIoControl(m_hDevice[DeviceNum],IOCTL_LoadUnit,//Грузим Плис
						pData,cb,
						NULL,0,
						&cb,NULL)))
	{
      ::MessageBox(NULL,"Устройство не отвечает на загрузку LCA","Очень плохая новость",MB_OK|MB_ICONERROR);
	    FreeResource(hglbData);
	    return FALSE;
	}
	FreeResource(hglbData);

	hRes=FindResource(theApp.hm,(LPCSTR)IDR_FullBin,"ZAGRFILE");
	hglbData=LoadResource(theApp.hm,hRes);
	pData=LockResource(hglbData);
	cb=*((DWORD*)(hRes+1));// Хитрый способ получить длину данных ресурса
//    *((PULONG)pData)=0;

    if(!(DeviceIoControl(m_hDevice[DeviceNum],IOCTL_LoadUnit,//Грузим TMS
						pData,cb,
						NULL,0,
						&cb,NULL)))
	{
	   ::MessageBox(NULL,"Устройство не отвечает на загрузку DSP","Очень плохая новость",MB_OK|MB_ICONERROR);
	     FreeResource(hglbData);
	     return FALSE;
	}
	FreeResource(hglbData);
 }

    FlushData(0,DeviceNum);
    if(GetDataCount(0,DeviceNum)==0) {
//		::MessageBox(NULL,"Нет сигнала на входе!!!",NULL,NULL);
		return FALSE;
	}

    return TRUE; 
}


/*BOOL CMirage::LoadDSP(CString DumpFileName)
{
	// ~~~~~~~~~~~~ bit file mapping ~~~~~~~~~~~~~~~~~
	// Файл загрузки должен содержать правильный заголовок (смотри спецификацию драйвера)
	DWORD FileSize;
	PBYTE pBin=NULL;
	HANDLE hMapping=INVALID_HANDLE_VALUE;
	HANDLE hFile=CreateFile(LPCSTR(DumpFileName),GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile==INVALID_HANDLE_VALUE)	{::MessageBox(NULL,"Невозможно открыть файл загрузочного дампа DSP","Очень плохая новость",MB_OK|MB_ICONERROR);	return FALSE;}
	FileSize=GetFileSize(hFile,NULL);
	if(FileSize>20480){
		CloseHandle(hFile);
		return FALSE;
	}
	hMapping=CreateFileMapping(hFile,NULL,PAGE_WRITECOPY,0,0,NULL);
	CloseHandle(hFile);
	if(hMapping==INVALID_HANDLE_VALUE)	return FALSE;
	pBin=(PBYTE)MapViewOfFile(hMapping,FILE_MAP_COPY,0,0,0);
	if(!pBin){
		CloseHandle(hMapping);
		return FALSE;
	}
	//~~~~~~~~~~~~~~~~ bin file in memory ~~~~~~~~~~~~~
	DWORD Returned;
	return DeviceIoControl(m_hDevice[DeviceNum],IOCTL_LoadUnit,
						  pBin,FileSize,
						  NULL,0,
						  &Returned,NULL);

}


BOOL CMirage::LoadLCA(CString DumpFileName)
{
	// ~~~~~~~~~~~~ bit file mapping ~~~~~~~~~~~~~~~~~
	// Файл загрузки должен содержать правильный заголовок (смотри спецификацию драйвера)
	DWORD FileSize;
	PBYTE pBin=NULL;
	HANDLE hMapping=INVALID_HANDLE_VALUE;
	HANDLE hFile=CreateFile(LPCSTR(DumpFileName),GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile==INVALID_HANDLE_VALUE) { 	::MessageBox(NULL,"Невозможно открыть файл загрузочного дампа LCA ","Очень плохая новость",MB_OK|MB_ICONERROR);	return FALSE;}
	FileSize=GetFileSize(hFile,NULL);
	if(FileSize>20480){
		CloseHandle(hFile);
		return FALSE;
	}
	hMapping=CreateFileMapping(hFile,NULL,PAGE_WRITECOPY,0,0,NULL);
	CloseHandle(hFile);
	if(hMapping==INVALID_HANDLE_VALUE)	return FALSE;
	pBin=(PBYTE)MapViewOfFile(hMapping,FILE_MAP_COPY,0,0,0);
	if(!pBin){
		CloseHandle(hMapping);
		return FALSE;
	}
	//~~~~~~~~~~~~~~~~ bit file in memory ~~~~~~~~~~~~~
	DWORD Returned;
	return DeviceIoControl(m_hDevice[DeviceNum],IOCTL_LoadUnit,
					pBin,FileSize,
					NULL,0,
					&Returned,NULL);

}*/

DWORD CMirage::GetData(BYTE*pBuf, DWORD BufSize,int Num)
{
	DWORD Returned=0;
	InBuf[0]=0;
	DeviceIoControl(m_hDevice[Num],IOCTL_GetData, InBuf,4,
					pBuf,BufSize,
					&Returned,NULL);
	return Returned;
}

DWORD CMirage::GetBlock(BYTE*pBuf, DWORD BufSize,int Num)
{
	DWORD Returned=0;
	InBuf[0]=0;
	DeviceIoControl(m_hDevice[Num],IOCTL_GetBlock,InBuf,4,pBuf,BufSize,	&Returned,NULL);
	return Returned;
}


DWORD CMirage::GetDataCount(int DataChanel,int Num)
{	
	ULONG Returned;
	InBuf[0]=DataChanel;
	Sleep(100);
	DeviceIoControl(m_hDevice[Num],IOCTL_GetDataCount,InBuf,4,OutBuf,4,&Returned,NULL);
	return OutBuf[0];
}


BOOL CMirage::OpenTread(int Num)
{
 if(Num==0)
 {	
	Sleep(1); WorkFlag[Num]=TRUE;
	if(!(hTHR[Num]=AfxBeginThread(ThreadFunc,(void*)this,THREAD_PRIORITY_TIME_CRITICAL,
		                                                 0,0,NULL)))
	{	
	return FALSE;
	}
	else{
         return TRUE;
	}

 }
 if(Num==1)
 {	
	Sleep(1); WorkFlag[Num]=TRUE;
	if(!(hTHR[Num]=AfxBeginThread(ThreadFunc2,(void*)this,THREAD_PRIORITY_TIME_CRITICAL,
		                                                   0,0,NULL)))
	{	
	return FALSE;
	}
	else{
         
		 return TRUE;
	}

 }

return TRUE;
}


void CMirage::FlushData(int DataChanel,int Num)
{
	ULONG Returned;
	InBuf[0]=DataChanel;
	DeviceIoControl(m_hDevice[Num],IOCTL_FlushData,InBuf,4,NULL,0,&Returned,NULL);
}



void CMirage::SetBoardAttribute()
{
	ULONG Written;
	static UCHAR ControlByte=0;
	typedef struct ParcelTag{
		ULONG Port 			:8;
		ULONG DataChannel	:5;
		ULONG Width			:3;
		ULONG Delay 		:15;
		ULONG ReadWrite		:1;
		ULONG Reserv;
		ULONG Value;
	}PortParcel;
	PortParcel Shablon[2];
	int i;

	ControlByte|=0x02;		
//	ControlByte|=0x08;		
	
	for(i=0;i<2;i++){
		Shablon[i].Port=4;
		Shablon[i].DataChannel=0;
		Shablon[i].Width=2;
		Shablon[i].Delay=0;
		Shablon[i].ReadWrite=1;
		Shablon[i].Reserv=0;
		Shablon[i].Value=ControlByte;
	}
	WriteFile(m_hDevice,Shablon,24,&Written,NULL);	
}




