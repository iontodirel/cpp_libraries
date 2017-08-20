#include "..\version.h"

#include <cassert>
#include <string>

int main()
{
	version ver(1, 0, 7, "rc2");
	int major = ver.major();
	int minor = ver.minor();
	int rev = ver.revision();
	int build = ver.build();
	std::string release = ver.release();
	/* number of set fields */
	int fields = ver.fields();
	/* 1.0.7-rc2 */
	std::string str = ver.to_string();
	/* clearing all the fields */
	ver.clear();
	/* construction from strings like 1.0.7-rc2 */
	ver = version(str);

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

	try
	{
		version ver16("1..");
		assert(false);
	}
	catch (version_parse_exception)
	{
	}
}