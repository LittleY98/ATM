#include "stdafx.h"
#include "ATM.h"
#include "ATMDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CATMApp

BEGIN_MESSAGE_MAP(CATMApp, CWinApp)
	//{{AFX_MSG_MAP(CATMApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CATMApp construction

CATMApp::CATMApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	AfxOleInit();
	m_pConnection.CreateInstance(__uuidof(Connection));
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CATMApp object

CATMApp		theApp;//全局对象
/////////////////////////////////////////////////////////////////////////////
// CATMApp initialization

BOOL CATMApp::InitInstance()
{
	skinppLoadSkin("AlphaOS.ssk");
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CATMDlg dlg;
	m_pMainWnd = &dlg;
	SetDialogBkColor(RGB(51,102,153),RGB(0,0,0));
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
BOOL CATMApp::InitDataBase()
{   
	// 在ADO操作中用try...catch()来捕获错误信息
	if(m_pConnection->IsolationLevel)
		try {	
			// 打开本地Access库
			m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=.\\Data\\ATM.mdb","","",adModeUnknown);
		} catch(_com_error e) {
			AfxMessageBox("数据库连接失败，确认数据库是否在当前路径下!",MB_OK|MB_ICONHAND);
			return FALSE;
		}
		return TRUE;
}

int CATMApp::ExitInstance()
{
	skinppExitSkin();
	return CWinApp::ExitInstance();
}