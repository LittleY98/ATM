// ATMDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ATM.h"
#include "ATMDlg.h"
#include "Mainmenu.h"
#include "Register.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CATMDlg dialog

extern CATMApp theApp;//声明全局对象

CATMDlg::CATMDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CATMDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CATMDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_pRecordset.CreateInstance(__uuidof(Recordset));
    m_InputNum = _T("");
    m_EditOrder = 1;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CATMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CATMDlg)
	DDX_Control(pDX, IDC_STATIC_DATE, m_ctrlDate);
	DDX_Control(pDX, IDC_STATIC_TIP, m_ctrlError);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CATMDlg, CDialog)
	//{{AFX_MSG_MAP(CATMDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_MOD, OnBtnMod)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_STATIC_INPUT, OnStaticInput)
	ON_EN_KILLFOCUS(IDC_EDIT_CARDNO, OnKillfocusEditCardno)
	ON_BN_CLICKED(IDC_BTN_REGISTER, OnBtnRegister)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CATMDlg message handlers

BOOL CATMDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	// TODO: Add extra initialization here
	SetTimer(0,1000,0);
	GetDlgItem(IDC_EDIT_CARDNO)->SetWindowText("");
	GetDlgItem(IDC_EDIT_PWD)->SetWindowText("");
	InitData();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CATMDlg::OnPaint() 
{
	if (IsIconic()) {
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CATMDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CATMDlg::OnTimer(UINT nIDEvent)//定时器响应函数 
{
	// TODO: Add your message handler code here and/or call default
	CTime t = CTime::GetCurrentTime();//获取当前时间
	CString datetime;
	LPCTSTR DateTime; 
	datetime = t.Format("  %Y年%m月%d日\n北京时间:%H:%M:%S");
	DateTime = datetime;
	m_ctrlDate.SetWindowText(DateTime);//显示时间
	CDialog::OnTimer(nIDEvent);
}
void CATMDlg::OnBtnMod() 
{
	// TODO: Add your control notification handler code here
	if(m_EditOrder == 1) {
		GetDlgItem(IDC_EDIT_CARDNO)->SetWindowText("");
		m_InputNum.Empty();
		m_EditOrder = 1;
	} else {
		GetDlgItem(IDC_EDIT_PWD)->SetWindowText("");
		m_InputNum.Empty();
		m_EditOrder = 2;
	}
}

void CATMDlg::OnBtnOk() 
{
	// TODO: Add your control notification handler code here
	OnStaticInput();
}

void CATMDlg::InitData()
{
	if(!theApp.m_pConnection->State)
		theApp.InitDataBase();
	try {
		m_pRecordset->Open("SELECT * FROM UsrInfo ",theApp.m_pConnection.GetInterfacePtr(),
			adOpenDynamic,adLockOptimistic,adCmdText);
	} catch(_com_error *e){
		AfxMessageBox(e->ErrorMessage());
	}  
}

BOOL CATMDlg::CheckPwd()
{
	_variant_t var;
    CString SCardno,SPwd,SUsrname,SUsrsex;
	long pwd;
	// TODO: Add your control notification handler code here
	UpdateData();//更新控件数据
	GetDlgItemText(IDC_EDIT_PWD, SPwd);
	m_longPwd = atol(SPwd);
	try
	{
		//从已找到账号的记录中比对密码项
		var = m_pRecordset->GetCollect("Pwd");
			if(var.vt != VT_NULL)
			{
				SPwd = (LPCSTR)_bstr_t(var);
			    pwd = atol(SPwd);
			}
			if(pwd == m_longPwd)
				return TRUE; 
			else
			{   
				GetDlgItem(IDC_EDIT_PWD)->SetWindowText("");
                m_ctrlError.SetWindowText("密码错误，请核对密码后重试!");
				return FALSE;
			}
	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
	} 
	return TRUE; 
}

BOOL CATMDlg::CheckCardNo()
{
	_variant_t var;
    CString SCardno,SPwd,SUsrname,SUsrsex;
    long cardno;
	int sex;
	// TODO: Add your control notification handler code here
	UpdateData();//更新控件数据
	GetDlgItemText(IDC_EDIT_CARDNO, SCardno);
	m_longCardno = atol(SCardno);
	try{
		if(!m_pRecordset->BOF)
			m_pRecordset->MoveFirst();
		// 读入库中各字段并加入列表框中
		while(!m_pRecordset->adoEOF){   
			var = m_pRecordset->GetCollect("Cardno");
			if(var.vt != VT_NULL){
				SCardno = (LPCSTR)_bstr_t(var);
				cardno = atol(SCardno);
			}
			if(cardno == m_longCardno){   
				CString temp;
				var = m_pRecordset->GetCollect("Usrname");
				SUsrname = (LPCSTR)_bstr_t(var);
				SUsrname=SUsrname.Left(2);
				var = m_pRecordset->GetCollect("Usrsex");
				SUsrsex = (LPCSTR)_bstr_t(var);
				sex = atoi(SUsrsex);
				if(sex == 0)
				  temp.Format("先生");
				else
				  temp.Format("女士");
				SUsrname += temp;
				m_UsrInfo = SUsrname;
				m_UsrInfo += "您好,请选择服务类型";
				m_ctrlError.SetWindowText("账号已找到,请输入密码");
				return TRUE;
			}
			else
				m_pRecordset->MoveNext();
		}
		if(m_pRecordset->adoEOF){
	
			m_ctrlError.SetWindowText("账号错误，请核对账号后重试!");
			return FALSE;
		}
	} catch(_com_error *e){
		AfxMessageBox(e->ErrorMessage());
	} 
	return TRUE;
}

void CATMDlg::OnBtnExit() {
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BTN_EXIT)->SetFocus();
    if(theApp.m_pConnection->State)
		theApp.m_pConnection->Close();
	theApp.m_pConnection = NULL;      
	PostQuitMessage(0);
}

void CATMDlg::OnStaticInput() {
	// TODO: Add your control notification handler code here
	static Trytime = 3;
	if(m_EditOrder == 1){
		m_longCardno = atol(m_InputNum);
		if(CheckCardNo() != TRUE)//判读卡号是否存在
			m_EditOrder = 1;
		else
			m_EditOrder = 2;
		m_InputNum.Empty();
		return;
	}
	if(m_EditOrder == 2)//编辑框焦点定在第二个时
		m_longPwd = atol(m_InputNum);//转化键入记录字符串到密码变量中
	if(Trytime == 0) { 
		//密码重试超过三次后将取消登录资格
		m_ctrlError.SetWindowText("密码错误次数超过三次,磁卡已锁定,请联系本行进行解锁!");
        m_InputNum.Empty();
		return;
	}
	if(CheckPwd()!=TRUE) {
		//检验密码的正确性
		m_InputNum.Empty();//出错时,键入的数字记录字符串清空，重新记录
		Trytime--;//若不正确则重试机会减少一次
	} else {
		//密码正确则显示交易主菜单
		CMainmenu Dlg;
		Dlg.m_longCardno = m_longCardno;
		CDialog::ShowWindow(SW_HIDE);//隐藏登录界面
		Dlg.UsrInfo = m_UsrInfo;
		Dlg.DoModal();//显示交易主菜单
		CDialog::ShowWindow(SW_SHOWNORMAL);
		GetDlgItem(IDC_EDIT_CARDNO)->SetWindowText("");
		GetDlgItem(IDC_EDIT_PWD)->SetWindowText("");
		m_ctrlError.SetWindowText("");
		m_InputNum.Empty();
	}
}

void CATMDlg::ShowInEdit(int num) {
    CString temp;
	LPCTSTR tempstr;
	temp.Format("%ld",num);
	m_InputNum += temp;
    tempstr = m_InputNum;
	if(m_EditOrder == 1)
		GetDlgItem(IDC_EDIT_CARDNO)->SetWindowText(tempstr);
	else
       GetDlgItem(IDC_EDIT_PWD)->SetWindowText(tempstr);
}

void CATMDlg::OnKillfocusEditCardno() {
	// TODO: Add your control notification handler code here
	m_longCardno=atol(m_InputNum);
	if(CheckCardNo() != TRUE){
		m_EditOrder = 1;
        GetDlgItem(IDC_EDIT_CARDNO)->SetWindowText("");
	} else
		m_EditOrder = 2;
	m_InputNum.Empty();
}

void CATMDlg::OnBtnRegister() 
{
	// TODO: Add your control notification handler code here
	Register dlg;
	dlg.m_longCardno = m_longCardno;
	CDialog::ShowWindow(SW_HIDE);/*隐藏登录界面*/
	dlg.DoModal();
	CDialog::ShowWindow(SW_SHOWNORMAL);
}
