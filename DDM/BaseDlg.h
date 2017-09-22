#pragma once
#include "PutInGrid.h"
#include "resource.h"
#include "afxdtctl.h"
#include "afxwin.h"
// CBaseDlg �Ի���

class CBaseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBaseDlg)

public:
	CBaseDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBaseDlg();
	enum { IDD = IDD_BASE_DLG };
public:
	CPutInGrid * m_pGridCtrl;
	_ConnectionPtr m_pConnection;//����access���ݿ�����Ӷ���  
	_RecordsetPtr m_pRecordset;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSavebtn();
	afx_msg void OnBnClickedExitbtn();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedPrintbtn();
	afx_msg void OnDDMGrid();
	CDateTimeCtrl m_DdmDate;
	CButton m_ExitBtn;
	CButton m_SaveBtn;
	CButton m_PrintBtn;
	BOOL	m_bPrintIf=FALSE;
	virtual void OnPrintGrid(CDC* /*pDC*/);
	BOOL CreateGrid(CPutInGrid* pGrid, int row, CStringArray *strA, CArray<int, int> *iG);
};
