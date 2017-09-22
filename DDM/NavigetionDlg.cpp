// NavigetionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DDM.h"
#include "NavigetionDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "DDMView.h"
#include "OutDlg.h"


// CNavigetionDlg �Ի���

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


// CNavigetionDlg ��Ϣ�������


void CNavigetionDlg::OnBnClickedPutinBtn()
{
	CMainFrame* frame = (CMainFrame*)AfxGetMainWnd();
	CDDMView* pView = (CDDMView*)frame->GetActiveView();
	CPutInDlg* Dlg = new CPutInDlg;
	pView->CreateDlg(Dlg, L"��ⵥ");
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
	pView->CreateDlg(Dlg, L"���ⵥ");
}

BOOL CNavigetionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	/*CMainFrame* frame = (CMainFrame*)AfxGetMainWnd();
	CDDMView* pView = (CDDMView*)frame->GetActiveView();*/

	return TRUE;  
}



