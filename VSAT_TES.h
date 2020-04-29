// VSAT_TES.h : main header file for the VSAT_TES application
//

#if !defined(AFX_VSAT_TES_H__8CEF3285_4396_11D5_ACD2_00A0CCD50301__INCLUDED_)
#define AFX_VSAT_TES_H__8CEF3285_4396_11D5_ACD2_00A0CCD50301__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "VSAT_TESDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CVSAT_TESApp:
// See VSAT_TES.cpp for the implementation of this class
//

class CVSAT_TESApp : public CWinApp
{
public:
	CVSAT_TESApp();
    CVSAT_TESDlg*dlg;	
	HMODULE hm;
    // Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVSAT_TESApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CVSAT_TESApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VSAT_TES_H__8CEF3285_4396_11D5_ACD2_00A0CCD50301__INCLUDED_)
