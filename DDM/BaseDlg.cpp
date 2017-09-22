// BaseDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DDM.h"
#include "BaseDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "DDMView.h"

// CBaseDlg 对话框

IMPLEMENT_DYNAMIC(CBaseDlg, CDialogEx)

CBaseDlg::CBaseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBaseDlg::IDD, pParent)
{
	m_pGridCtrl = NULL;

}

CBaseDlg::~CBaseDlg()
{
	if (m_pGridCtrl){
		delete m_pGridCtrl;
	}
}

void CBaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBaseDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SAVEBTN, &CBaseDlg::OnBnClickedSavebtn)
	ON_BN_CLICKED(IDC_EXITBTN, &CBaseDlg::OnBnClickedExitbtn)
	ON_WM_SIZE()
	ON_COMMAND(IDG_DDMGRID, &CBaseDlg::OnDDMGrid)
	ON_BN_CLICKED(IDC_PRINTBTN,&CBaseDlg::OnBnClickedPrintbtn)
END_MESSAGE_MAP()

BOOL CBaseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	m_ExitBtn.Create(L"退出", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(0, 0, 5, 5), this, IDC_EXITBTN);
	m_SaveBtn.Create(L"保存", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(0, 0, 5, 5), this, IDC_SAVEBTN);
	m_PrintBtn.Create(L"打印",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(0, 0, 5, 5), this, IDC_PRINTBTN);
	
	return TRUE;  
}

// CBaseDlg 消息处理程序
void CBaseDlg::OnBnClickedSavebtn()
{
	CTime time;
	m_DdmDate.GetTime(time);
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

void CBaseDlg::OnBnClickedExitbtn()
{
	CMainFrame* frame = (CMainFrame*)AfxGetMainWnd();
	CDDMView* pView = (CDDMView*)frame->GetActiveView();
	pView->ExitDlg();
}

void CBaseDlg::OnSize(UINT nType, int cx, int cy)
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
	if (m_PrintBtn){
		GetClientRect(rect);
		rect.left = 230;
		rect.top = rect.bottom - 60;//80
		rect.right = 320;
		rect.bottom = rect.bottom - 20;
		m_PrintBtn.MoveWindow(rect);
	}
}

void CBaseDlg::OnDDMGrid()
{
	float d = 0;
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


BOOL CBaseDlg::CreateGrid(CPutInGrid* pGrid, int row, CStringArray *strA, CArray<int, int> *iG)
{
	int colNumber = (*strA).GetCount();
	row++;
		pGrid->Create(CRect(0, 0, 5, 5), this, IDG_DDMGRID);
		// fill it up with stuff
		pGrid->SetEditable(TRUE);
		pGrid->EnableDragAndDrop(TRUE);

		try {
			pGrid->SetRowCount(row);
			pGrid->SetColumnCount(colNumber);
			pGrid->SetFixedRowCount(1);
			pGrid->SetFixedColumnCount(1);
		}
		catch (CMemoryException* e)
		{
			e->ReportError();
			e->Delete();
			return false;
		}
		// fill rows/cols with text
		GV_ITEM Item;
		Item.mask = GVIF_TEXT | GVIF_FORMAT;
		Item.nFormat = DT_CENTER | DT_WORDBREAK;
		
		for (int row = 0; row < pGrid->GetRowCount(); row++)
		for (int col = 0; col < pGrid->GetColumnCount(); col++)
		{
			GV_ITEM Item;
			Item.mask = GVIF_TEXT | GVIF_FORMAT;
			Item.row = row;
			Item.col = col;
			if (col < 1) {
				Item.nFormat = DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_NOPREFIX;
				Item.strText.Format(_T("%d"), row);
			}
			else if (row % 2 == 0 && row>0) {
				Item.mask |= GVIF_BKCLR;//背景色 GVIF_FGCLR(前景色) 
				Item.crBkClr = RGB(209, 238, 245);//GetSysColor(COLOR_3DFACE);//自已定 
			}
			pGrid->SetItem(&Item);
		}
		for (int i = 0; i < (*iG).GetCount(); i++){
			pGrid->SetColumnWidth(i, (*iG)[i]);
		}

		for (int i = 0; i < row; i++){
			
			pGrid->SetRowHeight(i, 28);
		}
	for (int c = 0; c < colNumber; c++){
		Item.row = 0;
		Item.col = c;
		Item.strText = ((*strA)[c]);
		pGrid->SetItem(&Item);
	}
}

void CBaseDlg::OnBnClickedPrintbtn(){

	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CDDMView* pView = (CDDMView*)pFrame->GetActiveView();
	HWND HView = pView->m_hWnd;
	::PostMessage(HView, WM_COMMAND, ID_FILE_PRINT,NULL);


	
	
}

	// 具体的页面绘制函数
void CBaseDlg::OnPrintGrid(CDC* pDC)
{
	AfxMessageBox(L"gooooooo");
}

