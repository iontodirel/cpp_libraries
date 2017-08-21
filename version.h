// sai - General purpose self-contained C++ libraries.
//
// version.h
// Stores version information.
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

#ifndef SAI_CORE_VERSION_H
#define SAI_CORE_VERSION_H

#include <string>
#include <stdexcept>
#include <sstream>
#include <algorithm>

class version_parse_exception : public std::exception
{
public:
    version_parse_exception() : std::exception() {}
    version_parse_exception(const std::string& message) : std::exception(message.c_str()) { message_ = message; }

    std::string message() { return message_; }

private:
    std::string message_;
};

class version
{
public:
    static version parse(const std::string& version_string)
    {
        return parse(version_string, "-");
    }
    // release separator start, release separator end...
    static version parse(const std::string& version_string, const std::string& release_separator)
    {
        version v;
        if (!try_parse(version_string, release_separator, v))
        {
            throw version_parse_exception("Could not parse version.");
        }
        return v;
    }

    static bool try_parse(const std::string& version_string, version& result) noexcept
    {
        return try_parse(version_string, "-", result);
    }

    static bool try_parse(const std::string& version_string, const std::string& release_separator, version& result) noexcept
    {
        version v;

        if (version_string.length() == 0)
        {
            return false;
        }

        int i = 0;
        std::stringstream ss(version_string);
        std::string s;
        while (std::getline(ss, s, '.'))
        {
            size_t release_index = s.find(release_separator);
            if (release_index != s.npos)
            {
                v.release_ = s.substr(release_index + release_separator.length());
                v.release_set_ = true;
                if (v.seq_field_count_ == 4)
                {
                    v.seq_field_count_++;
                }
                s = s.substr(0, release_index);
            }

            int n = 0;
            try
            {
                n = std::stoi(s);
            }
            catch (std::invalid_argument&)
            {
                return false;
            }
            catch (std::out_of_range&)
            {
                return false;
            }

            if (i == 0)
                v.major_ = n;
            else if (i == 1)
                v.minor_ = n;
            else if (i == 2)
            {
                v.revision_ = n;
                v.seq_field_count_++;
            }
            else if (i == 3)
            {
                v.build_ = n;
                v.seq_field_count_++;
            }

            i++;
        }

        // Only assign if successful
        result = v;

        return true;
    }

    version() {}
    explicit version(const std::string& version_string) { *this = parse(version_string); }
    version(int major, int minor) : major_(major), minor_(minor) {}
    version(int major, int minor, const std::string& release) : major_(major), minor_(minor), release_(release), seq_field_count_(2), release_set_(true) {}
    version(int major, int minor, int revision) : major_(major), minor_(minor), revision_(revision), seq_field_count_(3) {}
    version(int major, int minor, int revision, const std::string& release) : major_(major), minor_(minor), revision_(revision), seq_field_count_(3), release_(release), release_set_(true) {}
    version(int major, int minor, int revision, int build) : major_(major), minor_(minor), revision_(revision), build_(build), seq_field_count_(4) {}
    version(int major, int minor, int revision, int build, const std::string& release) : major_(major), minor_(minor), revision_(revision), build_(build), release_(release), seq_field_count_(5), release_set_(true) {}

    version(const version& other)
    {
        major_ = other.major_;
        minor_ = other.minor_;
        revision_ = other.revision_;
        build_ = other.build_;
        release_ = other.release_;
        seq_field_count_ = other.seq_field_count_;
        release_set_ = other.release_set_;
    }

    version& operator=(const version& other)
    {
        major_ = other.major_;
        minor_ = other.minor_;
        revision_ = other.revision_;
        build_ = other.build_;
        release_ = other.release_;
        seq_field_count_ = other.seq_field_count_;
        release_set_ = other.release_set_;
        return *this;
    }

    version(version&& other)
    {
        major_ = other.major_;
        minor_ = other.minor_;
        revision_ = other.revision_;
        build_ = other.build_;
        release_ = std::move(other.release_);
        seq_field_count_ = other.seq_field_count_;
        release_set_ = other.release_set_;
    }

    version& operator=(version&& other)
    {
        major_ = other.major_;
        minor_ = other.minor_;
        revision_ = other.revision_;
        build_ = other.build_;
        release_ = std::move(other.release_);
        seq_field_count_ = other.seq_field_count_;
        release_set_ = other.release_set_;
        return *this;
    }

    ~version() {}

    void swap(version& other)
    {
        std::swap(major_, other.major_);
        std::swap(minor_, other.minor_);
        std::swap(revision_, other.revision_);
        std::swap(build_, other.build_);
        std::swap(release_, other.release_);
        std::swap(seq_field_count_, other.seq_field_count_);
        std::swap(release_set_, other.release_set_);
    }

    int major() const { return major_; }
    int minor() const { return minor_; }
    int revision() const { return revision_; }
    int build() const { return build_; }
    std::string release() const { return release_; }

    int fields() const
    {
        return (seq_field_count_ < 5 && release_set_) ? seq_field_count_ + 1 : seq_field_count_;
    }

    bool empty() const
    {
        return major_ == 0 &&
            minor_ == 0 &&
            revision_ == 0 &&
            build_ == 0 &&
            release_.length() == 0 &&
            seq_field_count_ == 2 &&
            release_set_ == false;
    }

    void clear()
    {
        major_ = {};
        minor_ = {};
        revision_ = {};
        build_ = {};
        release_ = {};
        seq_field_count_ = 2;
        release_set_ = false;
    }

    std::string to_string() const
    {
        return to_string(seq_field_count_);
    }

    std::string to_string(int field_count) const
    {
        return to_string(seq_field_count_, release_set_);
    }

    std::string to_string(int field_count, bool include_release) const
    {
        return to_string(field_count, include_release, "-");
    }

    std::string to_string(int field_count, bool include_release, const std::string& release_separator) const
    {
        return to_string(field_count, include_release, release_separator.c_str());
    }

    std::string to_string(int field_count, bool include_release, const char* release_separator) const
    {
        std::string str = std::to_string(major_) + "." + std::to_string(minor_);
        if (field_count >= 3)
            str += "." + std::to_string(revision_);
        if (field_count >= 4)
            str += "." + std::to_string(build_);
        if ((field_count >= 5 && release_.length() > 0) || include_release)
            str += release_separator + release_;
        return str;
    }

    bool operator==(const version& other) const { return compare(other) == 0; }
    bool operator!=(const version& other) const { return compare(other) == -1; }
    bool operator<(const version& other) const { return compare(other) < 0; }
    bool operator>(const version& other) const { return compare(other) > 0; }
    bool operator<=(const version& other) const { return compare(other) <= 0; }
    bool operator>=(const version& other) const { return compare(other) >= 0; }

    int compare(const version& other) const
    {
        if (major_ != other.major_)
        {
            if (major_ < other.major_)
                return -1;
            return 1;
        }

        if (minor_ != other.minor_)
        {
            if (minor_ < other.minor_)
                return -1;
            return 1;
        }

        if (revision_ != other.revision_)
        {
            if (revision_ < other.revision_)
                return -1;
            return 1;
        }

        if (build_ != other.build_)
        {
            if (build_ < other.build_)
                return -1;
            return 1;
        }

        if (release_set_ != other.release_set_ && release_ != other.release_)
        {
            return -1;
        }

        return 0;
    }

    version& operator++()
    {
        operator+=(1);
        return *this;
    }

    version operator++(int)
    {
        version v(*this);
        operator++();
        return v;
    }

    version& operator--()
    {
        operator-=(1);
        return *this;
    }

    version operator--(int)
    {
        version v(*this);
        operator--();
        return v;
    }

    version& operator+=(const version& other)
    {
        major_ += other.major_;
        minor_ += other.minor_;
        revision_ += other.revision_;
        build_ += other.build_;
        seq_field_count_ = std::max(seq_field_count_, other.seq_field_count_);
        return *this;
    }

    version& operator-=(const version& other)
    {
        major_ = std::max(major_ - other.major_, 0);
        minor_ = std::max(minor_ - other.minor_, 0);
        revision_ = std::max(revision_ - other.revision_, 0);
        build_ = std::max(build_ - other.build_, 0);
        return *this;
    }

    version& operator+=(int value)
    {
        if (seq_field_count_ == 2)
            minor_ += value;
        else if (seq_field_count_ == 3)
            revision_ += value;
        else if (seq_field_count_ >= 4)
            build_ += value;
        return *this;
    }

    version& operator-=(int value)
    {
        if (seq_field_count_ == 2)
            minor_ = std::max(minor_ - value, 0);
        else if (seq_field_count_ == 3)
            revision_ = std::max(revision_ - value, 0);
        else if (seq_field_count_ >= 4)
            build_ = std::max(build_ - value, 0);
        return *this;
    }

    version operator+(const version& other) const
    {
        version v(*this);
        v += other;
        return v;
    }

    version operator-(const version& other) const
    {
        version v(*this);
        v -= other;
        return v;
    }

    version operator+(int value) const
    {
        version v(*this);
        v += value;
        return v;
    }

    version operator-(int value) const
    {
        version v(*this);
        v -= value;
        return v;
    }

private:
    int major_ = 0;
    int minor_ = 0;
    int revision_ = 0;
    int build_ = 0;
    std::string release_;
    int seq_field_count_ = 2;
    bool release_set_ = false;
};

#endif