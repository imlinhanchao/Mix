
// MixDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Mix.h"
#include "MixDlg.h"
#include "atlimage.h"
#include "Path.h"
using namespace Easy;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMixDlg dialog




CMixDlg::CMixDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMixDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMixDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMixDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_BROWSE1, &CMixDlg::OnBnClickedBtnBrowse1)
	ON_BN_CLICKED(IDC_BTN_BROWSE2, &CMixDlg::OnBnClickedBtnBrowse2)
	ON_BN_CLICKED(IDOK, &CMixDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMixDlg message handlers

BOOL CMixDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

	SetDlgItemInt(IDC_EDIT_X, 0);
	SetDlgItemInt(IDC_EDIT_Y, 0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMixDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMixDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMixDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMixDlg::OnBnClickedBtnBrowse1()
{
	CString sPath = Path::Browse(_T("Image File|*.jpg;*.bmp;*.jpeg;||"), _T(""), TRUE, _T(""));
	if(!sPath.IsEmpty()) SetDlgItemText(IDC_EDIT_PIC1, sPath);
}

void CMixDlg::OnBnClickedBtnBrowse2()
{
	CString sPath = Path::Browse(_T("Image File|*.png;||"), _T(""), TRUE, _T(""));
	if(!sPath.IsEmpty()) SetDlgItemText(IDC_EDIT_PIC2, sPath);
}

void CMixDlg::OnBnClickedOk()
{
	CString sPath1, sPath2;
	GetDlgItemText(IDC_EDIT_PIC1, sPath1);
	GetDlgItemText(IDC_EDIT_PIC2, sPath2);

	if (sPath1.IsEmpty() || sPath2.IsEmpty()) {
		MessageBox(_T("Browse picture first!!"));
		return;
	}

	CPoint ptPos(GetDlgItemInt(IDC_EDIT_X), GetDlgItemInt(IDC_EDIT_Y));
	CString sSave = Path::Browse(_T("Image File|*.jpg;*.bmp;*.jpeg;||"), _T(""), FALSE, _T(""));
	if (sSave.IsEmpty()) return;

	MixPicture(sPath1, sPath2, ptPos, sSave);
}

CString CMixDlg::MixPicture( CString sPic1, CString sPic2, CPoint ptPos, CString sSave )
{
	ATL::CImage img1, img2;
	img1.Load(sPic1); img2.Load(sPic2);
	int nWidth1 = img1.GetWidth(), nHeight1 = img1.GetHeight();
	int nWidth2 = img2.GetWidth(), nHeight2 = img2.GetHeight();

	for (int i = 0; i < nWidth2; i++)
	{
		int nX = ptPos.x + i;
		if (nX > nWidth1) break;
		for (int j = 0; j < nHeight2; j++)
		{
			int nY = ptPos.y + j;
			if (nY > nHeight1) break;

			COLORREF clr1 = img1.GetPixel(nX, nY);
			COLORREF clr2 = img2.GetPixel(i, j);
			BYTE* pAlpha = (BYTE*)img2.GetPixelAddress(i, j) + 3;
			int nAlpha = (*pAlpha), nRAlpha = 255 - (*pAlpha);
			
			DWORD dwR = (GetRValue(clr2) * nAlpha + GetRValue(clr1) * nRAlpha) / 255.0 + 0.5;
			DWORD dwG = (GetGValue(clr2) * nAlpha + GetGValue(clr1) * nRAlpha) / 255.0 + 0.5;
			DWORD dwB = (GetBValue(clr2) * nAlpha + GetBValue(clr1) * nRAlpha) / 255.0 + 0.5;
			COLORREF clrFinal = RGB(dwR, dwG, dwB);

			img1.SetPixel(nX, nY, clrFinal);
		}
	}

	img1.Save(sSave);

	return sSave;
}