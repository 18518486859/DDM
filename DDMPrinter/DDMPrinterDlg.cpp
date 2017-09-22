
// DDMPrinterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DDMPrinter.h"
#include "DDMPrinterDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDDMPrinterDlg 对话框



CDDMPrinterDlg::CDDMPrinterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDDMPrinterDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDDMPrinterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDDMPrinterDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CDDMPrinterDlg 消息处理程序

BOOL CDDMPrinterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MAXIMIZE);

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDDMPrinterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDDMPrinterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDDMPrinterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CView::DoPrintPreview(UINT nIDResource, CView* pPrintView,
	CRuntimeClass* pPreviewViewClass, CPrintPreviewState* pState)
{
	ASSERT_VALID_IDR(nIDResource);//资源是否有效
	ASSERT_VALID(pPrintView);
	ASSERT(pPreviewViewClass != NULL);
	ASSERT(pPreviewViewClass->IsDerivedFrom(RUNTIME_CLASS(CPreviewView)));
	ASSERT(pState != NULL);

	CWnd* pMainWnd = GetParentFrame();//则返回框架窗口的指针；否则返回NULL。

	//DYNAMIC_DOWNCAST(CFrameWnd, pMainWnd)
	//如果pMainWnd指针所指向的对象是CFrameWnd类型的，就返回这个指针。否则返回NULL
	if (DYNAMIC_DOWNCAST(CFrameWnd, pMainWnd) == NULL)
	{
		// 如果不是窗体，我们会尝获取试主窗口指针
		pMainWnd = AfxGetMainWnd();
	}

	//CFrameWnd* pParent = STATIC_DOWNCAST(CFrameWnd, pMainWnd)
	//将pMainWnd指针取出来转换成CFrameWnd类型并赋值给pParent 。
	CFrameWnd* pParent = STATIC_DOWNCAST(CFrameWnd, pMainWnd);
	ASSERT_VALID(pParent);

	CCreateContext context;
	context.m_pCurrentFrame = pParent;
	context.m_pCurrentDoc = GetDocument();
	context.m_pLastView = this;

	// Create the preview view object
	CPreviewView* pView = (CPreviewView*)pPreviewViewClass->CreateObject();
	if (pView == NULL)
	{
		TRACE(traceAppMsg, 0, "Error: Failed to create preview view.\n");
		return FALSE;
	}
	ASSERT_KINDOF(CPreviewView, pView);
	pView->m_pPreviewState = pState;        // save pointer

	pParent->OnSetPreviewMode(TRUE, pState);    // Take over Frame Window

	// Create the toolbar from the dialog resource
	pView->m_pToolBar = new CDialogBar;

	CFrameWnd *pParentFrame = pParent->GetActiveFrame();
	ASSERT(pParentFrame);

	COleIPFrameWnd *pInPlaceFrame = DYNAMIC_DOWNCAST(COleIPFrameWnd, pParentFrame);
	if (pInPlaceFrame)
	{
		CDocument *pViewDoc = GetDocument();
		COleServerDoc *pDoc = DYNAMIC_DOWNCAST(COleServerDoc, pViewDoc);
		if (!pDoc)
		{
			pParent->OnSetPreviewMode(FALSE, pState);   // restore Frame Window
			delete pView->m_pToolBar;       // not autodestruct yet
			pView->m_pToolBar = NULL;
			pView->m_pPreviewState = NULL;  // do not delete state structure
			delete pView;
			return FALSE;
		}

		CFrameWnd *pFrame = (CFrameWnd*)pInPlaceFrame->GetDocFrame();
		if (!pFrame)
			pFrame = pInPlaceFrame->GetMainFrame();
		ASSERT(pFrame != NULL);

		// hide existing toolbars.
		pDoc->OnDocWindowActivate(FALSE);

		if (pFrame && pView->m_pToolBar->Create(pFrame,
			ATL_MAKEINTRESOURCE(nIDResource), CBRS_TOP, AFX_IDW_PREVIEW_BAR))
		{
			// automatic cleanup
			pView->m_pToolBar->m_bAutoDelete = TRUE;

			// Tell the toolbar where to route command messages
			pView->m_pToolBar->SetInPlaceOwner(pInPlaceFrame);

			// now, merge the print preview toolbar into the
			// appropriate frame which would be the document
			// frame for an mdi container or the app frame for
			// an sdi container.
			CRect rcBorder;
			BOOL bFrame = FALSE;
			CComPtr<IOleInPlaceUIWindow> spIPUIWindow;

			if (FAILED(pInPlaceFrame->GetInPlaceDocFrame(&spIPUIWindow)))
			{
				pInPlaceFrame->GetInPlaceFrame(&spIPUIWindow);
				bFrame = TRUE;
			}
			ASSERT(spIPUIWindow);
			if (spIPUIWindow)
			{
				spIPUIWindow->GetBorder(rcBorder);
				pDoc->OnResizeBorder(rcBorder, spIPUIWindow, bFrame);
			}
			pInPlaceFrame->SetPreviewMode(TRUE);
		}
		else
		{
			TRACE(traceAppMsg, 0, "Error: Preview could not create toolbar dialog.\n");
			pParent->OnSetPreviewMode(FALSE, pState);   // restore Frame Window
			delete pView->m_pToolBar;       // not autodestruct yet
			pView->m_pToolBar = NULL;
			pView->m_pPreviewState = NULL;  // do not delete state structure
			delete pView;
			return FALSE;
		}
	}
	else
	{
		if (!pView->m_pToolBar->Create(pParent, ATL_MAKEINTRESOURCE(nIDResource),
			CBRS_TOP, AFX_IDW_PREVIEW_BAR))
		{
			TRACE(traceAppMsg, 0, "Error: Preview could not create toolbar dialog.\n");
			pParent->OnSetPreviewMode(FALSE, pState);   // restore Frame Window
			delete pView->m_pToolBar;       // not autodestruct yet
			pView->m_pToolBar = NULL;
			pView->m_pPreviewState = NULL;  // do not delete state structure
			delete pView;
			return FALSE;
		}
		pView->m_pToolBar->m_bAutoDelete = TRUE;    // automatic cleanup
	}

	// Create the preview view as a child of the App Main Window.  This
	// is a sibling of this view if this is an SDI app.  This is NOT a sibling
	// if this is an MDI app.

	if (!pView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), pParent, AFX_IDW_PANE_FIRST, &context))
	{
		TRACE(traceAppMsg, 0, "Error: couldn't create preview view for frame.\n");
		pParent->OnSetPreviewMode(FALSE, pState);   // restore Frame Window
		pView->m_pPreviewState = NULL;  // do not delete state structure
		delete pView;
		return FALSE;
	}

	// Preview window shown now
	pState->pViewActiveOld = pParent->GetActiveView();
	CView* pActiveView = pParent->GetActiveFrame()->GetActiveView();

	if (pActiveView != NULL)
		pActiveView->OnActivateView(FALSE, pActiveView, pActiveView);

	if (!pView->SetPrintView(pPrintView))
	{
		pView->OnPreviewClose();
		return TRUE;            // signal that OnEndPrintPreview was called
	}

	pParent->SetActiveView(pView);  // set active view - even for MDI

	pView->m_pToolBar->SendMessage(WM_IDLEUPDATECMDUI, (WPARAM)TRUE);
	pParent->RecalcLayout();            // position and size everything
	pParent->UpdateWindow();

	return TRUE;
}
