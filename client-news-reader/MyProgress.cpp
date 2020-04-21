#include "stdafx.h"
#include "MyProgress.h"


CMyProgress::CMyProgress(void)
{
	m_ColProgress = RGB(255,128,0);//��������ɫ  
    m_ColBlank = RGB(192,192,192); 
	flage = true;
}


CMyProgress::~CMyProgress(void)
{
}
BEGIN_MESSAGE_MAP(CMyProgress, CProgressCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CMyProgress::SetRGB(COLORREF progress,COLORREF blank)
{
	m_ColProgress = progress;
	m_ColBlank = blank;
}

void CMyProgress::InitMyProgress(int nX,int nY,int nW,int nH)
{
	MoveWindow(nX,nY,nW,nH);
}


void CMyProgress::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	flage = false;
	CRect r;
	this->GetClientRect(r);
	double With = r.Width();
	int n = point.x*100/With;
	this->SetPos(n);
	CProgressCtrl::OnLButtonDown(nFlags, point);
}


void CMyProgress::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	flage = true;
	CProgressCtrl::OnLButtonUp(nFlags, point);
}


void CMyProgress::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CBrush BackgroundBrush;
	BackgroundBrush.CreateSolidBrush(m_ColBlank); //������ɫ ��ɫ
	CBrush ForeBrush;
	ForeBrush.CreateSolidBrush(m_ColProgress); //��������ɫ  ��ɫ
	CRect r;
	this->GetClientRect(r);
	double With = r.Width();
	int min,max;
	this->GetRange(min, max);
	int pos = this->GetPos();
	double unit = With / (max - min);
	dc.FillRect(r,&BackgroundBrush);
	r.right = pos*unit;
	dc.FillRect(r, &ForeBrush);
}


