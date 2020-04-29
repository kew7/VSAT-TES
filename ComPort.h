// ComPort.h: interface for the CComPort class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPORT_H__F88E9941_243E_11D5_AC0C_00A0CCD50301__INCLUDED_)
#define AFX_COMPORT_H__F88E9941_243E_11D5_AC0C_00A0CCD50301__INCLUDED_

#include "AbonentDlg.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ASCII_BEL       0x07
#define ASCII_BS        0x08
#define ASCII_LF        0x0A
#define ASCII_CR        0x0D
#define ASCII_XON       0x10
#define ASCII_XOFF      0x13

DWORD WINAPI ComThreadFunc( void* );



class CPortCom  
{
public:
//	UINT ComThreadSyn2(LPVOID);
	CWinThread * hTHRSyn[2];
	CString strFREQ[2];
    CAbonentDlg*AbonDlg;
	BOOL WorkFlag[2];
	OVERLAPPED osRead[2],osWrite[2];
	BOOL OpenThreadSyn(CString,int);
	BOOL WriteCommBlock(CString,int),WriteCommBlock1(CString,int);
	BOOL ComFlag[2],SynFlag[2];
	BYTE NumDevice;
	BOOL OpenThread(int Num);
	BOOL Proverka(int Num);
    BOOL OpenConnection(HANDLE h);
	BOOL SetupConnection(HANDLE h);
	BOOL FlagQPSK,
		 FlagBPSK;
    HANDLE hCom[2],hTHR[2];
	DWORD Returned;
	char*BufCom;
	BOOL Create(int Num);
	CPortCom();
	virtual ~CPortCom();
protected:


};

typedef CPortCom*cClass;

#endif // !defined(AFX_COMPORT_H__F88E9941_243E_11D5_AC0C_00A0CCD50301__INCLUDED_)
