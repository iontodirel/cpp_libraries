#include "..\random_string.h"

#include <string>
#include <cstdio>

int main()
{
    std::string str = random_string(50);
    printf("%s", str.c_str());
}