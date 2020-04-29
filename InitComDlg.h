#if !defined(AFX_INITCOMDLG_H__C0517263_4F92_11D5_AD0B_00A0CCD50301__INCLUDED_)
#define AFX_INITCOMDLG_H__C0517263_4F92_11D5_AD0B_00A0CCD50301__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InitComDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInitComDlg dialog

class CInitComDlg : public CDialog
{
// Construction
public:
	CInitComDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInitComDlg)
	enum { IDD = IDD_INIT_COM };
	CProgressCtrl	m_Progress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInitComDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInitComDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INITCOMDLG_H__C0517263_4F92_11D5_AD0B_00A0CCD50301__INCLUDED_)
