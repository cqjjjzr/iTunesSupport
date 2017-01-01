#using "C:\Users\cqjjj\Documents\Visual Studio 2015\Projects\iTunesSupport\iTunesSupportImpl\bin\Debug\iTunesSupportImpl.dll"
#include "iTunesSupportInfoData.h"
#include "vcclr.h"
#include <NERvGear/string.h>
#include <NERvGear\plugin.h>
#include <NERvGear\NERvSDK.h>
#include <iostream>
#include <cstdio>
#include <sstream>
#include "iTunesSupport.h"

#include "iTunesSupportDataSource.h";

using namespace std;
using namespace iTunesSupportImpl;

const UID iTunesSupportInfoData::dataUID = { 0xf3594f55, 0xe57c, 0x4988,{ 0xbe, 0x3c, 0x2d, 0xd4, 0xbd, 0x02, 0xc9, 0xa4 } };

long NVG_METHOD iTunesSupportInfoData::GetId(NERvGear::UID * id)
{
	*id = dataUID;
	return S_OK;
}

size_t NVG_METHOD iTunesSupportInfoData::GetName(size_t len, wchar_t * name)
{
	return WriteString(len, L"iTunes数据获取", name);
}

size_t NVG_METHOD iTunesSupportInfoData::GetDescrip(size_t len, wchar_t * descrip)
{
	return WriteString(len, L"获取有关iTunes的信息。", descrip);
}

long NVG_METHOD iTunesSupportInfoData::QuerySource(NERvGear::IDataSource ** source)
{
	if (source == NULL)
		return E_INVALIDARG;

	*source = parentSource;
	(*source)->AddRef();

	return S_OK;
}

unsigned NVG_METHOD iTunesSupportInfoData::GetValueCount()
{
	return 9;
}

size_t getValueInternal(unsigned index, size_t nbyte, void * buf) {
	switch (index) {
	case 5:
		*reinterpret_cast<unsigned*>(buf) = iTunesSupportImplWrapper::getInstance()->volume;
		return sizeof(unsigned);
	case 0:
		*reinterpret_cast<unsigned*>(buf) = iTunesSupportImplWrapper::getInstance()->progressSecond;
		return sizeof(unsigned);
	case 1: return writeCSharpStringToValue(iTunesSupportImplWrapper::getInstance()->progressFormatted, nbyte, buf);
	case 2: return writeCSharpStringToValue(iTunesSupportImplWrapper::getInstance()->trackName, nbyte, buf);
	case 3: return writeCSharpStringToValue(iTunesSupportImplWrapper::getInstance()->trackArtist, nbyte, buf);
	case 4: return writeCSharpStringToValue(iTunesSupportImplWrapper::getInstance()->trackAlbum, nbyte, buf);
	case 6: return writeCSharpStringToValue(iTunesSupportImplWrapper::getInstance()->lyric->LyricLine1, nbyte, buf);
	case 7: return writeCSharpStringToValue(iTunesSupportImplWrapper::getInstance()->lyric->LyricLine2, nbyte, buf);
	case 8: return writeCSharpStringToValue(iTunesSupportImplWrapper::getInstance()->cover, nbyte, buf);
	default:return 0;
	}
}

size_t NVG_METHOD iTunesSupportInfoData::GetValue(unsigned index, size_t nbyte, void * buf)
{
	if (!iTunesSupport::initalized) return E_FAIL;
	return getValueInternal(index, nbyte, buf);
}

unsigned getTrackLengthInternal() {
	return iTunesSupportImplWrapper::getInstance()->trackLength;
}

size_t NVG_METHOD iTunesSupportInfoData::GetMaximum(unsigned index, size_t nbyte, void * buf)
{
	if (!iTunesSupport::initalized) return E_FAIL;
	switch (index) {
	case 5: 
		*reinterpret_cast<unsigned*>(buf) = 100;
		return sizeof(unsigned);
	case 0:
		*reinterpret_cast<unsigned*>(buf) = getTrackLengthInternal();
		return sizeof(unsigned);
	default:return 0;
	}
}

size_t NVG_METHOD iTunesSupportInfoData::GetMinimum(unsigned index, size_t nbyte, void * buf)
{
	switch (index) {
	case 5:
	case 0:
		*reinterpret_cast<unsigned*>(buf) = 0;
		return sizeof(unsigned);
	default:return 0;
	}
}

unsigned NVG_METHOD iTunesSupportInfoData::GetValueIndex(int id)
{
	if (id > NVG_ANY && id < 9)
		return id;

	return NVG_ANY;
}

int NVG_METHOD iTunesSupportInfoData::GetValueId(unsigned index)
{
	if (index < 9)
		return index;
	return NVG_ANY;
}

NERvGear::DATA::TYPE NVG_METHOD iTunesSupportInfoData::GetValueType(unsigned index)
{
	switch (index) {
	case 5:
	case 0: return NERvGear::DATA::INTEGER;
	case 1:
	case 2:
	case 3:
	case 4:
	case 6: 
	case 7: 
	case 8: return NERvGear::DATA::STRING;
	default:return NERvGear::DATA::RAW;
	}
}

size_t NVG_METHOD iTunesSupportInfoData::GetValueUnit(unsigned index, size_t len, wchar_t * unit)
{
	switch (index) {
	case 5: return NERvCopyString(L"%", len, unit);
	case 0: return NERvCopyString(L"秒", len, unit);
	default:return 0;
	}
}

size_t NVG_METHOD iTunesSupportInfoData::GetValueName(unsigned index, size_t len, wchar_t * name)
{
	switch (index) {
	case 0: return NERvCopyString(L"播放进度", len, name);
	case 1: return NERvCopyString(L"播放时间", len, name);
	case 2: return NERvCopyString(L"标题", len, name);
	case 3: return NERvCopyString(L"表演者", len, name);
	case 4: return NERvCopyString(L"专辑", len, name);
	case 5: return NERvCopyString(L"音量", len, name);
	case 6: return NERvCopyString(L"第一行歌词", len, name);
	case 7: return NERvCopyString(L"第二行歌词", len, name);
	case 8: return NERvCopyString(L"封面", len, name);
	default:return 0;
	}
}

size_t NVG_METHOD iTunesSupportInfoData::GetValueDescrip(unsigned index, size_t len, wchar_t * descrip)
{
	switch (index) {
	case 0: return NERvCopyString(L"获取当前音乐播放进度，建议以100ms为更新间隔。", len, descrip);
	case 1: return NERvCopyString(L"获取当前音乐播放时间，建议以100ms为更新间隔。", len, descrip);
	case 2: return NERvCopyString(L"获取当前音乐标题，建议以1s为更新间隔。", len, descrip);
	case 3: return NERvCopyString(L"获取当前音乐表演者，建议以1s为更新间隔。", len, descrip);
	case 4: return NERvCopyString(L"获取当前音乐专辑，建议以1s为更新间隔。", len, descrip);
	case 5: return NERvCopyString(L"获取当前音量。", len, descrip);
	case 6: return NERvCopyString(L"获取LRC中相同时间的标签中的第一次出现的歌词。建议以100ms为更新间隔。\n歌词来自于iTunes中歌曲的“歌词”标签，且要求使用LRC格式。", len, descrip);
	case 7: return NERvCopyString(L"获取LRC中相同时间的标签中的第二次出现的歌词。建议以100ms为更新间隔。\n歌词来自于iTunes中歌曲的“歌词”标签，且要求使用LRC格式。", len, descrip);
	case 8: return NERvCopyString(L"获取当前专辑封面。", len, descrip);
	default:return 0;
	}
}

unsigned NVG_METHOD iTunesSupportInfoData::GetUpdateInterval(unsigned index)
{
	switch (index) {
	case 0: return 100;
	case 1: return 100;
	case 2: return 1000;
	case 3: return 1000;
	case 4: return 1000;
	case 5: return 5;
	case 6: return 100;
	case 7: return 100;
	case 8: return 1000;
	default:return 0;
	}
}

long updateInternal(unsigned index, const wchar_t * param);

long NVG_METHOD iTunesSupportInfoData::Update(unsigned index, const wchar_t * param)
{
	if (!iTunesSupport::initalized) return E_FAIL;
	return updateInternal(index, param);
}

long updateInternal(unsigned index, const wchar_t * param) {
	//NO MEMORY LEAK!
	if (index >= 9)
		return E_INVALIDARG;
	iTunesSupportImplWrapper^ wrapper = iTunesSupportImplWrapper::getInstance();
	wrapper->activePointer();
	wrapper->update(index, gcnew System::String(param));
	return S_OK;
}

long NVG_METHOD iTunesSupportInfoData::Invoke(unsigned index, const wchar_t * param, NERvGear::UI::IWindow * window)
{
	return S_FALSE;
}

size_t NVG_METHOD iTunesSupportInfoData::Config(unsigned index, NERvGear::DATA::CONFIG type, NERvGear::UI::IWindow * window, size_t len, wchar_t * param)
{
	return 0;
}

long NVG_METHOD iTunesSupportInfoData::SetValueUnit(unsigned index, const wchar_t * unit)
{
	return S_OK;
}

size_t NVG_METHOD iTunesSupportInfoData::EnumValueUnit(unsigned index, size_t len, wchar_t * units)
{
	switch (index) {
	case 5:
		return NERvCopyStringDoubleNull(L"%\0", len, units);
	case 0:
		return NERvCopyStringDoubleNull(L"秒\0", len, units);
	default:return 0;
	}
}

long NVG_METHOD iTunesSupportInfoData::SetEventListener(NERvGear::IEventHandler * listener)
{
	return E_NOTIMPL;
}

iTunesSupportInfoData::iTunesSupportInfoData(iTunesSupportDataSource* dataSource) : parentSource(dataSource)
{
	if (parentSource)
		parentSource->AddRef();
}


iTunesSupportInfoData::~iTunesSupportInfoData()
{
	if (parentSource)
		parentSource->Release();
	parentSource = nullptr;
}
