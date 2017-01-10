#include "iTunesLibraryInitializer.h"
#include <Windows.h>
#include <NERvGear\plugin.h>
#include <NERvGear\log.h>
#include <io.h>
#include <NERvGear\NERv1API.h>

using namespace NERvGear;

BOOL iTunesLibraryInitializer::initialized = false;

BOOL checkiTunesCOMExists() {
	CLSID clsid;
	HRESULT result = CLSIDFromProgID(L"iTunes.Application", &clsid);
	return result != CO_E_CLASSSTRING;
}

int IsiTunesLibExists();
void initiTunesLib();

int PrepareiTunesLib() {
	wchar_t temp[200] = { 0 };
	GetCurrentDirectory(100, temp);
	SetCurrentDirectory(NERvGetModulePath());
	if (IsiTunesLibExists()) {
		SetCurrentDirectory(temp);
		return S_OK;
	}

	NERvLogInfo(NVG_TEXT("iTunesSupport"), NVG_TEXT("iTunes Library need be extracted!"));
	DeleteFile(L"..\\..\\Interop.iTunesLib.dll");
	BOOL result = CopyFile(L"Interop.iTunesLib.dll", L"..\\..\\Interop.iTunesLib.dll", FALSE);
	BOOL result2 = CopyFile(L"iTunesSupportImpl.dll", L"..\\..\\iTunesSupportImpl.dll", FALSE);
	if (result && result2) {
		NERvLogInfo(NVG_TEXT("iTunesSupport"), NVG_TEXT("Extracted successfully."));
		SetCurrentDirectory(temp);
		return result;
	}
	else {
		wchar_t inf[100] = { 0 };
		wchar_t cd[100] = { 0 };
		GetCurrentDirectory(100, cd);
		wsprintf(inf, L"Error while extracting! error=%d currentdict=%s", GetLastError(), cd);
		NERvLogError(NVG_TEXT("iTunesSupport"), inf);
		SetCurrentDirectory(temp);
		return 0;
	}
}

int IsiTunesLibExists() {
	int result = _access("..\\..\\iTunesSupportImpl.dll", 0);
	int result2 = _access("..\\..\\Interop.iTunesLib.dll", 0);

	if (result == -1 || result2 == -1) return 0;

	HANDLE fHandle = CreateFile(L"..\\..\\iTunesSupportImpl.dll",
		READ_CONTROL, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE fHandleNew = CreateFile(L"iTunesSupportImpl.dll",
		READ_CONTROL, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	int size = GetFileSize(fHandle, NULL);
	int sizeNew = GetFileSize(fHandleNew, NULL);
	CloseHandle(fHandle);
	CloseHandle(fHandleNew);
	return size == sizeNew;
}

long iTunesLibraryInitializer::init()
{
	if (!initialized) {
		if (!checkiTunesCOMExists()) {
			NERvLogError(NVG_TEXT("iTunesSupport"), NVG_TEXT("iTunes not found. Plugin stopping!"));
			return E_FAIL;
		}
		long result = PrepareiTunesLib();
		initialized = (result == S_OK);
		return result;
	}
	return S_OK;
}

BOOL iTunesLibraryInitializer::isInitialized()
{
	return iTunesLibraryInitializer::initialized;
}

iTunesLibraryInitializer::iTunesLibraryInitializer()
{
}


iTunesLibraryInitializer::~iTunesLibraryInitializer()
{
}
