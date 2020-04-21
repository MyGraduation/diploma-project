#pragma once
#include "afxcmn.h"
class CMyProgress :
	public CProgressCtrl
{
public:
	COLORREF m_ColProgress;//进度条颜色  
    COLORREF m_ColBlank;//空白区域颜色 
	bool flage;

public:
	CMyProgress(void);
	~CMyProgress(void);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();

public:
	void InitMyProgress(int nX,int nY,int nW,int nH);
	void SetRGB(COLORREF progress,COLORREF blank);
};



