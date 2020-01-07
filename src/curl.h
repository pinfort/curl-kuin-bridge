#pragma once

#include <curl/curl.h>
#include <stdexcept>
#include <future>

#include "common.h"

typedef struct SClass
{
	unsigned long long RefCnt;
	void* ClassTable;
} SClass;

typedef struct SCurl
{
	SClass Class;
	CURL* Curl;
} SCurl;

typedef struct SCurlAsyncTask
{
	SClass Class;
	std::future<long>* task;

	int setTask(std::future<long>* task)
	{
		this->task = task;
		return 0;
	}
} SCurlAsyncTask;

typedef struct SResponse
{
	SClass Class;
	unsigned char* body;
	unsigned char* header;

	int appendBody(std::wstring str)
	{
		if (this->body == NULL)
		{
			this->body = WStrToKuinStr(str);
		}
		else {
			std::wstring old = KuinStrToWStr(this->body);
			old.append(str);
			this->body = WStrToKuinStr(old);
		}
		return 0;
	}

	int appendHeader(std::wstring str)
	{
		if (this->header == NULL)
		{
			this->header = WStrToKuinStr(str);
		}
		else
		{
			std::wstring old = KuinStrToWStr(this->header);
			old.append(str);
			this->header = WStrToKuinStr(old);
		}
		return 0;
	}
} SResponse;

class Curl
{
public:
	using TCurlEasyInitProc = CURL * (*)(void);
	using TCurlEasySetOptProc = CURLcode(*)(CURL*, CURLoption, void*);
	using TCurlEasyPerformProc = CURLcode(*)(CURL*);
	using TCurlEasyCleanupProc = void(*)(CURL*);

	TCurlEasyInitProc curl_easy_init;
	TCurlEasySetOptProc curl_easy_setopt;
	TCurlEasyPerformProc curl_easy_perform;
	TCurlEasyCleanupProc curl_easy_cleanup;

	HMODULE dll;

	Curl::Curl(std::string path)
	{

		this->dll = LoadLibrary(path.c_str());
		if (this->dll == NULL)
		{
			printf("DLL of libcurl cannot be loaded.\n");
			std::runtime_error("DLL of libcurl cannot be loaded.\n");
		}

		FARPROC proc1 = GetProcAddress(dll, "curl_easy_init");
		if (proc1 == NULL)
		{
			printf("curl_easy_init func cannot be loaded.\n");
			std::runtime_error("curl_easy_init func cannot be loaded.\n");
		}
		this->curl_easy_init = reinterpret_cast<TCurlEasyInitProc>(proc1);

		FARPROC proc2 = GetProcAddress(dll, "curl_easy_setopt");
		if (proc2 == NULL)
		{
			printf("curl_easy_setopt func cannot be loaded.\n");
			std::runtime_error("curl_easy_setopt func cannot be loaded.\n");
		}
		this->curl_easy_setopt = reinterpret_cast<TCurlEasySetOptProc>(proc2);

		FARPROC proc3 = GetProcAddress(dll, "curl_easy_perform");
		if (proc3 == NULL)
		{
			printf("curl_easy_perform func cannot be loaded.\n");
			std::runtime_error("curl_easy_perform func cannot be loaded.\n");
		}
		this->curl_easy_perform = reinterpret_cast<TCurlEasyPerformProc>(proc3);

		FARPROC proc4 = GetProcAddress(dll, "curl_easy_cleanup");
		if (proc4 == NULL)
		{
			printf("curl_easy_cleanup func cannot be loaded.\n");
			std::runtime_error("curl_easy_cleanup func cannot be loaded.\n");
		}
		this->curl_easy_cleanup = reinterpret_cast<TCurlEasyCleanupProc>(proc4);
	};

	~Curl()
	{
		FreeLibrary(this->dll);
	};

private:

};
