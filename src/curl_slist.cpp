#pragma once

#include "slist.h"

Slist SlistDLLFuncs = Slist(dllPath);

extern "C" _declspec(dllexport) SClass * export_curl_slist_init(SClass * me_, unsigned char * string)
{
	SSlist* me2 = (SSlist*)me_;
	me2->slist = SlistDLLFuncs.curl_slist_append(NULL, WstrToStr(KuinStrToWStr(string)).c_str());
	return me_;
}

extern "C" _declspec(dllexport) SClass * export_curl_slist_append(SClass * me_, SClass * me2, unsigned char* string)
{
	SSlist* me3 = (SSlist*)me_;
	SSlist* me4 = (SSlist*)me2;
	me4->slist = SlistDLLFuncs.curl_slist_append(me3->slist, WstrToStr(KuinStrToWStr(string)).c_str());
	return me2;
}

extern "C" _declspec(dllexport) void export_curl_slist_free_all(SClass * me_)
{
	SSlist* me2 = (SSlist*)me_;
	return SlistDLLFuncs.curl_slist_free_all(me2->slist);
}
