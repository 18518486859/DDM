#pragma once
#include "PutInGrid.h"
#include "afxdtctl.h"
#include "afxwin.h"
#include "resource.h"

// CPutInDlg �Ի���

class CPutInDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPutInDlg)

public:
	CPutInDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPutInDlg();

// �Ի�������
	enum { IDD = IDD_PUTIN_DLG };

//��Ա����
public:
	CPutInGrid * m_pGridCtrl;
	_ConnectionPtr m_pConnection;//����access���ݿ�����Ӷ���  
	_RecordsetPtr m_pRecordset;
	CDateTimeCtrl m_DdmData;
	CButton m_SaveBtn;// ������Ᵽ�����
	CButton m_ExitBtn;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnIdgDdmgrid();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedExitputinbtn();
};
