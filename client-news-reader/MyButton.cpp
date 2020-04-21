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
	if(!(m_imgButton.IsNull()))    //Attach前，必须确认img中无位图，否则会弹出异常，但忽略也可继续运行
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
	bmpMen = CreateCompatibleBitmap(lpDrawItemStruct->hDC,lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left,lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top);  //创建与指定设备上下文关联的设备兼容的位图
	if(!bmpMen) return;

	hMemDC = CreateCompatibleDC(lpDrawItemStruct->hDC);  //创建与指定设备兼容的内存设备上下文(DC)
	if(!hMemDC)
	{
		if(bmpMen)
		{
			::DeleteObject(bmpMen);  //删除逻辑笔、画笔、字体、位图、区域或调色板，释放与对象关联的所有系统资源。删除对象后，指定的句柄不再有效
			bmpMen = NULL;
		}
		return;
	}

	hOldObj = ::SelectObject(hMemDC,bmpMen);  //函数在指定的设备上下文(DC)中选择一个对象。新对象替换相同类型的前一个对象
	
	RECT rectTmp = {0};
	rectTmp = lpDrawItemStruct->rcItem;
	MapWindowPoints(GetParent(),&rectTmp);  //将(映射)一组点从CWND的坐标空间转换为另一个窗口的坐标空间

	int nW = lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left;
	int nH = lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top;

	if(lpDrawItemStruct->itemState & ODS_SELECTED)
	{
		//按钮被选择
		m_imgButton.BitBlt(hMemDC,0,0,nW,nH,nW,0,SRCCOPY);
	}
	else if(lpDrawItemStruct->itemState & ODS_FOCUS)
	{
		//焦点状态if
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


