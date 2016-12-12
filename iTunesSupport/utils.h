#ifndef ITS_UTILS
#define ITS_UTILS

#include <string>
#include <NERvGear/string.h>
#include <NERvGear/NERvSDK.h>
#include <vcclr.h>

using namespace NERvGear;
using namespace std;

inline size_t WriteString(size_t len, const wchar_t* str, wchar_t *dest) {
	if (len < sizeof(str)) {
		wcscpy(dest, wstring().substr(0, len).c_str());
		return len;
	}
	wcscpy(dest, str);
	return sizeof(str);
}

inline size_t writeCSharpStringToValue(System::String ^value, size_t nbyte, void* buf) {
	pin_ptr<const wchar_t> pinchars = PtrToStringChars(value);
	int res = NERvCopyString(pinchars, nbyte / 2, static_cast<wchar_t*>(buf)) * 2;
	pinchars = nullptr;
	return res;
}
#endif