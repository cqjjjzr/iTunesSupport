#pragma once

#ifndef ITS_UTILS
#define ITS_UTILS

#include <string>

using namespace std;

inline size_t WriteString(size_t len, const wchar_t* str, wchar_t *dest) {
	if (len < sizeof(str)) {
		wcscpy(dest, wstring().substr(0, len).c_str());
		return len;
	}
	wcscpy(dest, str);
	return sizeof(str);
}


size_t writeCSharpStringToValue(System::String ^value, size_t nbyte, void* buf) {
	pin_ptr<const wchar_t> pinchars = PtrToStringChars(value);
	int res = NERvCopyString(pinchars, nbyte / 2, static_cast<wchar_t*>(buf)) * 2;
	pinchars = nullptr;
	System::GC::Collect();
	return res;
}
#endif