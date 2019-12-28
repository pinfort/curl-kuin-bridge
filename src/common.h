#pragma once

#include <Windows.h>
#include <string>

#define KUIN_MAX_PATH (512)

typedef struct SEnvVars
{
	void* Heap;
#if defined(_DEBUG)
	signed long long* HeapCnt;
#endif
	signed long long AppCode;
	const unsigned char* UseResFlags;
	wchar_t ResRoot[KUIN_MAX_PATH];
} SEnvVars;
extern SEnvVars EnvVars;

void* AllocMem(size_t size);
void FreeMem(void* ptr);

std::string WstrToStr(std::wstring wstr);
