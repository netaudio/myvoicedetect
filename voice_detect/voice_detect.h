
// voice_detect.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cvoice_detectApp:
// �йش����ʵ�֣������ voice_detect.cpp
//

class Cvoice_detectApp : public CWinAppEx
{
public:
	Cvoice_detectApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cvoice_detectApp theApp;