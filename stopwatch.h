// sai - General purpose self-contained C++ libraries.
//
// stopwatch.h
// Utility class that can be used to measure time intervals.
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

#ifndef SAI_CORE_STOPWATCH_H
#define SAI_CORE_STOPWATCH_H

#include <chrono>

class stopwatch
{
public:
    static stopwatch start_new()
    {
        stopwatch sw;
        sw.start();
        return sw;
    }

    void swap(stopwatch& other)
    {
        std::swap(*this, other);
    }

    void start()
    {
        if (running_)
            return;
        running_ = true;
        start_ = std::chrono::high_resolution_clock::now();
        end_ = {};
    }

    void stop()
    {
        if (!running_)
            return;
        running_ = false;
        end_ = std::chrono::high_resolution_clock::now();
    }

    void reset()
    {
        if (running_)
            start_ = std::chrono::high_resolution_clock::now();
        else
            start_ = {};
        end_ = {};
    }

    void restart()
    {
        running_ = false;
        reset();
        start();
    }

    bool running() const { return running_; }

    template <class Duration>
    Duration elapsed() const
    {
        std::chrono::high_resolution_clock::time_point end = end_;
        if (running_)
        {
            end = std::chrono::high_resolution_clock::now();
        }
        return std::chrono::duration_cast<Duration>(end - start_);
    }

    long long elapsed_nanoseconds() const { return elapsed<std::chrono::duration<long long, std::nano>>().count(); }
    long long elapsed_microseconds() const { return elapsed<std::chrono::duration<long long, std::micro>>().count(); }
    long long elapsed_milliseconds() const { return elapsed<std::chrono::duration<long long, std::milli>>().count(); }
    double elapsed_seconds() const { return elapsed<std::chrono::duration<double>>().count(); }
    double elapsed_minutes() const { return elapsed<std::chrono::duration<double, std::ratio<60>>>().count(); }
    double elapsed_hours() const { return elapsed<std::chrono::duration<double, std::ratio<3600>>>().count(); }
    double elapsed_days() const { return elapsed<std::chrono::duration<double, std::ratio<86400>>>().count(); }

private:
    std::chrono::high_resolution_clock::time_point start_;
    std::chrono::high_resolution_clock::time_point end_;
    bool running_ = false;
};

#endif