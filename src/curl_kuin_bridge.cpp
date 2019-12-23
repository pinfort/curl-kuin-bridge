#include "common.h"
#include "curl.h"
#include <stdexcept>

BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID)
{
	return TRUE;
}

std::string dllPath = std::string("data\\libcurl-x64.dll");
Curl DLLFuncs = Curl(dllPath);

extern "C" _declspec(dllexport) void* curl_easy_init()
{
	return DLLFuncs.curl_easy_init();
}

extern "C" _declspec(dllexport) int curl_easy_setopt(void* handle, int option, void* parameter)
{
	if (option >= CURLoption::CURLOPT_LASTENTRY)
	{
		std::runtime_error("invalid option value.\n");
	}
	return DLLFuncs.curl_easy_setopt(handle, (CURLoption)option, parameter);
}
