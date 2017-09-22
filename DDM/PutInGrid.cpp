#include "stdafx.h"
#include "PutInGrid.h"


CPutInGrid::CPutInGrid()
{
}


CPutInGrid::~CPutInGrid()
{
}
BEGIN_MESSAGE_MAP(CPutInGrid, CGridCtrl)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


void CPutInGrid::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
	if (nChar == VK_TAB){
		float d = 0;
		CString str;
		CCellID m_cell;
		m_cell = GetFocusCell();
		int col = m_cell.col, row = m_cell.row;

		if (col > 4 && col < 13){
			for (int i = 5; i < 13; i++){
				str = GetItemText(row, i);
				d += _ttof(str);
			}
			if (d>0){
				d += 0.05;		//ËÄÉáÎåÈë
				str.Format(L"%f", d);
				str = str.Left(str.GetLength() - 5);
				SetItemText(row, 14, str);
				AfxMessageBox(LPCTSTR(str));
				Invalidate();
			}
		//AfxMessageBox(L"good");
		}
	}
	CGridCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

int CPutInGrid::setGridStr( int col, LPCTSTR str)
{
	for (int i = 1; i > GetRowCount(); i++){
		SetItemText(i, col, str);
	}
	return 0;
}
void CPutInGrid::OnDraw(CDC* pDC){

	CGridCtrl::OnDraw(pDC);

}