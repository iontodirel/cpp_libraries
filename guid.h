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
// furnished to do so, subject to the following conditions:
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
#include <algorithm>
#include <Windows.h>

enum class guid_format
{
    default = 1,
    uppercase = 1,
    lowercase = 2,
    uppercase_no_brackets,
    lowercase_no_brackets
};

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
        return to_string(guid_format::default);
    }

    std::string to_string(guid_format format) const
    {
        std::string str;
        str.resize(39);

        std::string fmt;
        switch (format)
        {
        case guid_format::uppercase:
            fmt = "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}";
            break;
        case guid_format::lowercase:
            fmt = "{%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x}";
            break;
        case guid_format::uppercase_no_brackets:
            fmt = "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X";
            break;
        case guid_format::lowercase_no_brackets:
            fmt = "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x";
            break;
        }

        snprintf((char*)str.c_str(), str.length(), fmt.c_str(), guid_.Data1, guid_.Data2, guid_.Data3, guid_.Data4[0], guid_.Data4[1], guid_.Data4[2], guid_.Data4[3], guid_.Data4[4], guid_.Data4[5], guid_.Data4[6], guid_.Data4[7]);

        trim_null_terminators(str);

        return str;
    }

    std::string to_string(char format) const
    {
        guid_format fmt = guid_format::default;
        switch (format)
        {
        case 'B':
            fmt = guid_format::uppercase;
            break;
        case 'b':
            fmt = guid_format::lowercase;
            break;
        case 'A':
            fmt = guid_format::uppercase_no_brackets;
            break;
        case 'a':
            fmt = guid_format::lowercase_no_brackets;
            break;
        }
        return to_string(fmt);
    }

    std::string to_string(const std::string& format) const
    {
        guid_format fmt = guid_format::default;
        if (format.length() == 1)
        {
            switch (format[0])
            {
            case 'B':
                fmt = guid_format::uppercase;
                break;
            case 'b':
                fmt = guid_format::lowercase;
                break;
            case 'A':
                fmt = guid_format::uppercase_no_brackets;
                break;
            case 'a':
                fmt = guid_format::lowercase_no_brackets;
                break;
            }
        }
        return to_string(fmt);
    }

    std::wstring to_wstring() const
    {
        return to_wstring(guid_format::default);
    }

    std::wstring to_wstring(guid_format format) const
    {
        return string_to_wstring(to_string(format).c_str());
    }

    std::wstring to_wstring(char format) const
    {
        return string_to_wstring(to_string(format).c_str());
    }

    std::wstring to_wstring(const std::string& format) const
    {
        return string_to_wstring(to_string(format).c_str());
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
        trim_null_terminators(wstr);
        return wstr;
    }

    template <class Type>
    void trim_null_terminators(std::basic_string<Type>& str) const
    {
        str.erase(std::find_if(str.rbegin(), str.rend(), [](auto ch) { return ch != '\0'; }).base(), str.end());
    }

private:
    GUID guid_ = {};
};

#endif