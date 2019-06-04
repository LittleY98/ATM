// Record.cpp : implementation file
//

#include "stdafx.h"
#include "atm.h"
#include "Record.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecord dialog

extern CATMApp theApp;//声明全局对象

CRecord::CRecord(CWnd* pParent /*=NULL*/)
	: CDialog(CRecord::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRecord)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pRecordConsume.CreateInstance(__uuidof(Recordset));
}


void CRecord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRecord)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_LIST, this->m_listCtrl);
}


BEGIN_MESSAGE_MAP(CRecord, CDialog)
	//{{AFX_MSG_MAP(CRecord)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnClickList)
	ON_BN_CLICKED(IDC_BTN_MAINMENU, OnBtnMainmenu)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST, OnCustomdrawList)
	ON_BN_CLICKED(IDC_BTN_WRITE, OnBtnWrite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecord message handlers

BOOL CRecord::OnInitDialog() 
{
	CDialog::OnInitDialog();
	ListCtrlInit();
	CString tmp;	
	tmp.Format("%ld", m_longCardno);
	this->SelectData(tmp);
	// TODO: Add extra initialization here
	this->ShowData();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*初始化ListControl*/
void CRecord::ListCtrlInit(){
	DWORD dwStyle = m_listCtrl.GetExtendedStyle();     
    dwStyle |= LVS_EX_FULLROWSELECT;
    dwStyle |= LVS_EX_GRIDLINES;
	m_listCtrl.SetExtendedStyle(dwStyle);
	this->m_listCtrl.InsertColumn(0, _T("序号"), LVCFMT_LEFT, 50);
	this->m_listCtrl.InsertColumn(1, _T("时间"), LVCFMT_LEFT, 150);
	this->m_listCtrl.InsertColumn(2, _T("消费金额"), LVCFMT_LEFT, 80);
	this->m_listCtrl.InsertColumn(3, _T("消费类型"), LVCFMT_LEFT, 120);
	this->m_listCtrl.InsertColumn(4, _T("收款人"), LVCFMT_LEFT, 70);
}

void CRecord::OnBtnMainmenu() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}


void CRecord::SelectData(CString CardNO) {
	if(!theApp.m_pConnection->State)
		theApp.InitDataBase();
	try {
		CString strSql = "select * from UsrRecord where Cardno='";
		strSql += CardNO;
		strSql += "'";
		this->m_pRecordConsume->Open((_variant_t)strSql,theApp.m_pConnection.GetInterfacePtr(),
			adOpenDynamic,adLockOptimistic,adCmdText);
	} catch(_com_error *e){
		AfxMessageBox(e->ErrorMessage());
	} 
}

void CRecord::ShowData() {
	_variant_t var;
    CString CSDate, CSMoney, CSType, CSColNO = _T("");
	UpdateData();//更新控件数据
	try{
		if(!m_pRecordConsume->BOF)
			m_pRecordConsume->MoveFirst();
		// 获取库中各字段并加入列表框中
		while(!m_pRecordConsume->adoEOF){ 
			var = m_pRecordConsume->GetCollect("ConsumeDate");
			if(var.vt != VT_NULL){
				CSDate = (LPCSTR)_bstr_t(var);
			}
			var = m_pRecordConsume->GetCollect("ConsumeMoney");
			if(var.vt != VT_NULL){
				CSMoney = (LPCSTR)_bstr_t(var);
			}
			var = m_pRecordConsume->GetCollect("ConsumeType");
			if(var.vt != VT_NULL){
				CSType = (LPCSTR)_bstr_t(var);
			}
			if (CSType == "transfer"){
				var = m_pRecordConsume->GetCollect("ConsumeType");
				if(var.vt != VT_NULL){
					CSColNO = (LPCSTR)_bstr_t(var);
				}
			}
			InsertData(CSDate, CSMoney, CSType, CSColNO);
			CSDate = _T("");
			CSMoney = _T("");
			CSType = _T("");
			CSColNO = _T("");
			m_pRecordConsume->MoveNext();
		}
	} catch(_com_error *e){
		AfxMessageBox(e->ErrorMessage());
	} 
}

void CRecord::InsertData(CString Date, CString Money, CString type, CString ColCardNO){
	UpdateData();
	int nCount = m_listCtrl.GetItemCount();
	CString Num;
	Num.Format("%d", nCount);
	m_listCtrl.InsertItem(nCount, Num);
	m_listCtrl.SetItemText(nCount, 1, Date);
	m_listCtrl.SetItemText(nCount, 2, Money);
	m_listCtrl.SetItemText(nCount, 3, type);
	m_listCtrl.SetItemText(nCount, 4, ColCardNO);
}

void CRecord::OnClickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CRecord::OnCustomdrawList(NMHDR *pNMHDR, LRESULT *pResult){
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );
 
	*pResult = CDRF_DODEFAULT;
 
 
 
	if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		COLORREF crText,crBk;
		//奇偶判断
		if ( (pLVCD->nmcd.dwItemSpec % 2) == 0 )
		{
			crText = RGB(0,0,0);//RGB(32,32,255);
			crBk = RGB(229,232,239);
		}
		else if ( (pLVCD->nmcd.dwItemSpec % 2) == 1 )
		{
			crText = RGB(0,0,0);
			crBk = RGB(240,247,249);
		}
		else
		{
			crText = RGB(0,0,0);
			crBk = RGB(0,0,126);
		}
 
		pLVCD->clrText = crText;
		pLVCD->clrTextBk = crBk;
		//设置选择项的颜色
		if( this->m_listCtrl.GetItemState(pLVCD->nmcd.dwItemSpec, CDIS_SELECTED) )
		{
			crBk =RGB(75, 149, 229);//itunes//RGB(10, 36, 106);//RGB(0, 0, 64);
			crText = RGB(255,255,255);
			pLVCD->clrText = crText;
			pLVCD->clrTextBk = crBk;					
			*pResult = CDRF_NEWFONT;
		}
		if(LVIS_SELECTED == m_listCtrl.GetItemState(pLVCD->nmcd.dwItemSpec,LVIS_SELECTED))
		{
			//清除选择状态，如果不清除的话，还是会显示出蓝色的高亮条
			BOOL b = m_listCtrl.SetItemState(pLVCD->nmcd.dwItemSpec,0,LVIS_SELECTED); 
			pLVCD->clrText = crText;
			pLVCD->clrTextBk = crBk;
 
			*pResult = CDRF_NEWFONT;
			return;
		}
		*pResult = CDRF_NEWFONT;
	}
}

/*导出数据*/
void CRecord::OnBtnWrite() 
{
	// TODO: Add your control notification handler code here
	CString CSNum[1024], CSDate[1024], CSMoney[1024], CSType[1024], CSColCardNO[1024];
	CString filename = ".\\Data\\data.xls";
	CFile file(filename, CFile::modeCreate | CFile::modeReadWrite | CFile::shareExclusive);
	CString str = "序号\t时间\t消费金额\t消费类型\t收款方\n";
	file.Write(str, str.GetLength());
	int i = 0, j = 0;
	j = this->m_listCtrl.GetItemCount();
	if (j > 0){
		for (i = 0;i<j;i++){
			CSNum[i] = m_listCtrl.GetItemText(i, 0);
			CSDate[i] = m_listCtrl.GetItemText(i, 1);
			CSMoney[i] = m_listCtrl.GetItemText(i, 2);
			CSType[i] = m_listCtrl.GetItemText(i, 3);
			CSColCardNO[i] = m_listCtrl.GetItemText(i, 4);

			CString CSMsg;
			CSMsg.Format("%s\t%s\t%s\t%s\t%s\n", CSNum[i], CSDate[i], CSMoney[i], CSType[i], CSColCardNO[i]);
			file.Write(CSMsg, CSMsg.GetLength());
		}
	}
	file.Close();
	AfxMessageBox("导出成功!");
}
