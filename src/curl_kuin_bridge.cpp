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

extern "C" _declspec(dllexport) SClass * curl_easy_init(SClass * me_)
{
	SCurl* me2 = (SCurl*)me_;
	me2->Curl = DLLFuncs.curl_easy_init();
	return me_;
}

extern "C" _declspec(dllexport) int curl_easy_setopt_org(SClass* me_, int option, void* parameter)
{
	// ’lŒ^—pBŽQÆŒ^‚ð“n‚³‚È‚¢‚Å‚­‚¾‚³‚¢
	// “Á‚É•¶Žš—ñ’ˆÓ
	SCurl* me2 = (SCurl*)me_;
	CURL* handle = me2->Curl;
	if (option >= CURLoption::CURLOPT_LASTENTRY)
	{
		std::runtime_error("invalid option value.\n");
	}
	return DLLFuncs.curl_easy_setopt(handle, (CURLoption)option, parameter);
}

extern "C" _declspec(dllexport) int curl_easy_setopt_str(SClass * me_, int option, unsigned char* parameter)
{
	// •¶Žš—ñê—p
	std::wstring param_wstr = KuinStrToWStr(parameter);
	std::string param_str = std::string(param_wstr.begin(), param_wstr.end());

	return curl_easy_setopt_org(me_, (CURLoption)option, (void*)param_str.c_str());
}

extern "C" _declspec(dllexport) int curl_easy_perform(SClass * me_)
{
	SCurl* me2 = (SCurl*)me_;
	CURL* handle = me2->Curl;
	return DLLFuncs.curl_easy_perform(handle);
}

extern "C" _declspec(dllexport) void curl_easy_cleanup(SClass * me_)
{
	SCurl* me2 = (SCurl*)me_;
	CURL* handle = me2->Curl;
	return DLLFuncs.curl_easy_cleanup(handle);
}
