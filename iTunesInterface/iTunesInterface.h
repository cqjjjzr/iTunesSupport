// iTunesInterface.h : iTunesInterface DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#ifndef ITS_ITUNES_INTERFACE
#define ITS_ITUNES_INTERFACE
#include "resource.h"		// ������
#include "CiTunes.h"

// CiTunesInterfaceApp
// �йش���ʵ�ֵ���Ϣ������� iTunesInterface.cpp
//

class CiTunesInterfaceApp : public CWinApp
{
public:
	CiTunesInterfaceApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()

private:
	CiTunes iTunes;
};

#endif

