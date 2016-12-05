// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装器类

#import "C:\\Program Files\\iTunes\\iTunes.exe" no_namespace
// CITIPodSource 包装器类

class CITIPodSource : public COleDispatchDriver
{
public:
	CITIPodSource() {} // 调用 COleDispatchDriver 默认构造函数
	CITIPodSource(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CITIPodSource(const CITIPodSource& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 特性
public:

	// 操作
public:


	// IITIPodSource 方法
public:
	void GetITObjectIDs(long * sourceID, long * playlistID, long * trackID, long * databaseID)
	{
		static BYTE parms[] = VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4;
		InvokeHelper(0x60020000, DISPATCH_METHOD, VT_EMPTY, NULL, parms, sourceID, playlistID, trackID, databaseID);
	}
	CString get_Name()
	{
		CString result;
		InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_Name(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x60020001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Index()
	{
		long result;
		InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_sourceID()
	{
		long result;
		InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_playlistID()
	{
		long result;
		InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_trackID()
	{
		long result;
		InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_TrackDatabaseID()
	{
		long result;
		InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_Kind()
	{
		long result;
		InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	double get_Capacity()
	{
		double result;
		InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
		return result;
	}
	double get_FreeSpace()
	{
		double result;
		InvokeHelper(0x60030002, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Playlists()
	{
		LPDISPATCH result;
		InvokeHelper(0x60030003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void UpdateIPod()
	{
		InvokeHelper(0x60040000, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void EjectIPod()
	{
		InvokeHelper(0x60040001, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	CString get_SoftwareVersion()
	{
		CString result;
		InvokeHelper(0x60040002, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}

	// IITIPodSource 属性
public:

};
