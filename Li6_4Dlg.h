
// Li6_4Dlg.h: 头文件
//

#pragma once


// CLi64Dlg 对话框
class CLi64Dlg : public CDialogEx
{
// 构造
public:
	CLi64Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LI6_4_DIALOG };
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
	CListBox m_list;
	CString m_name;
	long m_number;
	CString m_sex;
	int m_age;
	CString m_class;
private:
	struct student
	{
		CString name;
		long number;
		CString sex;
		int age;
		CString classno;
	};
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnDestroy();
	virtual void OnOK();
	afx_msg void OnBnClickedButton3();
};
