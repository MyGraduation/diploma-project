#pragma once
#include "afxcmn.h"
class CMyVoicePro :
	public CProgressCtrl
{
public:
	bool flags;
public:
	CMyVoicePro(void);
	~CMyVoicePro(void);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};



