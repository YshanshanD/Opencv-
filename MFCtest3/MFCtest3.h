
// MFCtest3.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCtest3App: 
// �йش����ʵ�֣������ MFCtest3.cpp
//

class CMFCtest3App : public CWinApp
{
public:
	CMFCtest3App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCtest3App theApp;