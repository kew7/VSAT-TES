#if !defined(AFX_OTBORDLG_H__34335476_43B9_11D5_ACD3_00A0CCD50301__INCLUDED_)
#define AFX_OTBORDLG_H__34335476_43B9_11D5_ACD3_00A0CCD50301__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OtborDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COtborDlg dialog

class COtborDlg : public CDialog
{
// Construction
public:
	CString m_FileCodOtb;
	CString m_FileIdenOtb;
	COtborDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COtborDlg)
	enum { IDD = IDD_OTBOR_DLG };
	BOOL	m_Cod_Otbor;
	BOOL	m_Iden_Otbor;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COtborDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COtborDlg)
	afx_msg void OnCodOtbor();
	afx_msg void OnIdenOtbor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OTBORDLG_H__34335476_43B9_11D5_ACD3_00A0CCD50301__INCLUDED_)
