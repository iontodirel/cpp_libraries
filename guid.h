// sai - General purpose self-contained C++ libraries.
//
// guid.h
// Wrapper utility for Windows GUIDs.
// 
// MIT License
// 
// Copyright (c) 2017 Ion Todirel
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef SAI_CORE_GUID_H
#define SAI_CORE_GUID_H

#include <string>
#include <cwchar>

#include <Windows.h>

enum class guid_format
{
	include_brackets,
	exclude_brackets
};

class guid
{
public:
	static guid create_new()
	{
		GUID guid;
		CoCreateGuid(&guid);
		return class guid(guid);
	}

	guid()
	{
	}

	guid(const char* str)
	{
		std::wstring wstr;
		wstr.resize(40);
		MultiByteToWideChar(0, 0, str, (int)wstr.length(), (wchar_t*)wstr.c_str(), (int)wstr.length());
		CLSIDFromString(wstr.c_str(), &guid_);
	}

	guid(std::string str) : guid(str.c_str())
	{
	}

	guid(const wchar_t* str)
	{
		CLSIDFromString(str, &guid_);
	}

	guid(std::wstring str) : guid(str.c_str())
	{
	}

	guid(const guid& other)
	{
		guid_ = other.guid_;
	}

	guid& operator=(const guid& other)
	{
		guid_ = other.guid_;
		return *this;
	}

	void swap(guid& other)
	{
		std::swap(guid_, other.guid_);
	}

	std::string to_string() const
	{
		return to_string(guid_format::include_brackets);
	}

	std::string to_string(guid_format format) const
	{
		std::string str;
		str.resize(39);
		if (format == guid_format::include_brackets)
		{
			snprintf((char*)str.c_str(), str.length(), "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}", guid_.Data1, guid_.Data2, guid_.Data3, guid_.Data4[0], guid_.Data4[1], guid_.Data4[2], guid_.Data4[3], guid_.Data4[4], guid_.Data4[5], guid_.Data4[6], guid_.Data4[7]);
			str.erase(38, 1);
		}
		else
		{
			snprintf((char*)str.c_str(), str.length(), "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X", guid_.Data1, guid_.Data2, guid_.Data3, guid_.Data4[0], guid_.Data4[1], guid_.Data4[2], guid_.Data4[3], guid_.Data4[4], guid_.Data4[5], guid_.Data4[6], guid_.Data4[7]);
			str.erase(36, 3);
		}
		return str;
	}

	std::wstring to_wstring() const
	{
		return to_wstring(guid_format::include_brackets);
	}

	std::wstring to_wstring(guid_format format) const
	{
		std::wstring str;
		str.resize(39);
		if (format == guid_format::include_brackets)
		{
			swprintf((wchar_t*)str.c_str(), str.length(), L"{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}", guid_.Data1, guid_.Data2, guid_.Data3, guid_.Data4[0], guid_.Data4[1], guid_.Data4[2], guid_.Data4[3], guid_.Data4[4], guid_.Data4[5], guid_.Data4[6], guid_.Data4[7]);
			str.erase(38, 1);
		}
		else
		{
			swprintf((wchar_t*)str.c_str(), str.length(), L"%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X", guid_.Data1, guid_.Data2, guid_.Data3, guid_.Data4[0], guid_.Data4[1], guid_.Data4[2], guid_.Data4[3], guid_.Data4[4], guid_.Data4[5], guid_.Data4[6], guid_.Data4[7]);
			str.erase(36, 3);
		}		
		return str;
	}

	bool empty() const
	{
		return guid_.Data1 == 0 &&
			guid_.Data2 == 0 &&
			guid_.Data3 == 0 &&
			guid_.Data4[0] == 0 &&
			guid_.Data4[1] == 0 &&
			guid_.Data4[2] == 0 &&
			guid_.Data4[3] == 0 &&
			guid_.Data4[4] == 0 &&
			guid_.Data4[5] == 0 &&
			guid_.Data4[6] == 0 &&
			guid_.Data4[7] == 0;
	}

	bool operator == (const guid& other) const
	{
		return guid_.Data1 == other.guid_.Data1 &&
			guid_.Data2 == other.guid_.Data2 &&
			guid_.Data3 == other.guid_.Data3 &&
			guid_.Data4[0] == other.guid_.Data4[0] &&
			guid_.Data4[1] == other.guid_.Data4[1] &&
			guid_.Data4[2] == other.guid_.Data4[2] &&
			guid_.Data4[3] == other.guid_.Data4[3] &&
			guid_.Data4[4] == other.guid_.Data4[4] &&
			guid_.Data4[5] == other.guid_.Data4[5] &&
			guid_.Data4[6] == other.guid_.Data4[6] &&
			guid_.Data4[7] == other.guid_.Data4[7];
	}

	bool operator != (const guid& other) const
	{
		return !(*this == other);
	}
private:
	guid(GUID guid)
	{
		guid_ = guid;
	}

private:
	GUID guid_ = {};
};

guid new_guid()
{
	return guid::create_new();
}

#endif