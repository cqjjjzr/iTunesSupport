// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装器类

#import "C:\\Program Files\\iTunes\\iTunes.exe" no_namespace
// CITOperationStatus 包装器类

class CITOperationStatus : public COleDispatchDriver
{
public:
	CITOperationStatus() {} // 调用 COleDispatchDriver 默认构造函数
	CITOperationStatus(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CITOperationStatus(const CITOperationStatus& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 特性
public:

	// 操作
public:


	// IITOperationStatus 方法
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

	// IITOperationStatus 属性
public:

};
