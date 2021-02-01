
// MixDlg.h : header file
//

#pragma once


// CMixDlg dialog
class CMixDlg : public CDialog
{
// Construction
public:
	CMixDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MIX_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedBtnBrowse1();
	afx_msg void OnBnClickedBtnBrowse2();
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

	CString MixPicture(CString sPic1, CString sPic2, CPoint ptPos, CString sSave);
};
