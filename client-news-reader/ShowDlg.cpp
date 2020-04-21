// ShowDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientApp.h"
#include "ShowDlg.h"
#include "afxdialogex.h"


// CShowDlg 对话框
IMPLEMENT_DYNAMIC(CShowDlg, CDialogEx)




CShowDlg::CShowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CShowDlg::IDD, pParent)

{

}

CShowDlg::~CShowDlg()
{
}

void CShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_SIX, m_static_six);
	DDX_Control(pDX, IDC_SMEXIT, m_SMexit);
	DDX_Control(pDX, IDC_EDIT_ONE, m_edit);
	DDX_Control(pDX, IDC_TXT_PICTURE, m_show_picture);
}


BEGIN_MESSAGE_MAP(CShowDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SMEXIT, &CShowDlg::OnBnClickedSmexit)
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CShowDlg 消息处理程序
BOOL CShowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	//初始化背景
	m_bmpsmallback = ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_HL));
	BITMAP hb;
	GetObject(m_bmpsmallback,sizeof(BITMAP),(LPBYTE)&hb);
	MoveWindow(0,0,hb.bmWidth,hb.bmHeight);
	CBitmap bmpTmp;
	bmpTmp.Attach(m_bmpsmallback);
	m_bksmallBrush.CreatePatternBrush(&bmpTmp);

	//退出按钮
	m_SMexit.SetButtonBmp(IDB_JIANTOU);
	m_SMexit.InitMyButton(0,5,40,40);

	//图片位置
	m_show_picture.MoveWindow(110,60,180,90);

	//正文控件位置
	m_static_six.MoveWindow(50,10,300,30);
	m_edit.MoveWindow(0,150,400,600);

	//优化静态文本框的字体和颜色
	CFont* font;
	font = m_static_six.GetFont();//获取cfont对象
	LOGFONT lf;
	font->GetLogFont(&lf);//获取LOGFONT结构体
	lf.lfHeight = 30;//修改字体大小
	lf.lfItalic = FALSE;  //倾斜
	lf.lfWeight = 200; //修改字体的粗细
	newFont.CreateFontIndirect(&lf);//创建一个新的字体
	m_static_six.SetFont(&newFont);

	CFont* font1;
	font1 = m_edit.GetFont();//获取cfont对象
	LOGFONT lf1;
	font1->GetLogFont(&lf1);//获取LOGFONT结构体
	lf1.lfHeight = 25;//修改字体大小
	lf1.lfItalic = FALSE;  //倾斜
	lf1.lfWeight = 100; //修改字体的粗细
	newFont1.CreateFontIndirect(&lf1);//创建一个新的字体
	
	m_edit.SetFont(&newFont1);

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CShowDlg::OnBnClickedSmexit()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
	SetDlgItemText(IDC_EDIT1,(LPCTSTR)"");
}

HBRUSH CShowDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if(pWnd->GetDlgCtrlID() == IDC_STATIC_SIX )//判断发出消息的空间是否是该静态文本框
	{
		pDC->SetTextColor(RGB(0,0,0));////设置文本颜色为黑色
		pDC->SetBkMode(TRANSPARENT);//设置文本背景模式为透明
		hbr = CreateSolidBrush(RGB(255,255,255));//控件的背景色为白色
	}

	if(pWnd == this)
	{
		return m_bksmallBrush;
	}
	return hbr;
}

void CShowDlg::OnSize(UINT nType, int cx, int cy)
{
	//CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	//控件随程序自适应全屏后更改位置及大小
	if(1)
	{
		float fsp[2];		
		POINT Newp; //获取现在对话框的大小		
		CRect recta;		
		GetClientRect(&recta);     //取客户区大小  		
		Newp.x = recta.right - recta.left;		
		Newp.y = recta.bottom - recta.top;		
		fsp[0] = (float)Newp.x/Sold.x;		
		fsp[1] = (float)Newp.y/Sold.y;		
		CRect Rect;		
		int woc;		
		CPoint OldTLPoint, TLPoint; //左上角		
		CPoint OldBRPoint, BRPoint; //右下角		
		HWND  hwndChild = ::GetWindow(m_hWnd,GW_CHILD);  //列出所有控件 
		while (hwndChild)
		{
			woc = ::GetDlgCtrlID(hwndChild);//取得ID			
			GetDlgItem(woc)->GetWindowRect(Rect);			
			ScreenToClient(Rect);			
			OldTLPoint = Rect.TopLeft();			
			TLPoint.x = long(OldTLPoint.x*fsp[0]);			
			TLPoint.y = long(OldTLPoint.y*fsp[1]);			
			OldBRPoint = Rect.BottomRight();			
			BRPoint.x = long(OldBRPoint.x *fsp[0]);			
			BRPoint.y = long(OldBRPoint.y *fsp[1]);			
			Rect.SetRect(TLPoint,BRPoint);			
			GetDlgItem(woc)->MoveWindow(Rect,TRUE);			
			hwndChild =::GetWindow(hwndChild,GW_HWNDNEXT);
			}
		Sold = Newp;
	}
}

int CShowDlg::Show_TXT(CString str)
{

	CString pstr = NULL;//创建一个字符串用于给静态文本框赋值
	CString newstr = NULL; // 用于字符排版
	char buf[4002];//创建一个char字符串指针用于读取数据
	memset(buf,'\0',sizeof(buf));
	int nCount = 0;
	int nBegin = 0;
	int nEnd = 0;
	CFile fd;//创建一个文件指针用于打开文件读取内容
	

	TCHAR *pszFileName = filenameTT;//文件标题

	//如果打开文件成功就开始进行读取
	if(fd.Open(pszFileName,CFile::modeRead) == 0)
	{	
		m_static_six.SetWindowText("打开文件失败");
		m_static_six.ShowWindow(SW_HIDE);
		m_static_six.UpdateData(false);
		m_static_six.ShowWindow(SW_SHOW);
		return 0;
	}

	//加载标题
	m_static_six.SetWindowText(str);
	m_static_six.ShowWindow(SW_HIDE);
	m_static_six.UpdateData(false);
	m_static_six.ShowWindow(SW_SHOW);

	int iLen = 0;

	while(!nCount)
	{
		nCount = fd.Read(buf,sizeof(buf));
		if(nCount > 0)
			pstr = pstr + buf;

		memset(buf,'\0',sizeof(buf));
	}

	fd.Close();
	//remove("date\\tt.txt");

	remove(filenameTT);
	
	//加载文本
	m_edit.SetWindowText("\r\n");
	iLen = m_edit.GetWindowTextLength();
	m_edit.SetSel(iLen,iLen,TRUE);

	while(nBegin != -1)
	{
		newstr.Delete(newstr.GetLength());
		nBegin = pstr.Find("<1>");
		if(nBegin == -1)
			break;
		nBegin = nBegin + strlen("<1>");
		pstr.Delete(0,nBegin);
		nEnd = pstr.Find("<1>");
		newstr = pstr.Left(nEnd);
		pstr.Delete(0,nEnd+strlen("<1>"));

		if(newstr.Find("5s后自动返回") != -1)
			break;
		
		m_edit.ReplaceSel(newstr, FALSE); //加载文字，操做和静态文本框操作一样
		
		m_edit.ReplaceSel("\r\n\r\n",FALSE);

	}


	m_edit.LineScroll(-m_edit.GetWindowTextLength(),0);
	m_edit.SetFocus(); //避免数据出现后被选中返回值需要改成FALSE
	
	return 1;
}

int CShowDlg::Show_picture(char* filename,int id)
{
	char str[100];



	if(*filename == 0)
	{
		strcpy_s(str,sizeof(str), dirstr);
		strcat_s(str, sizeof(str), "\\renmin.jpg");

	}else
	{
		strcpy_s(str,sizeof(str), dirstr);
		strcat_s(str,sizeof(str),"\\");
		strcat_s(str, sizeof(str), filename);
	}
	
	
	float cx, cy, dx, dy, k, t;		//跟控件的宽和高以及图片宽和高有关的参数
    CRect   rect;					//用于获取图片控件的宽和高
    CImage q;						//为cimage图片类创建一个对象
    HRESULT hresult1 = q.Load(str);  //构造函数的形参是所加载图片的路径 

	if(E_FAIL == hresult1)
		return 0;

    cx = q.GetWidth();
    cy = q.GetHeight();				//获取图片的宽 高
    k = cy / cx;						//获得图片的宽高比

    CWnd *pWnd = NULL;
    pWnd = GetDlgItem(id);		//获取控件句柄
    pWnd->GetClientRect(&rect);			//获取Picture Control控件的客户区
    dx = rect.Width();
    dy = rect.Height();					//获得控件的宽高比
    t = dy / dx;							//获得控件的宽高比
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

	//相关的计算为了让图片在绘图区居中按比例显示，原理很好懂，如果图片很宽但是不高，就上下留有空白区；如果图片很高而不宽就左右留有空白区，并且保持两边空白区一样大

    CDC *pDc = NULL;
    pDc = pWnd->GetDC();			//获取picture control的DC，这是什么玩意我也不知道，百度就行
    int ModeOld = SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);//设置指定设备环境中的位图拉伸模式

    GetDlgItem(id)->ShowWindow(FALSE);
    GetDlgItem(id)->ShowWindow(TRUE);
    q.StretchBlt(pDc->m_hDC, rect, SRCCOPY);//显示函数
    SetStretchBltMode(pDc->m_hDC, ModeOld);


    ReleaseDC(pDc);//释放指针空间

	return 1;

}

