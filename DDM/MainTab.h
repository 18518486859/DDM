#pragma once
#include "afxcmn.h"

class CMainTab :
	public CTabCtrl
{
public:
	CMainTab();
	~CMainTab();

public:

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

