#pragma once
#include "BaseDlg.h"
class COutDlg :
	public CBaseDlg
{
	DECLARE_DYNAMIC(COutDlg)
public:
	COutDlg();
	~COutDlg();
	virtual BOOL OnInitDialog();
public:
	CStringArray strOutGrid;
	CArray<int, int> intOutGrid;
	int k;//����п��׼
	virtual void OnPrintGrid(CDC* /*pDC*/);
	BOOL Draw(CDC* pDC, int nRow, int nCol, CRect rect, BOOL bEraseBkgnd = TRUE);

};

