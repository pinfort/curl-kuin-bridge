#include "common.h"
#include "curl.h"
#include <stdexcept>
#include <kuin_type_bridge.h>

BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID)
{
	return TRUE;
}

std::string dllPath = std::string("data\\libcurl-x64.dll");
Curl DLLFuncs = Curl(dllPath);

extern "C" _declspec(dllexport) SClass * export_curl_easy_init(SClass * me_)
{
	SCurl* me2 = (SCurl*)me_;
	me2->Curl = DLLFuncs.curl_easy_init();
	return me_;
}

extern "C" _declspec(dllexport) int export_curl_easy_setopt_org(SClass* me_, int option, void* parameter)
{
	// ílå^ópÅBéQè∆å^ÇìnÇ≥Ç»Ç¢Ç≈Ç≠ÇæÇ≥Ç¢
	// ì¡Ç…ï∂éöóÒíçà”
	SCurl* me2 = (SCurl*)me_;
	CURL* handle = me2->Curl;
	if (option >= CURLoption::CURLOPT_LASTENTRY)
	{
		std::runtime_error("invalid option value.\n");
	}
	return DLLFuncs.curl_easy_setopt(handle, (CURLoption)option, parameter);
}

extern "C" _declspec(dllexport) int export_curl_easy_setopt_str(SClass * me_, int option, unsigned char* parameter)
{
	// ï∂éöóÒêÍóp
	std::wstring param_wstr = KuinStrToWStr(parameter);
	std::string param_str = WstrToStr(param_wstr);

	return export_curl_easy_setopt_org(me_, option, const_cast<char*>(param_str.c_str()));
}

extern "C" _declspec(dllexport) int export_curl_easy_perform(SClass * me_)
{
	SCurl* me2 = (SCurl*)me_;
	CURL* handle = me2->Curl;
	return DLLFuncs.curl_easy_perform(handle);
}

extern "C" _declspec(dllexport) void export_curl_easy_cleanup(SClass * me_)
{
	SCurl* me2 = (SCurl*)me_;
	CURL* handle = me2->Curl;
	return DLLFuncs.curl_easy_cleanup(handle);
}
