#pragma once

#include <curl/curl.h>

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
