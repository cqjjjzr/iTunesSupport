// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装器类

#import "C:\\Program Files\\iTunes\\iTunes.exe" no_namespace
// CITEQPreset 包装器类

class CITEQPreset : public COleDispatchDriver
{
public:
	CITEQPreset() {} // 调用 COleDispatchDriver 默认构造函数
	CITEQPreset(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CITEQPreset(const CITEQPreset& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 特性
public:

	// 操作
public:


	// IITEQPreset 方法
public:
	CString get_Name()
	{
		CString result;
		InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	BOOL get_Modifiable()
	{
		BOOL result;
		InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	double get_Preamp()
	{
		double result;
		InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
		return result;
	}
	void put_Preamp(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x60020002, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	double get_Band1()
	{
		double result;
		InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
		return result;
	}
	void put_Band1(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x60020004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	double get_Band2()
	{
		double result;
		InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
		return result;
	}
	void put_Band2(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x60020006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	double get_Band3()
	{
		double result;
		InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
		return result;
	}
	void put_Band3(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x60020008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	double get_Band4()
	{
		double result;
		InvokeHelper(0x6002000a, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
		return result;
	}
	void put_Band4(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x6002000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	double get_Band5()
	{
		double result;
		InvokeHelper(0x6002000c, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
		return result;
	}
	void put_Band5(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x6002000c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	double get_Band6()
	{
		double result;
		InvokeHelper(0x6002000e, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
		return result;
	}
	void put_Band6(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x6002000e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	double get_Band7()
	{
		double result;
		InvokeHelper(0x60020010, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
		return result;
	}
	void put_Band7(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x60020010, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	double get_Band8()
	{
		double result;
		InvokeHelper(0x60020012, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
		return result;
	}
	void put_Band8(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x60020012, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	double get_Band9()
	{
		double result;
		InvokeHelper(0x60020014, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
		return result;
	}
	void put_Band9(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x60020014, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	double get_Band10()
	{
		double result;
		InvokeHelper(0x60020016, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
		return result;
	}
	void put_Band10(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x60020016, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void Delete(BOOL updateAllTracks)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x60020018, DISPATCH_METHOD, VT_EMPTY, NULL, parms, updateAllTracks);
	}
	void Rename(LPCTSTR newName, BOOL updateAllTracks)
	{
		static BYTE parms[] = VTS_BSTR VTS_BOOL;
		InvokeHelper(0x60020019, DISPATCH_METHOD, VT_EMPTY, NULL, parms, newName, updateAllTracks);
	}

	// IITEQPreset 属性
public:

};
