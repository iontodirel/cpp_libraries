#include "..\stopwatch.h"

#include <thread>
#include <chrono>
#include <cassert>

using namespace std::literals;

int main()
{
    /* api documentation */

    // create and start a stopwatch
    stopwatch sw = stopwatch::start_new();
    // checking if the stopwatch is running
    if (sw.running() == true) {}
    // stopping the stopwatch
    sw.stop();
    // returning the elapsed milliseconds
    long long elapsed_ms = sw.elapsed_milliseconds();
    // get a display friendly representation of the elapsed time ex: 1h34m10s
    std::string str = sw.to_string();

    /* tests */

    stopwatch sw2;
    assert(sw2.running() == false);
    sw2.start();
    assert(sw2.running() == true);
    // Sleep for 100 milliseconds
    std::this_thread::sleep_for(500ms);
    sw2.stop();
    assert(sw2.running() == false);
    assert(sw2.elapsed_nanoseconds() >= 100000000);
    assert(sw2.elapsed_microseconds() >= 100000);
    assert(sw2.elapsed_milliseconds() >= 100);
    assert(sw2.elapsed_seconds() >= 0.1);

    sw2.reset();
    assert(sw2.running() == false);
    assert(sw2.elapsed_nanoseconds() == 0);
    assert(sw2.elapsed_microseconds() == 0);
    assert(sw2.elapsed_milliseconds() == 0);
    assert(sw2.elapsed_seconds() == 0.0);
    assert(sw2.elapsed_minutes() == 0.0);
    assert(sw2.elapsed_hours() == 0.0);
    assert(sw2.elapsed_hours() == 0.0);

    sw2.restart();
    std::this_thread::sleep_for(200ms);

    stopwatch sw3(sw2);
    assert(sw3.elapsed_milliseconds() == sw2.elapsed_milliseconds());
    stopwatch sw4 = sw3;
    assert(sw4.elapsed_milliseconds() == sw3.elapsed_milliseconds());
    stopwatch sw5;
    sw5 = sw4;
    assert(sw5.elapsed_milliseconds() == sw4.elapsed_milliseconds());
    stopwatch sw6;
    sw6.swap(sw5);
    assert(sw6.elapsed_milliseconds() == sw4.elapsed_milliseconds());

    // create a stopwatch and set its elapsed value
    stopwatch sw7;
    sw7.elapsed(100ms);
    assert(sw7.elapsed_milliseconds() == 100);

    // create a stopwatch and start it in place
    stopwatch sw8(autostart);
    std::this_thread::sleep_for(200ms);
    assert(sw8.elapsed_milliseconds() >= 100);

    return 0;
}