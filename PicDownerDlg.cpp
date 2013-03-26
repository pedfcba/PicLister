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
	
	IniList();		//初始化
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
	
	//获取关键字
	GetDlgItemText(IDC_EDIT2,key_word);
	
	result_word = "";
	
	//利用关键字进行搜索
	
	status_word="搜索中～";
	((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);    //status_word
	limit = "100";
	
	((CComboBox*)GetDlgItem(IDC_COMBO2))->GetWindowText(page);
	int x = atoi (page);
	for (int y = 1 ; y <= x ; y++)
	{
		page.Format("%d",y);
		status_word = "正在获取第" + page + "页" ;
		((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);    //status_word
		
		hMutex = CreateMutex(NULL,FALSE,NULL);							//互斥锁
		//	Sleep(1);	
		//		WaitForSingleObject(hMutex,INFINITE);
		//		ReleaseMutex(hMutex);
			status_word="地址文档获取中～";
			((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);    //status_word
		if (ListDown(key_word , limit) == TRUE)
		{
			//获取下载地址，结果保存到lst_word
			
			//		WaitForSingleObject(hMutex,INFINITE);
			if (FALSE == GetResult())
			{
				status_word="no body here but us chicks，无结果返回恩" ;
				((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);    //status_word
				break;
			}
			
			//		ReleaseMutex(hMutex);
			
		}
		else
		{
			//		WaitForSingleObject(hMutex,INFINITE);
			status_word="列表文档获取失败，可能是：网络RP了，网站RP了，您RP了";
			((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);    //status_word
			
			//		ReleaseMutex(hMutex);
//			GetResult();		/////////////////////////////////////////////////
			
			
		}
	}
	
	if(count != 0)
	{
		
		
		CString x;
		x.Format("%d",count);
		status_word = "分析完毕，共返回" + x + "个结果，可以保存了哦";
		((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);  	//status_word
		
		GetDlgItem(IDC_SAVE)->EnableWindow(TRUE);
		count = 0;
	}
	
		GetDlgItem(IDC_ANL)->EnableWindow(TRUE);
	//返回目标
}

void CPicDownerDlg::OnSave() 
{
	// TODO: Add your control notification handler code here
	//保存结果到列表文件

	CFileDialog fileDlg(FALSE);
	fileDlg.m_ofn.lpstrTitle="信仰は儚き人間の為に";
	fileDlg.m_ofn.lpstrFilter="列表文件 (*.lst)\0*.lst\0\0";
	fileDlg.m_ofn.lpstrDefExt="lst";
	if(fileDlg.DoModal()&&(fileDlg.GetFileName()!=""))
	{
		CFile file(fileDlg.GetFileName(),CFile::modeCreate | CFile::modeWrite);
		file.Write(result_word,strlen(result_word));
		file.Close();
	}
}


//初始化可支持网站列表
void CPicDownerDlg::IniList()
{
	//清空列表
	((CListBox*)GetDlgItem(IDC_LIST1))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_COMBO1))->ResetContent();	
	
	status_word="网站列表加载中";
	((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);    //status_word
	
	//定位及读取网站列表
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
			
			
			status_word="列表加载完毕";
			((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
			
			//////////////////////////////////////////
			
			if (TRUE == GetNetValue())									//获取网站参数
			{
				status_word="糟糕，您获得了 " + web_name + RPGenerator() + " 的效果!";
				((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
			}
			else
			{
				status_word="网站参数初始化失败";
				((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
			}
			
		}
		else 
		{
			status_word = "好吧，没有读取任何网站。。";
			((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
		}
	}
}

//初始化网站列表项
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

//RP生成器
CString CPicDownerDlg::RPGenerator()
{
	CString rp[5] = {"的正义","服务器好感度","费洛蒙中毒","将您关键字掉的可能性","瞬杀"};
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

//选择下拉列表后改变web_name，读取相应网站内容
void CPicDownerDlg::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	((CComboBox*)GetDlgItem(IDC_COMBO1))->GetWindowText(web_name);
	
			if (TRUE == GetNetValue())									//获取网站参数
			{
				status_word="糟糕，您获得了 " + web_name + RPGenerator() + " 的效果!";
				((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
			}
			else
			{
				status_word="网站参数初始化失败";
				((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
			}
			
	
}

//获取返回的列表  x:tags .y:limit  
bool CPicDownerDlg::ListDown(CString x , CString y)
{
	status_word = x;
	if (x == "")
		status_word = "tagme";
	strURL = site_name ;		//关键字					XML		tags
	strURL += limit_name ;
	strURL += y;
	strURL += tag_name ;			//下载数量					 XML	limit
	strURL += status_word ;
	strURL += page_name ;
	strURL += page ;				//page//////////////////////////////////////////////
	
		((CListBox*)GetDlgItem(IDC_LIST1))->AddString(strURL);   //status_word/////////////////////////////////////////////
	status_word = file_path + "\\xmls\\" ;			 //下载xml到指定位置  文件名 XML  imouto
	status_word += web_name;
	status_word += page;
	status_word += ".xml";
		((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word/////////////////////////////////////////////
/*多线程
	
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
																		status_word = "获取列表成功";
																		((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
																		return 1;
																		}
																		else 
																		{		
																		status_word = "获取列表失败";
																		((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
																		return 0;
																		}
																		*/
}

//分析XML文件并存储图片地址到lst_word
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
		status_word = "XML读取失败，可能是缺少MSXML4.DLL";
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
		VARIANT_BOOL bRet = pDoc->load(vFile);//文件名 XML
		
		if ( bRet != VARIANT_TRUE )
		{
			status_word = "地址文档未能读取";				
			((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
			return FALSE;
		}
		else
		{
			status_word = "文档分析中恩";
			
			((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
			MSXML2::IXMLDOMNodePtr pNode;
			
			status_word = "//" + xmlr_name ;
			pNode = (MSXML2::IXMLDOMNodePtr)(pDoc->selectSingleNode((_bstr_t)status_word));            //节点的属性名 XML
			
			MSXML2::IXMLDOMNamedNodeMapPtr pAttrs = NULL;
			MSXML2::IXMLDOMNodePtr pAttrItem;
			
			
			pNode->get_attributes(&pAttrs);
			long nCount;
			//		result_word = "";
			pAttrs->get_length(&nCount);												//得到属性长度
			//		pAttrs->get_item(0,&pAttrItem);
			
			//		long nCount;
			//		pAttrs->get_length(&nCount);
			
			
			status_word = "count" ;												//下载地址的属性名 XML
			//遍历属性，找到下载地址
			for ( int k = 0;k < nCount;k++)			
			{
				pAttrs->get_item(k , &pAttrItem);
				if ((char *) (_bstr_t)pAttrItem->nodeName == status_word)			//定位下载地址在属性中的位置
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
				//添加文档中的下载地址到result_word
				while (pNode != NULL)
				{
					pNode->get_attributes(&pAttrs);
					long nCount;
					//		result_word = "";
					pAttrs->get_length(&nCount);												//得到属性长度
					//		pAttrs->get_item(0,&pAttrItem);
					
					//		long nCount;
					//		pAttrs->get_length(&nCount);
					
					
					status_word = att_name ;												//下载地址的属性名 XML
					//遍历属性，找到下载地址
					for ( int k = 0;k < nCount;k++)			
					{
						pAttrs->get_item(k , &pAttrItem);
						if ((char *) (_bstr_t)pAttrItem->nodeName == status_word)			//定位下载地址在属性中的位置
							break;
					}
					
					//			result_word += (char *) (_bstr_t)pAttrItem->nodeTypeString;
					
					
					result_word += (char *) (_bstr_t)pAttrItem->nodeTypedValue;				//循环添加下载地址到result_word
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
				  //	lst_word += key_word;    //结果lst_word+=result_word;
}


//分析XML并取出下载地址到result_word
/*
CString CPicDownerDlg::XmlAtt()
{
}
*/

//获取网站参数
bool CPicDownerDlg::GetNetValue()
{
	
	
	MSXML2::IXMLDOMDocumentPtr pDoc;
	HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	if (!SUCCEEDED(hr))
	{
		status_word = "XML读取失败，可能是缺少MSXML4.DLL";
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
		VARIANT_BOOL bRet = pDoc->load(vFile);//文件名 XML
		
		if ( bRet != VARIANT_TRUE )
		{
			status_word = "未读取到网站文档，可能是文档错误";				
			((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
			return 0;
		}
		else
		{
			status_word = "网站参数加载中恩";
			
			((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
			
			MSXML2::IXMLDOMNodePtr pNode;
			pNode = (MSXML2::IXMLDOMNodePtr)(pDoc->selectSingleNode("//name"));            //节点名 XML
			site_name = (char *) (_bstr_t)pNode->nodeTypedValue;
			pNode =  (MSXML2::IXMLDOMNodePtr)(pDoc->selectSingleNode("//limit"));            //节点名 XML
			limit_name = (char *) (_bstr_t)pNode->nodeTypedValue;
			pNode = (MSXML2::IXMLDOMNodePtr)(pDoc->selectSingleNode("//page"));            //节点名 XML
			page_name = (char *) (_bstr_t)pNode->nodeTypedValue;
			pNode = (MSXML2::IXMLDOMNodePtr)(pDoc->selectSingleNode("//tags"));            //节点名 XML
			tag_name = (char *) (_bstr_t)pNode->nodeTypedValue;
			pNode = (MSXML2::IXMLDOMNodePtr)(pDoc->selectSingleNode("//xml_root"));            //节点名 XML
			xmlr_name = (char *) (_bstr_t)pNode->nodeTypedValue;
			pNode = (MSXML2::IXMLDOMNodePtr)(pDoc->selectSingleNode("//att"));            //节点名 XML
			att_name = (char *) (_bstr_t)pNode->nodeTypedValue;
			pNode = (MSXML2::IXMLDOMNodePtr)(pDoc->selectSingleNode("//page_limit"));            //节点名 XML
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
	  status_word = "读取文档失败了";
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
		VARIANT_BOOL bRet = pDoc->load(vFile);//文件名 XML
		
		  if ( bRet != VARIANT_TRUE )
		  {
		  status_word = "网站参数未能读取";				
		  ((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
		  }
		  else
		  {
		  
			status_word = "文档分析中恩";
			
			  ((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
			  
				MSXML2::IXMLDOMNodePtr pNode;
				pNode = (MSXML2::IXMLDOMNodePtr)(pDoc->selectSingleNode("name"));            //节点名 XML
				web_name = (char *) (_bstr_t)pNode->nodeTypedValue;
				((CListBox*)GetDlgItem(IDC_LIST1))->AddString(status_word);   //status_word
				pNode = (MSXML2::IXMLDOMNodePtr)(pDoc->selectSingleNode("limit"));            //节点的属性名 XML
				pNode = (MSXML2::IXMLDOMNodePtr)(pDoc->selectSingleNode("tags"));            //节点的属性名 XML
				pNode = (MSXML2::IXMLDOMNodePtr)(pDoc->selectSingleNode("file"));            //节点的属性名 XML
				pNode = (MSXML2::IXMLDOMNodePtr)(pDoc->selectSingleNode("xml_root"));            //节点的属性名 XML
				pNode = (MSXML2::IXMLDOMNodePtr)(pDoc->selectSingleNode("att"));            //节点的属性名 XML
				
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
	
	
	//		down_to = "开始下载列表咯";
	//		list_box->AddString(down_url);
	
	if (::URLDownloadToFile(NULL,down_url,down_to,0,NULL) == S_OK)
	{
		//		down_to = "下载列表成功";
		//		list_box->AddString(down_url);
		//		((CListBox*)GetDlgItem(IDC_LIST1))->AddString(down_to);   //status_word
		
		ReleaseMutex(hMutex);
		int rt = 3;
		return rt;
	}
	else 
	{		
		//		down_to = "下载列表失败";
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
