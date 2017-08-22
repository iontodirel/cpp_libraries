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

class guid
{
public:
    static guid create_new()
    {
        guid g;
        g.create();
        return g;
    }

    guid()
    {
    }

    explicit guid(const char* str)
    {
        create_from_string(string_to_wstring(str));
    }

    explicit guid(const std::string& str) : guid(str.c_str())
    {
    }

    explicit guid(const wchar_t* str)
    {
        create_from_string(std::wstring(str));
    }

    explicit guid(const std::wstring& str) : guid(str.c_str())
    {
    }

    void swap(guid& other)
    {
        std::swap(guid_, other.guid_);
    }

    void create()
    {
        if (empty())
        {
            CoCreateGuid(&guid_);
        }
    }

    void clear()
    {
        guid_ = {};
    }

    bool empty() const
    {
        return guid_ == GUID_NULL;
    }

    std::string to_string() const
    {
        std::string str;
        str.resize(39);
        snprintf((char*)str.c_str(), str.length(), "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}", guid_.Data1, guid_.Data2, guid_.Data3, guid_.Data4[0], guid_.Data4[1], guid_.Data4[2], guid_.Data4[3], guid_.Data4[4], guid_.Data4[5], guid_.Data4[6], guid_.Data4[7]);
        str.erase(38, str.npos);
        return str;
    }

    std::string to_string_no_brackets() const
    {
        return std::string(to_string(), 1, 36);
    }

    std::wstring to_wstring() const
    {
        return string_to_wstring(to_string().c_str());
    }

    std::wstring to_wstring_no_brackets() const
    {
        return std::wstring(to_wstring(), 1, 36);
    }

    bool operator == (const guid& other) const
    {
        return IsEqualGUID(guid_, other.guid_) == TRUE;
    }

    bool operator != (const guid& other) const
    {
        return !(*this == other);
    }

private:
    void create_from_string(std::wstring str)
    {
        if (str.length() > 1)
        {
            if (str[0] != L'{')
                str.insert(0, L"{");
            if (str[str.length() - 1] != L'}')
                str.append(L"}");
        }
        CLSIDFromString(str.c_str(), &guid_);
    }

    std::wstring string_to_wstring(const char* str) const
    {
        std::wstring wstr;
        wstr.resize(39);
        MultiByteToWideChar(0, 0, str, (int)wstr.length(), (wchar_t*)wstr.c_str(), (int)wstr.length());
        wstr.erase(38, wstr.npos);
        return wstr;
    }

private:
    GUID guid_ = {};
};

#endif