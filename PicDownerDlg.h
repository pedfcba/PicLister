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
	CString status_word;	//��ǰ״̬
	CString strURL;			//���ص�ַ
	CString web_name;		//��վ��
	CString web_list;		//��վ�б�	
	CString file_path;		//����·��
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
		CString key_word;		//�����ؼ���
		CString lst_word;		//�����б�
		CString result_word;	//��ȡ��ͼƬ��������
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICDOWNERDLG_H__7D826D72_62E7_49CD_B440_C548C4239B6A__INCLUDED_)
