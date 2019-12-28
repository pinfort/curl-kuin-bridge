#pragma once

#include <curl/curl.h>

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

	Curl(std::string);
	~Curl();

private:

};
