
// DDMPrinter.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDDMPrinterApp: 
// �йش����ʵ�֣������ DDMPrinter.cpp
//

class CDDMPrinterApp : public CWinApp
{
public:
	CDDMPrinterApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDDMPrinterApp theApp;