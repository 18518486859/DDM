
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

#define RUNTIME_CLASS(CPreviewView) (CPreviewView::GetThisClass())
	//m_PWnd.CreateEx(WS_CHILD | WS_VISIBLE, NULL, L"paper", NULL, CRect(30, 30, 500, 500), this, 201709);
	//m_PWnd.CreateEx(WS_EX_MDICHILD, L"", L"ahh", WS_CHILD | WS_VISIBLE, CRect(30, 30, 500, 500), this, 201709);
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

		CPaintDC dc(this); // 用于绘制的设备上下文
		/*CRect   rect;
		GetClientRect(rect);
		dc.FillSolidRect(rect, RGB(229, 233,237));

		CRect rect2(30, 30, 500, 500);
		dc.Rectangle(rect2);
		
		CBrush brush(HS_HORIZONTAL, RGB(150,150,150));
		dc.FrameRect(rect2,&brush);*/
		//dc.SelectObject(CBrush(RGB(255, 125, 20)));
		//dc.Rectangle(30, 30, 500, 500);

}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDDMPrinterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

