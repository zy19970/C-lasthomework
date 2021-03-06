
// VC59_15154010923Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VC59_15154010923.h"
#include "VC59_15154010923Dlg.h"
#include "afxdialogex.h"
#include "Afxsock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CWinThread* pRecvThread = NULL;
UINT RecvThread(LPVOID pParam);
BOOL m_threadRun = 0;

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


// CVC5915154010923Dlg 对话框



CVC5915154010923Dlg::CVC5915154010923Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VC59_15154010923_DIALOG, pParent)
	, m_Input(_T(""))
	, m_state(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVC5915154010923Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Input);
	DDX_Text(pDX, IDC_EDIT2, m_state);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ip);
	DDX_Control(pDX, IDC_PROGRESS1, m_slider);
	DDX_Control(pDX, IDC_BUTTON1, m_connect);
	DDX_Control(pDX, IDC_BUTTON2, m_send);
	DDX_Control(pDX, IDC_BUTTON3, m_close);
}

BEGIN_MESSAGE_MAP(CVC5915154010923Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CVC5915154010923Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CVC5915154010923Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CVC5915154010923Dlg::OnBnClickedButton3)
	ON_COMMAND(ID_32771, &CVC5915154010923Dlg::On32771)
	ON_COMMAND(ID_32772, &CVC5915154010923Dlg::On32772)
	ON_COMMAND(ID_32773, &CVC5915154010923Dlg::On32773)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CVC5915154010923Dlg 消息处理程序

BOOL CVC5915154010923Dlg::OnInitDialog()
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

	// TODO: 在此添加额外的初始化代码
	m_slider.SetRange(0, 100);
	//m_slider.SetTicFreq(1);
	m_close.EnableWindow(0);
	m_send.EnableWindow(0);

	m_ip.SetAddress(127, 0, 0, 1);
	// 打开对话框头文件***Dlg.h，声明CMenu 变量,例如m_Menu;
	//打开***Dlg.cpp 文件，在***Dlg::OnInitDlg()中加入如下语句
	CMenu m_Menu;
	m_Menu.LoadMenu(IDR_MENU1);  //  IDR_MENU1为你加入的菜单的ID，在Resource视图的Menu文件夹下可以找到,如果代码提示中说IDR_MENU1没有定义的话（我遇到了这个问题，ID一样，但是提示没有定义，我是重新新建了一个工程就解决了）。
	SetMenu(&m_Menu);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CVC5915154010923Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CVC5915154010923Dlg::OnPaint()
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
HCURSOR CVC5915154010923Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CVC5915154010923Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(1);
	CString ip0;
	BYTE f0, f1, f2, f3;
	m_ip.GetAddress(f0, f1, f2, f3);//m_IP是ip控件的控制变量   
	ip0.Format("%d%s%d%s%d%s%d", f0, ".", f1, ".", f2, ".", f3);
	//----------------------------------
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket == INVALID_SOCKET)
	{
		//MessageBox("套接字创建失败!");
		IsSock = 0;
		m_state += "【状态】   套接字创建失败。\r\n";
		UpdateData(0);
		return;
	}
	m_slider.SetPos(50);
	IsSock = 1;
	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htons(9000);
	//m_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	m_addr.sin_addr.S_un.S_addr = inet_addr(ip0);
	int  n = connect(m_socket, (SOCKADDR*)&m_addr, sizeof(SOCKADDR));
	if (n == SOCKET_ERROR)
	{
		//MessageBox("网络连接失败！");
		IsConnect = 0;
		m_state += "【状态】   未连接到服务器。\r\n";
		UpdateData(0);
		return;
	}
	IsConnect = 1;
	send(m_socket, (LPCSTR)"一台新设备（ID：15154010923）接入系统。", 100, 0);
	m_state = m_state+"【状态】   连接到服务器"+ip0+"。\r\n";
	UpdateData(0);
	m_slider.SetPos(100);
	pRecvThread = AfxBeginThread(RecvThread, this);
	//m_slider.SetPos(0);
	m_slider.EnableWindow(FALSE);
	m_connect.EnableWindow(0);
	m_close.EnableWindow(1);
	m_send.EnableWindow(1);
}

void CVC5915154010923Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (IsSock&&IsConnect)
	{
		UpdateData(1);
		send(m_socket, (LPCSTR)m_Input, 100, 0);
		m_state = m_state + "【发送消息】   " + m_Input + "\r\n";
		m_Input = "";
		UpdateData(0);
	}
	else
	{
		UpdateData(1);
		m_state = m_state + "【发送失败】   " + m_Input + "\r\n";
		m_Input = "";
		UpdateData(0);
	}

}


void CVC5915154010923Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(1);

	send(m_socket, (LPCSTR)"一台设备（ID：15154010923）断开连接。", 50, 0);
	closesocket(m_socket);

	m_state += "【状态】   连接已断开！\r\n";

	UpdateData(0);
	m_connect.EnableWindow(1);
	m_close.EnableWindow(0);
	m_send.EnableWindow(0);
}

CString m_strInfo = "";
UINT RecvThread(LPVOID pParam)
{
	CVC5915154010923Dlg* pThis = (CVC5915154010923Dlg*)pParam;
	SOCKET sock = pThis->m_socket;
	while (1)
	{
		char recvBuf[4096] = "";
		int retval;
		retval = recv(sock, (LPSTR)recvBuf, 4096, 0);
		if (SOCKET_ERROR == retval || retval == 0)
		{
			closesocket(sock);
			break;

		}
		m_strInfo = "";
		m_strInfo += recvBuf;
		m_strInfo = pThis->m_state + "【收到消息】   " + m_strInfo + "\r\n";
		pThis->m_state = m_strInfo;
		pThis->GetDlgItem(IDC_EDIT2)->SetWindowText(pThis->m_state);
	}
	return 0;
}



void CVC5915154010923Dlg::On32771()
{
	// TODO: 在此添加命令处理程序代码
	CVC5915154010923Dlg::OnBnClickedButton1();
}


void CVC5915154010923Dlg::On32772()
{
	// TODO: 在此添加命令处理程序代码
	CVC5915154010923Dlg::OnBnClickedButton3();
}


void CVC5915154010923Dlg::On32773()
{
	// TODO: 在此添加命令处理程序代码
	CVC5915154010923Dlg::OnClose();
}


void CVC5915154010923Dlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnClose();
}


BOOL CVC5915154010923Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		if (GetFocus() == GetDlgItem(IDC_EDIT1))  //根据不同控件焦点判断是那个在执行  
		{
			CVC5915154010923Dlg::OnBnClickedButton2();
		}
		if (GetFocus() == GetDlgItem(IDC_IPADDRESS1))  //根据不同控件焦点判断是那个在执行  
		{
			CVC5915154010923Dlg::OnBnClickedButton1();
		}
	}

	return 0;
	//return CDialogEx::PreTranslateMessage(pMsg);
}
