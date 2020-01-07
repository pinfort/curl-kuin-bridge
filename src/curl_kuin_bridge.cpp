#include "common.h"
#include "curl.h"
#include <stdexcept>
#include <kuin_type_bridge.h>
#include <future>

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

extern "C" _declspec(dllexport) int export_curl_easy_setopt_org(SClass* me_, signed long long option, void* parameter)
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

extern "C" _declspec(dllexport) int export_curl_easy_setopt_str(SClass * me_, signed long long option, unsigned char* parameter)
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

static size_t WriteCallback(char* contents, size_t size, size_t nmemb, SResponse** userp)
{
	std::string input(contents);
	(*userp)->appendBody(StrToWstr(input));
	return size * nmemb;
}

extern "C" _declspec(dllexport) int export_config_easy_response(SClass* me_, SClass** me2)
{
	SCurl* me3 = (SCurl*)me_;
	CURL* handle = me3->Curl;
	SResponse** me4 = reinterpret_cast<SResponse**>(me2);

	//#ifdef SKIP_PEER_VERIFICATION
	DLLFuncs.curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L);
	//#endif
	//#ifdef SKIP_HOSTNAME_VERIFICATION
	DLLFuncs.curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0L);
	//#endif
	DLLFuncs.curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, WriteCallback);
	return DLLFuncs.curl_easy_setopt(handle, CURLOPT_WRITEDATA, me4);
}

extern "C" _declspec(dllexport) SClass* export_async_perform(SClass* me_)
{
	SCurl* me2 = (SCurl*)me_;
	CURL* handle = me2->Curl;

	//std::future<long> task = std::future<long>();
	//task = std::async(std::launch::async,
	//	[handle]() -> long
	//	{
	//		//return DLLFuncs.curl_easy_perform(handle);
	//		return 0L;
	//	}
	//);
	SCurlAsyncTask* task_manager = new SCurlAsyncTask();
	//task_manager->setTask(&task);
	return (SClass*)task_manager;
}

static size_t HeaderCallback(char* contents, size_t size, size_t nmemb, SResponse** userp)
{
	std::string input(contents);
	(*userp)->appendHeader(StrToWstr(input));
	return size * nmemb;
}

extern "C" _declspec(dllexport) int export_config_easy_header(SClass * me_, SClass * *me2)
{
	SCurl* me3 = (SCurl*)me_;
	CURL* handle = me3->Curl;
	SResponse** me4 = reinterpret_cast<SResponse**>(me2);
	DLLFuncs.curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L);
	DLLFuncs.curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0L);
	DLLFuncs.curl_easy_setopt(handle, CURLOPT_HEADERFUNCTION, HeaderCallback);
	return DLLFuncs.curl_easy_setopt(handle, CURLOPT_HEADERDATA, me4);
}

extern "C" _declspec(dllexport) void export_curl_easy_cleanup(SClass * me_)
{
	SCurl* me2 = (SCurl*)me_;
	CURL* handle = me2->Curl;
	return DLLFuncs.curl_easy_cleanup(handle);
}

extern "C" _declspec(dllexport) int export_async_task_get(SClass * me_)
{
	printf("called\n");
	/*SCurlAsyncTask* task = (SCurlAsyncTask*)me_;
	printf("convt\n");
	std::future<long>* a = task->task;
	printf("take\n");
	long b = a->get();
	printf("execute\n");*/
	return 0;
}
