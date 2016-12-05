// �����Ϳ������á�����ࡱ�����ļ�������ɵ� IDispatch ��װ����

#import "C:\\Program Files\\iTunes\\iTunes.exe" no_namespace
// CITPlaylistCollection ��װ����

class CITPlaylistCollection : public COleDispatchDriver
{
public:
	CITPlaylistCollection() {} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CITPlaylistCollection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CITPlaylistCollection(const CITPlaylistCollection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// IITPlaylistCollection ����
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
	LPDISPATCH get_ItemByName(LPCTSTR Name)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Name);
		return result;
	}
	LPUNKNOWN get__NewEnum()
	{
		LPUNKNOWN result;
		InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_ItemByPersistentID(long highID, long lowID)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, highID, lowID);
		return result;
	}

	// IITPlaylistCollection ����
public:

};
