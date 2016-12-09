#pragma once

#ifndef ITS_ITUNES_SUPPORT_DATA_SOURCE
#define ITS_ITUNES_SUPPORT_DATA_SOURCE

#include <NERvGear/interface/IDataSource.h>
#include <NERvGear/object.h>
#include <NERvGear\template.h>

using namespace NERvGear;

class iTunesSupportInfoData;

class iTunesSupportDataSource : public IDataSource
{
public:
	const UID srcUID = { 0x1c0c1731, 0xd190, 0x49f3,{ 0xb3, 0x4d, 0x4a, 0x69, 0xef, 0xd3, 0xc2, 0x49 } };
	//const UID infoDataUID = { 0xf3594f55, 0xe57c, 0x4988,{ 0xbe, 0x3c, 0x2d, 0xd4, 0xbd, 0x2, 0xc9, 0xa4 } };

	virtual long NVG_METHOD GetId(NERvGear::UID* id);

	virtual size_t NVG_METHOD GetName(size_t len, wchar_t* name);
	virtual size_t NVG_METHOD GetDescrip(size_t len, wchar_t* descrip);

	virtual unsigned NVG_METHOD GetDataCount();

	virtual long NVG_METHOD GetData(unsigned index, NERvGear::IData** data);

	virtual long NVG_METHOD FindData(const NERvGear::UID& id, NERvGear::IData** data);

	iTunesSupportDataSource();
	virtual ~iTunesSupportDataSource();
private:    
	//iTunesSupportInfoData* infoData;

	NVG_DECLARE_OBJECT(iTunesSupportDataSource)
};

#endif
