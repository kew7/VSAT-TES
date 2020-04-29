#if !defined(AFX_CONFIGDLG_H__DBEC85D1_43C3_11D5_ACD3_00A0CCD50301__INCLUDED_)
#define AFX_CONFIGDLG_H__DBEC85D1_43C3_11D5_ACD3_00A0CCD50301__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog

class CConfigDlg : public CDialog
{
// Construction
public:
	COLORREF m_ColorFreeDisk;

	HWND inhwnd;
	CConfigDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigDlg)
	enum { IDD = IDD_CONFIG_DLG };
	CSliderCtrl	m_MinSize;
	CSliderCtrl	m_MaxSize;
	BOOL	m_Chek_Del;
	BOOL	m_Chek_Max;
	int		m_Radio;
	int		m_Radio4Hhz;
	CString	m_SizeTempMax;
	CString	m_SizeTempMin;
	CString	m_Speed;
	BOOL	m_Zanos;
	CString	m_NumSeans;
	CString	m_Speed2;
	CString	m_Cod;
	CString	m_Freq;
	CString	m_Step;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigDlg)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnRadio();
	afx_msg void OnRadio2();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnZanos();
	afx_msg void OnChekDel();
	afx_msg void OnChekMax();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGDLG_H__DBEC85D1_43C3_11D5_ACD3_00A0CCD50301__INCLUDED_)
