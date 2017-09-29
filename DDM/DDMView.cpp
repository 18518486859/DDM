
// DDMView.cpp : CDDMView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "DDM.h"
#endif

#include "DDMDoc.h"
#include "DDMView.h"
#include "PutInDlg.h"
#include "BaseDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
CPrintPreviewState 


// CDDMView

IMPLEMENT_DYNCREATE(CDDMView, CView)

BEGIN_MESSAGE_MAP(CDDMView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_NOTIFY(TCN_SELCHANGE, IDT_DDMTAB, &CDDMView::OnTcnSelchangeTab1)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CDDMView ����/����

CDDMView::CDDMView()
{
	// TODO:  �ڴ˴���ӹ������
	i = 0;
}

CDDMView::~CDDMView()
{
	/*if (*m_Tab)
		delete m_Tab;*/
}

BOOL CDDMView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CDDMView ����

void CDDMView::OnDraw(CDC* pDC)
{
	CDDMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) return;

	if (LOWORD(GetCurrentMessage()->wParam) == ID_FILE_PRINT) ((CBaseDlg*)m_pNowDlg)->OnPrintGrid(pDC);
	
}


// CDDMView ��ӡ

BOOL CDDMView::OnPreparePrinting(CPrintInfo* pInfo)
{
	
	return DoPreparePrinting(pInfo);
}

void CDDMView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	
}

void CDDMView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CDDMView ���

#ifdef _DEBUG
void CDDMView::AssertValid() const
{
	CView::AssertValid();
}

void CDDMView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDDMDoc* CDDMView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDDMDoc)));
	return (CDDMDoc*)m_pDocument;
}
#endif //_DEBUG


// CDDMView ��Ϣ�������


void CDDMView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	//��ʼ�����ݿ�
	if (!ADOInit()){
		AfxMessageBox(L"���ݿ��ʼ��ʧ�ܣ�");	
	}

	CRect rect;
	GetClientRect(rect);
	rect.right -= 3;
	rect.left += 3;
	rect.bottom -= 3;
	m_Tab.Create(WS_CHILD | WS_VISIBLE | TCS_BUTTONS, rect, this, IDT_DDMTAB);
	m_Tab.InsertItem(0, L"����ͼ");

	m_Nav.Create(IDD_NAVIGETION_DLG, &m_Tab);
	rect.top += 40;
	rect.right -= 6;
	rect.left += 6;
	rect.bottom -= 6;
	m_Nav.MoveWindow(rect);
	m_Nav.ShowWindow(true);

	TabArray.InsertAt(0,&m_Nav);
	m_pNowDlg = &m_Nav;
	TabDlg.InsertAt(0,&m_Nav);
}

void CDDMView::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	int it = m_Tab.GetCurSel();
	m_pNowDlg->ShowWindow(false);
	TabDlg[it]->ShowWindow(true);
	m_pNowDlg = TabDlg[it];
	if (TabDlg[it] != &m_Nav){
		TabArray.InsertAt(0, TabDlg[it]);
	}
	else{
		TabArray.RemoveAll();
		TabArray.InsertAt(0, &m_Nav);
	}

	CRect rect;
	GetClientRect(rect);
	rect.top += 25;
	rect.right -= 3;
	rect.left += 3;
	rect.bottom -= 10;
	m_pNowDlg->MoveWindow(rect);

	*pResult = 0;
}

void CDDMView::OnSize(UINT nType, int cx, int cy)
{
	
	CView::OnSize(nType, cx, cy);
	CRect rect;
	if (m_Tab){
		GetClientRect(rect);
		//rect.top += 15;
		rect.right -= 3;
		rect.left += 3;
		rect.bottom -= 3;
		m_Tab.MoveWindow(rect);
	}	
	if (i>1){     //��һ�ε��ô˴�������쳣
			GetClientRect(rect);
			rect.top += 25;
			rect.right -= 3;
			rect.left += 3;
			rect.bottom -= 10;
			m_pNowDlg->MoveWindow(rect);
	}
	else{
		i++;
	}
}


BOOL CDDMView::ADOInit()
{
	::WritePrivateProfileStringW(_T("DDM"), _T("HAIMING"), _T("Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=Ddm2017;Data Source=HAIMING;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=HAIMING;Use Encryption for Data=False;Tag with column collation when possible=False"), _T(".\\DDM.ini"));//д���ַ���
	::WritePrivateProfileStringW(_T("DDM"), _T("DMA"), _T("Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=DDM;Data Source=DMA\\DDM;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=DMA;Use Encryption for Data=False;Tag with column collation when possible=False;"), _T(".\\DDM.ini"));//д���ַ���
	try{
		CString strBasedata;
		DWORD d = 32;
		TCHAR strHostName[64];
		GetComputerNameW(strHostName, &d);
		if (CString(strHostName) == "HAIMING"){
			::GetPrivateProfileString(_T("DDM"), _T("HAIMING"), _T("û���ҵ���ȷ�������ļ�"), strBasedata.GetBuffer(MAX_PATH), MAX_PATH, _T(".\\DDM.ini"));
			strBasedata.ReleaseBuffer();
		}
		else if (CString(strHostName) == L"DMA"){
			::GetPrivateProfileString(_T("DDM"), _T("DMA"), _T("û���ҵ���ȷ�������ļ�"), strBasedata.GetBuffer(MAX_PATH), MAX_PATH, _T(".\\DDM.ini"));
			strBasedata.ReleaseBuffer();
		}
		//AfxMessageBox(LPCTSTR(strBasedata));
		CoInitialize(NULL);
		m_pConnection = _ConnectionPtr(__uuidof(Connection));
		m_pConnection->ConnectionString = LPCTSTR(strBasedata);//L"Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=Ddm2017;Data Source=HAIMING;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=HAIMING;Use Encryption for Data=False;Tag with column collation when possible=False";
		m_pConnection->Open("", "", "", adConnectUnspecified);
		AfxMessageBox(_T("���ݿ����ӳɹ���"));
	}
	catch (_com_error e){
		e.Description();
		return FALSE;
	}
	return true;
}

void CDDMView::CreateDlg(CDialog* Dlg, LPCTSTR str)
{
	int i = m_Tab.GetItemCount();
	m_Tab.InsertItem(i, str);
	m_Tab.SetCurSel(i);
	Dlg ->Create(IDD_PUTIN_DLG, &m_Tab);;
	CRect rect;
	GetClientRect(rect);
	rect.top += 40;
	rect.right -= 6;
	rect.left += 6;
	rect.bottom -= 6;
	Dlg->MoveWindow(rect);
	m_pNowDlg->ShowWindow(false);
	Dlg->ShowWindow(true);
	m_pNowDlg = Dlg;
	TabDlg.Add(Dlg);
	TabArray.InsertAt(0,Dlg);
}

void CDDMView::ExitDlg()
{
	int i = m_Tab.GetCurSel();
	CDialog* pDia = TabDlg[i];
	delete TabDlg[i];
	TabDlg.RemoveAt(i);
	m_Tab.DeleteItem(i);
	for (int f = TabArray.GetCount() - 1; f >= 0; f--){
		if (TabArray[f] == pDia){
			TabArray.RemoveAt(f);
		}
		
	}

	for (int s = 0; s < TabDlg.GetCount(); s++){
		if (TabArray[0] == TabDlg[s]){
			m_Tab.SetCurSel(s);
			TabDlg[s]->ShowWindow(true);
			m_pNowDlg = TabDlg[s];
			return;
		}
	}
	
}

