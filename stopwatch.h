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
	static stopwatch start_new() { return stopwatch(true); }

	stopwatch() : stopwatch(false) {}

	explicit stopwatch(bool start)
	{
		if (start)
		{
			this->start();
		}
	}

	stopwatch(const stopwatch& other)
	{
		if (this != &other)
		{
			start_ = other.start_;
			end_ = other.end_;
			running_ = other.running_;
		}
	}

	stopwatch& operator=(const stopwatch& other)
	{
		if (this != &other)
		{
			start_ = other.start_;
			end_ = other.end_;
			running_ = other.running_;
		}
		return *this;
	}

	~stopwatch()
	{
	}

	void swap(stopwatch& other)
	{
		std::swap(running_, other.running_);
		std::swap(start_, other.start_);
		std::swap(end_, other.end_);
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

	bool running() const
	{
		return running_;
	}

	long long elapsed_nanoseconds() const { return elapsed_ll<std::chrono::nanoseconds>(); }
	long long elapsed_microseconds() const { return elapsed_ll<std::chrono::microseconds>(); }
	long long elapsed_milliseconds() const { return elapsed_ll<std::chrono::milliseconds>(); }
	long long elapsed_seconds() const { return elapsed_ll<std::chrono::seconds>(); }
	long long elapsed_minutes() const { return elapsed_ll<std::chrono::minutes>(); }
	long long elapsed_hours() const { return elapsed_ll<std::chrono::hours>(); }

private:
	template<class D> long long elapsed_ll() const
	{
		std::chrono::high_resolution_clock::time_point end = end_;
		if (running_)
		{
			end = std::chrono::high_resolution_clock::now();
		}		
		return (long long) std::chrono::duration_cast<D>(end - start_).count();
	}

	std::chrono::high_resolution_clock::time_point start_;
	std::chrono::high_resolution_clock::time_point end_;
	bool running_ = false;
};

#endif