// �����Ϳ������á�����ࡱ�����ļ�������ɵ� IDispatch ��װ����

#import "C:\\Program Files\\iTunes\\iTunes.exe" no_namespace
// CITOperationStatus ��װ����

class CITOperationStatus : public COleDispatchDriver
{
public:
	CITOperationStatus() {} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CITOperationStatus(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CITOperationStatus(const CITOperationStatus& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// IITOperationStatus ����
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

	// IITOperationStatus ����
public:

};
