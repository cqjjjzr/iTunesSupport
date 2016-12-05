// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装器类

#import "C:\\Program Files\\iTunes\\iTunes.exe" no_namespace
// CITEncoder 包装器类

class CITEncoder : public COleDispatchDriver
{
public:
	CITEncoder() {} // 调用 COleDispatchDriver 默认构造函数
	CITEncoder(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CITEncoder(const CITEncoder& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 特性
public:

	// 操作
public:


	// IITEncoder 方法
public:
	CString get_Name()
	{
		CString result;
		InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_Format()
	{
		CString result;
		InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}

	// IITEncoder 属性
public:

};
