// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装器类

#import "C:\\Program Files\\iTunes\\iTunes.exe" no_namespace
// CITConvertOperationStatus 包装器类

class CITConvertOperationStatus : public COleDispatchDriver
{
public:
	CITConvertOperationStatus() {} // 调用 COleDispatchDriver 默认构造函数
	CITConvertOperationStatus(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CITConvertOperationStatus(const CITConvertOperationStatus& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 特性
public:

	// 操作
public:


	// IITConvertOperationStatus 方法
public:
	BOOL get_InProgress()
	{
		BOOL result;
		InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Tracks()
	{
		LPDISPATCH result;
		InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void GetConversionStatus(BSTR * trackName, long * progressValue, long * maxProgressValue)
	{
		static BYTE parms[] = VTS_PBSTR VTS_PI4 VTS_PI4;
		InvokeHelper(0x60030000, DISPATCH_METHOD, VT_EMPTY, NULL, parms, trackName, progressValue, maxProgressValue);
	}
	void StopConversion()
	{
		InvokeHelper(0x60030001, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	CString get_trackName()
	{
		CString result;
		InvokeHelper(0x60030002, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long get_progressValue()
	{
		long result;
		InvokeHelper(0x60030003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_maxProgressValue()
	{
		long result;
		InvokeHelper(0x60030004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}

	// IITConvertOperationStatus 属性
public:

};
