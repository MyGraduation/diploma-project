// ShowDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ClientApp.h"
#include "ShowDlg.h"
#include "afxdialogex.h"


// CShowDlg �Ի���
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


// CShowDlg ��Ϣ�������
BOOL CShowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//��ʼ������
	m_bmpsmallback = ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_HL));
	BITMAP hb;
	GetObject(m_bmpsmallback,sizeof(BITMAP),(LPBYTE)&hb);
	MoveWindow(0,0,hb.bmWidth,hb.bmHeight);
	CBitmap bmpTmp;
	bmpTmp.Attach(m_bmpsmallback);
	m_bksmallBrush.CreatePatternBrush(&bmpTmp);

	//�˳���ť
	m_SMexit.SetButtonBmp(IDB_JIANTOU);
	m_SMexit.InitMyButton(0,5,40,40);

	//ͼƬλ��
	m_show_picture.MoveWindow(110,60,180,90);

	//���Ŀؼ�λ��
	m_static_six.MoveWindow(50,10,300,30);
	m_edit.MoveWindow(0,150,400,600);

	//�Ż���̬�ı�����������ɫ
	CFont* font;
	font = m_static_six.GetFont();//��ȡcfont����
	LOGFONT lf;
	font->GetLogFont(&lf);//��ȡLOGFONT�ṹ��
	lf.lfHeight = 30;//�޸������С
	lf.lfItalic = FALSE;  //��б
	lf.lfWeight = 200; //�޸�����Ĵ�ϸ
	newFont.CreateFontIndirect(&lf);//����һ���µ�����
	m_static_six.SetFont(&newFont);

	CFont* font1;
	font1 = m_edit.GetFont();//��ȡcfont����
	LOGFONT lf1;
	font1->GetLogFont(&lf1);//��ȡLOGFONT�ṹ��
	lf1.lfHeight = 25;//�޸������С
	lf1.lfItalic = FALSE;  //��б
	lf1.lfWeight = 100; //�޸�����Ĵ�ϸ
	newFont1.CreateFontIndirect(&lf1);//����һ���µ�����
	
	m_edit.SetFont(&newFont1);

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CShowDlg::OnBnClickedSmexit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	EndDialog(0);
	SetDlgItemText(IDC_EDIT1,(LPCTSTR)"");
}

HBRUSH CShowDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if(pWnd->GetDlgCtrlID() == IDC_STATIC_SIX )//�жϷ�����Ϣ�Ŀռ��Ƿ��Ǹþ�̬�ı���
	{
		pDC->SetTextColor(RGB(0,0,0));////�����ı���ɫΪ��ɫ
		pDC->SetBkMode(TRANSPARENT);//�����ı�����ģʽΪ͸��
		hbr = CreateSolidBrush(RGB(255,255,255));//�ؼ��ı���ɫΪ��ɫ
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

	// TODO: �ڴ˴������Ϣ����������
	//�ؼ����������Ӧȫ�������λ�ü���С
	if(1)
	{
		float fsp[2];		
		POINT Newp; //��ȡ���ڶԻ���Ĵ�С		
		CRect recta;		
		GetClientRect(&recta);     //ȡ�ͻ�����С  		
		Newp.x = recta.right - recta.left;		
		Newp.y = recta.bottom - recta.top;		
		fsp[0] = (float)Newp.x/Sold.x;		
		fsp[1] = (float)Newp.y/Sold.y;		
		CRect Rect;		
		int woc;		
		CPoint OldTLPoint, TLPoint; //���Ͻ�		
		CPoint OldBRPoint, BRPoint; //���½�		
		HWND  hwndChild = ::GetWindow(m_hWnd,GW_CHILD);  //�г����пؼ� 
		while (hwndChild)
		{
			woc = ::GetDlgCtrlID(hwndChild);//ȡ��ID			
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

	CString pstr = NULL;//����һ���ַ������ڸ���̬�ı���ֵ
	CString newstr = NULL; // �����ַ��Ű�
	char buf[4002];//����һ��char�ַ���ָ�����ڶ�ȡ����
	memset(buf,'\0',sizeof(buf));
	int nCount = 0;
	int nBegin = 0;
	int nEnd = 0;
	CFile fd;//����һ���ļ�ָ�����ڴ��ļ���ȡ����
	

	TCHAR *pszFileName = filenameTT;//�ļ�����

	//������ļ��ɹ��Ϳ�ʼ���ж�ȡ
	if(fd.Open(pszFileName,CFile::modeRead) == 0)
	{	
		m_static_six.SetWindowText("���ļ�ʧ��");
		m_static_six.ShowWindow(SW_HIDE);
		m_static_six.UpdateData(false);
		m_static_six.ShowWindow(SW_SHOW);
		return 0;
	}

	//���ر���
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
	
	//�����ı�
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

		if(newstr.Find("5s���Զ�����") != -1)
			break;
		
		m_edit.ReplaceSel(newstr, FALSE); //�������֣������;�̬�ı������һ��
		
		m_edit.ReplaceSel("\r\n\r\n",FALSE);

	}


	m_edit.LineScroll(-m_edit.GetWindowTextLength(),0);
	m_edit.SetFocus(); //�������ݳ��ֺ�ѡ�з���ֵ��Ҫ�ĳ�FALSE
	
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
	
	
	float cx, cy, dx, dy, k, t;		//���ؼ��Ŀ�͸��Լ�ͼƬ��͸��йصĲ���
    CRect   rect;					//���ڻ�ȡͼƬ�ؼ��Ŀ�͸�
    CImage q;						//ΪcimageͼƬ�ഴ��һ������
    HRESULT hresult1 = q.Load(str);  //���캯�����β���������ͼƬ��·�� 

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

    GetDlgItem(id)->ShowWindow(FALSE);
    GetDlgItem(id)->ShowWindow(TRUE);
    q.StretchBlt(pDc->m_hDC, rect, SRCCOPY);//��ʾ����
    SetStretchBltMode(pDc->m_hDC, ModeOld);


    ReleaseDC(pDc);//�ͷ�ָ��ռ�

	return 1;

}

