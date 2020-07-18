#pragma once

#include <stdexcept>

#include "common.h"

typedef struct SSlist
{
	SClass Class;
	struct curl_slist* slist;
} SSlist;

class Slist
{
public:
	using TCurlSlistAppendProc = struct curl_slist* (*)(struct curl_slist*, const char*);
	using TCurlSlistFreeAllProc = void(*)(struct curl_slist*);

	TCurlSlistAppendProc curl_slist_append;
	TCurlSlistFreeAllProc curl_slist_free_all;

	HMODULE dll;

	Slist::Slist(std::string path)
	{

		this->dll = LoadLibrary(path.c_str());
		if (this->dll == NULL)
		{
			printf("DLL of libcurl cannot be loaded.\n");
			std::runtime_error("DLL of libcurl cannot be loaded.\n");
		}

		FARPROC proc1 = GetProcAddress(dll, "curl_slist_append");
		if (proc1 == NULL)
		{
			printf("curl_slist_append func cannot be loaded.\n");
			std::runtime_error("curl_slist_append func cannot be loaded.\n");
		}
		this->curl_slist_append = reinterpret_cast<TCurlSlistAppendProc>(proc1);


		FARPROC proc2 = GetProcAddress(dll, "curl_slist_free_all");
		if (proc2 == NULL)
		{
			printf("curl_slist_free_all func cannot be loaded.\n");
			std::runtime_error("curl_slist_free_all func cannot be loaded.\n");
		}
		this->curl_slist_free_all = reinterpret_cast<TCurlSlistFreeAllProc>(proc2);
	};

	~Slist()
	{
		FreeLibrary(this->dll);
	};
};
