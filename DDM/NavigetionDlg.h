#pragma once
//#include "DDMView.h"

// CNavigetionDlg �Ի���

class CNavigetionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNavigetionDlg)

public:
	CNavigetionDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNavigetionDlg();

// �Ի�������
	enum { IDD = IDD_NAVIGETION_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	CDDMView* pView;

public:
	afx_msg void OnBnClickedPutinBtn();
	afx_msg void OnBnClickedPutinBtn2();
	afx_msg void OnBnClickedOutBtn();
	virtual BOOL OnInitDialog();
};
