// Login.cpp: 实现文件
//

#include "stdafx.h"
#include "VC59_15154010923.h"
#include "Login.h"
#include "afxdialogex.h"


// Login 对话框

IMPLEMENT_DYNAMIC(Login, CDialog)

Login::Login(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
	, m_user(_T(""))
	, m_psw(_T(""))
{

}

Login::~Login()
{
}

void Login::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_psw);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	m_combo.AddString("admin");
	m_combo.AddString("teacher");
	m_combo.AddString("student");
	m_combo.InsertString(1, "hadmaster");
	m_combo.SetCurSel(0);
	GetDlgItem(IDC_EDIT1)->SetWindowText("admin");
	GetDlgItem(IDC_EDIT2)->SetWindowText("123");
	
}


BEGIN_MESSAGE_MAP(Login, CDialog)
	ON_BN_CLICKED(IDOK, &Login::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &Login::OnEnChangeEdit1)
END_MESSAGE_MAP()


// Login 消息处理程序


void Login::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//UpdateData(1);
	GetDlgItem(IDC_EDIT1)->GetWindowText(m_user);
	GetDlgItem(IDC_EDIT2)->GetWindowText(m_psw);
	if (m_user == "admin"&&m_psw == "123")
	{
		CString str;
		m_combo.GetWindowText(str);
		MessageBox("Welcome " + str+" !");
		CDialog::OnOK();
	}
	else
	{
		MessageBox("用户名密码错误!");
		m_psw = "";
		UpdateData(0);
	}

}


void Login::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
