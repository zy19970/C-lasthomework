
// VC59_15154010923Dlg.h: 头文件
//

#pragma once


// CVC5915154010923Dlg 对话框
class CVC5915154010923Dlg : public CDialogEx
{
// 构造
public:
	CVC5915154010923Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VC59_15154010923_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButton1();
	CString m_Input;
	CString m_state;
	CIPAddressCtrl m_ip;
	SOCKET m_socket;
	SOCKADDR_IN m_addr;
	bool IsSock;
	bool IsConnect;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void On32771();
	afx_msg void On32772();
	afx_msg void On32773();
	afx_msg void OnClose();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CProgressCtrl m_slider;
	CButton m_connect;
	CButton m_send;
	CButton m_close;
};
