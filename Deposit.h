#if !defined(AFX_DEPOSIT_H__24B82AC6_F4C6_46C3_8E60_8181876EACA7__INCLUDED_)
#define AFX_DEPOSIT_H__24B82AC6_F4C6_46C3_8E60_8181876EACA7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Deposit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Deposit dialog

class Deposit : public CDialog
{
// Construction
public:
	Deposit(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Deposit)
	enum { IDD = IDD_DIALOG_DEPOSIT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	
	_RecordsetPtr m_pRecordset;
	_RecordsetPtr m_pRecordConsume;
	CStatic	m_ctrlError;
	void  InitData();
	int   FindIndex();
	long  GetSavedMoney();
	bool  Judge100Integer();
	void  InsertConsumeRecord();
	long	m_longCardno;
	long	m_longPwd;
private:
	CString m_strCarNO;
	CString m_strPwd;
	CString m_strName;
	CString m_strSex;
	CString m_strAddr;
	CString m_strPhone;
	CString m_strMoney;
	CString m_strConMoney;
	CString m_InputNum;
	CString m_UsrInfo;
	CComboBox m_cb;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Deposit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Deposit)
	afx_msg void OnBtnOk();
	afx_msg void OnBtnExit();
	afx_msg void OnBtnMainmenu();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEPOSIT_H__24B82AC6_F4C6_46C3_8E60_8181876EACA7__INCLUDED_)
