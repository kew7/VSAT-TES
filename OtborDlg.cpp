// OtborDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VSAT_TES.h"
#include "OtborDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COtborDlg dialog


COtborDlg::COtborDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COtborDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COtborDlg)
	m_Cod_Otbor = FALSE;
	m_Iden_Otbor = FALSE;
	//}}AFX_DATA_INIT
}


void COtborDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COtborDlg)
	DDX_Check(pDX, IDC_COD_OTBOR, m_Cod_Otbor);
	DDX_Check(pDX, IDC_IDEN_OTBOR, m_Iden_Otbor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COtborDlg, CDialog)
	//{{AFX_MSG_MAP(COtborDlg)
	ON_BN_CLICKED(IDC_COD_OTBOR, OnCodOtbor)
	ON_BN_CLICKED(IDC_IDEN_OTBOR, OnIdenOtbor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COtborDlg message handlers

void COtborDlg::OnCodOtbor() 
{
	// TODO: Add your control notification handler code here
   CFileDialog fdd(TRUE,NULL,NULL,OFN_HIDEREADONLY,
					"Ôאיכ מעבמנא (*.slc)|*.slc|All Files (*.*)|*.*||",NULL);
  UpdateData(TRUE);
  if(m_Cod_Otbor)
   {
    if(fdd.DoModal()==IDOK)
    {
     m_FileCodOtb=fdd.GetPathName();
    }
	else
	{
     m_FileCodOtb="";
     m_Cod_Otbor=FALSE;
	 UpdateData(FALSE);
	}
  }
  else
  {
     m_FileCodOtb="";
  }
return;
}

void COtborDlg::OnIdenOtbor() 
{
	// TODO: Add your control notification handler code here
	  CFileDialog fdd(TRUE,NULL,NULL,OFN_HIDEREADONLY,
					"Ôאיכ מעבמנא (*.slc)|*.slc|All Files (*.*)|*.*||",NULL);

   UpdateData(TRUE);
   if(m_Iden_Otbor)
   {
    if(fdd.DoModal()==IDOK)
    {
     m_FileIdenOtb=fdd.GetPathName();
    }
    else
	{
	  m_FileIdenOtb="";
      m_Iden_Otbor=FALSE;
	  UpdateData(FALSE);
	}
   }
   else
   {
    m_FileIdenOtb="";
   }
   
return;	
}
