// ConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VSAT_TES.h"
#include "ConfigDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CVSAT_TESApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog


CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigDlg)
	m_Chek_Del = FALSE;
	m_Chek_Max = FALSE;
	m_Radio = 0;
	m_Radio4Hhz = 0;
	m_SizeTempMax = _T("1000 K");
	m_SizeTempMin = _T("10 K");
	m_Speed = _T("");
	m_Zanos = FALSE;
	m_NumSeans = _T("");
	m_Speed2 = _T("");
	m_Cod = _T("");
	m_Freq = _T("");
	m_Step = _T("");
	//}}AFX_DATA_INIT
}


void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigDlg)
	DDX_Control(pDX, IDC_MinSize, m_MinSize);
	DDX_Control(pDX, IDC_MaxSize, m_MaxSize);
	DDX_Check(pDX, IDC_Chek_Del, m_Chek_Del);
	DDX_Check(pDX, IDC_Chek_Max, m_Chek_Max);
	DDX_Radio(pDX, IDC_RADIO, m_Radio);
	DDX_Radio(pDX, IDC_RADIO_4HHz, m_Radio4Hhz);
	DDX_Text(pDX, IDC_SizeTempMax, m_SizeTempMax);
	DDX_Text(pDX, IDC_SizeTempMin, m_SizeTempMin);
	DDX_Text(pDX, IDC_SPEED, m_Speed);
	DDX_Check(pDX, IDC_ZANOS, m_Zanos);
	DDX_Text(pDX, IDC_NumSeans, m_NumSeans);
	DDX_Text(pDX, IDC_SPEED2, m_Speed2);
	DDX_Text(pDX, IDC_COD, m_Cod);
	DDX_Text(pDX, IDC_FREQ, m_Freq);
	DDX_Text(pDX, IDC_STEP, m_Step);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CConfigDlg)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_RADIO, OnRadio)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_ZANOS, OnZanos)
	ON_BN_CLICKED(IDC_Chek_Del, OnChekDel)
	ON_BN_CLICKED(IDC_Chek_Max, OnChekMax)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg message handlers

void CConfigDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
  if(m_Chek_Del)
	{
	// TODO: Add your message handler code here and/or call default
	m_SizeTempMin.Format("%d K",m_MinSize.GetPos());
    SetDlgItemText(IDC_SizeTempMin,m_SizeTempMin);	
 	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	  if(theApp.dlg->flWork==TRUE)
	  {
        theApp.dlg->Com.AbonDlg->MinSizeFile=m_MinSize.GetPos();   
	  }
	}

  if(m_Chek_Max)
	{
	// TODO: Add your message handler code here and/or call default
	m_SizeTempMax.Format("%d K",m_MaxSize.GetPos());
    SetDlgItemText(IDC_SizeTempMax,m_SizeTempMax);	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	 if(theApp.dlg->flWork==TRUE)
	  {
        theApp.dlg->Com.AbonDlg->MaxSizeFile=m_MaxSize.GetPos();   
	  }
	}
  
	return;
}

void CConfigDlg::OnRadio() 
{
	// TODO: Add your control notification handler code here
    theApp.dlg->GetMenu()->EnableMenuItem(ID_DIR_OPEN,MF_GRAYED); 
	theApp.dlg->GetMenu()->EnableMenuItem(ID_TEMP_DIR,MF_ENABLED);
	theApp.dlg->GetMenu()->EnableMenuItem(ID_FILE_FREQ,MF_GRAYED);

	GetDlgItem(IDC_SPEED)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPEED2)->EnableWindow(FALSE);
	GetDlgItem(IDC_Txt_Speed1)->EnableWindow(FALSE);
	GetDlgItem(IDC_TXT_SPEED2)->EnableWindow(FALSE);
	GetDlgItem(IDC_TXT_SPEED)->EnableWindow(FALSE);

	GetDlgItem(IDC_Chek_Del)->EnableWindow(FALSE);
	GetDlgItem(IDC_Txt_Min)->EnableWindow(FALSE);
	GetDlgItem(IDC_MinSize)->EnableWindow(FALSE);
	GetDlgItem(IDC_Chek_Max)->EnableWindow(FALSE);
	GetDlgItem(IDC_Txt_Max)->EnableWindow(FALSE);
	GetDlgItem(IDC_MaxSize)->EnableWindow(FALSE);
	GetDlgItem(IDC_SizeTempMin)->EnableWindow(FALSE);
	GetDlgItem(IDC_SizeTempMax)->EnableWindow(FALSE);
	GetDlgItem(IDC_Txt_Seans)->EnableWindow(FALSE);
	GetDlgItem(IDC_Txt_Disk)->EnableWindow(FALSE);

	GetDlgItem(IDC_ZANOS)->EnableWindow(TRUE);
    GetDlgItem(IDC_COD)->EnableWindow(FALSE);
	GetDlgItem(IDC_Txt_Cod)->EnableWindow(TRUE);
	GetDlgItem(IDC_FREQ)->EnableWindow(FALSE);
	GetDlgItem(IDC_Txt_Freq)->EnableWindow(TRUE);
	GetDlgItem(IDC_STEP)->EnableWindow(FALSE);
	GetDlgItem(IDC_Txt_Step)->EnableWindow(TRUE);

	GetDlgItem(IDC_FreeDisk)->EnableWindow(FALSE);
	GetDlgItem(IDC_NumSeans)->EnableWindow(FALSE);
	SetDlgItemText(IDC_FreeDisk,"");

	GetDlgItem(IDC_TXT_PATH)->EnableWindow(FALSE);
	GetDlgItem(IDC_PATH)->EnableWindow(FALSE);

	theApp.dlg->m_OtborDlg.GetDlgItem(IDC_IDEN_OTBOR)->EnableWindow(FALSE);
	theApp.dlg->m_OtborDlg.GetDlgItem(IDC_COD_OTBOR)->EnableWindow(FALSE);
return;	

	
}

void CConfigDlg::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	theApp.dlg->GetMenu()->EnableMenuItem(ID_DIR_OPEN,MF_ENABLED); 
	theApp.dlg->GetMenu()->EnableMenuItem(ID_TEMP_DIR,MF_GRAYED);
	theApp.dlg->GetMenu()->EnableMenuItem(ID_FILE_FREQ,MF_ENABLED);

	GetDlgItem(IDC_SPEED)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPEED2)->EnableWindow(TRUE);
	GetDlgItem(IDC_Txt_Speed1)->EnableWindow(TRUE);
	GetDlgItem(IDC_TXT_SPEED2)->EnableWindow(TRUE);
    GetDlgItem(IDC_TXT_SPEED)->EnableWindow(TRUE);

	GetDlgItem(IDC_Chek_Del)->EnableWindow(TRUE);
	GetDlgItem(IDC_Txt_Min)->EnableWindow(TRUE);
	if(m_Chek_Del==FALSE) GetDlgItem(IDC_MinSize)->EnableWindow(FALSE);
	else GetDlgItem(IDC_MinSize)->EnableWindow(TRUE);
	GetDlgItem(IDC_Chek_Max)->EnableWindow(TRUE);
	GetDlgItem(IDC_Txt_Max)->EnableWindow(TRUE);
	if(m_Chek_Max==FALSE)	GetDlgItem(IDC_MaxSize)->EnableWindow(FALSE);
	else GetDlgItem(IDC_MaxSize)->EnableWindow(TRUE);
	GetDlgItem(IDC_SizeTempMin)->EnableWindow(TRUE);
	GetDlgItem(IDC_SizeTempMax)->EnableWindow(TRUE);
	GetDlgItem(IDC_Txt_Seans)->EnableWindow(TRUE);
	GetDlgItem(IDC_Txt_Disk)->EnableWindow(TRUE);

	GetDlgItem(IDC_ZANOS)->EnableWindow(FALSE);
    GetDlgItem(IDC_COD)->EnableWindow(FALSE);
	GetDlgItem(IDC_Txt_Cod)->EnableWindow(FALSE);
	GetDlgItem(IDC_FREQ)->EnableWindow(FALSE);
	GetDlgItem(IDC_Txt_Freq)->EnableWindow(FALSE);
	GetDlgItem(IDC_STEP)->EnableWindow(FALSE);
	GetDlgItem(IDC_Txt_Step)->EnableWindow(FALSE);

	GetDlgItem(IDC_FreeDisk)->EnableWindow(TRUE);
	GetDlgItem(IDC_NumSeans)->EnableWindow(TRUE);

	GetDlgItem(IDC_TXT_PATH)->EnableWindow(TRUE);
	GetDlgItem(IDC_PATH)->EnableWindow(TRUE);

	theApp.dlg->m_OtborDlg.GetDlgItem(IDC_IDEN_OTBOR)->EnableWindow(TRUE);
	theApp.dlg->m_OtborDlg.GetDlgItem(IDC_COD_OTBOR)->EnableWindow(TRUE);
return;	
	
}

BOOL CConfigDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
    theApp.dlg->GetMenu()->EnableMenuItem(ID_DIR_OPEN,MF_GRAYED); 
	theApp.dlg->GetMenu()->EnableMenuItem(ID_FILE_FREQ,MF_GRAYED);
	theApp.dlg->m_OtborDlg.GetDlgItem(IDC_IDEN_OTBOR)->EnableWindow(FALSE);
	theApp.dlg->m_OtborDlg.GetDlgItem(IDC_COD_OTBOR)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_Txt_Speed1)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPEED)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPEED2)->EnableWindow(FALSE);
	GetDlgItem(IDC_TXT_SPEED2)->EnableWindow(FALSE);
	GetDlgItem(IDC_TXT_SPEED)->EnableWindow(FALSE);
		

	GetDlgItem(IDC_Chek_Del)->EnableWindow(FALSE);
//	GetDlgItem(IDC_MinSize)->EnableWindow(FALSE);
	GetDlgItem(IDC_Chek_Max)->EnableWindow(FALSE);
//	GetDlgItem(IDC_MaxSize)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_Txt_Min)->EnableWindow(FALSE);
	GetDlgItem(IDC_SizeTempMin)->EnableWindow(FALSE);
	GetDlgItem(IDC_Txt_Max)->EnableWindow(FALSE);
	GetDlgItem(IDC_SizeTempMax)->EnableWindow(FALSE);

	GetDlgItem(IDC_Txt_Seans)->EnableWindow(FALSE);
	GetDlgItem(IDC_Txt_Disk)->EnableWindow(FALSE);

    GetDlgItem(IDC_ZANOS)->EnableWindow(TRUE);
    GetDlgItem(IDC_COD)->EnableWindow(FALSE);
	GetDlgItem(IDC_FREQ)->EnableWindow(FALSE);
	GetDlgItem(IDC_STEP)->EnableWindow(FALSE);
	GetDlgItem(IDC_TXT_PATH)->EnableWindow(FALSE);
	GetDlgItem(IDC_PATH)->EnableWindow(FALSE);
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CConfigDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	int TargetControl=pWnd->GetDlgCtrlID();
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	switch(TargetControl){
	case IDC_FreeDisk: pDC->SetTextColor(m_ColorFreeDisk); break;
	default :                                            break;
	}	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CConfigDlg::OnZanos() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_Zanos==FALSE)
	{
	 GetDlgItem(IDC_COD)->EnableWindow(FALSE);
	 GetDlgItem(IDC_FREQ)->EnableWindow(FALSE);
	 GetDlgItem(IDC_STEP)->EnableWindow(FALSE);
	}
	
}

void CConfigDlg::OnChekDel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_Chek_Del==TRUE)
	{
	 GetDlgItem(IDC_MinSize)->EnableWindow(TRUE);
		}
	else 
	{
		GetDlgItem(IDC_MinSize)->EnableWindow(FALSE);
		theApp.dlg->Com.AbonDlg->MinSizeFile=0;   
	}
	
}

void CConfigDlg::OnChekMax() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
	if(m_Chek_Max==TRUE)
	{
	 GetDlgItem(IDC_MaxSize)->EnableWindow(TRUE);
	}
	else
	{
        GetDlgItem(IDC_MaxSize)->EnableWindow(FALSE);
	    theApp.dlg->Com.AbonDlg->MaxSizeFile=0;   
	}
	
}
