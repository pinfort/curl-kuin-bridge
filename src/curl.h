#pragma once

#include <stdexcept>
#include <future>

#include "common.h"

typedef struct SCurl
{
	SClass Class;
	CURL* Curl;
} SCurl;

typedef struct SCurlAsyncTask
{
	SClass Class;
	std::future<long> Task;
} SCurlAsyncTask;

typedef struct SResponse
{
	SClass Class;
	unsigned char* body = nullptr;
	unsigned char* header = nullptr;
	unsigned char* binary_body = nullptr;

	int appendBody(std::wstring str)
	{
		if (this->body == nullptr)
		{
			this->body = WStrToKuinStr(str, 10);
		}
		else {
			std::wstring old = KuinStrToWStr(this->body);
			old.append(str);
			this->body = WStrToKuinStr(old, KuinArray(this->body).getDefaultRefCntFunc());
		}
		return 0;
	}

	int appendHeader(std::wstring str)
	{
		if (this->header == nullptr)
		{
			this->header = WStrToKuinStr(str, 10);
		}
		else
		{
			std::wstring old = KuinStrToWStr(this->header);
			old.append(str);
			this->header = WStrToKuinStr(old, KuinArray(this->header).getDefaultRefCntFunc());
		}
		return 0;
	}

	int appendBinaryBody(unsigned char* str, size_t size)
	{
		std::vector<unsigned char> str_vector;
		str_vector.insert(str_vector.end(), &str[0], &str[size]);

		if (this->binary_body == nullptr)
		{
			this->binary_body = CppVectorToKuinArray(str_vector, 10);
		}
		else
		{
			unsigned char* bin = this->binary_body;
			KuinArray kuin_arr = KuinArray(bin);
			unsigned long long len = kuin_arr.getLen();
			std::vector<unsigned char> old = KuinArrayToCppVector(this->binary_body);
			old.insert(old.end(), str_vector.begin(), str_vector.end());
			this->binary_body = CppVectorToKuinArray(old, kuin_arr.getDefaultRefCntFunc());
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
