#pragma once
#include "MyButton.h"
#include "afxwin.h"

// CShowDlg �Ի���
extern char filenameTT[150];
extern char dirstr[50];

class CShowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CShowDlg)

public:
	CShowDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CShowDlg();

// �Ի�������
	enum { IDD = IDD_SHOW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	HBITMAP m_bmpsmallback;
	CBrush m_bksmallBrush;
	CMyButton m_SMexit;
	CStatic m_static_six;
	CEdit m_edit;
	CFont newFont;//��̬�ı�����Ż�
	CFont newFont1;//��̬�ı�����Ż�
	POINT Sold;
	CStatic m_show_picture;

public:
	int Show_TXT(CString str);
	int Show_picture(char* str,int id);    //��ʾλͼ

public:
	afx_msg void OnBnClickedSmexit();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
};


