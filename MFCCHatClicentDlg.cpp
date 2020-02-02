
// MFCCHatClicentDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCCHatClicent.h"
#include "MFCCHatClicentDlg.h"
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


// CMFCCHatClicentDlg 对话框



CMFCCHatClicentDlg::CMFCCHatClicentDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCHATCLICENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCCHatClicentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_SENDMSG_EDIT, m_input);
	DDX_Control(pDX, IDC_COLOER_COMBO, m_WordColoerCombo);
}

BEGIN_MESSAGE_MAP(CMFCCHatClicentDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT_BIN, &CMFCCHatClicentDlg::OnBnClickedConnectBin)
	ON_BN_CLICKED(IDC_DISCONNECT_BIN, &CMFCCHatClicentDlg::OnBnClickedDisconnectBin)
	ON_BN_CLICKED(IDC_SENT_BTN, &CMFCCHatClicentDlg::OnBnClickedSentBtn)
	ON_BN_CLICKED(IDC_SVAENAME_BIN, &CMFCCHatClicentDlg::OnBnClickedSvaenameBin)
	//ON_BN_CLICKED(IDC_AUTOSENT_RADIO, &CMFCCHatClicentDlg::OnBnClickedAutosentRadio)
	ON_BN_CLICKED(IDC_CLEARMSG_BTN, &CMFCCHatClicentDlg::OnBnClickedClearmsgBtn)
	ON_BN_CLICKED(IDC_AUTOSENT_CHECK, &CMFCCHatClicentDlg::OnBnClickedAutosentCheck)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()
//函数表


// CMFCCHatClicentDlg 消息处理程序

BOOL CMFCCHatClicentDlg::OnInitDialog()
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
	GetDlgItem(IDC_PORT_EDIT)->SetWindowText(_T("5000"));
	GetDlgItem(IDC_IPADDRESS)->SetWindowText(_T("127.0.0.1"));

	WCHAR wszName[MAX_PATH] = { 0 };
	WCHAR strPath[MAX_PATH] = { 0 };
	//获取当前路径
	GetCurrentDirectoryW(MAX_PATH, strPath);
	//TRACE("####strPath =%ls", strPath);//没有打印出来
	TRACE("####开始=%ls", strPath);


	//TRACE("strPath =%ls", strPath);
	//TRACE("####1");
	CString strFilePath;
	strFilePath.Format(L"%ls//Test.ini", strPath);

	//WritePrivateProfileString(_T("CLIEXT"), _T("NAME"), strName, strFilePath);

	DWORD dwNum=GetPrivateProfileStringW(_T("CLIEXT"), _T("NAME"), NULL, wszName, MAX_PATH,strFilePath);
	if (dwNum>0)
	{
		SetDlgItemText(IDC_NAME_EDIT, wszName);
		UpdateData(FALSE);
	}
	else
	{
		WritePrivateProfileString(_T("CLIEXT"), _T("NAME"),L"客户端", strFilePath);
		SetDlgItemText(IDC_NAME_EDIT, L"客户端");
		UpdateData(FALSE);
	}
	//初始化控件
	GetDlgItem(IDC_SENT_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_DISCONNECT_BIN)->EnableWindow(FALSE);
	GetDlgItem(IDC_CONNECT_BIN)->EnableWindow(TRUE);
	GetDlgItem(IDC_AUTOSENT_CHECK)->EnableWindow(FALSE);
	GetDlgItem(IDC_COLOER_COMBO)->EnableWindow(FALSE);

	m_WordColoerCombo.AddString(_T("黑色"));
	m_WordColoerCombo.AddString(_T("红色"));
	m_WordColoerCombo.AddString(_T("蓝色"));
	m_WordColoerCombo.AddString(_T("绿色"));
	//m_WordColoerCombo.AddString(_T("色"));

	m_WordColoerCombo.SetCurSel(0);//设置当前的选择 
	SetDlgItemText(IDC_COLOER_COMBO,_T("黑色"));

// 	TRACE("####wszName=%ls",wszName);//可以打印
// 	TRACE("####开始=%ls",strPath);//不可以打印
	//SetDlgItemText(IDC_NAME_EDIT, wszName);
	//UpdateData(FALSE);

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCCHatClicentDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCCHatClicentDlg::OnPaint()
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
		TRACE("width=%d,he=%d", rect.Width(), rect.Height());

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
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0, bBitMap.bmWidth, bBitMap.bmHeight
			, SRCCOPY);

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCCHatClicentDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCCHatClicentDlg::OnBnClickedConnectBin()
{

	GetDlgItem(IDC_SENT_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_DISCONNECT_BIN)->EnableWindow(TRUE);
	GetDlgItem(IDC_CONNECT_BIN)->EnableWindow(FALSE);
	GetDlgItem(IDC_AUTOSENT_CHECK)->EnableWindow(TRUE);
	GetDlgItem(IDC_COLOER_COMBO)->EnableWindow(TRUE);



	//把IP与端口拿到
	TRACE("####[Charcli]connect btm");//使用TRACH调试
	CString strPort, strIP;
	//从控件里面获取内容
	GetDlgItem(IDC_PORT_EDIT)->GetWindowText(strPort);
	GetDlgItem(IDC_IPADDRESS)->GetWindowText(strIP);

	//cstring转char*使用一个宏
	USES_CONVERSION;
	LPCSTR szPont = (LPCSTR)T2A(strPort);
	LPCSTR szIP = (LPCSTR)T2A(strIP);
	TRACE("####szPort-%s,szIP-%s", szPont, szIP);

	int iPort = _ttoi(strPort);
	//创建一个socket对象
	m_client = new CMySocket;
	//创建套接字 容错
	if (!m_client->Create())
	{
		TRACE("#####m_client create error %d", GetLastError());//查找错误码getlasterror是获取错误码
		return;
	}
	/*else
	{
		TRACE("m_client create success");
	}*/
	//m_client->Create();

	//链接
	if (m_client->Connect(strIP, iPort)!=SOCKET_ERROR)
	{
		TRACE("######m_client Connect error %d", GetLastError());//查找错误码getlasterror是获取错误码
		return;
	}
}
//111


void CMFCCHatClicentDlg::OnBnClickedDisconnectBin()//断开按键
{

	//控制控件
	GetDlgItem(IDC_SENT_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_DISCONNECT_BIN)->EnableWindow(FALSE);
	GetDlgItem(IDC_CONNECT_BIN)->EnableWindow(TRUE);
	GetDlgItem(IDC_AUTOSENT_CHECK)->EnableWindow(FALSE);
	GetDlgItem(IDC_COLOER_COMBO)->EnableWindow(FALSE);

	//网络断开，回收资源
	m_client->Close();
	if (m_client!=NULL)
	{
		delete m_client;
		m_client = NULL;
	}

	//3显示列表框

	CString strShow;
	strShow = CatShowString(_T(""), _T("断开连接"));
	m_list.AddString(strShow);
	UpdateData(FALSE);


}



CString CMFCCHatClicentDlg::CatShowString(CString strInfo, CString strMsg)
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



void CMFCCHatClicentDlg::OnBnClickedSentBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	//1.获取编辑框内容
	CString strTmpMsg;
	GetDlgItem(IDC_SENDMSG_EDIT)->GetWindowTextW(strTmpMsg);

	CString strName;
	//strInfo += _T("：");
	GetDlgItem(IDC_NAME_EDIT)->GetWindowTextW(strName);

	strTmpMsg = strName + _T("：") + strTmpMsg;

	USES_CONVERSION;
	char* szSendbuff = T2A(strTmpMsg);

	//2发送个客服端
	m_client->Send(szSendbuff,SEND_MAX_BUFF,0);

	//3显示到列表框
	CString strShow;
 	CString strInfo;
	strInfo = _T("");
// 	GetDlgItem(IDC_NAME_EDIT)->GetWindowTextW(strInfo);
	//TRACE("####strInfo=%ls", strInfo);
	//CString strInfo = _T("我: ");
	//CString strMsg = _T("");

	strShow=CatShowString(strInfo, strTmpMsg);
	m_list.AddString(strShow);
	UpdateData(FALSE);

	//清空编辑框
	GetDlgItem(IDC_SENDMSG_EDIT)->SetWindowTextW(_T(""));
}


void CMFCCHatClicentDlg::OnBnClickedSvaenameBin()
{
	// TODO: 在此添加控件通知处理程序代码
	//保存昵称
	//怎么使用配置文件
	CString strName;
	GetDlgItemText(IDC_NAME_EDIT, strName);
	if (strName.GetLength()<=0)
	{
		MessageBox(_T("昵称不能为空"));
		return;
	}
	if (IDOK==AfxMessageBox(_T("要修改昵称吗？"),MB_OKCANCEL))
	{
		TRACE("####开始");
		//CString strName;
		WCHAR strPath[MAX_PATH] = { 0 };
		//获取当前路径
		GetCurrentDirectoryW(MAX_PATH, strPath);
		TRACE("####strPath =%ls", strPath);//没有打印出来
		//TRACE("strPath =%ls", strPath);
		//TRACE("####1");
		CString strFilePath;
		strFilePath.Format(L"%ls//Test.ini", strPath);

		//GetDlgItemText(IDC_NAME_EDIT, strName);

		WritePrivateProfileStringW(_T("CLIEXT"), _T("NAME"), strName, strFilePath);
	}
	
}


// void CMFCCHatClicentDlg::OnBnClickedAutosentRadio()
// {
// 	// TODO: 在此添加控件通知处理程序代码
// 	if (((CButton*)GetDlgItem(IDC_AUTOSENT_RADIO))->GetCheck())
// 	{
// 		((CButton*)GetDlgItem(IDC_AUTOSENT_RADIO))->SetCheck(FALSE);
// 	}
// 	else
// 	{
// 		((CButton*)GetDlgItem(IDC_AUTOSENT_RADIO))->SetCheck(TRUE);
// 	}
// }


void CMFCCHatClicentDlg::OnBnClickedClearmsgBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list.ResetContent();
}


void CMFCCHatClicentDlg::OnBnClickedAutosentCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	if (((CButton*)GetDlgItem(IDC_AUTOSENT_CHECK))->GetCheck())
	{
		((CButton*)GetDlgItem(IDC_AUTOSENT_CHECK))->SetCheck(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_AUTOSENT_CHECK))->SetCheck(TRUE);
	}
}


HBRUSH CMFCCHatClicentDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)//颜色消息函数
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
	if (IDC_LIST1 == pWnd->GetDlgCtrlID() || IDC_SENDMSG_EDIT == pWnd->GetDlgCtrlID())
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


BOOL CMFCCHatClicentDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	//要规避回车键 
	if (pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)
	{
		TRACE("####回车键");
		return TRUE;
	}

	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_SPACE)
	{
		TRACE("####回车键");
		return TRUE;
	}

	//添加快捷键ctrl+X退出

	if (pMsg->message == WM_KEYDOWN )
	{
		if (GetKeyState(VK_CONTROL)<0)//ctrl按下
		{
			if (pMsg->wParam =='X')
			{
				CDialogEx::OnOK();
			}
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
