#using "C:\Users\cqjjj\Documents\Visual Studio 2015\Projects\iTunesSupport\iTunesSupportImpl\bin\Debug\iTunesSupportImpl.dll"
#include <NERvGear\plugin.h>
#include <NERvGear\NERvSDK.h>
#include <NERvGear\COM.h>
#include <NERvGear\object.h>
#include <NERvGear\NERv1API.h>
#include <string>

#include <io.h>
#include <Windows.h>
#include <direct.h>

#include "iTunesSupport.h"
#include "iTunesSupportDataSource.h"
#include "iTunesSupportInfoData.h"
#include "iTunesLibraryInitializer.h"
#include "stdafx.h"
#include "ref.h"

using namespace iTunesSupportImpl;
using namespace std;
using namespace NERvGear;

char* WcharToChar(const wchar_t* wp)
{
	char *m_char;
	int len = WideCharToMultiByte(CP_ACP, 0, wp, wcslen(wp), NULL, 0, NULL, NULL);
	m_char = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, wp, wcslen(wp), m_char, len, NULL, NULL);
	m_char[len] = '\0';
	return m_char;
}

void initiTunesLib() {
	iTunesSupportImpl::iTunesSupportImplWrapper::getInstance()->init(gcnew System::String(NERvGetModulePath()));
}

long NVG_METHOD iTunesSupport::OnInitial()
{
	NERvLogInfo(NVG_TEXT("iTunesSupport"), L"iTunes Support ver%d.%d.%d"
		, ITS_VERSION_MAJOR, ITS_VERSION_MINOR, ITS_VERSION_SUBMINOR);
	if (!CoInitialize(NULL)) return E_FAIL;
	if (iTunesLibraryInitializer::init()) return E_FAIL;
	//iTunesLibraryInitializer::init();
	initiTunesLib();
	_mkdir((string(WcharToChar(NERvGetModulePath())) + "\\artworks").c_str());
	NERvLogInfo(NVG_TEXT("iTunesSupport"), NVG_TEXT("Initialized."));

	return PluginImpl::OnInitial();
}

long NVG_METHOD iTunesSupport::OnReady()
{
	return PluginImpl::OnReady();
}

long NVG_METHOD iTunesSupport::OnRelease()
{
	NERvLogInfo(NVG_TEXT("iTunesSupport"), NVG_TEXT("Unloading iTunes Support"));
	iTunesSupportImplWrapper::getInstance()->destroy();
	return PluginImpl::OnRelease();
}

NVG_BEGIN_PLUGIN_INFO(iTunesSupport)
NVG_DECLARE_PLUGIN_UID(0x8d9dcc7d, 0x3e42, 0x4c66, 0x97, 0x21, 0x89, 0x75, 0x50, 0xda, 0x05, 0x8c)
NVG_DECLARE_PLUGIN_TYPE(PLUGIN::BASIC)
NVG_DECLARE_PLUGIN_VERSION(ITS_VERSION_MAJOR, ITS_VERSION_MINOR, ITS_VERSION_SUBMINOR)
NVG_DECLARE_PLUGIN_NAME("iTunes Support")
NVG_DECLARE_PLUGIN_DESCRIP("iTunes数据源支持。")
NVG_DECLARE_PLUGIN_COMMENT("添加音乐播放器iTunes支持。")
NVG_DECLARE_PLUGIN_AUTHOR("Charlie Jiang")
NVG_DECLARE_PLUGIN_HOMEPAGE("https://github.com/cqjjjzr/iTunesSupport")
NVG_DECLARE_PLUGIN_EMAIL("cqjjjzr@126.com")
NVG_END_PLUGIN_INFO(iTunesSupport)

NVG_BEGIN_COMPONENT_REGISTER(iTunesSupport)
NVG_REGISTER_OBJECT(iTunesSupportDataSource, false) // no aggregation
NVG_END_COMPONENT_REGISTER()

NVG_IMPLEMENT_PLUGIN(iTunesSupport)
