#include "stdafx.h"
#include "MyVoicePro.h"


CMyVoicePro::CMyVoicePro(void)
{
	flags = false;
}


CMyVoicePro::~CMyVoicePro(void)
{
}
BEGIN_MESSAGE_MAP(CMyVoicePro, CProgressCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


void CMyVoicePro::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	flags = true;
	CRect r;
	this->GetClientRect(r);
	double Height = r.Height();
	int n = (100-point.y)*Height/100;
	this->SetPos(n);
	CProgressCtrl::OnLButtonDown(nFlags, point);
}


void CMyVoicePro::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	flags = false;
	CProgressCtrl::OnLButtonUp(nFlags, point);
}


