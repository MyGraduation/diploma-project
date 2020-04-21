#pragma once
#include "afxwin.h"
class CMyButton :
	public CButton
{
public:
	CMyButton(void);
	~CMyButton(void);
public:
	void SetButtonBmp(int Path);
	void InitMyButton(int nX,int nY,int nW,int nH);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
public:
	CImage m_imgButton;
};



