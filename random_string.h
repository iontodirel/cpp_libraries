// sai - General purpose self-contained C++ libraries.
//
// random_string.h
// Utility function for generating random strings of specified lengths.
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

#ifndef SAI_CORE_RANDOM_STRING
#define SAI_CORE_RANDOM_STRING

#include <string>
#include <random>

template <class StringType, class Traits, class Allocator>
inline auto random_string(const std::basic_string<StringType, Traits, Allocator>& allowed_chars, int length)
{
    std::random_device generator;
    std::uniform_int_distribution<int> distribution(0, allowed_chars.size() - 1);
    std::basic_string<StringType, Traits, Allocator> random_string;
    std::generate_n(std::back_inserter(random_string), length, [&]() { return allowed_chars[distribution(generator)]; });
    return random_string;
}

inline std::string random_string(int length)
{
    const std::string allowed_chars = "abcdefghijklmnopqrstuvwxyz0123456789";
    return random_string(allowed_chars, length);
}

inline std::wstring random_wstring(int length)
{
    const std::wstring allowed_chars = L"abcdefghijklmnopqrstuvwxyz0123456789";
    return random_string(allowed_chars, length);
}

inline std::u16string random_u16string(int length)
{
    const std::u16string allowed_chars = u"abcdefghijklmnopqrstuvwxyz0123456789";
    return random_string(allowed_chars, length);
}

inline std::u32string random_u32string(int length)
{
    const std::u32string allowed_chars = U"abcdefghijklmnopqrstuvwxyz0123456789";
    return random_string(allowed_chars, length);
}

#endif
