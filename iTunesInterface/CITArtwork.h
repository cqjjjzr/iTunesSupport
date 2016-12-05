// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装器类

#import "C:\\Program Files\\iTunes\\iTunes.exe" no_namespace
// CITArtwork 包装器类

class CITArtwork : public COleDispatchDriver
{
public:
	CITArtwork() {} // 调用 COleDispatchDriver 默认构造函数
	CITArtwork(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CITArtwork(const CITArtwork& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 特性
public:

	// 操作
public:


	// IITArtwork 方法
public:
	void Delete()
	{
		InvokeHelper(0x60020000, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SetArtworkFromFile(LPCTSTR filePath)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x60020001, DISPATCH_METHOD, VT_EMPTY, NULL, parms, filePath);
	}
	void SaveArtworkToFile(LPCTSTR filePath)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x60020002, DISPATCH_METHOD, VT_EMPTY, NULL, parms, filePath);
	}
	long get_Format()
	{
		long result;
		InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	BOOL get_IsDownloadedArtwork()
	{
		BOOL result;
		InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	CString get_Description()
	{
		CString result;
		InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_Description(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x60020005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}

	// IITArtwork 属性
public:

};
