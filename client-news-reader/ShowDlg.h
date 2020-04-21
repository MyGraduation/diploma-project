#pragma once
#include "MyButton.h"
#include "afxwin.h"

// CShowDlg 对话框
extern char filenameTT[150];
extern char dirstr[50];

class CShowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CShowDlg)

public:
	CShowDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CShowDlg();

// 对话框数据
	enum { IDD = IDD_SHOW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	HBITMAP m_bmpsmallback;
	CBrush m_bksmallBrush;
	CMyButton m_SMexit;
	CStatic m_static_six;
	CEdit m_edit;
	CFont newFont;//静态文本框的优化
	CFont newFont1;//静态文本框的优化
	POINT Sold;
	CStatic m_show_picture;

public:
	int Show_TXT(CString str);
	int Show_picture(char* str,int id);    //显示位图

public:
	afx_msg void OnBnClickedSmexit();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
};


