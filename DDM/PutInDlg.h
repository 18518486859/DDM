#pragma once
#include "PutInGrid.h"
#include "afxdtctl.h"
#include "afxwin.h"
#include "resource.h"

// CPutInDlg 对话框

class CPutInDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPutInDlg)

public:
	CPutInDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPutInDlg();

// 对话框数据
	enum { IDD = IDD_PUTIN_DLG };

//成员属性
public:
	CPutInGrid * m_pGridCtrl;
	_ConnectionPtr m_pConnection;//连接access数据库的链接对象  
	_RecordsetPtr m_pRecordset;
	CDateTimeCtrl m_DdmData;
	CButton m_SaveBtn;// 面料入库保存操作
	CButton m_ExitBtn;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnIdgDdmgrid();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedExitputinbtn();
};
