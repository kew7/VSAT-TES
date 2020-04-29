// DirOpenDialog.cpp : implementation file
//

#include "stdafx.h"
#include "VSAT_TES.h"
#include "DirOpenDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDirOpenDialog dialog


CDirOpenDialog::CDirOpenDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDirOpenDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDirOpenDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDirOpenDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDirOpenDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDirOpenDialog, CDialog)
	//{{AFX_MSG_MAP(CDirOpenDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDirOpenDialog message handlers
