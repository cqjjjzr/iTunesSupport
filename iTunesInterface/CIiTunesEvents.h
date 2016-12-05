// �����Ϳ������á�����ࡱ�����ļ�������ɵ� IDispatch ��װ����

#import "C:\\Program Files\\iTunes\\iTunes.exe" no_namespace
// CIiTunesEvents ��װ����

class CIiTunesEvents : public COleDispatchDriver
{
public:
	CIiTunesEvents() {} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CIiTunesEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CIiTunesEvents(const CIiTunesEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// _IiTunesEvents ����
public:
	STDMETHOD(OnDatabaseChangedEvent)(VARIANT& deletedObjectIDs, VARIANT& changedObjectIDs)
	{
		HRESULT result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_HRESULT, (void*)&result, parms, &deletedObjectIDs, &changedObjectIDs);
		return result;
	}
	STDMETHOD(OnPlayerPlayEvent)(VARIANT& iTrack)
	{
		HRESULT result;
		static BYTE parms[] = VTS_VARIANT;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_HRESULT, (void*)&result, parms, &iTrack);
		return result;
	}
	STDMETHOD(OnPlayerStopEvent)(VARIANT& iTrack)
	{
		HRESULT result;
		static BYTE parms[] = VTS_VARIANT;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_HRESULT, (void*)&result, parms, &iTrack);
		return result;
	}
	STDMETHOD(OnPlayerPlayingTrackChangedEvent)(VARIANT& iTrack)
	{
		HRESULT result;
		static BYTE parms[] = VTS_VARIANT;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_HRESULT, (void*)&result, parms, &iTrack);
		return result;
	}
	STDMETHOD(OnUserInterfaceEnabledEvent)()
	{
		HRESULT result;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_HRESULT, (void*)&result, NULL);
		return result;
	}
	STDMETHOD(OnCOMCallsDisabledEvent)(long reason)
	{
		HRESULT result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_HRESULT, (void*)&result, parms, reason);
		return result;
	}
	STDMETHOD(OnCOMCallsEnabledEvent)()
	{
		HRESULT result;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_HRESULT, (void*)&result, NULL);
		return result;
	}
	STDMETHOD(OnQuittingEvent)()
	{
		HRESULT result;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_HRESULT, (void*)&result, NULL);
		return result;
	}
	STDMETHOD(OnAboutToPromptUserToQuitEvent)()
	{
		HRESULT result;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_HRESULT, (void*)&result, NULL);
		return result;
	}
	STDMETHOD(OnSoundVolumeChangedEvent)(long newVolume)
	{
		HRESULT result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_HRESULT, (void*)&result, parms, newVolume);
		return result;
	}

	// _IiTunesEvents ����
public:

};
