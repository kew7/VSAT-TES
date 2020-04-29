// Abonent.h: interface for the CAbonent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABONENT_H__28E80975_363C_11D5_ACAB_00A0CCD50301__INCLUDED_)
#define AFX_ABONENT_H__28E80975_363C_11D5_ACAB_00A0CCD50301__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CAbonent  
{

public:
	void SdvigG728(int, UINT);
	void SdvigG726(int, UINT);
    void SinchroSearhG728(int);
	BOOL Demultiplex(BYTE*buf,int len);
	BYTE Variant1,Variant2,Variant;
	BYTE simv_desdvig,simv_desdvig1,simv_desdvig2;
	BYTE buf_save[2],
		 buf_save1[2],
		 buf_save2[2],
		 buf_saveG728[2][2],
		 buf_saveG726[2],
		 m_MaxSynIndex[2];
	void desdvig(BYTE*,int,BYTE,BYTE Num);
	void init(BYTE);
	BYTE reg_decode,reg_decode1,reg_decode2;
	CFile fout1,fout2,fout3,fout4,fout;
    BYTE *buf_temp,*buf_out,*buf_deper,*buf_dec,*buf_dif,*buf_dskr;  
    BYTE*massiv[112];
	BYTE reg_shift,reg_shift1,reg_shift2;
	BYTE prev_shift,prev_shift1,prev_shift2;
	BYTE sdwig,sdwig1,sdwig2;
	BOOL Obrabotka(BYTE*,int,BYTE Num);
	unsigned char turn_faza,turn_faza1,turn_faza2;
    int sdvig(BYTE*buf, int len,int i);
	int Num_kan,
		Flag_kan;
	BOOL FlagG728,SynchroG728[2],
		 FlagG726,SynchroG726[2];	
	BOOL synchro_search(BYTE*buf_in,int lenb,BYTE Num);
    BYTE ch_sind(BYTE*, unsigned int,BYTE Num);
	BYTE* buf_in1,*buf_in2;
	unsigned int SizeBuf_kan; 
	CAbonent();
	virtual ~CAbonent();

protected:

};

#endif // !defined(AFX_OCC_H__875EAC26_FC0E_11D4_AB61_00A0CCD50301__INCLUDED_)



