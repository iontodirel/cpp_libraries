#include "..\guid.h"
#include <cassert>
#include <string>

int main()
{
    /* api documentation */

    // create a guid using the static guid::create_new function
    guid g = guid::create_new();
    // check if empty
    bool empty = g.empty();
    // convert the guid to a string like xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx
    std::string s = g.to_string('a');

    // Create a guid using guid::create member function
    guid g2;
    g2.create();

    /* tests */

    guid g3("2AC3E955-939F-4756-8BC1-940BB7C882C3");
    assert(g3.empty() == false);
    assert(g3 != g);
    assert(!(g3 == g));
    std::string s2 = g3.to_string();
    assert(s2.compare("{2AC3E955-939F-4756-8BC1-940BB7C882C3}") == 0);
    assert(g3.to_string(guid_format::uppercase_no_brackets).compare("2AC3E955-939F-4756-8BC1-940BB7C882C3") == 0);

    guid g4(g3);
    assert(g4 == g3);
    guid g5 = g4;
    assert(g5 == g4);
    guid g6;
    g6 = g5;
    assert(g6 == g5);
    g6.swap(g);
    assert(g6 != g5);
    assert(g == g3);

    guid g7 = guid::create_new();
    assert(g7.empty() == false);
    guid g8;
    assert(g8.empty());
    g8.create();
    assert(g8.empty() == false);
    guid g9(g8);
    assert(g9 == g8);
    g9.create();
    assert(g9 == g8);

    guid g10("2AC3E955-939F-4756-8BC1-940BB7C882C3");
    assert(g10.empty() == false);
}