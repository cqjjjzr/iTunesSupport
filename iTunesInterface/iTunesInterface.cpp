// iTunesInterface.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "iTunesInterface.h"

#include "CiTunes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO:  ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ��  ����ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CiTunesInterfaceApp

BEGIN_MESSAGE_MAP(CiTunesInterfaceApp, CWinApp)
END_MESSAGE_MAP()


// CiTunesInterfaceApp ����

CiTunesInterfaceApp::CiTunesInterfaceApp()
{
}


// Ψһ��һ�� CiTunesInterfaceApp ����

CiTunesInterfaceApp theApp;


// CiTunesInterfaceApp ��ʼ��

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
