// �����Ϳ������á�����ࡱ�����ļ�������ɵ� IDispatch ��װ����

#import "C:\\Program Files\\iTunes\\iTunes.exe" no_namespace
// CITEncoder ��װ����

class CITEncoder : public COleDispatchDriver
{
public:
	CITEncoder() {} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CITEncoder(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CITEncoder(const CITEncoder& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// IITEncoder ����
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

	// IITEncoder ����
public:

};
