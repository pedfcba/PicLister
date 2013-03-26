// PicDownerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "afxinet.h"		//net
#include "PicDowner.h"
#include "PicDownerDlg.h"
#include "Splash.h"

#import "msxml4.dll"		//XML
//#include "XML.h"			//XML

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




HANDLE hMutex;
int count = 0;

// int mutex = 1;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About



class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	
	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
// No message handlers
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPicDownerDlg dialog


CPicDownerDlg::CPicDownerDlg(CWnd* pParent /*=NULL*/)
: CDialog(CPicDownerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPicDownerDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPicDownerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPicDownerDlg)
	DDX_Control(pDX, IDC_LIST1, m_listbox);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPicDownerDlg, CDialog)
//{{AFX_MSG_MAP(CPicDownerDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_ANL, OnAnl)
ON_BN_CLICKED(IDC_SAVE, OnSave)
ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPicDownerDlg message handlers

BOOL CPicDownerDlg::OnInitDialog()
{
	CSplash::ShowSplashScreen(this);		//SPLASH
	
	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	IniList();		//��ʼ��
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPicDownerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPicDownerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);	
		
		
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPicDownerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPicDownerDlg::OnAnl() 
{
	// TODO: Add your control notification handler code here
	
		GetDlgItem(IDC_ANL)->EnableWindow(FALSE);
	
	//��ȡ�ؼ���
	GetDlgItemText(IDC_EDIT2,key_word);
	
	result_word = "";
	
	//���ùؼ��ֽ�������
	
	status_word="�����С�";
	((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);    //status_word
	limit = "100";
	
	((CComboBox*)GetDlgItem(IDC_COMBO2))->GetWindowText(page);
	int x = atoi (page);
	for (int y = 1 ; y <= x ; y++)
	{
		page.Format("%d",y);
		status_word = "���ڻ�ȡ��" + page + "ҳ" ;
		((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);    //status_word
		
		hMutex = CreateMutex(NULL,FALSE,NULL);							//������
		//	Sleep(1);	
		//		WaitForSingleObject(hMutex,INFINITE);
		//		ReleaseMutex(hMutex);
			status_word="��ַ�ĵ���ȡ�С�";
			((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);    //status_word
		if (ListDown(key_word , limit) == TRUE)
		{
			//��ȡ���ص�ַ��������浽lst_word
			
			//		WaitForSingleObject(hMutex,INFINITE);
			if (FALSE == GetResult())
			{
				status_word="no body here but us chicks���޽�����ض�" ;
				((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);    //status_word
				break;
			}
			
			//		ReleaseMutex(hMutex);
			
		}
		else
		{
			//		WaitForSingleObject(hMutex,INFINITE);
			status_word="�б��ĵ���ȡʧ�ܣ������ǣ�����RP�ˣ���վRP�ˣ���RP��";
			((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);    //status_word
			
			//		ReleaseMutex(hMutex);
//			GetResult();		/////////////////////////////////////////////////
			
			
		}
	}
	
	if(count != 0)
	{
		
		
		CString x;
		x.Format("%d",count);
		status_word = "������ϣ�������" + x + "����������Ա�����Ŷ";
		((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);  	//status_word
		
		GetDlgItem(IDC_SAVE)->EnableWindow(TRUE);
		count = 0;
	}
	
		GetDlgItem(IDC_ANL)->EnableWindow(TRUE);
	//����Ŀ��
}

void CPicDownerDlg::OnSave() 
{
	// TODO: Add your control notification handler code here
	//���������б��ļ�

	CFileDialog fileDlg(FALSE);
	fileDlg.m_ofn.lpstrTitle="�����σ������g�Ξ��";
	fileDlg.m_ofn.lpstrFilter="�б��ļ� (*.lst)\0*.lst\0\0";
	fileDlg.m_ofn.lpstrDefExt="lst";
	if(fileDlg.DoModal()&&(fileDlg.GetFileName()!=""))
	{
		CFile file(fileDlg.GetFileName(),CFile::modeCreate | CFile::modeWrite);
		file.Write(result_word,strlen(result_word));
		file.Close();
	}
}


//��ʼ����֧����վ�б�
void CPicDownerDlg::IniList()
{
	//����б�
	((CListBox*)GetDlgItem(IDC_LIST1))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_COMBO1))->ResetContent();	
	
	status_word="��վ�б������";
	((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);    //status_word
	
	//��λ����ȡ��վ�б�
	TCHAR szDirectory[MAX_PATH];
	if(::GetCurrentDirectory(MAX_PATH,szDirectory))
	{
		file_path = szDirectory;
		status_word = file_path;
		status_word += "\\sites";			//status_word=szDirectory
		::SetCurrentDirectory(status_word);		
		if(TRUE == GetList())
		{
			((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);
			((CComboBox*)GetDlgItem(IDC_COMBO1))->GetWindowText(web_name);
			
			
			status_word="�б�������";
			((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
			
			//////////////////////////////////////////
			
			if (TRUE == GetNetValue())									//��ȡ��վ����
			{
				status_word="��⣬������� " + web_name + RPGenerator() + " ��Ч��!";
				((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
			}
			else
			{
				status_word="��վ������ʼ��ʧ��";
				((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
			}
			
		}
		else 
		{
			status_word = "�ðɣ�û�ж�ȡ�κ���վ����";
			((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
		}
	}
}

//��ʼ����վ�б���
bool CPicDownerDlg::GetList()
{
	CFileFind finder;
	status_word += "\\*.xml";
	BOOL bFind = FALSE;			
	
	bFind = finder.FindFile(status_word);				
	if (bFind)
	{
		while (bFind)
		{
			bFind=finder.FindNextFile();
			if (finder.IsDots())
			{
				continue;
			}
			if (finder.IsDirectory())	
			{
				continue;
			}
			web_list = finder.GetFileTitle();        	
			((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(web_list);
		}
		finder.Close();
		return 1;
	}
	else 
		return 0;
}

//RP������
CString CPicDownerDlg::RPGenerator()
{
	CString rp[5] = {"������","�������øж�","�������ж�","�����ؼ��ֵ��Ŀ�����","˲ɱ"};
	srand((unsigned)time(NULL));
	int i = rand();
	i %= 5;
	int j = rand();
	CString x,y;
	if (j%2 == 0)
		x = "+";
	else
		x = "-";
	int k = rand();
	k %= 10;
	y.Format("%d",k);
	CString ret = rp[i] + x + y;
	return ret;
}

//ѡ�������б��ı�web_name����ȡ��Ӧ��վ����
void CPicDownerDlg::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	((CComboBox*)GetDlgItem(IDC_COMBO1))->GetWindowText(web_name);
	
			if (TRUE == GetNetValue())									//��ȡ��վ����
			{
				status_word="��⣬������� " + web_name + RPGenerator() + " ��Ч��!";
				((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
			}
			else
			{
				status_word="��վ������ʼ��ʧ��";
				((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
			}
			
	
}

//��ȡ���ص��б�  x:tags .y:limit  
bool CPicDownerDlg::ListDown(CString x , CString y)
{
	status_word = x;
	if (x == "")
		status_word = "tagme";
	strURL = site_name ;		//�ؼ���					XML		tags
	strURL += limit_name ;
	strURL += y;
	strURL += tag_name ;			//��������					 XML	limit
	strURL += status_word ;
	strURL += page_name ;
	strURL += page ;				//page//////////////////////////////////////////////
	
		((CListBox*)GetDlgItem(IDC_LIST1))->AddString(strURL);   //status_word/////////////////////////////////////////////
	status_word = file_path + "\\xmls\\" ;			 //����xml��ָ��λ��  �ļ��� XML  imouto
	status_word += web_name;
	status_word += page;
	status_word += ".xml";
		((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word/////////////////////////////////////////////
/*���߳�
	
	//	((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word/////////////////////////////////////////////
	DOWN_FILE *down_file = new DOWN_FILE;
	down_file->down_url = strURL;
	down_file->down_to = status_word;
	//	down_file->list_box = &m_listbox;
	/////////////////////
	
	//	DWORD threadID;
	HANDLE hThread = CreateThread(NULL,0,DownFile,(LPVOID)down_file,0,NULL);
//	Sleep(1);
//	MsgWaitForMultipleObjects(2,;
	
//	ReleaseMutex(hMutex);
	
	DWORD ExitCode = 0;
	GetExitCodeThread(hThread,&ExitCode);
	while (1)
	{
		GetExitCodeThread(hThread,&ExitCode);
		if (ExitCode != STILL_ACTIVE)
				break;
	}


	//	status_word = (char *)ExitCode;
//	((CListBox*)GetDlgItem(IDC_LIST1))->AddString((CString)ExitCode);   //status_word
	CString code ;
	code.Format("%d",ExitCode);

	CloseHandle(hThread);
*/
	if (::URLDownloadToFile(NULL,strURL,status_word,0,NULL) == S_OK)
	return TRUE;
		else 
	return FALSE;
															//			return 	(bool)ExitCode;															 
/*
CXML *SelX;
																																						 SelX = m_XmlPtrArray.GetAt(find);
																																						 // Display the Attributes
																																						 long count = SelX->GetAttrCount();
																																						 m_AttrGrid.SetRowCount(count+1);
																																						 long i = 1;
																																						 CAttribute *a;
																																						 a = SelX->GetFirstAttribute();
																																						 while(a!=NULL && i<=count)
																																						 {
																																						 m_AttrGrid.SetItemText(i,0,a->GetAttributeName());
																																						 m_AttrGrid.SetItemText(i,1,a->GetAttributeText());
																																						 i++;
																																						 a = SelX->GetNextAttribute();
																																						 }
																																						 m_AttrGrid.Invalidate();
																																						 *pResult = 0;
																		*/
																		
																		//////////////////////////////////////////////////////////////////////////////////////////
																		/*
																		if (::URLDownloadToFile(NULL,strURL,status_word,0,NULL) == S_OK)
																		{
																		status_word = "��ȡ�б�ɹ�";
																		((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
																		return 1;
																		}
																		else 
																		{		
																		status_word = "��ȡ�б�ʧ��";
																		((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
																		return 0;
																		}
																		*/
}

//����XML�ļ����洢ͼƬ��ַ��lst_word
bool CPicDownerDlg::GetResult()
{
/*	CComPtr<IXMLDOMElement> spRootEle;
spDoc->get_documentElement(&spRootEle);
CComPtr<IXMLDOMNodeList> spNodeList;
spRootEle->get_childNodes(&spNodeList);
	*/	
	
	/*
	long nLen;
	spNodeList->get_length(&nLen);
	for (long i = 0;i != nLen; ++i)
	{
	CComPtr<IXMLDOMNode> spNode;
	spNodeList->get_item(i,&spNode);
	_variant_t vName = spNode->attributes->getNamedItem(L"file_url")->nodeName;
	status_word = (LPCWSTR)vName.bstrVal;
	((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
	
	  }
	  
	*/
	
	
	MSXML2::IXMLDOMDocumentPtr pDoc;
	HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	if (!SUCCEEDED(hr))
	{
		status_word = "XML��ȡʧ�ܣ�������ȱ��MSXML4.DLL";
		((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
		return FALSE;
		
	}
	else
	{
		status_word = file_path + "\\xmls\\" ;
		status_word += web_name ;
		status_word += page ;
		status_word += ".xml";
		
		_variant_t vFile((LPCTSTR)status_word);
		pDoc->async = VARIANT_FALSE;
		pDoc->validateOnParse = VARIANT_TRUE;
		VARIANT_BOOL bRet = pDoc->load(vFile);//�ļ��� XML
		
		if ( bRet != VARIANT_TRUE )
		{
			status_word = "��ַ�ĵ�δ�ܶ�ȡ";				
			((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
			return FALSE;
		}
		else
		{
			status_word = "�ĵ������ж�";
			
			((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
			MSXML2::IXMLDOMNodePtr pNode;
			
			status_word = "//" + xmlr_name ;
			pNode = (MSXML2::IXMLDOMNodePtr)(pDoc->selectSingleNode((_bstr_t)status_word));            //�ڵ�������� XML
			
			MSXML2::IXMLDOMNamedNodeMapPtr pAttrs = NULL;
			MSXML2::IXMLDOMNodePtr pAttrItem;
			
			
			pNode->get_attributes(&pAttrs);
			long nCount;
			//		result_word = "";
			pAttrs->get_length(&nCount);												//�õ����Գ���
			//		pAttrs->get_item(0,&pAttrItem);
			
			//		long nCount;
			//		pAttrs->get_length(&nCount);
			
			
			status_word = "count" ;												//���ص�ַ�������� XML
			//�������ԣ��ҵ����ص�ַ
			for ( int k = 0;k < nCount;k++)			
			{
				pAttrs->get_item(k , &pAttrItem);
				if ((char *) (_bstr_t)pAttrItem->nodeName == status_word)			//��λ���ص�ַ�������е�λ��
					break;
			}
			
			status_word = (char *) (_bstr_t)pAttrItem->nodeTypedValue;


			if("0" == status_word)
			{
				return FALSE;
			}
			else
			{
				pNode = pNode->GetfirstChild();
				//����ĵ��е����ص�ַ��result_word
				while (pNode != NULL)
				{
					pNode->get_attributes(&pAttrs);
					long nCount;
					//		result_word = "";
					pAttrs->get_length(&nCount);												//�õ����Գ���
					//		pAttrs->get_item(0,&pAttrItem);
					
					//		long nCount;
					//		pAttrs->get_length(&nCount);
					
					
					status_word = att_name ;												//���ص�ַ�������� XML
					//�������ԣ��ҵ����ص�ַ
					for ( int k = 0;k < nCount;k++)			
					{
						pAttrs->get_item(k , &pAttrItem);
						if ((char *) (_bstr_t)pAttrItem->nodeName == status_word)			//��λ���ص�ַ�������е�λ��
							break;
					}
					
					//			result_word += (char *) (_bstr_t)pAttrItem->nodeTypeString;
					
					
					result_word += (char *) (_bstr_t)pAttrItem->nodeTypedValue;				//ѭ��������ص�ַ��result_word
					result_word += "\r\n";
					count++;
					pNode = pNode->GetnextSibling();
				}
			return TRUE;
			}
		}
	}
	/*
	while (pNode==NULL)
	{
	MSXML2::IXMLDOMNamedNodeMapPtr pAttrs = NULL;
	MSXML2::IXMLDOMNodePtr pAttrItem;
	pNode->get_attributes(&pAttrs);
	//	childNode->get_attributes(&pAttrs);
	
	  long nCount;
	  pAttrs->get_length(&nCount);
	  result_word = "";
	  for (int i = 0;i < nCount ; i++)
	  {
	  pAttrs->get_item(i , &pAttrItem);
	  result_word += (char *) (_bstr_t)pAttrItem->nodeTypeString;
	  }
	  pDoc->get_nextSibling(&pNode);
	  }
	  /*	MSXML2::IXMLDOMElementPtr childNode;
	  childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//post"));
	  
		MSXML2::DOMNodeType nodeType;
		childNode->get_nodeType(&nodeType);
		*/	
		
		/*
		((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
		//	BSTR var;
		//	CString name;
		
		  ((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
		  //	childNode->get_nodeName(&var);
		  //	name = (char*)(_bstr_t)var;
		  
			((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
			//	VARIANT varVal;
			//	childNode->get_nodeTypedValue(&varVal);
			//	CString strValue = (char*)(_bstr_t)varVal;
			/*	MSXML2::IXMLDOMNamedNodeMapPtr pAttrs = NULL;
			MSXML2::IXMLDOMNodePtr pAttrItem;
			childNode->get_attributes(&pAttrs);
			
			  ((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
			  //	long nCount;
			  int nCount = 3;
			  
				//pAttrs->get_length(&nCount);
				for (int i = 0;i < nCount ;i++)
				{
				pAttrs->get_item(i,&pAttrItem);
				
				  CString strAttName = (char*)(_bstr_t)pAttrItem->nodeName;
				  //		CString strAttrValue = (char*)(_bstr_t)pAttrItem->nodeTypeString;
				  ((CListBox*)GetDlgItem(IDC_LIST1))->AddString(strAttName);   //status_word
				  }
				  */
				  
				  //	lst_word += "|\r\n";		//resultword+="|\r\n";
				  //	lst_word += key_word;    //���lst_word+=result_word;
}


//����XML��ȡ�����ص�ַ��result_word
/*
CString CPicDownerDlg::XmlAtt()
{
}
*/

//��ȡ��վ����
bool CPicDownerDlg::GetNetValue()
{
	
	
	MSXML2::IXMLDOMDocumentPtr pDoc;
	HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	if (!SUCCEEDED(hr))
	{
		status_word = "XML��ȡʧ�ܣ�������ȱ��MSXML4.DLL";
		((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
		return 0;		
	}
	else
	{
		
		status_word = file_path + "\\sites\\" ;
		status_word += web_name ;
		status_word += ".xml" ;
		
		_variant_t vFile((LPCTSTR)status_word);
		pDoc->async = VARIANT_FALSE;
		pDoc->validateOnParse = VARIANT_TRUE;
		VARIANT_BOOL bRet = pDoc->load(vFile);//�ļ��� XML
		
		if ( bRet != VARIANT_TRUE )
		{
			status_word = "δ��ȡ����վ�ĵ����������ĵ�����";				
			((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
			return 0;
		}
		else
		{
			status_word = "��վ���������ж�";
			
			((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
			
			MSXML2::IXMLDOMNodePtr pNode;
			pNode = (MSXML2::IXMLDOMNodePtr)(pDoc->selectSingleNode("//name"));            //�ڵ��� XML
			site_name = (char *) (_bstr_t)pNode->nodeTypedValue;
			pNode =  (MSXML2::IXMLDOMNodePtr)(pDoc->selectSingleNode("//limit"));            //�ڵ��� XML
			limit_name = (char *) (_bstr_t)pNode->nodeTypedValue;
			pNode = (MSXML2::IXMLDOMNodePtr)(pDoc->selectSingleNode("//page"));            //�ڵ��� XML
			page_name = (char *) (_bstr_t)pNode->nodeTypedValue;
			pNode = (MSXML2::IXMLDOMNodePtr)(pDoc->selectSingleNode("//tags"));            //�ڵ��� XML
			tag_name = (char *) (_bstr_t)pNode->nodeTypedValue;
			pNode = (MSXML2::IXMLDOMNodePtr)(pDoc->selectSingleNode("//xml_root"));            //�ڵ��� XML
			xmlr_name = (char *) (_bstr_t)pNode->nodeTypedValue;
			pNode = (MSXML2::IXMLDOMNodePtr)(pDoc->selectSingleNode("//att"));            //�ڵ��� XML
			att_name = (char *) (_bstr_t)pNode->nodeTypedValue;
			pNode = (MSXML2::IXMLDOMNodePtr)(pDoc->selectSingleNode("//page_limit"));            //�ڵ��� XML
			page_limit = (char *) (_bstr_t)pNode->nodeTypedValue;  
			
			PageInit(page_limit);
			
		}
		return 1;
	}
	
	/*
	web_name = Web_Name;
	
	  MSXML2::IXMLDOMDocumentPtr pDoc;
	  HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	  if (!SUCCEEDED(hr))
	  {
	  status_word = "��ȡ�ĵ�ʧ����";
	  ((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
	  }
	  else
	  {
	  status_word = file_path + "\\sites\\" ;
	  status_word += "imouto" ;
	  status_word += ".xml";
	  
		_variant_t vFile((LPCTSTR)status_word);
		pDoc->async = VARIANT_FALSE;
		pDoc->validateOnParse = VARIANT_TRUE;
		VARIANT_BOOL bRet = pDoc->load(vFile);//�ļ��� XML
		
		  if ( bRet != VARIANT_TRUE )
		  {
		  status_word = "��վ����δ�ܶ�ȡ";				
		  ((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
		  }
		  else
		  {
		  
			status_word = "�ĵ������ж�";
			
			  ((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
			  
				MSXML2::IXMLDOMNodePtr pNode;
				pNode = (MSXML2::IXMLDOMNodePtr)(pDoc->selectSingleNode("name"));            //�ڵ��� XML
				web_name = (char *) (_bstr_t)pNode->nodeTypedValue;
				((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
				pNode = (MSXML2::IXMLDOMNodePtr)(pDoc->selectSingleNode("limit"));            //�ڵ�������� XML
				pNode = (MSXML2::IXMLDOMNodePtr)(pDoc->selectSingleNode("tags"));            //�ڵ�������� XML
				pNode = (MSXML2::IXMLDOMNodePtr)(pDoc->selectSingleNode("file"));            //�ڵ�������� XML
				pNode = (MSXML2::IXMLDOMNodePtr)(pDoc->selectSingleNode("xml_root"));            //�ڵ�������� XML
				pNode = (MSXML2::IXMLDOMNodePtr)(pDoc->selectSingleNode("att"));            //�ڵ�������� XML
				
				  //}
				  
					}
	*/
	
}


DWORD WINAPI CPicDownerDlg::DownFile(LPVOID lpParameter)
{
	WaitForSingleObject(hMutex,INFINITE);
	//	Sleep(4000);
	CString down_to = ((DOWN_FILE*)lpParameter)->down_to;
	CString down_url = ((DOWN_FILE*)lpParameter)->down_url;
	//	CListBox* list_box = ((DOWN_FILE*)lpParameter)->list_box;
	delete lpParameter;
	
	
	//		down_to = "��ʼ�����б�";
	//		list_box->AddString(down_url);
	
	if (::URLDownloadToFile(NULL,down_url,down_to,0,NULL) == S_OK)
	{
		//		down_to = "�����б�ɹ�";
		//		list_box->AddString(down_url);
		//		((CListBox*)GetDlgItem(IDC_LIST1))->AddString(down_to);   //status_word
		
		ReleaseMutex(hMutex);
		int rt = 3;
		return rt;
	}
	else 
	{		
		//		down_to = "�����б�ʧ��";
		//		list_box->AddString(down_url);
		//		((CListBox*)GetDlgItem(IDC_LIST1))->AddString(down_to);   //status_word
		ReleaseMutex(hMutex);
		int rt = 2;
		return rt;
	}
	
	
}

void CPicDownerDlg::PageInit(CString page)
{
	int x = atoi(page);
	CString pg;
	((CComboBox*)GetDlgItem(IDC_COMBO2))->ResetContent();
	for (int y = 1;y <= x;y++)
	{
		pg.Format("%d",y);
		((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(pg);
	}
	((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(0);
	
}
