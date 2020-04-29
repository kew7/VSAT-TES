// Occ.h: interface for the Occ class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OCC_H__875EAC26_FC0E_11D4_AB61_00A0CCD50301__INCLUDED_)
#define AFX_OCC_H__875EAC26_FC0E_11D4_AB61_00A0CCD50301__INCLUDED_

//#include "Mirag_VvodDlg.h"	// Added by ClassView
//#include "HDLC.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif

#include "HDLC.h"

#define LENG_SHAB 100
#define T_0   0
#define T_90  1
#define T_180 2
#define T_270 3

class Occ  
{

public:

	HWND inhWnd;
	CHDLC Process;
	BYTE simv_desdvig;
	BYTE buf_save[2];
	void desdvig(BYTE*,int,BYTE);
	CFile fout;
    BYTE *buf_temp,*buf_out,*buf_deper,*buf_dec,*buf_dif,*buf_dskr;  
    BYTE*massiv[112];
	BYTE prev_shift;
	int decoder(BYTE*,int);
	BYTE sdwig;
	BYTE reg_decode;
	BOOL Obrabotka(BYTE*,int );
	unsigned char turn_faza;
    int sdvig(BYTE*buf, int len,int i);
	BOOL synchro_search(BYTE*buf_in,int lenb);
	Occ();
	virtual ~Occ();

};

#endif // !defined(AFX_OCC_H__875EAC26_FC0E_11D4_AB61_00A0CCD50301__INCLUDED_)
