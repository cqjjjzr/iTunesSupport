// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装器类

#import "C:\\Program Files\\iTunes\\iTunes.exe" no_namespace
// CIITConvertOperationStatusEvents 包装器类

class CIITConvertOperationStatusEvents : public COleDispatchDriver
{
public:
	CIITConvertOperationStatusEvents() {} // 调用 COleDispatchDriver 默认构造函数
	CIITConvertOperationStatusEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CIITConvertOperationStatusEvents(const CIITConvertOperationStatusEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 特性
public:

	// 操作
public:


	// _IITConvertOperationStatusEvents 方法
public:
	STDMETHOD(OnConvertOperationStatusChangedEvent)(LPCTSTR trackName, long progressValue, long maxProgressValue)
	{
		HRESULT result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_HRESULT, (void*)&result, parms, trackName, progressValue, maxProgressValue);
		return result;
	}
	STDMETHOD(OnConvertOperationCompleteEvent)()
	{
		HRESULT result;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_HRESULT, (void*)&result, NULL);
		return result;
	}

	// _IITConvertOperationStatusEvents 属性
public:

};
