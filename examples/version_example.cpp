#include "..\version.h"

#include <cassert>
#include <string>

int main()
{
    /* api documentation */

    // create a new version
    version ver(1, 0, 7, "rc2");
    // get the components of the version
    int major = ver.major();
    int minor = ver.minor();
    int rev = ver.revision();
    int build = ver.build();
    std::string release = ver.release();
    // get the number of set components
    int fields = ver.fields();
    // convert the version to string
    std::string str = ver.to_string();
    // clearing the version
    ver.clear();
    // construction from strings like 1.0.7-rc2
    ver = version(str);

    /* tests */

    version ver1(0, 0);
    version ver2(0, 1);
    version ver3(0, 1, 1);
    version ver4(1, 0);
    version ver5(1, 0, 0);
    version ver6(1, 0, 1);
    version ver7(1, 0, 3);
    version ver8(2, 0);
    version ver9(2, 1);
    version ver10(1, 0, "rtm");
    version ver11(1, 0, 3);
    version ver12(1, 0, 3);

    assert(ver1.compare(ver2) == -1);
    assert(ver2.compare(ver1) == 1);
    assert(ver2.compare(ver3) == -1);
    assert(ver4.compare(ver5) == 0);
    assert(ver5.compare(ver4) == 0);
    assert(ver1 < ver2);
    assert(ver3 > ver2);
    assert(ver6 > ver5);
    assert(ver4 != ver10);
    assert(ver4 < ver10);

    version ver13;
    assert(version::try_parse("10.1.45243-rc", ver13));
    assert(ver13.major() == 10);
    assert(ver13.minor() == 1);
    assert(ver13.revision() == 45243);
    assert(ver13.build() == 0);
    assert(ver13.release() == "rc");
    assert(ver13.fields() == 4);

    version ver14;
    assert(version::try_parse("10.1.45243-", ver14));
    ver14.clear();
    assert(ver14.empty());
    assert(version::try_parse("", ver14) == false);
    assert(ver14.empty());
    ver14.clear();
    assert(version::try_parse("1", ver14));
    assert(!ver14.empty());
    ver14.clear();
    assert(version::try_parse("1..", ver14) == false);
    assert(ver14.empty());
    ver14.clear();
    assert(version::try_parse("1.s.", ver14) == false);
    assert(ver14.empty());

    version ver15("1.0.0");
    version ver16("1.0.0-rtm");

    try
    {
        version ver17("1..");
        assert(false);
    }
    catch (version_parse_exception)
    {
    }

    version ver18(1, 0, 1);
    version ver19 = ++ver18;
    assert(ver19.major() == 1);
    assert(ver19.minor() == 0);
    assert(ver19.revision() == 2);
    ver18++;
    version ver20 = ver18 + version(0, 2, 5);
    assert(ver20.major() == 1);
    assert(ver20.minor() == 2);
    assert(ver20.revision() == 8);
    ver20--;
    assert(ver20.revision() == 7);
    version ver21 = ver20 - 10;
    assert(ver21.revision() == 0);

    version ver22(1, 2, " (rtm)");
    std::string str2 = ver22.to_string(2, true, "");
    assert(str2.compare("1.2 (rtm)") == 0);

    version ver23(1, 2, ".3.4");
    std::string str3 = ver23.to_string(2, true, "");
    assert(str3.compare("1.2.3.4") == 0);

    version ver24(str3);
}