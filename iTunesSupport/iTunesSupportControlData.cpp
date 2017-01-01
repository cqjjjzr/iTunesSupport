#using "C:\Users\cqjjj\Documents\Visual Studio 2015\Projects\iTunesSupport\iTunesSupportImpl\bin\Debug\iTunesSupportImpl.dll"

#include "iTunesSupportControlData.h"
#include "iTunesSupportDataSource.h"
#include "vcclr.h"
#include <NERvGear/string.h>
#include <NERvGear\plugin.h>
#include <NERvGear\NERvSDK.h>
#include "iTunesSupport.h"

using namespace iTunesSupportImpl;
using namespace std;
using namespace NERvGear;

// {6709E316-86A1-4EB1-8D35-85E1F31D553F}
const UID iTunesSupportControlData::dataUID = { 0x6709e316, 0x86a1, 0x4eb1,{ 0x8d, 0x35, 0x85, 0xe1, 0xf3, 0x1d, 0x55, 0x3f } };

long NVG_METHOD iTunesSupportControlData::GetId(NERvGear::UID * id)
{
	*id = dataUID;
	return S_OK;
}

size_t NVG_METHOD iTunesSupportControlData::GetName(size_t len, wchar_t * name)
{
	return WriteString(len, L"iTunes控制", name);
}

size_t NVG_METHOD iTunesSupportControlData::GetDescrip(size_t len, wchar_t * descrip)
{
	return WriteString(len, L"控制iTunes。", descrip);
}

long NVG_METHOD iTunesSupportControlData::QuerySource(NERvGear::IDataSource ** source)
{
	if (source == NULL)
		return E_INVALIDARG;

	*source = parentSource;
	(*source)->AddRef();

	return S_OK;
}

unsigned NVG_METHOD iTunesSupportControlData::GetValueCount()
{
	return 5;
}

size_t NVG_METHOD iTunesSupportControlData::GetValue(unsigned index, size_t nbyte, void * buf)
{
	switch (index) {
	case 0: return NERvCopyString(str1, nbyte / 2, static_cast<wchar_t*>(buf)) * 2;
	case 1: return NERvCopyString(str2, nbyte / 2, static_cast<wchar_t*>(buf)) * 2;
	case 2: return NERvCopyString(str3, nbyte / 2, static_cast<wchar_t*>(buf)) * 2;
	case 3: return NERvCopyString(str4, nbyte / 2, static_cast<wchar_t*>(buf)) * 2;
	case 4: return NERvCopyString(str5, nbyte / 2, static_cast<wchar_t*>(buf)) * 2;
	}
	return 0;
}

size_t NVG_METHOD iTunesSupportControlData::GetMaximum(unsigned index, size_t nbyte, void * buf)
{
	return 0;
}

size_t NVG_METHOD iTunesSupportControlData::GetMinimum(unsigned index, size_t nbyte, void * buf)
{
	return 0;
}

unsigned NVG_METHOD iTunesSupportControlData::GetValueIndex(int id)
{
	if (id > NVG_ANY && id < 5)
		return id;

	return NVG_ANY;
}

int NVG_METHOD iTunesSupportControlData::GetValueId(unsigned index)
{
	if (index < 5)
		return index;
	return NVG_ANY;
}

NERvGear::DATA::TYPE NVG_METHOD iTunesSupportControlData::GetValueType(unsigned index)
{
	return NERvGear::DATA::TYPE::STRING;
}

size_t NVG_METHOD iTunesSupportControlData::GetValueUnit(unsigned index, size_t len, wchar_t * unit)
{
	return 0;
}

size_t NVG_METHOD iTunesSupportControlData::GetValueName(unsigned index, size_t len, wchar_t * name)
{
	switch (index) {
	case 0: return NERvCopyString(L"播放/暂停", len, name);
	case 1: return NERvCopyString(L"上一曲", len, name);
	case 2: return NERvCopyString(L"下一曲", len, name);
	case 3: return NERvCopyString(L"音量+", len, name);
	case 4: return NERvCopyString(L"音量-", len, name);
	default:return 0;
	}
}

size_t NVG_METHOD iTunesSupportControlData::GetValueDescrip(unsigned index, size_t len, wchar_t * descrip)
{
	switch (index) {
	case 0: return NERvCopyString(L"切换当前播放/暂停状态。", len, descrip);
	case 1: return NERvCopyString(L"跳转到当前曲目开头，如果已在开头则跳到上一曲。", len, descrip);
	case 2: return NERvCopyString(L"跳转到下一曲。", len, descrip);
	case 3: return NERvCopyString(L"增加10%音量。", len, descrip);
	case 4: return NERvCopyString(L"降低10%音量。", len, descrip);
	default:return 0;
	}
}

unsigned NVG_METHOD iTunesSupportControlData::GetUpdateInterval(unsigned index)
{
	return 1000;
}

long NVG_METHOD iTunesSupportControlData::Update(unsigned index, const wchar_t * param)
{
	if (param == nullptr || wcslen(param) == 0) {
		return E_FAIL;
	}
	switch (index) {
	case 0:wcscpy(str1, param); break;
	case 1:wcscpy(str2, param); break;
	case 2:wcscpy(str3, param); break;
	case 3:wcscpy(str4, param); break;
	case 4:wcscpy(str5, param); break;
	}
	return S_OK;
}

void invokeInternal(unsigned index) {
	switch (index) {
	case 0:iTunesSupportImplWrapper::getInstance()->playPause(); break;
	case 1:iTunesSupportImplWrapper::getInstance()->previous(); break;
	case 2:iTunesSupportImplWrapper::getInstance()->next(); break;
	case 3:iTunesSupportImplWrapper::getInstance()->volPlus(); break;
	case 4:iTunesSupportImplWrapper::getInstance()->volSub(); break;
	}
}

long NVG_METHOD iTunesSupportControlData::Invoke(unsigned index, const wchar_t * param, NERvGear::UI::IWindow * window)
{
	if (!iTunesSupport::initalized) return E_FAIL;
	invokeInternal(index);
	return S_OK;
}

size_t NVG_METHOD iTunesSupportControlData::Config(unsigned index, NERvGear::DATA::CONFIG type, NERvGear::UI::IWindow * window, size_t len, wchar_t * param)
{
	return 0;
}

long NVG_METHOD iTunesSupportControlData::SetValueUnit(unsigned index, const wchar_t * unit)
{
	return 0;
}

size_t NVG_METHOD iTunesSupportControlData::EnumValueUnit(unsigned index, size_t len, wchar_t * units)
{
	return 0;
}

long NVG_METHOD iTunesSupportControlData::SetEventListener(NERvGear::IEventHandler * listener)
{
	return E_NOTIMPL;
}

iTunesSupportControlData::iTunesSupportControlData(iTunesSupportDataSource* dataSource) : parentSource(dataSource)
{
	if (parentSource)
		parentSource->AddRef();
	str1 = (wchar_t*)malloc(200);
	str2 = (wchar_t*)malloc(200);
	str3 = (wchar_t*)malloc(200);
	str4 = (wchar_t*)malloc(200);
	str5 = (wchar_t*)malloc(200);
}


iTunesSupportControlData::~iTunesSupportControlData()
{
	if (parentSource)
		parentSource->Release();
	parentSource = nullptr;
	if (str1) free(str1);
	if (str2) free(str2);
	if (str3) free(str3);
	if (str4) free(str4);
	if (str5) free(str5);
	str1 = str2 = str3 = str4 = str5 = nullptr;
}
