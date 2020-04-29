#if !defined(AFX_TERMINALDLG_H__DE28FC51_43B3_11D5_ACD3_00A0CCD50301__INCLUDED_)
#define AFX_TERMINALDLG_H__DE28FC51_43B3_11D5_ACD3_00A0CCD50301__INCLUDED_

#include "ComPort.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TerminalDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTerminalDlg dialog

class CTerminalDlg : public CDialog
{
// Construction
public:
	COLORREF m_ColorSinOcc,
             m_ColorIden,
			 m_ColorIden2;
	CTerminalDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTerminalDlg)
	enum { IDD = IDD_TERMINAL_DLG };
	CString	m_Zes;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTerminalDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTerminalDlg)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TERMINALDLG_H__DE28FC51_43B3_11D5_ACD3_00A0CCD50301__INCLUDED_)
