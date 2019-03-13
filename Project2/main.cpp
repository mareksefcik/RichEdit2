#include <afxwin.h>
#include <afxcmn.h> // CRichEditCtrl
#include <xstring>  // std::wstring
#include "resource.h"
#include <fstream> // std::wofstream

// https://docs.microsoft.com/en-us/cpp/mfc/reference/cricheditctrl-class?view=vs-2017
// https://docs.microsoft.com/en-us/windows/desktop/controls/about-rich-edit-controls
// https://docs.microsoft.com/en-us/cpp/mfc/reference/application-information-and-management?view=vs-2017#afxinitrichedit
// Aby som zmenil verziu rich edit contol-u, musim zmeninit *.rc a volanie AfxInit... (ktore sa vola pred volanim ::DoModal). 
// 1.0 -> "RichEdit"   , AfxInitRichEdit() , C:\Windows\System32\riched32.dll
// 2.0 -> "RichEdit20W", AfxInitRichEdit2(), C:\Windows\System32\riched20.dll
// 4.1 -> "RichEdit50W", AfxInitRichEdit5(), C:\Windows\System32\msftedit.dll
// Filter : name: = riched32.dll OR name : = riched20.dll OR name : = msftedit.dll
// Dll-ka sa da overit pomocou Spy++.

std::wstring proposedFont(_T("Arial"));
std::wstring proposedString(_T("A≤B◇C◊D")); // A≤B◇C◊D

class CMyDialog : public CDialog
{
public :
	// Adding comment.
	CRichEditCtrl m_richEditCtrl;
	CStatic m_text1;
	CEdit m_EditControl;

	CMyDialog(CWnd* pParent = NULL) : CDialog(CMyDialog::IDD, pParent){}

	enum { IDD = IDD_DIALOG1 };

	virtual void DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		DDX_Control(pDX, IDC_RICHEDIT21, m_richEditCtrl);
		DDX_Control(pDX, IDC_TEXT1, m_text1);
	}

	virtual BOOL OnInitDialog()
	{
		CDilog::OnInitDialog();
		// Changing comment.
		m_richEditCtrl.SetEventMask(m_richEditCtrl.GetEventMask() | ENM_CHANGE);
		m_richEditCtrl.SetWindowTextW(proposedString.c_str());
		
		CRichEditCtrl* pCRichEditCtrl = new CRichEditCtrl();
		static_cast<CWnd*>(pCRichEditCtrl)->Create(RICHEDIT_CLASS, NULL, WS_VISIBLE, CRect(250, 150, 350, 250), this, 0);
		//pCRichEditCtrl->Create(WS_VISIBLE, CRect(250, 150, 350, 250), this, 0);
		pCRichEditCtrl->SetWindowTextW(proposedString.c_str());

		// Set font.
		if (1)
		{
			CHARFORMAT cf = { 0 };
			m_richEditCtrl.GetDefaultCharFormat(cf);
			wcscpy_s(cf.szFaceName, _countof(cf.szFaceName), proposedFont.c_str());
			cf.yHeight = 300; // In twips.
			m_richEditCtrl.SetDefaultCharFormat(cf);
		}
		else
		{		
			CFont font;
			font.CreatePointFont(140, proposedFont.c_str());
			font.DeleteObject();
			m_richEditCtrl.SetFont(&font);
		}

		return true;
	}

	void CMyDialog::OnBnClickedOk()
	{
		//CDialog::OnOK();
	}

	void CMyDialog::OnChange()
	{
		CString this is second change without push;
		CHARFORMAT cf;
		long len;
	
		CString outputText;
		len = m_richEditCtrl.GetTextLength();
		for (long i = 0; i < len; i++)
		{
			m_richEditCtrl.SetSel(i, i + 1);
			m_richEditCtrl.GetSelectionCharFormat(cf);
			int ret = m_richEditCtrl.GetTextRange(i, i + 1, selText);
			wchar_t selChar = selText.GetAt(0);
			// %#06x : # menas add 0x, 0 meand left-pad with zeros, 6 is minimal number of characters, x is hexadecimal specifier
			outputText.Format(_T("%s%s : %#06x : %s \r\n"), outputText, selText, selChar, cf.szFaceName);
			// Changing multiple files
		}
	
		m_text1.SetWindowText(outputText);
		m_richEditCtrl.SetSel(-1, -1);
	}

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CMyDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CMyDialog::OnBnClickedOk)
	ON_EN_CHANGE(IDC_RICHEDIT21, &CMyDialog::OnChange)
END_MESSAGE_MAP()

class CMyApp : public CWinApp
{
public:
	CMyApp() {}
	virtual BOOL InitInstance()
	{
		// Ak inicializujem vsetky rich edit dll-ky, nic by sa nemalo stat, verziu ovladam v templejte.
		::AfxInitRichEdit();
		::AfxInitRichEdit2();
		::AfxInitRichEdit5();
		CWinApp::InitInstance();
		CMyDialog myDialog;
		m_pMainWnd = &myDialog;
		INT_PTR nResponse = myDialog.DoModal();
		return FALSE;
	}
};

CMyApp theApp;