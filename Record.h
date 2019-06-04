#if !defined(AFX_RECORD_H__73CD5FF4_DF27_4E7B_899B_363162ECBE24__INCLUDED_)
#define AFX_RECORD_H__73CD5FF4_DF27_4E7B_899B_363162ECBE24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Record.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRecord dialog

class CRecord : public CDialog
{
// Construction
public:
	CRecord(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRecord)
	enum { IDD = IDD_DIALOG_RECORD };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	long          m_longCardno;
	_RecordsetPtr m_pRecordConsume;
	void ListCtrlInit();
	void SelectData(CString CardNO);
	void ShowData();
	void InsertData(CString Date, CString Money, CString type, CString ColCardNO);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecord)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRecord)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnMainmenu();
	afx_msg void OnCustomdrawList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBtnWrite();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CListCtrl m_listCtrl;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECORD_H__73CD5FF4_DF27_4E7B_899B_363162ECBE24__INCLUDED_)
