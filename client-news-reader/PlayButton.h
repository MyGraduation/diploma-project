#pragma once
#include "afxwin.h"
#include "resource.h"

class CPlayButton :
	public CButton
{
public:
	CPlayButton(void);
	~CPlayButton(void);

public:
	void SetButtonBmp(int Path);
	void InitMyButton(int nX,int nY,int nW,int nH);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

public:
	bool b_down;

public:
	CImage m_imgButton;
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	
};



