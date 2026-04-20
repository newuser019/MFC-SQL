
// Li6_4Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Li6_4.h"
#include "Li6_4Dlg.h"
#include "afxdialogex.h"
#include "afxdb.h"
// 数据库连接字符串，需根据实际情况修改
const CString strConnect = L"DRIVER={SQL Server};SERVER=LJH;DATABASE=student1;UID=sa;PWD=Ljh488606319!";

// 定义记录集类
class CStudentRecordset : public CRecordset
{
public:
	CStudentRecordset(CDatabase* pDatabase = NULL)
		: CRecordset(pDatabase)
	{
		m_name = m_sex = m_class = L"";
		m_number = m_age = 0;
		m_nFields = 5;
		m_nDefaultType = dynaset;
	}

	CString m_name;
	long m_number;
	CString m_sex;
	int m_age;
	CString m_class;
	virtual CString GetDefaultSQL()
	{
		return L"SELECT 姓名,学号,性别,年龄,班级 FROM [dbo].[Table_1]";
	}

	virtual void DoFieldExchange(CFieldExchange* pFX)
	{
		pFX->SetFieldType(CFieldExchange::outputColumn);
		RFX_Text(pFX, _T("[姓名]"), m_name);
		RFX_Long(pFX, _T("[学号]"), m_number);
		RFX_Text(pFX, _T("[性别]"), m_sex);
		RFX_Int(pFX, _T("[年龄]"), m_age);
		RFX_Text(pFX, _T("[班级]"), m_class);
	}
};

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


// CLi64Dlg 对话框



CLi64Dlg::CLi64Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LI6_4_DIALOG, pParent)
	, m_name(_T(""))
	, m_number(0)
	, m_sex(_T(""))
	, m_age(0)
	, m_class(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLi64Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT2, m_number);
	DDX_Text(pDX, IDC_EDIT3, m_sex);
	DDX_Text(pDX, IDC_EDIT4, m_age);
	DDX_Text(pDX, IDC_EDIT5, m_class);
}

BEGIN_MESSAGE_MAP(CLi64Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CLi64Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CLi64Dlg::OnBnClickedButton2)
	ON_LBN_SELCHANGE(IDC_LIST1, &CLi64Dlg::OnLbnSelchangeList1)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON3, &CLi64Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CLi64Dlg 消息处理程序

BOOL CLi64Dlg::OnInitDialog()
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

	 // 初始化时从数据库加载数据到列表框
	CDatabase db;
	try
	{
		db.OpenEx(strConnect, CDatabase::noOdbcDialog);
		CStudentRecordset rs(&db);
		rs.Open();
		while (!rs.IsEOF())
		{
			const int nIndex = m_list.AddString(rs.m_name);
			student stu;
			stu.name = rs.m_name;
			stu.number = rs.m_number;
			stu.sex = rs.m_sex;
			stu.age = rs.m_age;
			stu.classno = rs.m_class;
			m_list.SetItemDataPtr(nIndex, new student(stu));
			rs.MoveNext();
		}
		rs.Close();
		db.Close();
	}
	catch (CDBException* e)
	{
		e->ReportError();
		e->Delete();
		db.Close();
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLi64Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CLi64Dlg::OnPaint()
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
HCURSOR CLi64Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CLi64Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_name.IsEmpty())
	{
		MessageBox(L"学生姓名不能为空！");
		return;
	}
	m_name.TrimLeft();
	m_name.TrimRight();
	m_class.TrimLeft();
	m_class.TrimRight();
	m_sex.TrimLeft();
	m_sex.TrimRight();
	if (m_list.FindStringExact(-1, m_name) != LB_ERR)
	{
		MessageBox(L"列表框中已有该项，不能再添加！");
		return;
	}
	// 连接数据库
	CDatabase db;
	try
	{
		db.OpenEx(strConnect, CDatabase::noOdbcDialog);
		// 显式指定动态集和可读写选项
		CStudentRecordset rs(&db); 
		rs.Open(CRecordset::dynaset);
		
		// 检查记录集是否可更新
		if (!rs.CanUpdate())
		{
			MessageBox(L"记录集不可更新，请检查数据库表结构和权限！");
			rs.Close();
			db.Close();
			return;
		}

		// 移动到记录集末尾
		rs.MoveLast();

		rs.AddNew();
		rs.m_name = m_name;
		rs.m_number = m_number;
		rs.m_sex = m_sex;
		rs.m_age = m_age;
		rs.m_class = m_class;
		rs.Update();

		rs.Close();
		db.Close();

		const int nIndex = m_list.AddString(m_name);
		student stu;
		stu.name = m_name;
		stu.number = m_number;
		stu.sex = m_sex;
		stu.age = m_age;
		stu.classno = m_class;
		m_list.SetItemDataPtr(nIndex, new student(stu));
		MessageBox(L"记录添加成功！");
	}
	catch (CDBException* e)
	{
		e->ReportError();
		e->Delete();
		db.Close();
		MessageBox(L"记录添加失败，请检查数据库连接！");
	}
}

void CLi64Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = m_list.GetCurSel();
	if (nIndex != LB_ERR)
	{
		student* p = (student*)m_list.GetItemDataPtr(nIndex);
		if (!p) {
			MessageBox(L"学生数据指针为空，操作失败！", L"错误", MB_ICONERROR);
			return;
		}
		// 连接数据库
		CDatabase db;
		try
		{
			db.OpenEx(strConnect, CDatabase::noOdbcDialog);
			// 显式指定动态集和可读写选项
			CStudentRecordset rs(&db);
			// 设置过滤条件
			CString strFilter;
			/*strFilter.Format(_T("[学号] = %ld"), p->number);
			rs.m_strFilter = strFilter;*/
			// 优化点 1：使用参数化查询避免 SQL 注入
			rs.m_strFilter.Empty(); // 清空默认过滤条件
			rs.m_strSort = _T("学号"); // 可选：添加排序确保唯一性
			
			// 打开记录集
			rs.Open(CRecordset::dynaset);

			// 设置参数并执行查询（参数化方式）
			rs.MoveFirst();
			BOOL bFound = FALSE;
			while (!rs.IsEOF()) {
				if (rs.m_number == p->number) { // 直接对比长整型字段（安全）
					bFound = TRUE;
					break;
				}
				rs.MoveNext();
			}
			if (!bFound) {
				MessageBox(L"数据库中未找到对应记录，可能已被删除！", L"警告", MB_ICONWARNING);
				rs.Close();
				db.Close();
				return;
			}

			// 检查记录集是否可更新
			if (!rs.CanUpdate())
			{
				MessageBox(L"记录集不可更新，请检查数据库表结构和权限！");
				rs.Close();
				db.Close();
				return;
			}
			if (!rs.IsEOF())
			{
				rs.Delete();
			}
			rs.Close();
			db.Close();

			delete(student*)m_list.GetItemDataPtr(nIndex);
			p = NULL;// 置空防止野指针
			m_list.DeleteString(nIndex);
			m_name = m_sex = m_class = "";
			m_number = m_age = 0;
			UpdateData(FALSE);
			MessageBox(L"记录删除成功！");
		}
		catch (CDBException* e)
		{
			e->ReportError();
			e->Delete();
			db.Close();
			if (db.IsOpen()) db.Close(); // 确保异常时关闭连接
			MessageBox(L"记录删除失败，请检查数据库连接！");
		}
	}
	else
		MessageBox(L"没有选择列表项或列表框操作失败！");
}

void CLi64Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = m_list.GetCurSel();
	if (nIndex == LB_ERR)
	{
		MessageBox(L"请先在列表中选择要修改的学生记录！");
		return;
	}

	// 获取选中项的当前数据
	student* pStu = (student*)m_list.GetItemDataPtr(nIndex);
	if (!pStu)
	{
		MessageBox(L"获取学生数据失败！", L"错误", MB_ICONERROR);
		return;
	}

	// 验证输入数据
	UpdateData(TRUE);
	if (m_name.IsEmpty())
	{
		MessageBox(L"学生姓名不能为空！");
		return;
	}

	// 检查是否修改了姓名且新姓名已存在
	if (pStu->name != m_name && m_list.FindStringExact(-1, m_name) != LB_ERR)
	{
		MessageBox(L"输入的姓名已存在，不能修改！");
		return;
	}

	// 判断学号是否被修改
	BOOL bModifyNumber = (pStu->number != m_number);

	// 学号修改时的特殊处理
	if (bModifyNumber)
	{
		// 确认是否允许修改学号（主键通常不建议修改）
		CString strMsg;
		strMsg.Format(L"您正在修改学号（原学号：%ld，新学号：%ld）。\n学号通常作为唯一标识，修改可能影响数据一致性，是否继续？",
			pStu->number, m_number);

		if (MessageBox(strMsg, L"警告", MB_YESNO | MB_ICONWARNING) != IDYES)
		{
			return; // 用户取消修改学号
		}

		// 检查新学号是否已存在于数据库
		CDatabase dbCheck;
		BOOL bNumberExists = FALSE;
		try
		{
			dbCheck.OpenEx(strConnect, CDatabase::noOdbcDialog);
			CStudentRecordset rsCheck(&dbCheck);
			CString strFilter;
			strFilter.Format(_T("[学号] = %ld"), m_number);
			rsCheck.m_strFilter = strFilter;
			rsCheck.Open(CRecordset::snapshot); // 只读快照查询

			if (!rsCheck.IsEOF())
			{
				bNumberExists = TRUE;
			}
			rsCheck.Close();
			dbCheck.Close();
		}
		catch (CDBException* e)
		{
			e->ReportError();
			e->Delete();
			if (dbCheck.IsOpen()) dbCheck.Close();
		}

		if (bNumberExists)
		{
			MessageBox(L"新学号已存在于数据库中，不能重复！", L"错误", MB_ICONERROR);
			return;
		}
	}
	// 连接数据库并执行修改操作
	CDatabase db;
	try
	{
		db.OpenEx(strConnect, CDatabase::noOdbcDialog);
		CStudentRecordset rs(&db);

		// 设置过滤条件，根据学号查找要修改的记录
		CString strFilter;
		strFilter.Format(_T("[学号] = %ld"), pStu->number);
		rs.m_strFilter = strFilter;
		rs.Open(CRecordset::dynaset);

		// 检查记录集是否可更新
		if (!rs.CanUpdate())
		{
			MessageBox(L"记录集不可更新，请检查数据库表结构和权限！");
			rs.Close();
			db.Close();
			return;
		}

		// 如果找到记录，则进行修改
		if (!rs.IsEOF())
		{
			rs.Edit();
			rs.m_name = m_name;
			rs.m_number = m_number;
			rs.m_sex = m_sex;
			rs.m_age = m_age;
			rs.m_class = m_class;
			rs.Update();
		}
		else
		{
			MessageBox(L"未找到要修改的记录！", L"警告", MB_ICONWARNING);
			rs.Close();
			db.Close();
			return;
		}

		rs.Close();
		db.Close();

		// 更新列表框中的数据
		delete pStu; // 释放旧数据
		student* newStu = new student;
		newStu->name = m_name;
		newStu->number = m_number;
		newStu->sex = m_sex;
		newStu->age = m_age;
		newStu->classno = m_class;
		m_list.SetItemDataPtr(nIndex, newStu);

		MessageBox(L"记录修改成功！");
	}
	catch (CDBException* e)
	{
		e->ReportError();
		e->Delete();
		if (db.IsOpen()) db.Close();
		MessageBox(L"记录修改失败，请检查数据库连接！");
	}
}

void CLi64Dlg::OnLbnSelchangeList1()
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = m_list.GetCurSel();
	if (nIndex != LB_ERR)
	{
		student* p = (student *)m_list.GetItemDataPtr(nIndex);
		m_name = p->name;
		m_number = p->number;
		m_sex = p->sex;
		m_age = p->age;
		m_class = p->classno;
		UpdateData(FALSE);
	}
}

void CLi64Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	for (int nIndex = m_list.GetCount() - 1; nIndex >= 0; nIndex--)
	{
		delete(student*)m_list.GetItemDataPtr(nIndex);
	}
	// TODO: 在此处添加消息处理程序代码
}

void CLi64Dlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


