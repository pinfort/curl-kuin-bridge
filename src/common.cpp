#include "common.h"
#include <stdexcept>

SEnvVars EnvVars;

void FreeMem(void* ptr)
{
	HeapFree(EnvVars.Heap, 0, ptr);
#if defined(_DEBUG)
	(*EnvVars.HeapCnt)--;
	ASSERT(*EnvVars.HeapCnt >= 0);
#endif
}

std::string WstrToStr(std::wstring wstr)
{
	int len_str = wstr.length();
	size_t len = (size_t)(WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), len_str, NULL, 0, NULL, NULL));
	char* buf = (char*)malloc(sizeof(char) * (len + 1));
	memset(buf, 0, sizeof(char) * (len + 1));

	if (WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), len_str, buf, (int)len, NULL, NULL) != (int)len)
	{
		FreeMem(buf);
		std::runtime_error("wchar_t char convert failed\n");
	}
	buf[len] = '\0';
	std::string retVal(buf);
	return retVal;
}
