// �����Ϳ������á�����ࡱ�����ļ�������ɵ� IDispatch ��װ����

#import "C:\\Program Files\\iTunes\\iTunes.exe" no_namespace
// CITVisual ��װ����

class CITVisual : public COleDispatchDriver
{
public:
	CITVisual() {} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CITVisual(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CITVisual(const CITVisual& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// IITVisual ����
public:
	CString get_Name()
	{
		CString result;
		InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}

	// IITVisual ����
public:

};
