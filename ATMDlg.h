
#if !defined(AFX_ATMDLG_H__02D0999C_55C8_402E_B731_140C188ECABE__INCLUDED_)
#define AFX_ATMDLG_H__02D0999C_55C8_402E_B731_140C188ECABE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CATMDlg dialog

class CATMDlg : public CDialog
{
// Construction
public:
	CATMDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CATMDlg)
	enum { IDD = IDD_ATM_DIALOG };
	CStatic	m_ctrlDate;
	CStatic	m_ctrlError;
	//}}AFX_DATA
	long	m_longCardno;
	long	m_longPwd;
	_RecordsetPtr m_pRecordset;
    void  InitData();
	BOOL  CheckCardNo();
	BOOL  CheckPwd();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CATMDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
 
	// Generated message map functions
	//{{AFX_MSG(CATMDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBtnMod();
	afx_msg void OnBtnOk();
	afx_msg void OnBtnExit();
	afx_msg void OnStaticInput();
	afx_msg void OnKillfocusEditCardno();
	afx_msg void OnBtnRegister();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_EditOrder;
	void ShowInEdit(int num);
	CString m_InputNum;
	CString m_UsrInfo;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ATMDLG_H__02D0999C_55C8_402E_B731_140C188ECABE__INCLUDED_)
