// TerminalDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VSAT_TES.h"
#include "TerminalDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTerminalDlg dialog


CTerminalDlg::CTerminalDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTerminalDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTerminalDlg)
	m_Zes = _T("");
	//}}AFX_DATA_INIT
}


void CTerminalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTerminalDlg)
	DDX_Text(pDX, IDC_ZES, m_Zes);
	DDV_MaxChars(pDX, m_Zes, 16);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTerminalDlg, CDialog)
	//{{AFX_MSG_MAP(CTerminalDlg)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTerminalDlg message handlers


HBRUSH CTerminalDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	int TargetControl=pWnd->GetDlgCtrlID();
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	switch(TargetControl){
	case IDC_SYN:	    pDC->SetTextColor(m_ColorSinOcc);		break;
	case IDC_ID_CALL:	pDC->SetTextColor(m_ColorIden);	     	break;
	case IDC_ID_ANSWER:	pDC->SetTextColor(m_ColorIden2);     	break;
	}	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
