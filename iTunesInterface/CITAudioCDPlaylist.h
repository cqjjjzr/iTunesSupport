// �����Ϳ������á�����ࡱ�����ļ�������ɵ� IDispatch ��װ����

#import "C:\\Program Files\\iTunes\\iTunes.exe" no_namespace
// CITAudioCDPlaylist ��װ����

class CITAudioCDPlaylist : public COleDispatchDriver
{
public:
	CITAudioCDPlaylist() {} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CITAudioCDPlaylist(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CITAudioCDPlaylist(const CITAudioCDPlaylist& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// IITAudioCDPlaylist ����
public:
	void GetITObjectIDs(long * sourceID, long * playlistID, long * trackID, long * databaseID)
	{
		static BYTE parms[] = VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4;
		InvokeHelper(0x60020000, DISPATCH_METHOD, VT_EMPTY, NULL, parms, sourceID, playlistID, trackID, databaseID);
	}
	CString get_Name()
	{
		CString result;
		InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_Name(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x60020001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Index()
	{
		long result;
		InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_sourceID()
	{
		long result;
		InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_playlistID()
	{
		long result;
		InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_trackID()
	{
		long result;
		InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_TrackDatabaseID()
	{
		long result;
		InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void Delete()
	{
		InvokeHelper(0x60030000, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void PlayFirstTrack()
	{
		InvokeHelper(0x60030001, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Print(BOOL showPrintDialog, long printKind, LPCTSTR theme)
	{
		static BYTE parms[] = VTS_BOOL VTS_I4 VTS_BSTR;
		InvokeHelper(0x60030002, DISPATCH_METHOD, VT_EMPTY, NULL, parms, showPrintDialog, printKind, theme);
	}
	LPDISPATCH Search(LPCTSTR searchText, long searchFields)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_I4;
		InvokeHelper(0x60030003, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, searchText, searchFields);
		return result;
	}
	long get_Kind()
	{
		long result;
		InvokeHelper(0x60030004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Source()
	{
		LPDISPATCH result;
		InvokeHelper(0x60030005, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_Duration()
	{
		long result;
		InvokeHelper(0x60030006, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	BOOL get_Shuffle()
	{
		BOOL result;
		InvokeHelper(0x60030007, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_Shuffle(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x60030007, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	double get_Size()
	{
		double result;
		InvokeHelper(0x60030009, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
		return result;
	}
	long get_SongRepeat()
	{
		long result;
		InvokeHelper(0x6003000a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_SongRepeat(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x6003000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_Time()
	{
		CString result;
		InvokeHelper(0x6003000c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	BOOL get_Visible()
	{
		BOOL result;
		InvokeHelper(0x6003000d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Tracks()
	{
		LPDISPATCH result;
		InvokeHelper(0x6003000e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	CString get_Artist()
	{
		CString result;
		InvokeHelper(0x60040000, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	BOOL get_Compilation()
	{
		BOOL result;
		InvokeHelper(0x60040001, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	CString get_Composer()
	{
		CString result;
		InvokeHelper(0x60040002, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long get_DiscCount()
	{
		long result;
		InvokeHelper(0x60040003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_DiscNumber()
	{
		long result;
		InvokeHelper(0x60040004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString get_Genre()
	{
		CString result;
		InvokeHelper(0x60040005, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long get_Year()
	{
		long result;
		InvokeHelper(0x60040006, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void Reveal()
	{
		InvokeHelper(0x60040007, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

	// IITAudioCDPlaylist ����
public:

};
