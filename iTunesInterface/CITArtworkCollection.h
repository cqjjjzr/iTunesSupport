// �����Ϳ������á�����ࡱ�����ļ�������ɵ� IDispatch ��װ����

#import "C:\\Program Files\\iTunes\\iTunes.exe" no_namespace
// CITArtworkCollection ��װ����

class CITArtworkCollection : public COleDispatchDriver
{
public:
	CITArtworkCollection() {} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CITArtworkCollection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CITArtworkCollection(const CITArtworkCollection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// IITArtworkCollection ����
public:
	long get_Count()
	{
		long result;
		InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Item(long Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}
	LPUNKNOWN get__NewEnum()
	{
		LPUNKNOWN result;
		InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
		return result;
	}

	// IITArtworkCollection ����
public:

};
