#include "..\guid.h"
#include <cassert>
#include <string>

int main()
{
	guid g = guid::create_new();
	g.empty();
	g.to_string();
	
	guid g2("{2AC3E955-939F-4756-8BC1-940BB7C882C3}");
	assert(g2.empty() == false);
	assert(g2 != g);
	assert(!(g2 == g));
	std::string s = g2.to_string();
	assert(s.compare("{2AC3E955-939F-4756-8BC1-940BB7C882C3}") == 0);
	assert(g2.to_string(guid_format::exclude_brackets).compare("2AC3E955-939F-4756-8BC1-940BB7C882C3") == 0);
}