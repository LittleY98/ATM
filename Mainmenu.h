#if !defined(AFX_MAINMENU_H__FD05B083_C54E_4C2D_B56B_CF64220EBF84__INCLUDED_)
#define AFX_MAINMENU_H__FD05B083_C54E_4C2D_B56B_CF64220EBF84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMainmenu dialog
class CMainmenu : public CDialog
{
// Construction
public:
	long m_longCardno;
	CMainmenu(CWnd* pParent = NULL);   // standard constructor
    CString UsrInfo;
// Dialog Data
	//{{AFX_DATA(CMainmenu)
	enum { IDD = IDD_DIALOG_MAINMENU };
	CStatic	m_ctrlTip;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainmenu)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMainmenu)
	afx_msg void OnBtnGetmoney();
	afx_msg void OnBtnQuery();
	afx_msg void OnBtnTransmoney();
	afx_msg void OnBtnExit();
	afx_msg void OnBtnModpwd();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnDeposit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINMENU_H__FD05B083_C54E_4C2D_B56B_CF64220EBF84__INCLUDED_)
