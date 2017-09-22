
// DDMView.h : CDDMView 类的接口
//

#pragma once
#include "MainTab.h"
#include "PutInDlg.h"
#include "DDMDoc.h"
#include "NavigetionDlg.h"


class CDDMView : public CView
{
protected: // 仅从序列化创建
	CDDMView();
	DECLARE_DYNCREATE(CDDMView)

	// 特性
public:
	CDDMDoc* GetDocument() const;

	// 成员
public:
	
	CMainTab			m_Tab;;
	CNavigetionDlg		m_Nav;
	_ConnectionPtr m_pConnection;//连接access数据库的链接对象  
	_RecordsetPtr m_pRecordset;//结果集对象  
	int i;
	CArray<CDialog*, CDialog*> TabDlg;	//保存创建的对话框
	CDialog* m_pNowDlg;				//现在显示的对话框
	CArray<CDialog*, CDialog*> TabArray;	//保存对话框的显示次序

public:
	void ExitDlg();
	friend class CPutInDlg;
	friend class CNavigetionDlg;
	friend class COutDlg;



	// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// 实现
public:
	virtual ~CDDMView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	BOOL ADOInit();
	void CreateDlg(CDialog* dlg, LPCTSTR str);
};

#ifndef _DEBUG  // DDMView.cpp 中的调试版本
inline CDDMDoc* CDDMView::GetDocument() const
   { return reinterpret_cast<CDDMDoc*>(m_pDocument); }
#endif

