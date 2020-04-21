
// ClientAppDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ClientApp.h"
#include "ClientAppDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

char dirstr[50];
char filenameTXT[150];
char filenameJPG[150];
char filenameVIDEO[150];
char filenameTT[150];

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CClientAppDlg �Ի���

CClientAppDlg::CClientAppDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClientAppDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	flas = TRUE;
	show_static = TRUE;
	num_voice = 50;
	re_thread_num = 1;
	flasnumber = 0;
	m_hThread = NULL;
	memset(viotle,'\0',sizeof(viotle));
	tileTxtstr = "";
	tileJpgstr = "";
	tileVideostr = "";

}	

void CClientAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXIT, m_exit);
	DDX_Control(pDX, IDC_MIN, m_min);
	DDX_Control(pDX, IDC_SEARCH, m_search);
	DDX_Control(pDX, IDC_STATIC_ONE, m_static_one);
	DDX_Control(pDX, IDC_STATIC_TWO, m_static_two);
	DDX_Control(pDX, IDC_STATIC_THREE, m_static_three);
	DDX_Control(pDX, IDC_STATIC_FOUR, m_static_four);
	DDX_Control(pDX, IDC_STATIC_FIVE, m_static_five);
	DDX_Control(pDX, IDC_STATIC_SEVEN, m_static_seven);
	DDX_Control(pDX, IDC_STATIC_EIGHT, m_static_eight);
	DDX_Control(pDX, IDC_STATIC_NINE, m_static_nine);
	DDX_Control(pDX, IDC_STATIC_TEN, m_static_ten);
	DDX_Control(pDX, IDC_STATIC_ELEVEN, m_static_eleven);
	DDX_Control(pDX, IDC_STATIC_TWELVE, m_static_twelve);
	DDX_Control(pDX, IDC_STATIC_thirteen, m_static_thirteen);
	DDX_Control(pDX, IDC_STATIC_fourteen, m_static_fourteen);
	DDX_Control(pDX, IDC_STATIC_fifteen, m_static_fifteen);
	DDX_Control(pDX, IDC_STATIC_sixteen, m_static_sixteen);
	DDX_Control(pDX, IDC_MONTHCALENDAR1, m_date);
	DDX_Control(pDX, IDC_STATIC_SEARCH, m_static_search);
	DDX_Control(pDX, IDC_OCX1_Video, m_myplay);
	DDX_Control(pDX, IDC_BUTTON1, m_up_date);
	DDX_Control(pDX, IDC_PROGRESS1, m_vio_pro);
	DDX_Control(pDX, IDC_BUTTON2, m_play);
	DDX_Control(pDX, IDC_PRO_VOICE, m_pro_voice);
	DDX_Control(pDX, IDC_BU_VOICE, m_bu_voice);
	DDX_Control(pDX, IDC_PCTURE1, m_picture1);
	DDX_Control(pDX, IDC_PICTURE2, m_picture2);
	DDX_Control(pDX, IDC_PICTURE3, m_picture3);
	DDX_Control(pDX, IDC_STATIC_PICONE, m_static_picone);
	DDX_Control(pDX, IDC_STATIC_PICTOW, m_pic_two);
	DDX_Control(pDX, IDC_STATIC_PICTHREE, m_static_picthree);
	DDX_Control(pDX, IDC_STATIC_VIDEOTITLE, m_video_title);
	DDX_Control(pDX, IDC_STATIC_VIO, m_vio);
	DDX_Control(pDX, IDC_USR_INFO, usrinfo);
}

BEGIN_MESSAGE_MAP(CClientAppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EXIT, &CClientAppDlg::OnBnClickedExit)
	ON_BN_CLICKED(IDC_MIN, &CClientAppDlg::OnBnClickedMin)
	ON_MESSAGE(WM_SHOWTASK,&CClientAppDlg::OnShowTask)
	ON_STN_CLICKED(IDC_STATIC_ONE, &CClientAppDlg::OnStnClickedStaticOne)
	ON_STN_CLICKED(IDC_STATIC_TWO, &CClientAppDlg::OnStnClickedStaticTwo)
	ON_STN_CLICKED(IDC_STATIC_THREE, &CClientAppDlg::OnStnClickedStaticThree)
	ON_STN_CLICKED(IDC_STATIC_FOUR, &CClientAppDlg::OnStnClickedStaticFour)
	ON_STN_CLICKED(IDC_STATIC_FIVE, &CClientAppDlg::OnStnClickedStaticFive)
	ON_STN_CLICKED(IDC_STATIC_SEVEN, &CClientAppDlg::OnStnClickedStaticSeven)
	ON_STN_CLICKED(IDC_STATIC_EIGHT, &CClientAppDlg::OnStnClickedStaticEight)
	ON_STN_CLICKED(IDC_STATIC_NINE, &CClientAppDlg::OnStnClickedStaticNine)
	ON_STN_CLICKED(IDC_STATIC_TEN, &CClientAppDlg::OnStnClickedStaticTen)
	ON_STN_CLICKED(IDC_STATIC_ELEVEN, &CClientAppDlg::OnStnClickedStaticEleven)
	ON_WM_CTLCOLOR()	
	ON_STN_CLICKED(IDC_STATIC_TWELVE, &CClientAppDlg::OnStnClickedStaticTwelve)
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDC_SEARCH, &CClientAppDlg::OnBnClickedSearch)
	ON_NOTIFY(MCN_SELECT, IDC_MONTHCALENDAR1, &CClientAppDlg::OnMcnSelectMonthcalendar1)
	ON_STN_CLICKED(IDC_STATIC_thirteen, &CClientAppDlg::OnStnClickedStaticthirteen)
	ON_WM_MOVE()
	ON_BN_CLICKED(IDC_BUTTON1, &CClientAppDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CClientAppDlg::OnBnClickedButton2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BU_VOICE, &CClientAppDlg::OnBnClickedBuVoice)
	ON_STN_CLICKED(IDC_PCTURE1, &CClientAppDlg::OnStnClickedPcture1)
	ON_STN_CLICKED(IDC_PICTURE2, &CClientAppDlg::OnStnClickedPicture2)
	ON_STN_CLICKED(IDC_PICTURE3, &CClientAppDlg::OnStnClickedPicture3)
	ON_STN_CLICKED(IDC_STATIC_fourteen, &CClientAppDlg::OnStnClickedStaticfourteen)
	ON_STN_CLICKED(IDC_STATIC_fifteen, &CClientAppDlg::OnStnClickedStaticfifteen)
	ON_STN_CLICKED(IDC_STATIC_sixteen, &CClientAppDlg::OnStnClickedStaticsixteen)
	ON_STN_CLICKED(IDC_STATIC_PICONE, &CClientAppDlg::OnStnClickedStaticPicone)
	ON_STN_CLICKED(IDC_STATIC_PICTOW, &CClientAppDlg::OnStnClickedStaticPictow)
	ON_STN_CLICKED(IDC_STATIC_PICTHREE, &CClientAppDlg::OnStnClickedStaticPicthree)
	ON_BN_CLICKED(IDC_USR_INFO, &CClientAppDlg::OnBnClickedUsrInfo)
END_MESSAGE_MAP()

// CClientAppDlg ��Ϣ�������

void CALLBACK MyTimerProc(HWND hWnd,UINT nMsg,UINT_PTR nIDEvent, DWORD dwTime)
{
	CClientAppDlg *pthis = (CClientAppDlg*)CClientAppDlg::FromHandle(hWnd);
	
	while(!pthis->q_pic.empty())
	{
		remove(pthis->q_pic.front());
		pthis->q_pic.pop();
	}

	while(!pthis->video_pic.empty())
	{
		remove(pthis->video_pic.front());
		pthis->video_pic.pop();
	}

}

BOOL CClientAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	TCHAR appstr[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, appstr, MAX_PATH);

	string dirstr1 = appstr;
	
	dirstr1.erase(dirstr1.find("\\"), dirstr1.length());
	strcpy_s(dirstr, sizeof(dirstr), dirstr1.c_str());
	strcat_s(dirstr, sizeof(dirstr), "\\ClientApp");



	if (!PathIsDirectory(dirstr))
	{
		CreateDirectory(dirstr, NULL);
	}

	strcpy_s(filenameTXT, sizeof(filenameTXT), dirstr);
	strcpy_s(filenameTXT, sizeof(filenameTXT), "\\text_title.txt");

	strcpy_s(filenameVIDEO, sizeof(filenameVIDEO), dirstr);
	strcpy_s(filenameVIDEO, sizeof(filenameVIDEO), "\\text_video_title.txt");

	strcpy_s(filenameJPG, sizeof(filenameJPG), dirstr);
	strcpy_s(filenameJPG, sizeof(filenameJPG), "\\text_jpg_title.txt");

	strcpy_s(filenameTT, sizeof(filenameTT), dirstr);
	strcat_s(filenameTT, sizeof(filenameTT), "\\tt.txt");

	//��ʼ������
	m_bmpback = ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BACK));
	BITMAP hb;
	GetObject(m_bmpback,sizeof(BITMAP),(LPBYTE)&hb);
	MoveWindow(50,70,hb.bmWidth,hb.bmHeight);
	CBitmap bmpTmp;
	bmpTmp.Attach(m_bmpback);
	m_bkBrush.CreatePatternBrush(&bmpTmp);

	//λͼ�����˳���
	m_exit.SetButtonBmp(IDB_EXIT);
	m_exit.InitMyButton(1347,10,40,40);
	//λͼ������С����
	m_min.SetButtonBmp(IDB_MIN);
	m_min.InitMyButton(1300, 10, 40, 40);
	//λͼ����������Ϣ
	usrinfo.SetButtonBmp(IDB_MIN);
	usrinfo.InitMyButton(1253, 10, 40, 40);
	//λͼ����������
	m_search.SetButtonBmp(IDB_SEARCH);
	m_search.InitMyButton(300,15,40,40);
	m_static_search.MoveWindow(350,25,300,20);

	//λͼ����������Ϣ��
	m_up_date.SetButtonBmp(IDB_BMP_UP);
	m_up_date.InitMyButton(994,73,40,40);

	//��Ƶ����
	m_myplay.MoveWindow(300,80,585,350);
	m_controls=static_cast<CWMPControls>(m_myplay.get_controls());
	m_setting=static_cast<CWMPSettings>(m_myplay.get_settings());
	m_vio_pro.InitMyProgress(320,450,530,8);
	char palyname[100];
	strcpy_s(palyname,sizeof(palyname), dirstr);
	strcat_s(palyname, sizeof(palyname),"\\cc.mp4");
	m_myplay.put_URL(palyname);
	m_media=m_myplay.newMedia(palyname);
	m_vio_pro.SetRGB(RGB(255,128,0),RGB(192,192,192));
	m_play.SetButtonBmp(IDB_BMP_PLAY);
	m_play.InitMyButton(857,439,30,30);
	m_vio.MoveWindow(270,500,80,20);
	m_video_title.MoveWindow(350,500,585,20);

	m_pro_voice.MoveWindow(920,340,8,100);
	m_pro_voice.SetPos(50);
	m_bu_voice.SetButtonBmp(IDB_BMP_VOICE);
	m_bu_voice.InitMyButton(913,450,20,20);
	

	m_nid.cbSize = sizeof(NOTIFYICONDATA);
	m_nid.hWnd = this->m_hWnd;
	m_nid.uID = IDR_MAINFRAME;
	m_nid.uFlags = NIF_ICON|NIF_MESSAGE |NIF_TIP;
	m_nid.uCallbackMessage = WM_SHOWTASK;
	m_nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	strcpy_s(m_nid.szTip,strlen("Hot News")+1,"Hot News");
	Shell_NotifyIcon(NIM_ADD,&m_nid); // �����������ͼ��

	//�Ż���̬�ı�����������ɫ
	CFont* font;
	font = m_static_one.GetFont();//��ȡcfont����
	LOGFONT lf;
	font->GetLogFont(&lf);//��ȡLOGFONT�ṹ��
	lf.lfHeight = 25;//�޸������С
	lf.lfItalic = FALSE;  //��б
	lf.lfWeight = 700; //�޸�����Ĵ�ϸ
	newFont.CreateFontIndirect(&lf);//����һ���µ�����
	m_static_one.SetFont(&newFont);
	m_static_two.SetFont(&newFont);
	m_static_three.SetFont(&newFont);
	m_static_four.SetFont(&newFont);
	m_static_five.SetFont(&newFont);
	m_static_seven.SetFont(&newFont);
	m_static_eight.SetFont(&newFont);
	m_static_nine.SetFont(&newFont);
	m_static_ten.SetFont(&newFont);
	m_static_twelve.SetFont(&newFont);
	m_static_eleven.SetFont(&newFont);
	m_static_thirteen.SetFont(&newFont);
	m_static_fourteen.SetFont(&newFont);
	m_static_fifteen.SetFont(&newFont);
	m_static_sixteen.SetFont(&newFont);
	m_static_picone.SetFont(&newFont);
	m_pic_two.SetFont(&newFont);
	m_static_picthree.SetFont(&newFont);



	//�����ұ����ֱ������ĸ�������λ��
	m_static_one.MoveWindow(1060,110,300,50);
	m_static_two.MoveWindow(1060,180,300,50);
	m_static_three.MoveWindow(1060,250,300,50);
	m_static_four.MoveWindow(1060,320,300,50);
	m_static_five.MoveWindow(1060,390,300,50);
	m_static_seven.MoveWindow(1060,460,300,50);
	m_static_eight.MoveWindow(1060,530,300,50);
	m_static_nine.MoveWindow(1060,600,300,50);
	m_static_ten.MoveWindow(1060,670,300,50);
	m_static_twelve.MoveWindow(1060,740,300,50);

	//���������Ƶ�������Ĵ�С��λ��
	m_static_eleven.MoveWindow(40,280,200,50);
	m_static_thirteen.MoveWindow(40,360,200,50);
	m_static_fourteen.MoveWindow(40,440,200,50);
	m_static_fifteen.MoveWindow(40,520,200,50);
	m_static_sixteen.MoveWindow(40,600,200,50);


	//�·�ͼƬ����
	m_picture1.MoveWindow(300,600,200,100);
	m_static_picone.MoveWindow(300,710,200,100);
	m_picture2.MoveWindow(550,600,200,100);
	m_pic_two.MoveWindow(550,710,200,100);
	m_picture3.MoveWindow(800,600,200,100);
	m_static_picthree.MoveWindow(800,710,200,100);

	

	


	//���ӷ�����
	if(client.connect_server("39.96.190.77",8000) == 0)
	{
		m_static_search.SetWindowText("���ӷ�����ʧ��,���Ժ�����");
		m_static_search.ShowWindow(SW_HIDE);
		m_static_search.UpdateData(false);
		m_static_search.ShowWindow(SW_SHOW);
		
	}

	//������Ƶ����˿�
	if(Videoclient.connect_server("39.96.190.77",8000) == 0)
	{
		m_static_search.SetWindowText("���ӷ�����ʧ��,���Ժ�����");
		m_static_search.ShowWindow(SW_HIDE);
		m_static_search.UpdateData(false);
		m_static_search.ShowWindow(SW_SHOW);
		
	}


	//����ͼƬ����˿�
	if(Jpgclient.connect_server("39.96.190.77",8000) == 0)
	{
		m_static_search.SetWindowText("���ӷ�����ʧ��,���Ժ�����");
		m_static_search.ShowWindow(SW_HIDE);
		m_static_search.UpdateData(false);
		m_static_search.ShowWindow(SW_SHOW);
		
	}

	
	//���ñ���
	Recv_Up_Text();
	date_section(2);
	date_section(3);
	date_section(4);
	Set_Static_Title();

	CWnd::SetTimer(1,100,NULL);
	
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CClientAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CClientAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

void CClientAppDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	int time = 0;
	int a = 0;
	double dou = 0;
	double kk = 0;


	
	
	if(re_thread_num == 3)
	{	
		m_static_search.ShowWindow(SW_HIDE);
		re_thread_num = 1;
		char name[100];
		char vfilename[150];
		char videname[50];
		
		m_video_title.GetWindowText(name,100);
		strcpy_s(vfilename, sizeof(vfilename), dirstr);
		sprintf_s(videname, "\\%s.mp4", name);
		strcat_s(vfilename, sizeof(vfilename), videname);

		m_myplay.put_URL(vfilename);	
		m_media=m_myplay.newMedia(vfilename);	
		video_pic.push(vfilename);
		
	}

	a = m_media.get_duration();

	if(m_vio_pro.flage == true)
	{
	
		dou = m_controls.get_currentPosition();
		kk = dou/a;
		time = kk*100;
		m_vio_pro.SetPos(time);

	}
	else
	{
		dou = m_vio_pro.GetPos();
		kk = dou / 100;
		time = a * kk;
		m_controls.put_currentPosition(time);
		
	}

	//��������
	if(m_pro_voice.flags)
	{
		a = m_pro_voice.GetPos();
		m_setting.put_volume(a);
	}
		
	if(show_static)
	{
		Show_static_picture();
		show_static = FALSE;
	}

	if(flasnumber)
	{
		flasnumber -= 5;
		if(flasnumber == 0)
		{
			m_static_search.ShowWindow(SW_HIDE);
			flas = TRUE;
		}
	
	}
		
	
	CDialogEx::OnTimer(nIDEvent);
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CClientAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CClientAppDlg::OnBnClickedExit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	UINT i;
	i = MessageBox(TEXT("ȷ��Ҫ�˳�������"),TEXT("��ܰ��ʾ"),MB_YESNO|MB_ICONQUESTION);
	if(i == IDNO)
	{
		return;
	}


	closesocket(client.client);
	closesocket(Videoclient.client);
	closesocket(Jpgclient.client);
	remove(filenameTXT);
	remove(filenameVIDEO);
	remove(filenameJPG);

	CWnd::SetTimer(2,1,&MyTimerProc);

	show_static = TRUE;
	Shell_NotifyIcon(NIM_DELETE,&m_nid); // ��������ɾ��ͼ��


	CDialog::OnOK();
}

void CClientAppDlg::OnBnClickedMin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->ShowWindow(SW_MINIMIZE);
}

LRESULT CClientAppDlg::OnShowTask(WPARAM wParam,LPARAM lParam)
{
	if(wParam != IDR_MAINFRAME) 
		return 1;
	switch(lParam)
	{
		case WM_RBUTTONUP:               //�Ҽ�����ʱ�����˵�
        {
			LPPOINT lpoint = new tagPOINT;
			::GetCursorPos(lpoint);// �õ����λ��
			CMenu menu;
			menu.CreatePopupMenu();// ����һ������ʽ�˵�
			menu.AppendMenu(MF_STRING, WM_DESTROY,"�˳�");
			menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x ,lpoint->y,this);
			HMENU hmenu = menu.Detach();
			menu.DestroyMenu();
			delete lpoint;
			break;
		}
	    case WM_LBUTTONDBLCLK:// ˫������Ĵ���
	   {
			this->ShowWindow(SW_SHOWNORMAL);// ��ʾ������ 
			break;
	   }
	   return 0;
	}

	return 0;
}
//������С��ʱ����������ͼ��ĳ���
void CClientAppDlg::OnSize(UINT nType,int cx,int cy)
{
	CDialog::OnSize(nType,cx,cy);
	if (nType == SIZE_MINIMIZED)
	{
		ShowWindow(SW_HIDE);//������С������������ͼ��
	}
}

void CClientAppDlg::OnStnClickedStaticOne()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int k = m_static_one.GetDlgCtrlID();
	Show_One_News(title_map[k].url,title_map[k].title);
	m_showdlg.Show_picture(title_map[k].jpg_name,IDC_TXT_PICTURE);
	
}

void CClientAppDlg::OnStnClickedStaticTwo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int k = m_static_two.GetDlgCtrlID();
	Show_One_News(title_map[k].url,title_map[k].title);
	m_showdlg.Show_picture(title_map[k].jpg_name,IDC_TXT_PICTURE);
}

void CClientAppDlg::OnStnClickedStaticThree()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int k = m_static_three.GetDlgCtrlID();
	Show_One_News(title_map[k].url,title_map[k].title);
	m_showdlg.Show_picture(title_map[k].jpg_name,IDC_TXT_PICTURE);

}

void CClientAppDlg::OnStnClickedStaticFour()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int k = m_static_four.GetDlgCtrlID();
	Show_One_News(title_map[k].url,title_map[k].title);
	m_showdlg.Show_picture(title_map[k].jpg_name,IDC_TXT_PICTURE);

}

void CClientAppDlg::OnStnClickedStaticFive()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int k = m_static_five.GetDlgCtrlID();
	Show_One_News(title_map[k].url,title_map[k].title);
	m_showdlg.Show_picture(title_map[k].jpg_name,IDC_TXT_PICTURE);

}

void CClientAppDlg::OnStnClickedStaticSeven()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int k = m_static_seven.GetDlgCtrlID();
	Show_One_News(title_map[k].url,title_map[k].title);
	m_showdlg.Show_picture(title_map[k].jpg_name,IDC_TXT_PICTURE);

}

void CClientAppDlg::OnStnClickedStaticEight()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int k = m_static_eight.GetDlgCtrlID();
	Show_One_News(title_map[k].url,title_map[k].title);
	m_showdlg.Show_picture(title_map[k].jpg_name,IDC_TXT_PICTURE);

}

void CClientAppDlg::OnStnClickedStaticNine()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int k = m_static_nine.GetDlgCtrlID();
	Show_One_News(title_map[k].url,title_map[k].title);
	m_showdlg.Show_picture(title_map[k].jpg_name,IDC_TXT_PICTURE);

}

void CClientAppDlg::OnStnClickedStaticTen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int k = m_static_ten.GetDlgCtrlID();
	Show_One_News(title_map[k].url,title_map[k].title);
	m_showdlg.Show_picture(title_map[k].jpg_name,IDC_TXT_PICTURE);

}

void CClientAppDlg::OnStnClickedStaticTwelve()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int k = m_static_twelve.GetDlgCtrlID();
	Show_One_News(title_map[k].url,title_map[k].title);
	m_showdlg.Show_picture(title_map[k].jpg_name,IDC_TXT_PICTURE);

}

DWORD WINAPI recv_video( LPVOID lpParameter)
{
	CClientAppDlg *pthis = (CClientAppDlg*)lpParameter;
	cli_date_t date;
	TCP_net videonet;
	char name[100];
	char vfilename[150];
	_SYSTEMTIME  tt;
	GetLocalTime(&tt);
	
	pthis->Show_Video();

	int num = tt.wHour + tt.wSecond + tt.wMilliseconds;
	pthis->re_thread_num = num;

	if(videonet.connect_server("39.96.190.77",8000) == 0)
	{
		pthis->re_thread_num = -1;
		pthis->Show_Video();
		pthis->re_thread_num = 1;
		return 0;
		
	}
	

	if(videonet.ifcon == TRUE)
	{	
		strcpy_s(date.buf,sizeof(date.buf),pthis->viotle);
		strcpy_s(date.url,sizeof(date.url),pthis->viotle);
		date.number = 5;
		date.buflen = strlen(date.buf);
		
		if(videonet.Send_message(date) == 0)
		{
			pthis->re_thread_num = 0;
			pthis->Show_Video();
			pthis->re_thread_num = 1;
			return 0;
			
		}

	
		char videname[50];

		pthis->m_video_title.GetWindowText(name,100);
		strcpy_s(vfilename,sizeof(vfilename), dirstr);
		sprintf_s(videname,"\\%s.mp4",name);
		strcat_s(vfilename,sizeof(vfilename), videname);
		
		strcpy_s(date.buf,sizeof(date.buf),vfilename);

		if(videonet.Recv_video(&date) == 0)
		{
			pthis->re_thread_num = -1;
			pthis->Show_Video();
			pthis->re_thread_num = 1;
			return 0;

		}
	}

	closesocket(videonet.client);

	if(pthis->re_thread_num == num)
	{
		pthis->re_thread_num = 3;

	}else
	{
		remove(vfilename);
	}

	while(!pthis->video_pic.empty())
	{
		remove(pthis->video_pic.front());
		pthis->video_pic.pop();
	}

	return 1;

}

int CClientAppDlg::Show_Video()
{
	if(re_thread_num == 1)
	{
		m_static_search.SetWindowText("���ڽ��շ���������,���Ե�...");
		m_static_search.ShowWindow(SW_HIDE);
		m_static_search.ShowWindow(SW_SHOW);

		return -1;
	}

	
	if(re_thread_num == 0)
	{
		m_static_search.SetWindowText("���������������ʧ��");
		m_static_search.ShowWindow(SW_HIDE);
		m_static_search.ShowWindow(SW_SHOW);
		return -1;
	}

	if(re_thread_num == -1)
	{
		m_static_search.SetWindowText("���շ���������ʧ��");
		m_static_search.ShowWindow(SW_HIDE);
		m_static_search.ShowWindow(SW_SHOW);
		return -1;
	}

	return 1;

}

void CClientAppDlg::OnStnClickedStaticEleven()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int k = m_static_eleven.GetDlgCtrlID();
	memset(viotle,'\0',sizeof(viotle));
	m_myplay.close();
	strcpy_s(viotle,sizeof(viotle),title_map[k].url);

	m_video_title.SetWindowText(title_map[k].title);
	m_video_title.ShowWindow(SW_HIDE);
	m_video_title.UpdateData(false);
	m_video_title.ShowWindow(SW_SHOW);

	re_thread_num = 1;

	if(!m_hThread)
	{
			m_hThread = CreateThread(
									    NULL, //��ȫ����
										0 ,// ջ Ĭ��1MB
										&recv_video ,// �̺߳���
										(void*)this , //�̲߳���
										0 ,//������ʶ 0 ��������CREATE_SUSPENDED  ����
										NULL //�߳�ID
									  );
			CloseHandle(m_hThread);
			m_hThread = NULL;
	}


}

void CClientAppDlg::OnStnClickedStaticthirteen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int k = m_static_thirteen.GetDlgCtrlID();
	memset(viotle,'\0',sizeof(viotle));
	m_myplay.close();
	strcpy_s(viotle,sizeof(viotle),title_map[k].url);

	m_video_title.SetWindowText(title_map[k].title);
	m_video_title.ShowWindow(SW_HIDE);
	m_video_title.UpdateData(false);
	m_video_title.ShowWindow(SW_SHOW);

	re_thread_num = 1;
	
	if(!m_hThread)
	{
			m_hThread = CreateThread(
									    NULL, //��ȫ����
										0 ,// ջ Ĭ��1MB
										&recv_video ,// �̺߳���
										(void*)this , //�̲߳���
										0 ,//������ʶ 0 ��������CREATE_SUSPENDED  ����
										NULL //�߳�ID
									  );
			CloseHandle(m_hThread);
			m_hThread = NULL;
	}
	

}

void CClientAppDlg::OnStnClickedStaticfourteen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int k = m_static_fourteen.GetDlgCtrlID();
	memset(viotle,'\0',sizeof(viotle));
	m_myplay.close();
	strcpy_s(viotle,sizeof(viotle),title_map[k].url);

	m_video_title.SetWindowText(title_map[k].title);
	m_video_title.ShowWindow(SW_HIDE);
	m_video_title.UpdateData(false);
	m_video_title.ShowWindow(SW_SHOW);

	re_thread_num = 1;
	
	if(!m_hThread)
	{
			m_hThread = CreateThread(
									    NULL, //��ȫ����
										0 ,// ջ Ĭ��1MB
										&recv_video ,// �̺߳���
										(void*)this , //�̲߳���
										0 ,//������ʶ 0 ��������CREATE_SUSPENDED  ����
										NULL //�߳�ID
									  );
			CloseHandle(m_hThread);
			m_hThread = NULL;
	}

}

void CClientAppDlg::OnStnClickedStaticfifteen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int k = m_static_fifteen.GetDlgCtrlID();
	memset(viotle,'\0',sizeof(viotle));
	m_myplay.close();
	strcpy_s(viotle,sizeof(viotle),title_map[k].url);

	m_video_title.SetWindowText(title_map[k].title);
	m_video_title.ShowWindow(SW_HIDE);
	m_video_title.UpdateData(false);
	m_video_title.ShowWindow(SW_SHOW);
	

	if(!m_hThread)
	{
			m_hThread = CreateThread(
									    NULL, //��ȫ����
										0 ,// ջ Ĭ��1MB
										&recv_video ,// �̺߳���
										(void*)this , //�̲߳���
										0 ,//������ʶ 0 ��������CREATE_SUSPENDED  ����
										NULL //�߳�ID
									  );
			CloseHandle(m_hThread);
			m_hThread = NULL;
	}

}

void CClientAppDlg::OnStnClickedStaticsixteen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int k = m_static_sixteen.GetDlgCtrlID();
	m_myplay.close();
	memset(viotle,'\0',sizeof(viotle));
	strcpy_s(viotle,sizeof(viotle),title_map[k].url);

	m_video_title.SetWindowText(title_map[k].title);
	m_video_title.ShowWindow(SW_HIDE);
	m_video_title.UpdateData(false);
	m_video_title.ShowWindow(SW_SHOW);


	if(!m_hThread)
	{
			m_hThread = CreateThread(
									    NULL, //��ȫ����
										0 ,// ջ Ĭ��1MB
										&recv_video ,// �̺߳���
										(void*)this , //�̲߳���
										0 ,//������ʶ 0 ��������CREATE_SUSPENDED  ����
										NULL //�߳�ID
									  );
			CloseHandle(m_hThread);
			m_hThread = NULL;
	}

}

HBRUSH CClientAppDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)//CLIENTAPP_DIALOG(����)�е�����-��Ϣ����-WM_CTLCOLOR
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if(pWnd->GetDlgCtrlID() == IDC_STATIC_ONE         || 
		pWnd->GetDlgCtrlID() == IDC_STATIC_TWO        || 
		pWnd->GetDlgCtrlID() == IDC_STATIC_THREE      ||
		pWnd->GetDlgCtrlID() == IDC_STATIC_FOUR       ||
		pWnd->GetDlgCtrlID() == IDC_STATIC_FIVE       ||
		pWnd->GetDlgCtrlID() == IDC_STATIC_SEVEN      ||
		pWnd->GetDlgCtrlID() == IDC_STATIC_EIGHT      ||
		pWnd->GetDlgCtrlID() == IDC_STATIC_NINE       ||
		pWnd->GetDlgCtrlID() == IDC_STATIC_TEN	        ||
		pWnd->GetDlgCtrlID() == IDC_STATIC_TWELVE        ) //pWnd->GetDlgCtrlID() == IDC_STATIC_ELEVEN)///�жϷ�����Ϣ�Ŀռ��Ƿ��Ǹþ�̬�ı���
	{
		pDC->SetTextColor(RGB(192,192,192));////�����ı���ɫΪ��ɫ
		pDC->SetBkMode(TRANSPARENT);//�����ı�����ģʽΪ͸��
		hbr = CreateSolidBrush(RGB(0,0,0));//�ؼ��ı���ɫΪ��ɫ
	}

	if(pWnd->GetDlgCtrlID() == IDC_STATIC_ELEVEN   ||
	 pWnd->GetDlgCtrlID() == IDC_STATIC_thirteen   ||
	 pWnd->GetDlgCtrlID() == IDC_STATIC_fourteen   ||
	 pWnd->GetDlgCtrlID() == IDC_STATIC_fifteen    ||
	 pWnd->GetDlgCtrlID() == IDC_STATIC_sixteen      ) 
	{
		pDC->SetTextColor(RGB(0,0,0));
		pDC->SetBkMode(TRANSPARENT);
		return HBRUSH(GetStockObject(HOLLOW_BRUSH));
	}
	if(pWnd->GetDlgCtrlID() == IDC_STATIC_SEARCH)
	{
		pDC->SetTextColor(RGB(255,255,0));
		pDC->SetBkMode(TRANSPARENT);
		return HBRUSH(GetStockObject(HOLLOW_BRUSH));
	}

	if(pWnd->GetDlgCtrlID() == IDC_STATIC_PICONE     ||
	   pWnd->GetDlgCtrlID() == IDC_STATIC_PICTOW     ||
	   pWnd->GetDlgCtrlID() == IDC_STATIC_PICTHREE     )
	{
		pDC->SetTextColor(RGB(252,222,100));
		pDC->SetBkMode(TRANSPARENT);
		return HBRUSH(GetStockObject(HOLLOW_BRUSH));
	}

	if(pWnd->GetDlgCtrlID() == IDC_STATIC_VIDEOTITLE  ||
	    pWnd->GetDlgCtrlID() == IDC_STATIC_VIO          )
	{
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkMode(TRANSPARENT);
		return HBRUSH(GetStockObject(HOLLOW_BRUSH));

	}


	if(pWnd == this)
	{
		return m_bkBrush;
	}
	return hbr;
}

LRESULT CClientAppDlg::OnNcHitTest(CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect mRect;
	GetWindowRect(&mRect);
	CPoint m_point;
	m_point.x = mRect.left;
	m_point.y = mRect.top;

	if(point.x >= m_point.x && point.x <= (m_point.x+1400) && point.y >= m_point.y && point.y <= (m_point.y+50))
	{
		return HTCAPTION;
	}

	return CDialogEx::OnNcHitTest(point);
}

void CClientAppDlg::OnBnClickedSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(flas)
	{
		m_date.MoveWindow(15,70,230,210);
		m_date.ShowWindow(SW_SHOW);
		m_static_search.SetWindowText("ָ���鿴ĳһ������");
		m_static_search.ShowWindow(SW_HIDE);
		m_static_search.UpdateData(false);
		m_static_search.ShowWindow(SW_SHOW);
		flas = FALSE;
	}else
	{
		m_date.ShowWindow(SW_HIDE);
		m_static_search.ShowWindow(SW_HIDE);
		flas = TRUE;
	}



}

void CClientAppDlg::OnMcnSelectMonthcalendar1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);

	m_static_search.ShowWindow(SW_HIDE);
	flas = TRUE;
	int upbool = 1;


	remove(filenameTXT);
	remove(filenameJPG);
	remove(filenameVIDEO);

	cli_date_t date;
	m_date.ShowWindow(SW_HIDE);
	CTime tt;
	m_date.GetCurSel(tt);

	sprintf_s(date.url,sizeof(date.url),"%d%d%d",tt.GetYear(),tt.GetMonth(),tt.GetDay());

	if(client.ifcon == TRUE)
	{	
		strcpy_s(date.buf,sizeof(date.buf),"��������");
		date.number = 4;
		date.buflen = strlen(date.buf);
		
		if(client.Send_message(date) == 0)
		{
			m_static_search.SetWindowText("�ͻ��˷�������ʧ��");
			m_static_search.ShowWindow(SW_HIDE);
			m_static_search.UpdateData(false);
			m_static_search.ShowWindow(SW_SHOW);
			return;
		}
				

		if(client.Recv_message(&date,2) == 0)
		{
			m_static_search.SetWindowText("��Ǹ��������û�и��������");
			m_static_search.ShowWindow(SW_HIDE);
			m_static_search.UpdateData(false);
			m_static_search.ShowWindow(SW_SHOW);
			upbool = 0;
		}

		if(client.Recv_message(&date,3) == 0)
		{
			m_static_search.SetWindowText("��Ǹ��������û�и��������");
			m_static_search.ShowWindow(SW_HIDE);
			m_static_search.UpdateData(false);
			m_static_search.ShowWindow(SW_SHOW);
			upbool = 0;
		}

		if(client.Recv_message(&date,4) == 0)
		{
			m_static_search.SetWindowText("��Ǹ��������û�и��������");
			m_static_search.ShowWindow(SW_HIDE);
			m_static_search.UpdateData(false);
			m_static_search.ShowWindow(SW_SHOW);
			upbool = 0;
		}

		if(upbool)
		{
			tileTxtstr = "";
			tileJpgstr = "";
			tileVideostr = "";
			date_section(2);
			date_section(3);
			date_section(4);
			Set_Static_Title();
			show_static = TRUE;
		}else
		{
			flasnumber = 100;

		}

	}else
	{
		m_static_search.SetWindowText("δ���ӵ�������");
		m_static_search.ShowWindow(SW_HIDE);
		m_static_search.UpdateData(false);
		m_static_search.ShowWindow(SW_SHOW);
	}



}

void CClientAppDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);
	if(m_showdlg.GetSafeHwnd())
	{
		m_showdlg.MoveWindow(1400+x,80+y,400,770);
	}
	
}

int CClientAppDlg::Show_dlg()
{
	CRect rectDlg;
	GetWindowRect(rectDlg);
	if(!m_showdlg.GetSafeHwnd())
	{
		m_showdlg.Create(IDD_SHOW_DLG,this);
		m_showdlg.MoveWindow(1400+rectDlg.left,80+rectDlg.top,400,770);
		m_showdlg.ShowWindow(SW_SHOW);
		return 1;
	}
	else
	{
		m_showdlg.ShowWindow(SW_SHOW);
		return 1;
	}

}

int CClientAppDlg::Recv_Up_Text()  //����ϵͳ�ı����ű���
{
	cli_date_t date;

	if(client.ifcon == TRUE)
	{	
		strcpy_s(date.buf,sizeof(date.buf),"��������");
		strcpy_s(date.url,sizeof(date.url),"NULL");
		date.number = 2;
		date.buflen = strlen(date.buf);
		
		if(client.Send_message(date) == 0)
		{
			m_static_search.SetWindowText("�ͻ��˷�������ʧ��");
			m_static_search.ShowWindow(SW_HIDE);
			m_static_search.UpdateData(false);
			m_static_search.ShowWindow(SW_SHOW);
		}
				

		if(client.Recv_message(&date,2) == 0)
		{
			m_static_search.SetWindowText("���շ���������ʧ��");
			m_static_search.ShowWindow(SW_HIDE);
			m_static_search.UpdateData(false);
			m_static_search.ShowWindow(SW_SHOW);
		}
	
		if(client.Recv_message(&date,3) == 0)
		{
			m_static_search.SetWindowText("���շ���������ʧ��");
			m_static_search.ShowWindow(SW_HIDE);
			m_static_search.UpdateData(false);
			m_static_search.ShowWindow(SW_SHOW);
		}
		
		if(client.Recv_message(&date,4) == 0)
		{
			m_static_search.SetWindowText("���շ���������ʧ��");
			m_static_search.ShowWindow(SW_HIDE);
			m_static_search.UpdateData(false);
			m_static_search.ShowWindow(SW_SHOW);
		}


	}
	else
	{
		m_static_search.SetWindowText("δ���ӵ�������");
		m_static_search.ShowWindow(SW_HIDE);
		m_static_search.UpdateData(false);
		m_static_search.ShowWindow(SW_SHOW);
		return 0;
	}

	return 1;
}

void CClientAppDlg::OnBnClickedButton1()  //������������
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	date_section(2);
	date_section(3);
	date_section(4);
	Set_Static_Title();
	show_static = TRUE;

}

int CClientAppDlg::date_section(int num)
{
	FILE* fd = nullptr;
	CString delstr("");
	CString tilestr("");
	CString jpgstr("");
	char jpgch[100];
	map_date date;
	int fbegin = 0;
	int fend = 0;
	
	memset(date.url,'\0',sizeof(date.url));
	memset(date.title,'\0',sizeof(date.title));
	memset(date.jpg_url,'\0',sizeof(date.jpg_url));
	memset(date.jpg_name,'\0',sizeof(date.jpg_name));
	memset(jpgch,'\0',sizeof(jpgch));

	int i = 0;
	int nbegin = -1;
	int nend = -1;





	if(num == 2)
	{
		fbegin = 1006;
		fend = 1015;
		if(tileTxtstr == "")
		{
			fopen_s(&fd, filenameTXT,"r");
			if(fd == nullptr)
			{
				m_static_search.SetWindowText("δ���յ�����������");
				m_static_search.ShowWindow(SW_HIDE);
				m_static_search.UpdateData(false);
				m_static_search.ShowWindow(SW_SHOW);
				return 0;
			}

			while(!feof(fd))
			{
				tileTxtstr.AppendChar(getc(fd));
			}

			fclose(fd);
			tilestr = tileTxtstr;

		}else
		{
			tilestr = tileTxtstr;
		}
	}

	if(num == 3)
	{
		fbegin = 1020;
		fend = 1024;
		if(tileVideostr == "")
		{
			fopen_s(&fd, filenameVIDEO,"r");
			if(fd == nullptr)
			{
				m_static_search.SetWindowText("δ���յ�����������");
				m_static_search.ShowWindow(SW_HIDE);
				m_static_search.UpdateData(false);
				m_static_search.ShowWindow(SW_SHOW);
				return 0;
			}

			while(!feof(fd))
			{
				tileVideostr.AppendChar(getc(fd));
			}

			fclose(fd);
			tilestr = tileVideostr;

		}else
		{
			tilestr = tileVideostr;
		}
	}

	if(num == 4)
	{
		fbegin = 1040;
		fend = 1042;
		if(tileJpgstr == "")
		{
			fopen_s(&fd, filenameJPG,"r");
			if(fd == nullptr)
			{
				m_static_search.SetWindowText("δ���յ�����������");
				m_static_search.ShowWindow(SW_HIDE);
				m_static_search.UpdateData(false);
				m_static_search.ShowWindow(SW_SHOW);
				return 0;
			}

			while(!feof(fd))
			{
				tileJpgstr.AppendChar(getc(fd));
			}

			fclose(fd);
			tilestr = tileJpgstr;

		}else
		{
			tilestr = tileJpgstr;
		}
	}


	int del = -1;

	for(i = fbegin;i <= fend;i++)
	{
		nbegin = tilestr.Find("<1>");
		if(nbegin != -1)
		{
			//url
			nbegin = nbegin + strlen("<1>");
			nend = tilestr.Find("<1>",nbegin);
			tilestr.Delete(0,nbegin);
			strncpy_s(date.url,sizeof(date.url),tilestr,nend-nbegin);
			nbegin = nend-nbegin+strlen("<1>");
			tilestr.Delete(0,nbegin);
		
			//<2>
			nbegin = tilestr.Find("<2>");
			if(nbegin != 0)
			{
				i--;
				del = tilestr.Find("\n");
				tilestr.Delete(0,del);
				memset(date.url,'\0',sizeof(date.url));
				continue;
			}
			nbegin = nbegin + strlen("<2>");
			nend = tilestr.Find("<2>",nbegin);
			tilestr.Delete(0,nbegin);

			if(num == 2 || num == 3)
			{
				if(nend-nbegin <= sizeof(date.title))
					strncpy_s(date.title,sizeof(date.title),tilestr,nend-nbegin);
				else
				{
					del = tilestr.Find("\n");
					tilestr.Delete(0,del);
					i--;
					memset(date.url,'\0',sizeof(date.url));
					memset(date.title,'\0',sizeof(date.title));
					memset(date.jpg_url,'\0',sizeof(date.jpg_url));
					delstr = "";
					continue;

				}
				
			}else
			{
				if(nend-nbegin <= sizeof(jpgch))
					strncpy_s(jpgch,sizeof(jpgch),tilestr,nend-nbegin);
				else
				{
					del = tilestr.Find("\n");
					tilestr.Delete(0,del);
					i--;
					memset(date.url,'\0',sizeof(date.url));
					memset(date.title,'\0',sizeof(date.title));
					memset(date.jpg_url,'\0',sizeof(date.jpg_url));
					delstr = "";
					continue;

				}
			}

			nbegin = nend-nbegin+strlen("<2>");
			tilestr.Delete(0,nbegin);

			//<3>
			if(num == 4)
			{
				nbegin = tilestr.Find("<3>");
				if(nbegin != 0)
				{
					i--;
					del = tilestr.Find("\n");
					tilestr.Delete(0,del);
					memset(date.url,'\0',sizeof(date.url));
					memset(date.title,'\0',sizeof(date.title));
					memset(date.jpg_url,'\0',sizeof(date.jpg_url));
					memset(jpgch,'\0',sizeof(jpgch));
					continue;

				}
				nbegin = nbegin + strlen("<3>");
				nend = tilestr.Find("<3>",nbegin);
				tilestr.Delete(0,nbegin);
				if(nend-nbegin <= sizeof(date.title))
					strncpy_s(date.title,sizeof(date.title),tilestr,nend-nbegin);
				else
				{
					del = tilestr.Find("\n");
					tilestr.Delete(0,del);
					i--;
					memset(date.url,'\0',sizeof(date.url));
					memset(date.title,'\0',sizeof(date.title));
					memset(date.jpg_url,'\0',sizeof(date.jpg_url));
					memset(jpgch,'\0',sizeof(jpgch));
					delstr = "";
					continue;

				}
				nbegin = nend-nbegin+strlen("<3>");
				tilestr.Delete(0,nbegin);
			}


			delstr = date.title;
			if(delstr.Find("��") != -1 || delstr.Find("<1>") != -1||
				delstr.Find("<2>") != -1 )
			{
				i--;
				memset(date.url,'\0',sizeof(date.url));
				memset(date.title,'\0',sizeof(date.title));
				memset(date.jpg_url,'\0',sizeof(date.jpg_url));
				memset(jpgch,'\0',sizeof(jpgch));
				delstr = "";
				continue;
			}

			delstr = "";

			delstr = date.url;
			if(delstr.Find("��") != -1|| delstr.Find("<1>") != -1|| delstr.Find(" ") != -1 ||
				delstr.Find("<2>") != -1 || delstr.Find("\n") != -1)
			{
				i--;
				memset(date.url,'\0',sizeof(date.url));
				memset(date.title,'\0',sizeof(date.title));
				memset(date.jpg_url,'\0',sizeof(date.jpg_url));
				memset(jpgch,'\0',sizeof(jpgch));
				continue;
			}

			delstr = "";

			if(num == 4)
			{
				delstr = jpgch;
				if(delstr.Find("��") != -1 || delstr.Find("<1>") != -1||
				delstr.Find("<2>") != -1 || delstr.Find("<3>") != -1)
				{
					i--;
					memset(date.url,'\0',sizeof(date.url));
					memset(date.title,'\0',sizeof(date.title));
					memset(date.jpg_url,'\0',sizeof(date.jpg_url));
					memset(jpgch,'\0',sizeof(jpgch));
					continue;
				}

				jpgstr = date.url;
				nbegin = jpgstr.Find("//");
				nbegin = nbegin + strlen("//");
				nend = jpgstr.Find("/",nbegin);
				strncpy_s(date.jpg_url,sizeof(jpgch),jpgstr,nend);
				strcat_s(date.jpg_url,sizeof(date.jpg_url),jpgch);

				jpgstr = "";

				jpgstr = date.jpg_url;
				nbegin = jpgstr.ReverseFind('/');
				nbegin = nbegin + 1;
				jpgstr.Delete(0,nbegin);
				strcpy_s(date.jpg_name,sizeof(date.jpg_name),(char*)jpgstr.GetBuffer());

				delstr = date.jpg_url;
				if(delstr.Find("��") != -1|| delstr.Find("<1>") != -1|| delstr.Find(" ") != -1 ||
					delstr.Find("<2>") != -1)
				{
					i--;
					memset(date.url,'\0',sizeof(date.url));
					memset(date.title,'\0',sizeof(date.title));
					memset(date.jpg_url,'\0',sizeof(date.jpg_url));
					memset(jpgch,'\0',sizeof(jpgch));
					continue;
				}

			}
				
			title_map[i] = date;
			nbegin = -1;
			memset(date.url,'\0',sizeof(date.url));
			memset(date.title,'\0',sizeof(date.title));
			memset(date.jpg_url,'\0',sizeof(date.jpg_url));
			memset(date.jpg_name,'\0',sizeof(date.jpg_name));
			memset(jpgch,'\0',sizeof(jpgch));
		}

	}

	if(num == 2)
		tileTxtstr = tilestr;

	if(num == 3)
		tileVideostr = tilestr;
	
	if(num == 4)
		tileJpgstr = tilestr;

	return 1;

}

int CClientAppDlg::Set_Static_Title()  //Ϊ�ұ������������ñ���
{
	//one
	m_static_one.SetWindowText(title_map[1006].title);
	m_static_one.ShowWindow(SW_HIDE);
	m_static_one.UpdateData(false);
	m_static_one.ShowWindow(SW_SHOW);

	//tow
	m_static_two.SetWindowText(title_map[1007].title);
	m_static_two.ShowWindow(SW_HIDE);
	m_static_two.UpdateData(false);
	m_static_two.ShowWindow(SW_SHOW);

	//three
	m_static_three.SetWindowText(title_map[1008].title);
	m_static_three.ShowWindow(SW_HIDE);
	m_static_three.UpdateData(false);
	m_static_three.ShowWindow(SW_SHOW);

	//four
	m_static_four.SetWindowText(title_map[1009].title);
	m_static_four.ShowWindow(SW_HIDE);
	m_static_four.UpdateData(false);
	m_static_four.ShowWindow(SW_SHOW);

	//five
	m_static_five.SetWindowText(title_map[1010].title);
	m_static_five.ShowWindow(SW_HIDE);
	m_static_five.UpdateData(false);
	m_static_five.ShowWindow(SW_SHOW);

	//six + 1
	m_static_seven.SetWindowText(title_map[1011].title);
	m_static_seven.ShowWindow(SW_HIDE);
	m_static_seven.UpdateData(false);
	m_static_seven.ShowWindow(SW_SHOW);

	//seven
	m_static_eight.SetWindowText(title_map[1012].title);
	m_static_eight.ShowWindow(SW_HIDE);
	m_static_eight.UpdateData(false);
	m_static_eight.ShowWindow(SW_SHOW);

	//eight
	m_static_nine.SetWindowText(title_map[1013].title);
	m_static_nine.ShowWindow(SW_HIDE);
	m_static_nine.UpdateData(false);
	m_static_nine.ShowWindow(SW_SHOW);

	//nine
	m_static_ten.SetWindowText(title_map[1014].title);
	m_static_ten.ShowWindow(SW_HIDE);
	m_static_ten.UpdateData(false);
	m_static_ten.ShowWindow(SW_SHOW);

	//ten
	m_static_twelve.SetWindowText(title_map[1015].title);
	m_static_twelve.ShowWindow(SW_HIDE);
	m_static_twelve.UpdateData(false);
	m_static_twelve.ShowWindow(SW_SHOW);

	//�����Ƶ������
	//one
	m_static_eleven.SetWindowText(title_map[1020].title);
	m_static_eleven.ShowWindow(SW_HIDE);
	m_static_eleven.UpdateData(false);
	m_static_eleven.ShowWindow(SW_SHOW);

	//tow
	m_static_thirteen.SetWindowText(title_map[1021].title);
	m_static_thirteen.ShowWindow(SW_HIDE);
	m_static_thirteen.UpdateData(false);
	m_static_thirteen.ShowWindow(SW_SHOW);

	//three
	m_static_fourteen.SetWindowText(title_map[1022].title);
	m_static_fourteen.ShowWindow(SW_HIDE);
	m_static_fourteen.UpdateData(false);
	m_static_fourteen.ShowWindow(SW_SHOW);

	//four
	m_static_fifteen.SetWindowText(title_map[1023].title);
	m_static_fifteen.ShowWindow(SW_HIDE);
	m_static_fifteen.UpdateData(false);
	m_static_fifteen.ShowWindow(SW_SHOW);

	//five
	m_static_sixteen.SetWindowText(title_map[1024].title);
	m_static_sixteen.ShowWindow(SW_HIDE);
	m_static_sixteen.UpdateData(false);
	m_static_sixteen.ShowWindow(SW_SHOW);

	//�·�ͼƬ����
	//one
	m_static_picone.SetWindowText(title_map[1040].title);
	m_static_picone.ShowWindow(SW_HIDE);
	m_static_picone.UpdateData(false);
	m_static_picone.ShowWindow(SW_SHOW);
	

	//tow
	m_pic_two.SetWindowText(title_map[1041].title);
	m_pic_two.ShowWindow(SW_HIDE);
	m_pic_two.UpdateData(false);
	m_pic_two.ShowWindow(SW_SHOW);
	

	//three
	m_static_picthree.SetWindowText(title_map[1042].title);
	m_static_picthree.ShowWindow(SW_HIDE);
	m_static_picthree.UpdateData(false);
	m_static_picthree.ShowWindow(SW_SHOW);
	

	return 1;
}

int CClientAppDlg::Recv_One_Page_Date(char* url)  //ָ����ȡĳһ���ı���Ϣ
{
	cli_date_t date;
	date.number = 3;
	memset(date.buf,'\0',sizeof(date.buf));
	memset(date.url,'\0',sizeof(date.url));

	if(client.ifcon == TRUE)
	{	
		strcpy_s(date.buf,sizeof(date.buf),"��Ϣ");
		strcpy_s(date.url,sizeof(date.url),url);
		date.number = 3;
		date.buflen = strlen(date.buf);
		
		if(client.Send_message(date) == 0)
		{
			m_static_search.SetWindowText("�ͻ��˷�������ʧ��");
			m_static_search.ShowWindow(SW_HIDE);
			m_static_search.UpdateData(false);
			m_static_search.ShowWindow(SW_SHOW);
		}
				

		if(client.Recv_message(&date,1) == 0)
		{
			m_static_search.SetWindowText("���շ���������ʧ��");
			m_static_search.ShowWindow(SW_HIDE);
			m_static_search.UpdateData(false);
			m_static_search.ShowWindow(SW_SHOW);
		}


	}
	else
	{
		m_static_search.SetWindowText("������δ����");
		m_static_search.ShowWindow(SW_HIDE);
		m_static_search.UpdateData(false);
		m_static_search.ShowWindow(SW_SHOW);
		return 0;
	}

	return 1;
}

int CClientAppDlg::Show_One_News(char* url,char* name)
{
	if(Recv_One_Page_Date(url) == 0)
	{
		m_static_search.SetWindowText("���շ���������ʧ��");
		m_static_search.ShowWindow(SW_HIDE);
		m_static_search.UpdateData(false);
		m_static_search.ShowWindow(SW_SHOW);
		return 0;
	}

	Show_dlg();
	m_showdlg.Show_TXT(name);

	return 1;

}

void CClientAppDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_play.b_down)
	{
		m_play.SetButtonBmp(IDB_BMP_PLAY);	
		m_controls.play();

	}else
	{
		m_play.SetButtonBmp(IDB_BMP_PAUSE);
		m_controls.pause();
	}


	//��ȡ��ťˢ������
	CRect rec;
	rec.left = 857;
	rec.top = 439;
	rec.right = 887;
	rec.bottom = 469;

	InvalidateRect(rec,FALSE);
	UpdateData();

	return;
}

void CClientAppDlg::OnBnClickedBuVoice()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!m_bu_voice.b_down)
	{
		m_bu_voice.SetButtonBmp(IDB_BMP_VOICE_SHUT);
		num_voice = m_pro_voice.GetPos();
		m_pro_voice.SetPos(0);
		m_setting.put_volume(0);

	}else
	{
		m_bu_voice.SetButtonBmp(IDB_BMP_VOICE);
		m_pro_voice.SetPos(num_voice);
		m_setting.put_volume(num_voice);
	}

	CRect rec;
	rec.left = 913;
	rec.top = 450;
	rec.right = 933;
	rec.bottom = 470;

	InvalidateRect(rec,FALSE);
	UpdateData();

}

int CClientAppDlg::Show_picture(char* str,int id)
{
	float cx, cy, dx, dy, k, t;		//���ؼ��Ŀ�͸��Լ�ͼƬ��͸��йصĲ���
    CRect   rect;					//���ڻ�ȡͼƬ�ؼ��Ŀ�͸�
    CImage q;						//ΪcimageͼƬ�ഴ��һ������
	HRESULT hresult1 = q.Load(str);	//���캯�����β���������ͼƬ��·�� 

    if(E_FAIL == hresult1)
		return 0;

	cx = q.GetWidth();
	cy = q.GetHeight();				//��ȡͼƬ�Ŀ� ��
    k = cy / cx;						//���ͼƬ�Ŀ�߱�



    CWnd *pWnd = NULL;
    pWnd = GetDlgItem(id);		//��ȡ�ؼ����
    pWnd->GetClientRect(&rect);			//��ȡPicture Control�ؼ��Ŀͻ���
    dx = rect.Width();
    dy = rect.Height();					//��ÿؼ��Ŀ�߱�
    t = dy / dx;							//��ÿؼ��Ŀ�߱�
    if (k >= t)
    {

		rect.right = float(rect.bottom / k);
        rect.left = (dx - rect.right) / 2;
        rect.right = float(rect.bottom / k) + (dx - rect.right) / 2;
    }
    else
    {
        rect.bottom = float(k*rect.right);
        rect.top = (dy - rect.bottom) / 2;
        rect.bottom = float(k*rect.right) + (dy - rect.bottom) / 2;
    }

	//��صļ���Ϊ����ͼƬ�ڻ�ͼ�����а�������ʾ��ԭ��ܺö������ͼƬ�ܿ��ǲ��ߣ����������пհ��������ͼƬ�ܸ߶�������������пհ��������ұ������߿հ���һ����

    CDC *pDc = NULL;
    pDc = pWnd->GetDC();			//��ȡpicture control��DC������ʲô������Ҳ��֪�����ٶȾ���
    int ModeOld = SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);//����ָ���豸�����е�λͼ����ģʽ

    GetDlgItem(id)->ShowWindow(TRUE);
    q.StretchBlt(pDc->m_hDC, rect, SRCCOPY);//��ʾ����
    SetStretchBltMode(pDc->m_hDC, ModeOld);


    ReleaseDC(pDc);//�ͷ�ָ��ռ�

	return 1;

}

void CClientAppDlg::OnStnClickedPcture1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	/*Show_picture("date/MAIN201904290108490599364369006.jpg",IDC_PCTURE1);

	Show_picture("date/MAIN201904290109202109811039531.jpg",IDC_PICTURE2);

	Show_picture("date/MAIN201904290917406613270424345.jpg",IDC_PICTURE3);*/

}

void CClientAppDlg::OnStnClickedPicture2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//Show_picture("date/MAIN201904290109202109811039531.jpg",IDC_PICTURE2);
	
}

void CClientAppDlg::OnStnClickedPicture3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//Show_picture("date/ͼƬ3.jpg",IDC_PICTURE3);
}

void CClientAppDlg::OnStnClickedStaticPicone()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	int k = m_static_picone.GetDlgCtrlID();
	Show_One_News(title_map[k].url,title_map[k].title);
	m_showdlg.Show_picture(title_map[k].jpg_name,IDC_TXT_PICTURE);

}

void CClientAppDlg::OnStnClickedStaticPictow()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int k = m_pic_two.GetDlgCtrlID();
	Show_One_News(title_map[k].url,title_map[k].title);
	m_showdlg.Show_picture(title_map[k].jpg_name,IDC_TXT_PICTURE);
}

void CClientAppDlg::OnStnClickedStaticPicthree()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int k = m_static_picthree.GetDlgCtrlID();
	Show_One_News(title_map[k].url,title_map[k].title);
	m_showdlg.Show_picture(title_map[k].jpg_name,IDC_TXT_PICTURE);

}

int CClientAppDlg::Recv_show_jpg(int id,int jpid)
{

	cli_date_t date;
	char filename[100];

	memset(filename,'\0',sizeof(filename));
	memset(date.buf,'\0',sizeof(date.buf));
	memset(date.url,'\0',sizeof(date.url));


	if(client.ifcon == TRUE && Jpgclient.ifcon == TRUE)
	{	
		strcpy_s(date.buf,sizeof(date.buf),title_map[id].jpg_name);
		strcpy_s(date.url,sizeof(date.url),title_map[id].jpg_url);
		date.number = 6;
		date.buflen = strlen(date.buf);
		
		if(Jpgclient.Send_message(date) == 0)
		{
			m_static_search.SetWindowText("�ͻ��˷�������ʧ��");
			m_static_search.ShowWindow(SW_HIDE);
			m_static_search.UpdateData(false);
			m_static_search.ShowWindow(SW_SHOW);
			return 0;
		}
				

		if(Jpgclient.Recv_jpg(date,title_map[id].jpg_name) == 0)
		{
			return 0;
		}

		strcpy_s(filename,sizeof(filename), dirstr);
		strcat_s(filename, sizeof(filename),"\\");
		strcat_s(filename,sizeof(filename),title_map[id].jpg_name);
		Show_picture(filename,jpid);
		q_pic.push(filename);

	}
	else
	{
		m_static_search.SetWindowText("������δ����");
		m_static_search.ShowWindow(SW_HIDE);
		m_static_search.UpdateData(false);
		m_static_search.ShowWindow(SW_SHOW);
		return 0;
	}



	return 1;

}

int CClientAppDlg::Show_static_picture()
{
	Recv_show_jpg(1040,IDC_PCTURE1);
	Recv_show_jpg(1041,IDC_PICTURE2);
	Recv_show_jpg(1042,IDC_PICTURE3);

	return 1;

}


void CClientAppDlg::OnBnClickedUsrInfo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


