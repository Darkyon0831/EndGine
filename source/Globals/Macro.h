#pragma once

#include <cassert>
#include "Globals/String.h"
#include <string>

inline void CheckHRError(const char* filename, const int lineNumber, const char* functionName, HRESULT resultCode)
{
	// file, function, line
	EG::String string;
	string += filename;
	string += ", ";
	string += functionName;
	string += ", ";
	string += std::to_string(lineNumber).c_str();

	assert(resultCode == 0x00 && string.GetString());
}

#define EGCHECKHR(HRCODE) CheckHRError(__FILE__, __LINE__, __FUNCTION__, HRCODE);

