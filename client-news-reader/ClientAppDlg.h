
// ClientAppDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "MyButton.h"
#include "PlayButton.h"
#include "CWMPControls.h"
#include "CWMPMedia.h"
#include "CWMPPlayer4.h"
#include "CWMPSettings.h"
#include "ShowDlg.h"
#include "afxcmn.h"
#include "afxdtctl.h"
#include "TCP_net.h"
#include "MyProgress.h"
#include "MyVoicePro.h"
#include "TCP_Message.h"
#include <queue>
#include <direct.h>
#include "ocx1_video.h"

using namespace std;

#define WM_SHOWTASK WM_USER+1

// CClientAppDlg �Ի���
class CClientAppDlg : public CDialogEx
{
// ����
public:
	CClientAppDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CLIENTAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	HBITMAP m_bmpback;
	CBrush m_bkBrush;
	NOTIFYICONDATA m_nid; //NOTIFYICONDATA������������������������������Ϣ���Զ�����Ϣ��Ӧ����OnShowTask
	CMyButton m_exit;
	CMyButton m_min;
	CMyButton usrinfo;
	CMyButton m_search;
	CMyButton m_up_date; 
	CFont newFont;//��̬�ı�����Ż�
public:
	afx_msg LRESULT OnShowTask(WPARAM wParam,LPARAM lParam);
	afx_msg void OnSize(UINT nType,int cx,int cy);
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedMin();
	afx_msg void OnStnClickedStaticOne();
	afx_msg void OnStnClickedStaticTwo();
	afx_msg void OnStnClickedStaticThree();
	afx_msg void OnStnClickedStaticFour();
	afx_msg void OnStnClickedStaticFive();
	afx_msg void OnStnClickedStaticSeven();
	afx_msg void OnStnClickedStaticEight();
	afx_msg void OnStnClickedStaticNine();
	afx_msg void OnStnClickedStaticTen();
	afx_msg void OnStnClickedStaticEleven();
	afx_msg void OnStnClickedStaticTwelve();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg LRESULT OnNcHitTest(CPoint point);

public: 
	//map��������ID
	CMap<int,int,map_date,map_date> title_map;
	queue<CString> q_pic;
	queue<CString> video_pic;

	//���ڿؼ�
	CMonthCalCtrl m_date;
	//���Ĵ��ڿؼ�
	CShowDlg m_showdlg;

public:
	//�ұ����ű���
	CStatic m_static_one;
	CStatic m_static_two;
	CStatic m_static_three;
	CStatic m_static_four;
	CStatic m_static_five;
	CStatic m_static_seven;
	CStatic m_static_eight;
	CStatic m_static_nine;
	CStatic m_static_ten;
	CStatic m_static_twelve;

	//�����Ƶ����
	CStatic m_static_eleven;
	CStatic m_static_thirteen;
	CStatic m_static_fourteen;
	CStatic m_static_fifteen;
	CStatic m_static_sixteen;
	char viotle[300];

	//�·�ͼƬ����
	CStatic m_picture1;
	CStatic m_static_picone;

	CStatic m_picture2;
	CStatic m_pic_two;

	CStatic m_picture3;
	CStatic m_static_picthree;

public:
	CWMPPlayer4 m_myplay;     // ���ŵ�ַ����
    CWMPControls m_controls;    // ���ư�ť����
    CWMPSettings m_setting;     // ���ð�ť����
    CWMPMedia    m_media;       // ý��
	CMyProgress m_vio_pro;   //��Ƶ������
	CPlayButton m_play;       //��Ƶ����
	CMyVoicePro m_pro_voice;  //����������
	CPlayButton m_bu_voice;   //������ť
	CStatic m_vio;
	CStatic m_video_title;    //������Ƶ����
	
	int num_voice;
	int re_thread_num;         //�̷߳���ֵ
	bool show_static;          //���Ƴ�ʼ����ʾ����


	//������ʾ��Ϣ
	bool flas;
	int flasnumber;
	CStatic m_static_search;

public: 
	//���紫�����
	TCP_net client;
	TCP_net Videoclient;
	TCP_net Jpgclient;
	HANDLE  m_hThread;
	CString tileTxtstr;
	CString tileJpgstr;
	CString tileVideostr;

public:
	//�Զ��庯��
	int Set_Static_Title(); //Ϊ�������ñ����ͼƬ��ʾ
	int Show_dlg();    //��ʾ����
	int Recv_One_Page_Date(char* url);  //��ȡ�ı����ݲ���ʾ
	int Recv_Up_Text();   //����ϵͳ�ı����ű���
	int Show_One_News(char* url,char* name);  //����̬�ı��������ʾ��������
	int date_section(int num);  //�ָ��ı���ȡ����
	int Show_picture(char* str,int id);    //��ʾλͼ  
	int Show_Video();    //�ؼ��������ز�����Ƶ
	int Recv_show_jpg(int id,int jpid);     //�ؼ����ý���ͼƬ
	int Show_static_picture();     //���ø�����ʾͼƬ


public:
	afx_msg void OnBnClickedSearch();
	afx_msg void OnMcnSelectMonthcalendar1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnStnClickedStaticthirteen();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBuVoice();	
	afx_msg void OnStnClickedPcture1();
	afx_msg void OnStnClickedPicture2();
	afx_msg void OnStnClickedPicture3();
	afx_msg void OnStnClickedStaticfourteen();
	afx_msg void OnStnClickedStaticfifteen();
	afx_msg void OnStnClickedStaticsixteen();
	afx_msg void OnStnClickedStaticPicone();
	afx_msg void OnStnClickedStaticPictow();
	afx_msg void OnStnClickedStaticPicthree();
	afx_msg void OnBnClickedUsrInfo();
	
};


