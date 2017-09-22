#pragma once
//#include "DDMView.h"

// CNavigetionDlg 对话框

class CNavigetionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNavigetionDlg)

public:
	CNavigetionDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNavigetionDlg();

// 对话框数据
	enum { IDD = IDD_NAVIGETION_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	CDDMView* pView;

public:
	afx_msg void OnBnClickedPutinBtn();
	afx_msg void OnBnClickedPutinBtn2();
	afx_msg void OnBnClickedOutBtn();
	virtual BOOL OnInitDialog();
};
