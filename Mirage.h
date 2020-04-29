// Mirage.h: interface for the CMirage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIRAGE_H__A6307BB7_0FB1_46BC_A1CD_1B222F4742E1__INCLUDED_)
#define AFX_MIRAGE_H__A6307BB7_0FB1_46BC_A1CD_1B222F4742E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define DEVICE_NOT_CREATED	1
#define DEVICE_NOT_LOADED	2
#define DEVICE_NOT_EVENT	3

// Стандартные IOCTL-Коды для драйверов (ввод/вывод по прерываниям)
#define IOCTL_GetData			0x00222043
#define IOCTL_GetBlock			0x00222083
#define IOCTL_GetDataCount  	0x002220c3
#define IOCTL_FlushData			0x00222103
#define IOCTL_LoadUnit			0x00222140
#define IOCTL_Reset				0x00222180
#define IOCTL_Check				0x002221c0
#define IOCTL_SetAckn			0x00222203
#define IOCTL_PIPE              0x00222243 

#define PIPE_INIT				10
#define PIPE_TEST				20
#define PIPE_GET_MESSAGE		30
#define PIPE_MESSAGE_NOMESSAGE	100
#define PIPE_MESSAGE_OVERFLOW	110
#define PIPE_MESSAGE_OK			120
#define PIPE_MESSAGE_CANCEL		130
#define PIPE_MESSAGE_DATA_READY	140

#define MES_COUNT2 (WM_USER+1)
#define MES_COUNT (WM_USER+2)


class CMirage  
{
public:
	int DeviceNum;
	void SetBoardAttribute();
	int LengthUsBuf[2];
	BOOL WorkFlag[2];
	BOOL OpenTread(int Num);
	DWORD GetDataCount(int,int Num);
	BOOL Create(int DeviceNumber,HWND pParentWnd);

	HWND	inhwnd[2];
	HANDLE m_hEvent;
	HANDLE m_hDevice[2];
	CWinThread*hTHR[2];

	DWORD GetBlock(BYTE* pBuf,DWORD BufSize,int Num);
	DWORD GetData(BYTE* pBuf,DWORD BufSize,int Num);
	BOOL LoadLCA(CString DumpFileName);
	BOOL LoadDSP(CString DumpFileName);
	void FlushData(int DataChanel,int Num);
	CMirage();
	virtual ~CMirage();

private:
	ULONG InBuf[2],OutBuf[2];

};

typedef CMirage*pClass;

#endif // !defined(AFX_MIRAGE_H__A6307BB7_0FB1_46BC_A1CD_1B222F4742E1__INCLUDED_)
