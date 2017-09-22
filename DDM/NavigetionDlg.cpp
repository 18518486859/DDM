// NavigetionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DDM.h"
#include "NavigetionDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "DDMView.h"
#include "OutDlg.h"


// CNavigetionDlg 对话框

IMPLEMENT_DYNAMIC(CNavigetionDlg, CDialogEx)

CNavigetionDlg::CNavigetionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNavigetionDlg::IDD, pParent)
{
	
}

CNavigetionDlg::~CNavigetionDlg()
{
}

void CNavigetionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNavigetionDlg, CDialogEx)
	ON_BN_CLICKED(IDC_PUTIN_BTN, &CNavigetionDlg::OnBnClickedPutinBtn)
	ON_BN_CLICKED(IDC_PUTIN_BTN2, &CNavigetionDlg::OnBnClickedPutinBtn2)
	ON_BN_CLICKED(IDC_OUT_BTN, &CNavigetionDlg::OnBnClickedOutBtn)
END_MESSAGE_MAP()


// CNavigetionDlg 消息处理程序


void CNavigetionDlg::OnBnClickedPutinBtn()
{
	CMainFrame* frame = (CMainFrame*)AfxGetMainWnd();
	CDDMView* pView = (CDDMView*)frame->GetActiveView();
	CPutInDlg* Dlg = new CPutInDlg;
	pView->CreateDlg(Dlg, L"入库单");
}


void CNavigetionDlg::OnBnClickedPutinBtn2()
{
	DWORD d = 32;
	TCHAR str[64];
	GetComputerNameW(str,&d);
	AfxMessageBox(str);
}


void CNavigetionDlg::OnBnClickedOutBtn()
{
	CMainFrame* frame = (CMainFrame*)AfxGetMainWnd();
	CDDMView* pView = (CDDMView*)frame->GetActiveView();
	COutDlg* Dlg = new COutDlg;
	pView->CreateDlg(Dlg, L"出库单");
}

BOOL CNavigetionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	/*CMainFrame* frame = (CMainFrame*)AfxGetMainWnd();
	CDDMView* pView = (CDDMView*)frame->GetActiveView();*/

	return TRUE;  
}



