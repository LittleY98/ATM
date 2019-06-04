#if !defined(AFX_QUERY_H__060A6182_A644_47BA_975B_E195750996F2__INCLUDED_)
#define AFX_QUERY_H__060A6182_A644_47BA_975B_E195750996F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/////////////////////////////////////////////////////////////////////////////
// CQuery dialog
class CQuery : public CDialog
{
// Construction
public:
	CQuery(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CQuery)
	enum { IDD = IDD_DIALOG_QUERY };
	//}}AFX_DATA
	long m_longCardno;
	_RecordsetPtr m_pRecordset;
	CStatic	m_Tip;
    void  InitData();
    BOOL  GetRecord();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQuery)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CQuery)
	afx_msg void OnBtnBack();
	afx_msg void OnBtnRemainmoney();
	afx_msg void OnBtnHistory();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUERY_H__060A6182_A644_47BA_975B_E195750996F2__INCLUDED_)
