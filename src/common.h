#pragma once

#include <Windows.h>
#include <string>
#include <kuin_type_bridge.h>

std::string WstrToStr(std::wstring wstr);
std::wstring StrToWstr(std::string str);
