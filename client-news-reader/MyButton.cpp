#include "stdafx.h"
#include "MyButton.h"


CMyButton::CMyButton(void)
{
}


CMyButton::~CMyButton(void)
{
}

void CMyButton::SetButtonBmp(int Path)
{
	HBITMAP hBmp = ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(Path));
	if(!(m_imgButton.IsNull()))    //Attachǰ������ȷ��img����λͼ������ᵯ���쳣��������Ҳ�ɼ�������
		m_imgButton.Destroy();
	m_imgButton.Attach(hBmp);
}

void CMyButton::InitMyButton(int nX,int nY,int nW,int nH)
{
	MoveWindow(nX,nY,nW,nH);
}

void CMyButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	if(!lpDrawItemStruct) return;

	HDC hMemDC;
	HBITMAP bmpMen;
	HGDIOBJ hOldObj;
	bmpMen = CreateCompatibleBitmap(lpDrawItemStruct->hDC,lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left,lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top);  //������ָ���豸�����Ĺ������豸���ݵ�λͼ
	if(!bmpMen) return;

	hMemDC = CreateCompatibleDC(lpDrawItemStruct->hDC);  //������ָ���豸���ݵ��ڴ��豸������(DC)
	if(!hMemDC)
	{
		if(bmpMen)
		{
			::DeleteObject(bmpMen);  //ɾ���߼��ʡ����ʡ����塢λͼ��������ɫ�壬�ͷ���������������ϵͳ��Դ��ɾ�������ָ���ľ��������Ч
			bmpMen = NULL;
		}
		return;
	}

	hOldObj = ::SelectObject(hMemDC,bmpMen);  //������ָ�����豸������(DC)��ѡ��һ�������¶����滻��ͬ���͵�ǰһ������
	
	RECT rectTmp = {0};
	rectTmp = lpDrawItemStruct->rcItem;
	MapWindowPoints(GetParent(),&rectTmp);  //��(ӳ��)һ����CWND������ռ�ת��Ϊ��һ�����ڵ�����ռ�

	int nW = lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left;
	int nH = lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top;

	if(lpDrawItemStruct->itemState & ODS_SELECTED)
	{
		//��ť��ѡ��
		m_imgButton.BitBlt(hMemDC,0,0,nW,nH,nW,0,SRCCOPY);
	}
	else if(lpDrawItemStruct->itemState & ODS_FOCUS)
	{
		//����״̬if
		m_imgButton.BitBlt(hMemDC,0,0,nW,nH,0,0,SRCCOPY);

	}
	else
	{
		m_imgButton.BitBlt(hMemDC,0,0,nW,nH,0,0,SRCCOPY);
	}	
	::BitBlt(lpDrawItemStruct->hDC,0,0,nW,nH,hMemDC,0,0,SRCCOPY);
	SelectObject(hMemDC,hOldObj);
	if(bmpMen)
	{
		::DeleteObject(bmpMen);
		bmpMen = NULL;
	}

	if(hMemDC)
	{
		::DeleteObject(hMemDC);
		hMemDC = NULL;
	}
	return;
}


