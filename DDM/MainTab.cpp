#include "stdafx.h"
#include "MainTab.h"


CMainTab::CMainTab()
{
}


CMainTab::~CMainTab()
{

}
BEGIN_MESSAGE_MAP(CMainTab, CTabCtrl)
	ON_WM_SIZE()
	ON_WM_CREATE()
END_MESSAGE_MAP()


void CMainTab::OnSize(UINT nType, int cx, int cy)
{
	CTabCtrl::OnSize(nType, cx, cy);

	//CRect rect;
	//int i=0;
	//if (i>1){     //��һ�ε��ô˴�������쳣
	//	if (FromHandle(m_pNowDlg)){
	//		GetClientRect(rect);
	//		rect.top += 25;
	//		rect.right -= 3;
	//		rect.left += 3;
	//		rect.bottom -= 10;
	//		//FromHandle(m_Tab.m_pNowDlg)->
	//		SetWindowPos(this, 0, rect.top, rect.left, rect.right, rect.bottom);
	//		//FromHandle(m_pNowDlg)->MoveWindow(rect);
	//	}
	//	else{
	//		i++;
	//	}
	//}
	// TODO:  �ڴ˴������Ϣ����������
}





int CMainTab::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTabCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}
