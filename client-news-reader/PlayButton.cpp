#include "stdafx.h"
#include "PlayButton.h"


CPlayButton::CPlayButton(void)
{
	b_down = true;
}


CPlayButton::~CPlayButton(void)
{
}

void CPlayButton::InitMyButton(int nX,int nY,int nW,int nH)
{
	MoveWindow(nX,nY,nW,nH);
}

void CPlayButton::SetButtonBmp(int Path)
{
	HBITMAP bmap  = ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(Path));
	
	if(!(m_imgButton.IsNull()))    //Attach前，必须确认img中无位图，否则会弹出异常，但忽略也可继续运行
		m_imgButton.Destroy();
	m_imgButton.Attach(bmap);
}

void CPlayButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
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

	m_imgButton.BitBlt(hMemDC,0,0,nW,nH,0,0,SRCCOPY);
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
BEGIN_MESSAGE_MAP(CPlayButton, CButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


void CPlayButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(b_down)
	{
		b_down = false;
	}else
	{
		b_down = true;
	}
	
	CButton::OnLButtonDown(nFlags, point);
}


void CPlayButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	CButton::OnLButtonUp(nFlags, point);
}


