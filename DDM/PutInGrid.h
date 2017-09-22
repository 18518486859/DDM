#pragma once
#include "GridCtrl.h"
class CPutInGrid :
	public CGridCtrl
{
public:
	CPutInGrid();
	~CPutInGrid();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	int setGridStr(int col, LPCTSTR str);
	void OnDraw(CDC* pDC);
public:
	friend class COutDlg;
	friend class CDDMView;
};

