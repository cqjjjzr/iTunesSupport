// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装器类
//#undef GetFreeSpace
#import "C:\Program Files\iTunes\iTunes.exe" no_namespace
// CiTunes 包装器类

class CiTunes : public COleDispatchDriver
{
public:
	CiTunes() {} // 调用 COleDispatchDriver 默认构造函数
	CiTunes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CiTunes(const CiTunes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 特性
public:

	// 操作
public:


	// IiTunes 方法
public:
	void BackTrack()
	{
		InvokeHelper(0x60020000, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void FastForward()
	{
		InvokeHelper(0x60020001, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void NextTrack()
	{
		InvokeHelper(0x60020002, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Pause()
	{
		InvokeHelper(0x60020003, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Play()
	{
		InvokeHelper(0x60020004, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void PlayFile(LPCTSTR filePath)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x60020005, DISPATCH_METHOD, VT_EMPTY, NULL, parms, filePath);
	}
	void PlayPause()
	{
		InvokeHelper(0x60020006, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void PreviousTrack()
	{
		InvokeHelper(0x60020007, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Resume()
	{
		InvokeHelper(0x60020008, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Rewind()
	{
		InvokeHelper(0x60020009, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Stop()
	{
		InvokeHelper(0x6002000a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH ConvertFile(LPCTSTR filePath)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x6002000b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, filePath);
		return result;
	}
	LPDISPATCH ConvertFiles(VARIANT * filePaths)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_PVARIANT;
		InvokeHelper(0x6002000c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, filePaths);
		return result;
	}
	LPDISPATCH ConvertTrack(VARIANT * iTrackToConvert)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_PVARIANT;
		InvokeHelper(0x6002000d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, iTrackToConvert);
		return result;
	}
	LPDISPATCH ConvertTracks(VARIANT * iTracksToConvert)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_PVARIANT;
		InvokeHelper(0x6002000e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, iTracksToConvert);
		return result;
	}
	BOOL CheckVersion(long majorVersion, long minorVersion)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0x6002000f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, majorVersion, minorVersion);
		return result;
	}
	LPDISPATCH GetITObjectByID(long sourceID, long playlistID, long trackID, long databaseID)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x60020010, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, sourceID, playlistID, trackID, databaseID);
		return result;
	}
	LPDISPATCH CreatePlaylist(LPCTSTR playlistName)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x60020011, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, playlistName);
		return result;
	}
	void OpenURL(LPCTSTR URL)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x60020012, DISPATCH_METHOD, VT_EMPTY, NULL, parms, URL);
	}
	void GotoMusicStoreHomePage()
	{
		InvokeHelper(0x60020013, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void UpdateIPod()
	{
		InvokeHelper(0x60020014, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Authorize(long numElems, VARIANT * data, BSTR * names)
	{
		static BYTE parms[] = VTS_I4 VTS_PVARIANT VTS_PBSTR;
		InvokeHelper(0x60020015, DISPATCH_METHOD, VT_EMPTY, NULL, parms, numElems, data, names);
	}
	void Quit()
	{
		InvokeHelper(0x60020016, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH get_Sources()
	{
		LPDISPATCH result;
		InvokeHelper(0x60020017, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Encoders()
	{
		LPDISPATCH result;
		InvokeHelper(0x60020018, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_EQPresets()
	{
		LPDISPATCH result;
		InvokeHelper(0x60020019, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Visuals()
	{
		LPDISPATCH result;
		InvokeHelper(0x6002001a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Windows()
	{
		LPDISPATCH result;
		InvokeHelper(0x6002001b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_SoundVolume()
	{
		long result;
		InvokeHelper(0x6002001c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_SoundVolume(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x6002001c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_Mute()
	{
		BOOL result;
		InvokeHelper(0x6002001e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_Mute(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x6002001e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_PlayerState()
	{
		long result;
		InvokeHelper(0x60020020, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_PlayerPosition()
	{
		long result;
		InvokeHelper(0x60020021, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_PlayerPosition(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x60020021, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_CurrentEncoder()
	{
		LPDISPATCH result;
		InvokeHelper(0x60020023, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void put_CurrentEncoder(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x60020023, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_VisualsEnabled()
	{
		BOOL result;
		InvokeHelper(0x60020025, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_VisualsEnabled(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x60020025, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_FullScreenVisuals()
	{
		BOOL result;
		InvokeHelper(0x60020027, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_FullScreenVisuals(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x60020027, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_VisualSize()
	{
		long result;
		InvokeHelper(0x60020029, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_VisualSize(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x60020029, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_CurrentVisual()
	{
		LPDISPATCH result;
		InvokeHelper(0x6002002b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void put_CurrentVisual(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x6002002b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_EQEnabled()
	{
		BOOL result;
		InvokeHelper(0x6002002d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_EQEnabled(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x6002002d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_CurrentEQPreset()
	{
		LPDISPATCH result;
		InvokeHelper(0x6002002f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void put_CurrentEQPreset(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x6002002f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_CurrentStreamTitle()
	{
		CString result;
		InvokeHelper(0x60020031, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_CurrentStreamURL()
	{
		CString result;
		InvokeHelper(0x60020032, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_BrowserWindow()
	{
		LPDISPATCH result;
		InvokeHelper(0x60020033, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_EQWindow()
	{
		LPDISPATCH result;
		InvokeHelper(0x60020034, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_LibrarySource()
	{
		LPDISPATCH result;
		InvokeHelper(0x60020035, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_LibraryPlaylist()
	{
		LPDISPATCH result;
		InvokeHelper(0x60020036, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_CurrentTrack()
	{
		LPDISPATCH result;
		InvokeHelper(0x60020037, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_CurrentPlaylist()
	{
		LPDISPATCH result;
		InvokeHelper(0x60020038, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_SelectedTracks()
	{
		LPDISPATCH result;
		InvokeHelper(0x60020039, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	CString get_Version()
	{
		CString result;
		InvokeHelper(0x6002003a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void SetOptions(long options)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x6002003b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, options);
	}
	LPDISPATCH ConvertFile2(LPCTSTR filePath)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x6002003c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, filePath);
		return result;
	}
	LPDISPATCH ConvertFiles2(VARIANT * filePaths)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_PVARIANT;
		InvokeHelper(0x6002003d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, filePaths);
		return result;
	}
	LPDISPATCH ConvertTrack2(VARIANT * iTrackToConvert)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_PVARIANT;
		InvokeHelper(0x6002003e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, iTrackToConvert);
		return result;
	}
	LPDISPATCH ConvertTracks2(VARIANT * iTracksToConvert)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_PVARIANT;
		InvokeHelper(0x6002003f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, iTracksToConvert);
		return result;
	}
	BOOL get_AppCommandMessageProcessingEnabled()
	{
		BOOL result;
		InvokeHelper(0x60020040, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_AppCommandMessageProcessingEnabled(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x60020040, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_ForceToForegroundOnDialog()
	{
		BOOL result;
		InvokeHelper(0x60020042, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_ForceToForegroundOnDialog(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x60020042, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH CreateEQPreset(LPCTSTR eqPresetName)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x60020044, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, eqPresetName);
		return result;
	}
	LPDISPATCH CreatePlaylistInSource(LPCTSTR playlistName, VARIANT * iSource)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_PVARIANT;
		InvokeHelper(0x60020045, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, playlistName, iSource);
		return result;
	}
	void GetPlayerButtonsState(BOOL * previousEnabled, long * playPauseStopState, BOOL * nextEnabled)
	{
		static BYTE parms[] = VTS_PBOOL VTS_PI4 VTS_PBOOL;
		InvokeHelper(0x60020046, DISPATCH_METHOD, VT_EMPTY, NULL, parms, previousEnabled, playPauseStopState, nextEnabled);
	}
	void PlayerButtonClicked(long playerButton, long playerButtonModifierKeys)
	{
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0x60020047, DISPATCH_METHOD, VT_EMPTY, NULL, parms, playerButton, playerButtonModifierKeys);
	}
	BOOL get_CanSetShuffle(VARIANT * iPlaylist)
	{
		BOOL result;
		static BYTE parms[] = VTS_PVARIANT;
		InvokeHelper(0x60020048, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, iPlaylist);
		return result;
	}
	BOOL get_CanSetSongRepeat(VARIANT * iPlaylist)
	{
		BOOL result;
		static BYTE parms[] = VTS_PVARIANT;
		InvokeHelper(0x60020049, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, iPlaylist);
		return result;
	}
	LPDISPATCH get_ConvertOperationStatus()
	{
		LPDISPATCH result;
		InvokeHelper(0x6002004a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void SubscribeToPodcast(LPCTSTR URL)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x6002004b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, URL);
	}
	void UpdatePodcastFeeds()
	{
		InvokeHelper(0x6002004c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH CreateFolder(LPCTSTR folderName)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x6002004d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, folderName);
		return result;
	}
	LPDISPATCH CreateFolderInSource(LPCTSTR folderName, VARIANT * iSource)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_PVARIANT;
		InvokeHelper(0x6002004e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, folderName, iSource);
		return result;
	}
	BOOL get_SoundVolumeControlEnabled()
	{
		BOOL result;
		InvokeHelper(0x6002004f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	CString get_LibraryXMLPath()
	{
		CString result;
		InvokeHelper(0x60020050, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long get_ITObjectPersistentIDHigh(VARIANT * iObject)
	{
		long result;
		static BYTE parms[] = VTS_PVARIANT;
		InvokeHelper(0x60020051, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, iObject);
		return result;
	}
	long get_ITObjectPersistentIDLow(VARIANT * iObject)
	{
		long result;
		static BYTE parms[] = VTS_PVARIANT;
		InvokeHelper(0x60020052, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, iObject);
		return result;
	}
	void GetITObjectPersistentIDs(VARIANT * iObject, long * highID, long * lowID)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_PI4 VTS_PI4;
		InvokeHelper(0x60020053, DISPATCH_METHOD, VT_EMPTY, NULL, parms, iObject, highID, lowID);
	}
	long get_PlayerPositionMS()
	{
		long result;
		InvokeHelper(0x60020054, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_PlayerPositionMS(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x60020054, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}

	// IiTunes 属性
public:

};
