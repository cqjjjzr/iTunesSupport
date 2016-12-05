// iTunesInterface.h : iTunesInterface DLL 的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#ifndef ITS_ITUNES_INTERFACE
#define ITS_ITUNES_INTERFACE
#include "resource.h"		// 主符号
#include "CiTunes.h"

// CiTunesInterfaceApp
// 有关此类实现的信息，请参阅 iTunesInterface.cpp
//

class CiTunesInterfaceApp : public CWinApp
{
public:
	CiTunesInterfaceApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()

private:
	CiTunes iTunes;
};

#endif

