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
#endif