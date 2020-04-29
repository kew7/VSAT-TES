// InitComDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VSAT_TES.h"
#include "InitComDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInitComDlg dialog


CInitComDlg::CInitComDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInitComDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInitComDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CInitComDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInitComDlg)
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInitComDlg, CDialog)
	//{{AFX_MSG_MAP(CInitComDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInitComDlg message handlers

BOOL CInitComDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Progress.SetRange(0,120);
    m_Progress.SetStep(10);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
