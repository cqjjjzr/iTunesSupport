// �����Ϳ������á�����ࡱ�����ļ�������ɵ� IDispatch ��װ����

#import "C:\\Program Files\\iTunes\\iTunes.exe" no_namespace
// CITArtwork ��װ����

class CITArtwork : public COleDispatchDriver
{
public:
	CITArtwork() {} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CITArtwork(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CITArtwork(const CITArtwork& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// IITArtwork ����
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

	// IITArtwork ����
public:

};
