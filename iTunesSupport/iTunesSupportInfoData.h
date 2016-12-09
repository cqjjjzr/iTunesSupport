#ifndef ITS_ITUNES_SUPPORT_INFO_DATA
#define ITS_ITUNES_SUPPORT_INFO_DATA
#include <NERvGear\template.h>
#include <NERvGear\interface\IData.h>

using namespace NERvGear;

class iTunesSupportDataSource;

class iTunesSupportInfoData :
	public NERvGear::ImplT<NVG_ARGS_ITF_UID(IData)>
{
public:
	// {F3594F55-E57C-4988-BE3C-2DD4BD02C9A4}
	const static UID dataUID;

	virtual long NVG_METHOD GetId(NERvGear::UID* id);

	virtual size_t NVG_METHOD GetName(size_t len, wchar_t* name);
	virtual size_t NVG_METHOD GetDescrip(size_t len, wchar_t* descrip);
	virtual long NVG_METHOD QuerySource(NERvGear::IDataSource** source);

	virtual unsigned NVG_METHOD GetValueCount();

	virtual size_t NVG_METHOD GetValue(unsigned index, size_t nbyte, void* buf);
	virtual size_t NVG_METHOD GetMaximum(unsigned index, size_t nbyte, void* buf);
	virtual size_t NVG_METHOD GetMinimum(unsigned index, size_t nbyte, void* buf);

	virtual unsigned NVG_METHOD GetValueIndex(int id);
	virtual int NVG_METHOD GetValueId(unsigned index);
	virtual NERvGear::DATA::TYPE NVG_METHOD GetValueType(unsigned index);
	virtual size_t NVG_METHOD GetValueUnit(unsigned index, size_t len, wchar_t* unit);
	virtual size_t NVG_METHOD GetValueName(unsigned index, size_t len, wchar_t* name);
	virtual size_t NVG_METHOD GetValueDescrip(unsigned index, size_t len, wchar_t* descrip);

	virtual unsigned NVG_METHOD GetUpdateInterval(unsigned index);
	virtual long NVG_METHOD Update(unsigned index = NVG_ANY, const wchar_t* param = NULL);
	virtual long NVG_METHOD Invoke(unsigned index, const wchar_t* param = NULL, NERvGear::UI::IWindow* window = NULL);
	virtual size_t NVG_METHOD Config(unsigned index, NERvGear::DATA::CONFIG type, NERvGear::UI::IWindow* window, size_t len, wchar_t* param);

	virtual long NVG_METHOD SetValueUnit(unsigned index, const wchar_t* unit);
	virtual size_t NVG_METHOD EnumValueUnit(unsigned index, size_t len, wchar_t* units);

	virtual long NVG_METHOD SetEventListener(NERvGear::IEventHandler* listener);

	iTunesSupportInfoData(iTunesSupportDataSource* dataSource);
	~iTunesSupportInfoData();

private:
	iTunesSupportDataSource* parentSource;
};
#endif
