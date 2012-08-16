#include <boost/test/unit_test.hpp>
#include "DirectoryRange.hpp"
#include <vector>
#include <boost/range/algorithm/find.hpp>
#include <algorithm>

BOOST_AUTO_TEST_SUITE( DirectoryRangeTest )

BOOST_AUTO_TEST_CASE( Basic )
{
	using namespace wc;
	auto range = makeDirectoryRange("./DirectoryRangeTest");

	std::vector<std::string> expectedResult {
			"./DirectoryRangeTest/3.h",
			"./DirectoryRangeTest/3.h",
			"./DirectoryRangeTest/4.c",
			"./DirectoryRangeTest/5.hpp",
			"./DirectoryRangeTest/6.cpp",
			"./DirectoryRangeTest/7.hh",
			"./DirectoryRangeTest/8.cc",
			"./DirectoryRangeTest/dir1/6.cpp",
			"./DirectoryRangeTest/dir1/5.hpp"
	};

	for (auto p : range) {
		BOOST_MESSAGE("Check whether the next file is in the expected result set, " << p);
		BOOST_CHECK(boost::find(expectedResult, p.string()) != expectedResult.end());
	}
}

BOOST_AUTO_TEST_SUITE_END()
