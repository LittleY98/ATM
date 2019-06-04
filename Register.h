#if !defined(AFX_REGISTER_H__DF330491_21EC_424E_8AA8_4EDC711FF6A0__INCLUDED_)
#define AFX_REGISTER_H__DF330491_21EC_424E_8AA8_4EDC711FF6A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Register.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Register dialog

class Register : public CDialog
{
// Construction
public:
	Register(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Register)
	enum { IDD = IDD_DIALOG_REGISTER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	_RecordsetPtr m_pRecordset;
	CStatic	m_ctrlError;
	void  InitData();
	BOOL  CheckCardNo();
	BOOL  CheckPwd();
	bool  CheckSex();
	void  InsertData();
	bool  IsEmpty(CString str);
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
	CString m_InputNum;
	CString m_UsrInfo;
	CComboBox m_cb;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Register)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Register)
	afx_msg void OnBtnCheck();
	afx_msg void OnBtnOk();
	afx_msg void OnBtnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGISTER_H__DF330491_21EC_424E_8AA8_4EDC711FF6A0__INCLUDED_)
