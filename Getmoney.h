#if !defined(AFX_GETMONEY_H__3E3ECD2F_23F8_414E_A544_327ACB613E60__INCLUDED_)
#define AFX_GETMONEY_H__3E3ECD2F_23F8_414E_A544_327ACB613E60__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/////////////////////////////////////////////////////////////////////////////
// CGetmoney dialog
class CGetmoney : public CDialog
{
// Construction
public:
	

	CGetmoney(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CGetmoney)
	enum { IDD = IDD_DIALOG_GETMONEY };
	CStatic	m_ctrlTip;
	//}}AFX_DATA
	long			m_longCardno;
	_RecordsetPtr	m_pRecordset;
	_RecordsetPtr   m_pRecordConsume;
	CString         m_strConMoney;
	long			m_longGetmoney;
    void			InitData();
	BOOL            GetRecord();
	void            CheckGetmoney();
	void            InsertConsumeRecord();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetmoney)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGetmoney)
	afx_msg void OnBtnOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnPrintinfo();
	afx_msg void OnBtn100();
	afx_msg void OnBtn1000();
	afx_msg void OnBtn300();
	afx_msg void OnBtn500();
	afx_msg void OnBtn800();
	afx_msg void OnBtnExit();
	afx_msg void OnBtnBack();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETMONEY_H__3E3ECD2F_23F8_414E_A544_327ACB613E60__INCLUDED_)
