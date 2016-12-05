// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装器类

#import "C:\\Program Files\\iTunes\\iTunes.exe" no_namespace
// CITVisual 包装器类

class CITVisual : public COleDispatchDriver
{
public:
	CITVisual() {} // 调用 COleDispatchDriver 默认构造函数
	CITVisual(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CITVisual(const CITVisual& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 特性
public:

	// 操作
public:


	// IITVisual 方法
public:
	CString get_Name()
	{
		CString result;
		InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}

	// IITVisual 属性
public:

};
