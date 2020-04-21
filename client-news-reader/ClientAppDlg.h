
// ClientAppDlg.h : 头文件
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

// CClientAppDlg 对话框
class CClientAppDlg : public CDialogEx
{
// 构造
public:
	CClientAppDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CLIENTAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	HBITMAP m_bmpback;
	CBrush m_bkBrush;
	NOTIFYICONDATA m_nid; //NOTIFYICONDATA作用是用来向任务栏托盘区域发送消息和自定义消息响应函数OnShowTask
	CMyButton m_exit;
	CMyButton m_min;
	CMyButton usrinfo;
	CMyButton m_search;
	CMyButton m_up_date; 
	CFont newFont;//静态文本框的优化
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
	//map容器关联ID
	CMap<int,int,map_date,map_date> title_map;
	queue<CString> q_pic;
	queue<CString> video_pic;

	//日期控件
	CMonthCalCtrl m_date;
	//正文窗口控件
	CShowDlg m_showdlg;

public:
	//右边新闻标题
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

	//左边视频标题
	CStatic m_static_eleven;
	CStatic m_static_thirteen;
	CStatic m_static_fourteen;
	CStatic m_static_fifteen;
	CStatic m_static_sixteen;
	char viotle[300];

	//下方图片标题
	CStatic m_picture1;
	CStatic m_static_picone;

	CStatic m_picture2;
	CStatic m_pic_two;

	CStatic m_picture3;
	CStatic m_static_picthree;

public:
	CWMPPlayer4 m_myplay;     // 播放地址关联
    CWMPControls m_controls;    // 控制按钮关联
    CWMPSettings m_setting;     // 设置按钮关联
    CWMPMedia    m_media;       // 媒体
	CMyProgress m_vio_pro;   //视频进度条
	CPlayButton m_play;       //视频播放
	CMyVoicePro m_pro_voice;  //声音进度条
	CPlayButton m_bu_voice;   //声音按钮
	CStatic m_vio;
	CStatic m_video_title;    //播放视频名字
	
	int num_voice;
	int re_thread_num;         //线程返回值
	bool show_static;          //控制初始化显示标题


	//搜索提示信息
	bool flas;
	int flasnumber;
	CStatic m_static_search;

public: 
	//网络传输相关
	TCP_net client;
	TCP_net Videoclient;
	TCP_net Jpgclient;
	HANDLE  m_hThread;
	CString tileTxtstr;
	CString tileJpgstr;
	CString tileVideostr;

public:
	//自定义函数
	int Set_Static_Title(); //为新闻设置标题和图片显示
	int Show_dlg();    //显示窗口
	int Recv_One_Page_Date(char* url);  //获取文本数据并显示
	int Recv_Up_Text();   //更新系统文本新闻标题
	int Show_One_News(char* url,char* name);  //供静态文本框调用显示新闻正文
	int date_section(int num);  //分割文本获取标题
	int Show_picture(char* str,int id);    //显示位图  
	int Show_Video();    //控件调用下载播放视频
	int Recv_show_jpg(int id,int jpid);     //控件调用接收图片
	int Show_static_picture();     //调用更新显示图片


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


