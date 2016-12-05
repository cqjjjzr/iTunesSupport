// iTunesInterface.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "iTunesInterface.h"

#include "CiTunes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO:  如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。  这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CiTunesInterfaceApp

BEGIN_MESSAGE_MAP(CiTunesInterfaceApp, CWinApp)
END_MESSAGE_MAP()


// CiTunesInterfaceApp 构造

CiTunesInterfaceApp::CiTunesInterfaceApp()
{
}


// 唯一的一个 CiTunesInterfaceApp 对象

CiTunesInterfaceApp theApp;


// CiTunesInterfaceApp 初始化

BOOL CiTunesInterfaceApp::InitInstance()
{
	CWinApp::InitInstance();
	HRESULT hRes;
	CLSID classID;
	CLSIDFromString(L"DC0C2640-1415-4644-875C-6F4D769839BA", &classID);
	IID typeID;
	CLSIDFromString(L"9E93C96F-CF0D-43F6-8BA8-B807A3370712", &typeID);

	hRes = ::CoCreateInstance(classID, NULL, CLSCTX_LOCAL_SERVER, typeID, (PVOID*) &iTunes);
	return TRUE;
}
