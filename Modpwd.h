#if !defined(AFX_MODPWD_H__DC9F503D_AA57_47F6_9E2C_B9C16B467AFB__INCLUDED_)
#define AFX_MODPWD_H__DC9F503D_AA57_47F6_9E2C_B9C16B467AFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/////////////////////////////////////////////////////////////////////////////
// CModpwd dialog

class CModpwd : public CDialog
{
// Construction
public:
	long m_longCardno;
	CModpwd(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CModpwd)
	enum { IDD = IDD_DIALOG_Mod };
	CStatic	m_ctrlTip;
	long	m_longInputPwd;
	//}}AFX_DATA
   _RecordsetPtr	m_pRecordset;
   BOOL GetRecord();
   void  InitData();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModpwd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModpwd)
	afx_msg void OnBtnOk();
	afx_msg void OnBtnMod();
	afx_msg void OnBtnBack();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnCancle();
	afx_msg void OnBtnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	long m_longPwd;
	long UsrPwd;
	int TryTime;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODPWD_H__DC9F503D_AA57_47F6_9E2C_B9C16B467AFB__INCLUDED_)
