#include "iTunesSupportDataSource.h"

#include <string>
#include <NERvGear/string.h>
#include <NERvGear/new.h>
#include <NERvGear/log.h>
#include <NERvGear/component/CDataSource.h>

#include "utils.h"
#include "iTunesSupportInfoData.h"

using namespace std;
using namespace NERvGear;

const UID infoDataUID = { 0xf3594f55, 0xe57c, 0x4988,{ 0xbe, 0x3c, 0x2d, 0xd4, 0xbd, 0x02, 0xc9, 0xa4 } };

iTunesSupportDataSource::iTunesSupportDataSource()
{
}

iTunesSupportDataSource::~iTunesSupportDataSource()
{
}

long NVG_METHOD iTunesSupportDataSource::GetId(NERvGear::UID * id)
{
	*id = srcUID;
	return S_OK;
}

size_t NVG_METHOD iTunesSupportDataSource::GetName(size_t len, wchar_t * name)
{
	const wchar_t* str = L"iTunes Support";
	return WriteString(len, str, name);
}

size_t NVG_METHOD iTunesSupportDataSource::GetDescrip(size_t len, wchar_t * descrip)
{
	const wchar_t* str = L"支持iTunes音乐播放器。";
	return WriteString(len, str, descrip);
}

unsigned NVG_METHOD iTunesSupportDataSource::GetDataCount()
{
	return 2;
}

long NVG_METHOD iTunesSupportDataSource::GetData(unsigned index, NERvGear::IData ** data)
{
	if (index >= 2 || data == NULL)
		return E_INVALIDARG;

	switch (index) {
	case 0: *data = nvg_new iTunesSupportInfoData(this); break;
	//case 1: *data = nvg_new iTunesSupportInfoControl(this); break;
	default: return E_FAIL;
	}
	return S_OK;
}

long iTunesSupportDataSource::FindData(const NERvGear::UID& id, NERvGear::IData ** data)
{
	if (data == NULL)
		return E_INVALIDARG; 

	if (id.Data1 == 0xf3594f55) 
		*data = nvg_new iTunesSupportInfoData(this);
	else return E_FAIL;
	return S_OK;
}

NVG_BEGIN_OBJECT_INFO(iTunesSupportDataSource)
NVG_DECLARE_OBJECT_CLASSID_UID(ID_CDataSource)
// {1C0C1731-D190-49F3-B34D-4A69EFD3C249}
NVG_DECLARE_OBJECT_OBJECTID(0x1c0c1731, 0xd190, 0x49f3, 0xb3, 0x4d, 0x4a, 0x69, 0xef, 0xd3, 0xc2, 0x49)
NVG_DECLARE_OBJECT_VERSION(1, 0, 0)
NVG_DECLARE_OBJECT_NAME("iTunes Support")
NVG_DECLARE_OBJECT_DESCRIP("支持iTunes音乐播放器。")
NVG_END_OBJECT_INFO()

NVG_BEGIN_INTERFACE_INFO(iTunesSupportDataSource)
NVG_DECLARE_INTERFACE(ID_IUnknown, IUnknown, this)
NVG_DECLARE_INTERFACE(ID_IDataSource, IDataSource, this)
NVG_END_INTERFACE_INFO()
