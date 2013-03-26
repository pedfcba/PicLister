// PicDownerDlg.h : header file
//

#if !defined(AFX_PICDOWNERDLG_H__7D826D72_62E7_49CD_B440_C548C4239B6A__INCLUDED_)
#define AFX_PICDOWNERDLG_H__7D826D72_62E7_49CD_B440_C548C4239B6A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPicDownerDlg dialog


struct DOWN_FILE
{
	CString down_url;
	CString down_to;
//	CListBox* list_box;
};


class CPicDownerDlg : public CDialog
{
// Construction
public:
	CPicDownerDlg(CWnd* pParent = NULL);	// standard constructor
	
	static DWORD WINAPI DownFile(LPVOID lpParameter);

//	int		m_nMilliSecond;

// Dialog Data
	//{{AFX_DATA(CPicDownerDlg)
	enum { IDD = IDD_PICDOWNER_DIALOG };
	CListBox	m_listbox;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPicDownerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void PageInit(CString page);
	CString page_limit;
	CString page_name;
	CString page;
	CString limit;
	CString att_name;
	CString xmlr_name;
	CString tag_name;
	CString limit_name;
	CString site_name;
	bool GetNetValue();
	bool GetResult();
	bool ListDown(CString x ,CString y);
	CString RPGenerator();
//	CString XmlAtt();
	bool GetList();
	void IniList();
//	CWinThread* pThread;
	CString status_word;	//当前状态
	CString strURL;			//下载地址
	CString web_name;		//网站名
	CString web_list;		//网站列表	
	CString file_path;		//进程路径
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPicDownerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAnl();
	afx_msg void OnSave();
	afx_msg void OnSelchangeCombo1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
		CString key_word;		//搜索关键字
		CString lst_word;		//下载列表
		CString result_word;	//获取的图片下载链接
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICDOWNERDLG_H__7D826D72_62E7_49CD_B440_C548C4239B6A__INCLUDED_)
