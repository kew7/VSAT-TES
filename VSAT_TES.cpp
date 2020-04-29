// VSAT_TES.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "VSAT_TES.h"
#include "VSAT_TESDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVSAT_TESApp

BEGIN_MESSAGE_MAP(CVSAT_TESApp, CWinApp)
	//{{AFX_MSG_MAP(CVSAT_TESApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVSAT_TESApp construction

CVSAT_TESApp::CVSAT_TESApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CVSAT_TESApp object

CVSAT_TESApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CVSAT_TESApp initialization

BOOL CVSAT_TESApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
	dlg=new CVSAT_TESDlg;
	int nResponse = dlg->DoModal();   
    m_pMainWnd = dlg;
	hm=AfxGetResourceHandle();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
