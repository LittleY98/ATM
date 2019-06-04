#if !defined(AFX_TRANSMONEY_H__DA9C5523_3758_4387_8C96_2D8E5F165F43__INCLUDED_)
#define AFX_TRANSMONEY_H__DA9C5523_3758_4387_8C96_2D8E5F165F43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/////////////////////////////////////////////////////////////////////////////
// CTransmoney dialog
class CTransmoney : public CDialog
{
// Construction
public:

	CTransmoney(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CTransmoney)
	enum { IDD = IDD_DIALOG_TRANSMONEY };
	CStatic	m_ctrlTip;
	long	m_longTransinfo;
	//}}AFX_DATA
    _RecordsetPtr	m_pRecordset;
	_RecordsetPtr   m_pRecordConsume;
    long            m_longCardno;
	BOOL            GetRecord();
	void            InitData();
	void			InsertConsumeRecord();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransmoney)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTransmoney)
	afx_msg void OnBtnBack();
	afx_msg void OnBtnCancle();
	afx_msg void OnBtnOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnRetry();
	afx_msg void OnBtnMod();
	afx_msg void OnBtnPrintinfo();
	afx_msg void OnBtnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	long      m_longTranscard;
	CString   m_UsrInfo;
	int       m_Index;
	long      m_longRemainmoney;
	int       m_TryTime;
	CString   m_strConMoney;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSMONEY_H__DA9C5523_3758_4387_8C96_2D8E5F165F43__INCLUDED_)
