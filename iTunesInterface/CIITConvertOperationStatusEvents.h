// �����Ϳ������á�����ࡱ�����ļ�������ɵ� IDispatch ��װ����

#import "C:\\Program Files\\iTunes\\iTunes.exe" no_namespace
// CIITConvertOperationStatusEvents ��װ����

class CIITConvertOperationStatusEvents : public COleDispatchDriver
{
public:
	CIITConvertOperationStatusEvents() {} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CIITConvertOperationStatusEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CIITConvertOperationStatusEvents(const CIITConvertOperationStatusEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// _IITConvertOperationStatusEvents ����
public:
	STDMETHOD(OnConvertOperationStatusChangedEvent)(LPCTSTR trackName, long progressValue, long maxProgressValue)
	{
		HRESULT result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_HRESULT, (void*)&result, parms, trackName, progressValue, maxProgressValue);
		return result;
	}
	STDMETHOD(OnConvertOperationCompleteEvent)()
	{
		HRESULT result;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_HRESULT, (void*)&result, NULL);
		return result;
	}

	// _IITConvertOperationStatusEvents ����
public:

};
