#include "common.h"
#include <stdexcept>

std::string WstrToStr(std::wstring wstr)
{
	int len_str = wstr.length();
	size_t len = (size_t)(WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), len_str, NULL, 0, NULL, NULL));
	char* buf = (char*)malloc(sizeof(char) * (len + 1));
	memset(buf, 0, sizeof(char) * (len + 1));

	if (WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), len_str, buf, (int)len, NULL, NULL) != (int)len)
	{
		free(buf);
		std::runtime_error("wchar_t char convert failed\n");
	}
	buf[len] = '\0';
	std::string retVal(buf);
	return retVal;
}

std::wstring StrToWstr(std::string str)
{
	int len_str = str.length();
	size_t len = (size_t)MultiByteToWideChar(CP_UTF8, 0, str.c_str(), len_str, NULL, 0);
	wchar_t* buf = (wchar_t*)malloc(sizeof(wchar_t) * (len + 1));
	memset(buf, 0, sizeof(wchar_t) * (len + 1));

	if (MultiByteToWideChar(CP_UTF8, 0, str.c_str(), len_str, buf, (int)len) != (int)len)
	{
		free(buf);
		std::runtime_error("char wchar_t convert failed\n");;
	}
	buf[len] = '\0';
	std::wstring retVal(buf);
	return retVal;
}
