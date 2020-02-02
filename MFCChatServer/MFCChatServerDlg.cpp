
// MFCChatServerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCChatServer.h"
#include "MFCChatServerDlg.h"
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
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCChatServerDlg 对话框



CMFCChatServerDlg::CMFCChatServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCHATSERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCChatServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MOSG_LIST, m_list);
	DDX_Control(pDX, IDC_COLOER_COMBO, m_WordColoerCombo);
}

BEGIN_MESSAGE_MAP(CMFCChatServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_STATAT_BUTTON, &CMFCChatServerDlg::OnBnClickedStatatButton)
	ON_BN_CLICKED(IDC_SENT_BTN, &CMFCChatServerDlg::OnBnClickedSentBtn)
	ON_BN_CLICKED(IDC_CLEARMSG_BTN, &CMFCChatServerDlg::OnBnClickedClearmsgBtn)
	ON_BN_CLICKED(IDC_STOP_BUTTON, &CMFCChatServerDlg::OnBnClickedStopButton)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CAL_BUTTON, &CMFCChatServerDlg::OnBnClickedCalButton)
	ON_BN_CLICKED(IDC_MAIL_BUTTON, &CMFCChatServerDlg::OnBnClickedMailButton)
	ON_BN_CLICKED(IDC_QQ_BUTTON, &CMFCChatServerDlg::OnBnClickedQqButton)
	ON_BN_CLICKED(IDC_BAIDU_BUTTON, &CMFCChatServerDlg::OnBnClickedBaiduButton)
END_MESSAGE_MAP()


// CMFCChatServerDlg 消息处理程序

BOOL CMFCChatServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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
	GetDlgItem(IDC_POND_EDIT)->SetWindowText(_T("5000"));

	// TODO: 在此添加额外的初始化代码

	//初始化控件
	GetDlgItem(IDC_SENT_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_STOP_BUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATAT_BUTTON)->EnableWindow(TRUE);
	GetDlgItem(IDC_COLOER_COMBO)->EnableWindow(FALSE);
	//GetDlgItem(IDC_AUTOSENT_CHECK)->EnableWindow(FALSE);

	m_WordColoerCombo.AddString(_T("黑色"));
	m_WordColoerCombo.AddString(_T("红色"));
	m_WordColoerCombo.AddString(_T("蓝色"));
	m_WordColoerCombo.AddString(_T("绿色"));

	SetDlgItemText(IDC_COLOER_COMBO, _T("黑色"));


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCChatServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCChatServerDlg::OnPaint()
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
		//定义目的区域 2.加载资源资源图片
		//1.定义DC
		CPaintDC dc(this); // 用于绘制的设备上下文
		//2.确定绘制的区域
		CRect rect;
		GetClientRect(&rect);
		TRACE("width=%d,he=%d",rect.Width(),rect.Height());

		//3.定义并创建一个内存环境，创建兼容性DC
		CDC dcBmp;
		dcBmp.CreateCompatibleDC(&dcBmp);

		//4.加载位图
		CBitmap bmpBackGroud;
		bmpBackGroud.LoadBitmapW(IDB_BEIJING_BITMAP);

		//5.将图片载入位图里面，bBitmap位图
		BITMAP bBitMap;
		bmpBackGroud.GetBitmap(&bBitMap);

		//6.将位图选入临时的内存环境中
		CBitmap* pbmpOld = dcBmp.SelectObject(&bmpBackGroud);

		//7.绘制图标
		dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcBmp,0,0,bBitMap.bmWidth,bBitMap.bmHeight
		              ,SRCCOPY);

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCChatServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCChatServerDlg::OnBnClickedStatatButton()
{

	GetDlgItem(IDC_SENT_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_STOP_BUTTON)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATAT_BUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_COLOER_COMBO)->EnableWindow(TRUE);


	TRACE("####OnBnClickedStatatButton");
	CString strPort, strIP;
	//从控件里面获取内容
	GetDlgItem(IDC_POND_EDIT)->GetWindowText(strPort);

	//cstring转char*使用一个宏
	USES_CONVERSION;
	LPCSTR szPont = (LPCSTR)T2A(strPort);
	TRACE("szPort=%s", szPont);
	
	int iport = _ttoi(strPort);

	m_server = new CSererSocket;

	if (!m_server->Create(iport))
	{
		TRACE("m_server create error =%d", GetLastError());//查找错误码getlasterror是获取错误码
		return;
	}

	if (!m_server->Listen())
	{
		TRACE("m_server Listen error =%d", GetLastError());//查找错误码getlasterror是获取错误码
		return;
	}

	/*CString str;
	m_tm = CTime::GetCurrentTime();
	str=m_tm.Format("%X ");
	TRACE("调试");
	str += _T("建立服务");*/

	CString strShow;
	CString strInfo = _T("");
	CString strMsg = _T("建立服务");

	strShow = CatShowString(strInfo, strMsg);

	m_list.AddString(strShow);
	UpdateData(FALSE);//false是数据复制下来，true是数据往控件送

}
CString CMFCChatServerDlg::CatShowString(CString strInfo, CString strMsg)
{
	//时间+信息（昵称+消息）
	CString strTime;
	CTime tmNow;
	tmNow = CTime::GetCurrentTime();
	strTime = tmNow.Format("%X");
	CString strShow;
	strShow = strTime + strShow;
	strShow += strInfo;
	strShow += strMsg;
	return strShow;
}

void CMFCChatServerDlg::OnBnClickedSentBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	//1.获取编辑框内容
	CString strTmpMsg;
	GetDlgItem(IDC_SENT_EDIT)->GetWindowTextW(strTmpMsg);


	USES_CONVERSION;
	char* szSendbuff = T2A(strTmpMsg);

	//2发送个客服端
	m_chat->Send(szSendbuff, SEND_MAX_BUFF, 0);

	//3显示到列表框
	/*CString strShow = _T("服务端: ");
	CString strTime;
	m_tm = CTime::GetCurrentTime();
	strTime = m_tm.Format("%X");

	strShow = strTime + _T(":") + strShow;
	strShow += strTmpMsg;*/

	CString strShow;
	CString strInfo = _T("服务端: ");
	//CString strMsg = _T("建立服务");

	strShow = CatShowString(strInfo, strTmpMsg);

	m_list.AddString(strShow);
	UpdateData(FALSE);

	//清空编辑框
	GetDlgItem(IDC_SENT_EDIT)->SetWindowTextW(_T(""));
}


void CMFCChatServerDlg::OnBnClickedClearmsgBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list.ResetContent();
}


void CMFCChatServerDlg::OnBnClickedStopButton()
{
	GetDlgItem(IDC_SENT_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_STOP_BUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATAT_BUTTON)->EnableWindow(TRUE);
	GetDlgItem(IDC_COLOER_COMBO)->EnableWindow(FALSE);

	m_server->Close();
	if (m_server != NULL)
	{
		delete m_server;
		m_server = NULL;
	}

	//m_chat->Close();
	if (m_chat != NULL)
	{
		delete m_chat;
		m_chat = NULL;
	}
	//3显示列表框

	CString strShow;
	strShow = CatShowString(_T(""), _T("断开连接"));
	m_list.AddString(strShow);
	UpdateData(FALSE);

	// TODO: 在此添加控件通知处理程序代码
}




HBRUSH CMFCChatServerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	CString strColor;
	m_WordColoerCombo.GetWindowTextW(strColor);
	// 	switch (switch_on)
	// 	{
	// 	default:
		//	break;
	// 	}
	if (IDC_MOSG_LIST == pWnd->GetDlgCtrlID() || IDC_SENT_EDIT == pWnd->GetDlgCtrlID())
	{
		if (strColor == L"黑色")
		{
			pDC->SetTextColor(RGB(0, 0, 0));
		}
		if (strColor == L"红色")
		{
			pDC->SetTextColor(RGB(255, 0, 0));
		}
		if (strColor == L"蓝色")
		{
			pDC->SetTextColor(RGB(0, 0, 255));
		}
		if (strColor == L"绿色")
		{
			pDC->SetTextColor(RGB(0, 255, 0));
		}
	}
	return hbr;
}


void CMFCChatServerDlg::OnBnClickedCalButton()
{
	//执行shell命令
	// TODO: 在此添加控件通知处理程序代码
	ShellExecute(NULL,L"open",L"calc.exe",NULL,NULL,SW_SHOWNORMAL);
}


void CMFCChatServerDlg::OnBnClickedMailButton()
{
	// TODO: 在此添加控件通知处理程序代码
	ShellExecute(NULL, L"open", L"http://mail.qq.com", NULL, NULL, SW_SHOWNORMAL);
}


void CMFCChatServerDlg::OnBnClickedQqButton()
{
	// TODO: 在此添加控件通知处理程序代码
	ShellExecute(NULL, L"open", _T("C:\\Program Files (x86)\\Tencent\\QQ\\Bin\\QQScLauncher.exe"),
		NULL, NULL, SW_SHOWNORMAL);
}


void CMFCChatServerDlg::OnBnClickedBaiduButton()
{
	// TODO: 在此添加控件通知处理程序代码
	ShellExecute(NULL, L"open", L"http://baidu.com", NULL, NULL, SW_SHOWNORMAL);
}
