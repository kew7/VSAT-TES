// HDLC.h: interface for the CHDLC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HDLC_H__29CC6703_0262_11D5_AB84_00A0CCD50301__INCLUDED_)
#define AFX_HDLC_H__29CC6703_0262_11D5_AB84_00A0CCD50301__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MES_VKL (WM_USER+13)
#define MES_OTKL (WM_USER+12)


class CHDLC 
{
	char Maska_Frq[16];

public:
	BOOL FlagOtbCod,FlagOtbIden;
	BOOL FlagZes;
	HWND inhWnd;
	int ObsluvFlag,FlagOtb;
	CString strFREQ[2];
	CStdioFile finFREQ;
	int Radio;

	BYTE d_kod;
    CString NEW1,NEW2,NEW3,NEW4;
	long Vkl_Done;
    unsigned short int buf_freq[65535];
    int firstFlag,ChisloID;
    char buf_kod[2][6],buf_id[6],buf_id2[6],bufID[1000][6];
	BYTE reg;
    void FirstFlag(BYTE*,int);
	CHDLC();
	virtual ~CHDLC();

protected:

};

#endif // !defined(AFX_HDLC_H__29CC6703_0262_11D5_AB84_00A0CCD50301__INCLUDED_)
