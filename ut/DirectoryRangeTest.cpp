#include <boost/test/unit_test.hpp>
#include "DirectoryRange.hpp"
#include <vector>
#include <boost/range/algorithm/find.hpp>
#include <algorithm>

BOOST_AUTO_TEST_SUITE( DirectoryRangeTest )

BOOST_AUTO_TEST_CASE( Basic )
{
	using namespace wc;
	auto range = makeDirectoryRange("./testDirs/DirectoryRangeTest");

	std::vector<std::string> expectedResult {
			"./testDirs/DirectoryRangeTest/3.h",
			"./testDirs/DirectoryRangeTest/3.h",
			"./testDirs/DirectoryRangeTest/4.c",
			"./testDirs/DirectoryRangeTest/5.hpp",
			"./testDirs/DirectoryRangeTest/6.cpp",
			"./testDirs/DirectoryRangeTest/7.hh",
			"./testDirs/DirectoryRangeTest/8.cc",
			"./testDirs/DirectoryRangeTest/dir1/6.cpp",
			"./testDirs/DirectoryRangeTest/dir1/5.hpp"
	};

	for (auto p : range) {
		BOOST_MESSAGE("Check whether the next file is in the expected result set, " << p);
		BOOST_CHECK(boost::find(expectedResult, p.string()) != expectedResult.end());
	}
}

BOOST_AUTO_TEST_SUITE_END()
