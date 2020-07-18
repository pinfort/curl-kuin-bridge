#pragma once

#include <Windows.h>
#include <string>
#include <kuin_type_bridge.h>
#include <curl/curl.h>

typedef struct SClass
{
	unsigned long long RefCnt;
	void* ClassTable;
} SClass;

static const std::string dllPath = std::string("data\\libcurl-x64.dll");

std::string WstrToStr(std::wstring wstr);
std::wstring StrToWstr(std::string str);
