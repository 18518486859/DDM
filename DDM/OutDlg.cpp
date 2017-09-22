#include "stdafx.h"
#include "OutDlg.h"
#include "Windows.h"


IMPLEMENT_DYNAMIC(COutDlg,CBaseDlg)

COutDlg::COutDlg()
{
	k = 5;
	strOutGrid.Add(L"序号");
	strOutGrid.Add(L"编号");
	strOutGrid.Add(L"品名");
	strOutGrid.Add(L"款号");
	strOutGrid.Add(L"颜色");
	strOutGrid.Add(L"L1");
	strOutGrid.Add(L"L2");
	strOutGrid.Add(L"L3");
	strOutGrid.Add(L"L4");
	strOutGrid.Add(L"L5");
	strOutGrid.Add(L"L6");
	strOutGrid.Add(L"L7");
	strOutGrid.Add(L"L8");
	strOutGrid.Add(L"单位");
	strOutGrid.Add(L"合计");

	intOutGrid.Add(k * 10);
	intOutGrid.Add(k * 18);
	intOutGrid.Add(k * 18);
	intOutGrid.Add(k * 18);
	intOutGrid.Add(k * 18);
	intOutGrid.Add(k * 13);
	intOutGrid.Add(k * 13);
	intOutGrid.Add(k * 13);
	intOutGrid.Add(k * 13);
	intOutGrid.Add(k * 13);
	intOutGrid.Add(k * 13);
	intOutGrid.Add(k * 13);
	intOutGrid.Add(k * 13);
	intOutGrid.Add(k * 10);
	intOutGrid.Add(k * 18);
}


COutDlg::~COutDlg()
{
}


//BEGIN_MESSAGE_MAP(COutDlg, CDialogEx)
//
//	ON_BN_DOUBLECLICKED(IDG_DDMGRID, &CBaseDlg::OnDDMGrid)
//END_MESSAGE_MAP()
BOOL COutDlg::OnInitDialog()
{
	CBaseDlg::OnInitDialog();

	if (m_pGridCtrl == NULL)
	{
		m_pGridCtrl = new CPutInGrid;
		if (!m_pGridCtrl) 
			return false;
	}
	CreateGrid(m_pGridCtrl, 10, &strOutGrid, &intOutGrid);
	m_pGridCtrl->setGridStr(13, L"米");
	return TRUE;  
}

void COutDlg::OnPrintGrid(CDC* pDC)
{
	CString str = L"DingDaMa发料单";
	int rowHeight = 0;
	CString kehu = L"客  户:";
	CString data = L"日  期:";
	CString NO = L"编  号:";
	CSize PaperSize = CSize(pDC->GetDeviceCaps(HORZRES), pDC->GetDeviceCaps(VERTRES));
	int MM = PaperSize.cx / 210;

	//------------------抬头--------------------
	CFont PrinterFont;
	PrinterFont.CreateFont(10*MM, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET,
		OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, L"宋体");
	CFont *pOldFont = pDC->SelectObject(&PrinterFont);
	CSize strSize = pDC->GetTextExtent(str, str.GetLength());
	rowHeight += 10 * MM;
	pDC->TextOut((PaperSize.cx-strSize.cx)/2, rowHeight, str);

	//----------------表头----------------------
	CFont PrinterFont2;
	PrinterFont2.CreateFont(5 * MM, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET,
		OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, L"宋体");
	pDC->SelectObject(&PrinterFont2);
	rowHeight += 15 * MM;
	pDC->TextOut(10 * MM, rowHeight, kehu);
	pDC->TextOut(70 * MM, rowHeight, data);
	pDC->TextOut(140 * MM, rowHeight, NO);

	//--------------------表体------------------------
	int width = 7 * MM;
	int height = 31 * MM, colWidth=10*MM;
	int bian = 1.4*MM;
	CRect rectG, rectT;
	CGridCellBase* pCell;
	CString strCell;
	CFont fontG, fontW;

	fontG.CreateFont(4 * MM, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET,
		OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, L"宋体");
	pDC->SelectObject(&fontG);
	for (int row = 0; row < 11; row++){
		rectG.top = height;
		rectG.bottom = rectG.top + width;
		rectG.left = 10 * MM;
		for (int col = 0; col < intOutGrid.GetCount(); col++){
			pCell = m_pGridCtrl->GetCell(row, col);
			strCell = pCell->GetText();
			rectG.right = rectG.left + intOutGrid[col] * MM/k;
			//pDC->Rectangle(rectG);

			rectT.left = rectG.left + 10;
			rectT.top = rectG.top + bian;
			rectT.right = rectG.right - 10;
			rectT.bottom = rectG.bottom - bian;
			pDC->DrawText(strCell, -1, rectT, DT_CENTER);
			rectG.left = rectG.right;
		}
		height += width;
	}
	height = 31 * MM;
	pDC->MoveTo(10 * MM, height);
	pDC->LineTo(206 * MM, height);
	pDC->LineTo(206 * MM, width * 11 + height);
	pDC->LineTo(10 * MM, width * 11 + height);
	pDC->LineTo(10 * MM,  31 * MM);
	for (int row = 0; row < 11; row++){
		height += width;
		pDC->MoveTo(10*MM,height);
		pDC->LineTo(206 * MM, height);
	}
	for (int col = 0; col < 13; col++){
		colWidth += (intOutGrid[col] / k*MM);
		pDC->MoveTo(colWidth, height - width * 11);
		pDC->LineTo(colWidth, height);
	}

	//-------------------表尾------------------------
	height += 2 * MM;
	pDC->TextOut(10 * MM, height, L"备注:");
	height += 5 * MM;
	pDC->MoveTo(10*MM, height);
	pDC->LineTo(206*MM, height);
	height += 3 * MM;
	
	fontW.CreateFont(6 * MM, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET,
		OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, L"宋体");
	pDC->SelectObject(&fontW);
	pDC->TextOut(11 * MM, height, L"经手人：赵亮    咨询电话：18518486859     领料人：");

	////////////////////////////////////////////////////////////

	/*BOOL SetForm(
		_In_ HANDLE hPrinter,
		_In_ LPTSTR pFormName,
		_In_ DWORD  Level,
		_In_ LPTSTR pForm
		);*/

}
