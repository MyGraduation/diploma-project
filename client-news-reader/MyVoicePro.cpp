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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	flags = false;
	CProgressCtrl::OnLButtonUp(nFlags, point);
}


