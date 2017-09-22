// PutInDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DDM.h"
#include "PutInDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "DDMView.h"

// CPutInDlg 对话框

IMPLEMENT_DYNAMIC(CPutInDlg, CDialogEx)

CPutInDlg::CPutInDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPutInDlg::IDD, pParent)
{
	m_pGridCtrl = NULL;
}

CPutInDlg::~CPutInDlg()
{
	if (m_pGridCtrl){
		delete m_pGridCtrl;
	}
}

void CPutInDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DDMDATA, m_DdmData);
	//DDX_Control(pDX, IDC_SAVEPUTINBTN, m_SaveBtn);
	//DDX_Control(pDX, IDC_EXITPUTINBTN, m_ExitBtn);
}

BEGIN_MESSAGE_MAP(CPutInDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SAVEPUTINBTN, &CPutInDlg::OnBnClickedButton1)
	ON_WM_SIZE()
	ON_COMMAND(IDG_DDMGRID, &CPutInDlg::OnIdgDdmgrid)
	ON_BN_CLICKED(IDC_EXITPUTINBTN, &CPutInDlg::OnBnClickedExitputinbtn)
END_MESSAGE_MAP()

// CPutInDlg 消息处理程序

BOOL CPutInDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	

	if (m_pGridCtrl == NULL)
	{
		// Create the Gridctrl object
		m_pGridCtrl = new CPutInGrid;
		if (!m_pGridCtrl) return false;

		// Create the Gridctrl window
		CRect rect;
		GetClientRect(rect);
		m_pGridCtrl->Create(CRect(0, 80, 953, 395), this, IDG_DDMGRID);

		// fill it up with stuff
		m_pGridCtrl->SetEditable(TRUE);
		m_pGridCtrl->EnableDragAndDrop(TRUE);

		try {
			m_pGridCtrl->SetRowCount(11);
			m_pGridCtrl->SetColumnCount(16);
			m_pGridCtrl->SetFixedRowCount(1);
			m_pGridCtrl->SetFixedColumnCount(1);
		}
		catch (CMemoryException* e)
		{
			e->ReportError();
			e->Delete();
			return false;
		}

		// fill rows/cols with text
		for (int row = 0; row < m_pGridCtrl->GetRowCount(); row++)
		for (int col = 0; col < m_pGridCtrl->GetColumnCount(); col++)
		{
			GV_ITEM Item;
			Item.mask = GVIF_TEXT | GVIF_FORMAT;
			Item.row = row;
			Item.col = col;
			if (row < 1) {
				Item.nFormat = DT_CENTER | DT_WORDBREAK;
				if (col == 0) Item.strText = L"序号";
				if (col == 1) Item.strText = L"品名";
				if (col == 2) Item.strText = L"颜色";
				if (col == 3) Item.strText = L"匹/零";
				if (col == 4) Item.strText = L"匹数";
				if (col == 5) Item.strText = L"长度1";
				if (col == 6) Item.strText = L"长度2";
				if (col == 7) Item.strText = L"长度3";
				if (col == 8) Item.strText = L"长度4";
				if (col == 9) Item.strText = L"长度5";
				if (col == 10) Item.strText = L"长度6";
				if (col == 11) Item.strText = L"长度7";
				if (col == 12) Item.strText = L"长度8";
				if (col == 13) Item.strText = L"单位";
				if (col == 14) Item.strText = L"合计";
				if (col == 15) Item.strText = L"备注";


			}
			else if (col < 1) {
				Item.nFormat = DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_NOPREFIX;
				Item.strText.Format(_T("%d"), row);
			}
			else if (/*row>0 &&*/ row%2==0) {
				Item.mask |= GVIF_BKCLR;//背景色 GVIF_FGCLR(前景色) 
				Item.crBkClr = RGB(209, 238, 245);//GetSysColor(COLOR_3DFACE);//自已定 
			}


			m_pGridCtrl->SetItem(&Item);
		}
		for (int i = 1; i > 11; i++){
			m_pGridCtrl->SetItemText(i, 13, L"米");
		}
		int k = 18;
		m_pGridCtrl->SetColumnWidth(0, k * 2);
		m_pGridCtrl->SetColumnWidth(1, k * 4);
		m_pGridCtrl->SetColumnWidth(2, k * 4);
		m_pGridCtrl->SetColumnWidth(3, k * 3);
		m_pGridCtrl->SetColumnWidth(4, k * 3);
		m_pGridCtrl->SetColumnWidth(5, k * 3);
		m_pGridCtrl->SetColumnWidth(6, k * 3);
		m_pGridCtrl->SetColumnWidth(7, k * 3);
		m_pGridCtrl->SetColumnWidth(8, k * 3);
		m_pGridCtrl->SetColumnWidth(9, k * 3);
		m_pGridCtrl->SetColumnWidth(10, k * 3);
		m_pGridCtrl->SetColumnWidth(11, k * 3);
		m_pGridCtrl->SetColumnWidth(12, k * 3);
		m_pGridCtrl->SetColumnWidth(13, k * 3);
		m_pGridCtrl->SetColumnWidth(14, k * 3);
		m_pGridCtrl->SetColumnWidth(15, k * 8);

		for (int i = 0; i < 11; i++){
			m_pGridCtrl->SetRowHeight(i, k + 10);
		}
	}
	for (int i = 1; i < 11; i++){
		m_pGridCtrl->SetItemText(i, 13, L"米");
	}
	return TRUE;  
}

void CPutInDlg::OnBnClickedButton1()//保存按钮
{
	CTime time;
	m_DdmData.GetTime(time);
	CString strTime = time.Format("%Y-%m-%d");

	_variant_t RecordsAffected;
	CString AddSql;
	for (int i = 1; i < 11; i++){
		for (int j = 5; j < 13; j++){
			if (m_pGridCtrl->GetItemText(i, j) != ""){
				AddSql.Format(_T("INSERT INTO DDM2017.dbo.面料(日期,品名,颜色,匹零,匹数,长度) VALUES(%s,'%s','%s','%s',%s,%s)"),
					strTime,
					m_pGridCtrl->GetItemText(i, 1),
					m_pGridCtrl->GetItemText(i, 2),
					m_pGridCtrl->GetItemText(i, 3),
					m_pGridCtrl->GetItemText(i, 4),
					m_pGridCtrl->GetItemText(i, j),
					m_pGridCtrl->GetItemText(i, 15));
				try{
					m_pConnection->Execute((_bstr_t)AddSql, &RecordsAffected, adCmdText);
				
				}
				catch (_com_error* e){
					e->Description();
					AfxMessageBox(_T("添加数据失败！"));
				}
			}
		}
		for (int k = 1; k < 15; k++){
			m_pGridCtrl->SetItemText(i, k, L"");
		}
		m_pGridCtrl->Invalidate();
	}
	//if (m_pGridCtrl->IsModified())
	AfxMessageBox(L"保存完毕！");
}

void CPutInDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	CRect rect;

	if (m_pGridCtrl){
		GetClientRect(rect);
		rect.top = 80;
		rect.bottom -= 80;
		m_pGridCtrl->MoveWindow(rect);
	}
	if (m_SaveBtn){
		GetClientRect(rect);
		rect.left = 30;
		rect.top = rect.bottom - 60;//80
		rect.right = 120;
		rect.bottom = rect.bottom - 20;
		m_SaveBtn.MoveWindow(rect);
	}
	if (m_ExitBtn){
		GetClientRect(rect);
		rect.left = 130;
		rect.top = rect.bottom - 60;//80
		rect.right = 220;
		rect.bottom = rect.bottom - 20;
		m_ExitBtn.MoveWindow(rect);
	}
}

void CPutInDlg::OnIdgDdmgrid()
{
	float d=0;
	CString str;
	CCellID m_cell;
	m_cell = m_pGridCtrl->GetFocusCell();
	int col = m_cell.col, row = m_cell.row;

	if (col > 4 && col < 13){
		for (int i = 5; i < 13; i++){
			str = m_pGridCtrl->GetItemText(row, i);
			d += _ttof(str);
		}
		if (d>0){
			d += 0.05;		//四舍五入
			str.Format(L"%f", d);
			str = str.Left(str.GetLength() - 5);
			m_pGridCtrl->SetItemText(row, 14, str);
			m_pGridCtrl->Invalidate();
		}
	}
}

void CPutInDlg::OnBnClickedExitputinbtn()
{
	CMainFrame* frame = (CMainFrame*)AfxGetMainWnd();
	CDDMView* pView = (CDDMView*)frame->GetActiveView();
	pView->ExitDlg();
}