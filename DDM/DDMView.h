
// DDMView.h : CDDMView ��Ľӿ�
//

#pragma once
#include "MainTab.h"
#include "PutInDlg.h"
#include "DDMDoc.h"
#include "NavigetionDlg.h"


class CDDMView : public CView
{
protected: // �������л�����
	CDDMView();
	DECLARE_DYNCREATE(CDDMView)

	// ����
public:
	CDDMDoc* GetDocument() const;

	// ��Ա
public:
	
	CMainTab			m_Tab;;
	CNavigetionDlg		m_Nav;
	_ConnectionPtr m_pConnection;//����access���ݿ�����Ӷ���  
	_RecordsetPtr m_pRecordset;//���������  
	int i;
	CArray<CDialog*, CDialog*> TabDlg;	//���洴���ĶԻ���
	CDialog* m_pNowDlg;				//������ʾ�ĶԻ���
	CArray<CDialog*, CDialog*> TabArray;	//����Ի������ʾ����

public:
	void ExitDlg();
	friend class CPutInDlg;
	friend class CNavigetionDlg;
	friend class COutDlg;



	// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// ʵ��
public:
	virtual ~CDDMView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	BOOL ADOInit();
	void CreateDlg(CDialog* dlg, LPCTSTR str);
};

#ifndef _DEBUG  // DDMView.cpp �еĵ��԰汾
inline CDDMDoc* CDDMView::GetDocument() const
   { return reinterpret_cast<CDDMDoc*>(m_pDocument); }
#endif

