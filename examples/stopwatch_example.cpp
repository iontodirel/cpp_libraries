#include "..\stopwatch.h"

#include <thread>
#include <chrono>
#include <cassert>

int main()
{
    stopwatch sw = stopwatch::start_new();
    /* code to profile */
    if (sw.running() == true) {}
    sw.stop();
    sw.reset();
    sw.restart();
    sw.elapsed_milliseconds();

    stopwatch sw2;
    assert(sw2.running() == false);
    sw2.start();
    assert(sw2.running() == true);
    // Sleep for 100 milliseconds
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    sw2.stop();
    assert(sw2.running() == false);
    assert(sw2.elapsed_nanoseconds() >= 100000000);
    assert(sw2.elapsed_microseconds() >= 100000);
    assert(sw2.elapsed_milliseconds() >= 100);
    assert(sw2.elapsed_seconds() >= 100);
    assert(sw2.elapsed_minutes() >= 100);
    assert(sw2.elapsed_hours() >= 100);

    sw2.reset();
    assert(sw2.running() == false);
    assert(sw2.elapsed_nanoseconds() == 0);
    assert(sw2.elapsed_microseconds() == 0);
    assert(sw2.elapsed_milliseconds() == 0);
    assert(sw2.elapsed_seconds() == 0);
    assert(sw2.elapsed_minutes() == 0);
    assert(sw2.elapsed_hours() == 0);

    sw2.restart();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

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

    return 0;
}