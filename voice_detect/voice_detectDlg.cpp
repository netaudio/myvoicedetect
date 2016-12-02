
// voice_detectDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "voice_detect.h"
#include "voice_detectDlg.h"
#include "WavData.h"
#include "Preprocess.h"
#include "Complex.h"
#include "DataProcess.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// Cvoice_detectDlg 对话框




Cvoice_detectDlg::Cvoice_detectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cvoice_detectDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cvoice_detectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cvoice_detectDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// Cvoice_detectDlg 消息处理程序

BOOL Cvoice_detectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CWavData wavData1("../wav/b8k.pcm");
	vector<double> vecNormalizeData1;
	vecNormalizeData1 = wavData1.getNormalizedData();
	vector<vector<double>> mfcc1 = CDataProcess::getMfcc(vecNormalizeData1);

	CWavData wavData2("../wav/c8k.pcm");
	vector<double> vecNormalizeData2;
	vecNormalizeData2 = wavData2.getNormalizedData();
	vector<vector<double>> mfcc2 = CDataProcess::getMfcc(vecNormalizeData2);
	
	double dis1 = CDataProcess::getDTW(mfcc1,mfcc2);
	double meanErr1 = dis1 * 2 / (mfcc1.size() + mfcc2.size());

	vector<double> vecHighpass = CPreprocess::highpass(vecNormalizeData1);

	CComplex c1(2,3);
	CComplex c2(4,5);
	CComplex c3 = CComplex::add(c1,c2);
	CComplex c4 = CComplex::multiply(c1,c2);
	CComplex c5 = CComplex::minus(c1,c2);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cvoice_detectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cvoice_detectDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cvoice_detectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

