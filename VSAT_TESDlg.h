// VSAT_TESDlg.h : header file
//

#if !defined(AFX_VSAT_TESDLG_H__8CEF3287_4396_11D5_ACD2_00A0CCD50301__INCLUDED_)
#define AFX_VSAT_TESDLG_H__8CEF3287_4396_11D5_ACD2_00A0CCD50301__INCLUDED_

#include "TerminalDlg.h"	// Added by ClassView
#include "OtborDlg.h"	// Added by ClassView
#include "ConfigDlg.h"	// Added by ClassView
#include "Mirage.h"
#include "ComPort.h"
#include "Occ.h"
#include "DirOpenDlg.h"	// Added by ClassView
#include "InitComDlg.h"	// Added by ClassView
//#include "UstanDlg.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MES_SHOW_DISK (WM_USER+10)

/////////////////////////////////////////////////////////////////////////////
// CVSAT_TESDlg dialog

class CVSAT_TESDlg : public CDialog
{
// Construction
public:

    CPortCom Com;	
	CInitComDlg*m_InitComDlg;
	CString m_TargetDirSave,m_TargetDirTemp;
	void ConvertCod_Freq(unsigned short);
	void zagruzka_iden();
	void zagruzka_cod();
	CStdioFile foutFREQ,foutID,foutIdenOtb,foutCodOtb;
    Occ Ocean;
	BOOL flWork;
	CMirage Mirag;
    HANDLE HMutex;
	CConfigDlg m_ConfigDlg;
	COtborDlg m_OtborDlg;
	CTerminalDlg m_TerminalDlg;
	CVSAT_TESDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CVSAT_TESDlg)
	enum { IDD = IDD_VSAT_TES_DIALOG };
	CTabCtrl	m_Cards;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVSAT_TESDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString m_FileFreqName;
	HICON m_hIcon;
	void Ustan_Razw();
	void Ustan_Priem(); 
	afx_msg LRESULT OnShowDisk(WPARAM,LPARAM);
	// Generated message map functions
	//{{AFX_MSG(CVSAT_TESDlg)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangingTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPusk();
	afx_msg void OnStop();
	afx_msg LRESULT OnMesCount2(WPARAM def, LPARAM Block );
	afx_msg LRESULT OnMesVkl(WPARAM,LPARAM);
	afx_msg LRESULT OnMesOtkl(WPARAM,LPARAM);
	afx_msg void OnClose();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDirOpen();
	afx_msg void OnFileFreq();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VSAT_TESDLG_H__8CEF3287_4396_11D5_ACD2_00A0CCD50301__INCLUDED_)
