
// MFCCHatClicentDlg.h: 头文件
//

#pragma once
#include "CMySocket.h"


// CMFCCHatClicentDlg 对话框
class CMFCCHatClicentDlg : public CDialogEx
{
// 构造
public:
	CMFCCHatClicentDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCHATCLICENT_DIALOG };
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
	afx_msg void OnBnClickedConnectBin();
	afx_msg void OnBnClickedDisconnectBin();
	CMySocket* m_client;
	//添加的部分
	CListBox m_list;
	//CTime m_tm;
	CEdit m_input;//
	afx_msg void OnBnClickedSentBtn();
	CString CMFCCHatClicentDlg::CatShowString(CString strInfo,CString strMsg);
	afx_msg void OnBnClickedSvaenameBin();
	/*afx_msg void OnBnClickedAutosentRadio();*/
	afx_msg void OnBnClickedClearmsgBtn();
	afx_msg void OnBnClickedAutosentCheck();
	CComboBox m_WordColoerCombo;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
