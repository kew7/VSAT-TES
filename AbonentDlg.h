#if !defined(AFX_ABONENTDLG_H__E44404A4_3637_11D5_ACAA_00A0CCD50301__INCLUDED_)
#define AFX_ABONENTDLG_H__E44404A4_3637_11D5_ACAA_00A0CCD50301__INCLUDED_


#include "Abonent2.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AbonentDlg.h : header file
//

#define MES_SYN (WM_USER+11)
#define MES_OTKL (WM_USER+12)

#include "Resource.h"
#include "Mirage.h"	// Added by ClassView
#include "Abonent.h"	// Added by ClassView


/////////////////////////////////////////////////////////////////////////////
// CAbonentDlg dialog

class CAbonentDlg : public CDialog
{
// Construction
public:
	CAbonent2 Ocean2;
	HANDLE HMutexMax,HMutexDir,HMutexMin;
	CString m_TargetDir;
	COLORREF m_ColorSyn1,m_ColorSyn2;
    unsigned long NumFile,m_FilesDone;
	BOOL WorkFlag;
	BOOL Flag1_2,
		 Flag3_4;
	void OnStop();
	long BytesDone1,BytesDone2;
	unsigned MinSizeFile,MaxSizeFile;
	BOOL SynFlag1,SynFlag2;
	CString FileNameC,
		    FileNameA;
	CMirage Mirag;
	CAbonent Ocean;
	BYTE m_Quality[2],
         NumBlock[2];
	int SynFlag;
	HWND inhWnd;
	CAbonentDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAbonentDlg)
	enum { IDD = IDD_ABON_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAbonentDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:

//	CPortCom Com;
	HICON m_hIcon;


	// Generated message map functions
	//{{AFX_MSG(CAbonentDlg)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg LRESULT OnMesCount(WPARAM def,LPARAM Block);
    afx_msg LPARAM OnMesSyn(WPARAM Num,LPARAM Vkl);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ABONENTDLG_H__E44404A4_3637_11D5_ACAA_00A0CCD50301__INCLUDED_)
