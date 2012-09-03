#include <vector>
#include <algorithm>

#include <boost/test/unit_test.hpp>
#include <boost/range/algorithm/find.hpp>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

#include "DirectoryRange.hpp"
#include "wc/Options.hpp"

BOOST_AUTO_TEST_SUITE( DirectoryRangeTest )

BOOST_AUTO_TEST_CASE( Basic )
{
	using namespace wc;

	std::vector<std::string> expectedResult {
			"./testDirs/DirectoryRangeTest/3.h",
			"./testDirs/DirectoryRangeTest/4.c",
			"./testDirs/DirectoryRangeTest/5.hpp",
			"./testDirs/DirectoryRangeTest/6.cpp",
			"./testDirs/DirectoryRangeTest/7.hh",
			"./testDirs/DirectoryRangeTest/8.cc",
			"./testDirs/DirectoryRangeTest/dir1/6.cpp",
			"./testDirs/DirectoryRangeTest/dir1/5.hpp"
	};

	Options op;
	op.path = "./testDirs/DirectoryRangeTest";

	auto range = makeDirectoryRange(op);
	auto rangeSize = std::distance(range.begin(), range.end());
	BOOST_CHECK_EQUAL(rangeSize, expectedResult.size());

	// recursive_directory_iterator is a SinglePass iterator.
	// The previous operator++ in std::distance
	// ruined our range. That is why a new range is needed to be created.
	auto range2 = makeDirectoryRange(op);
	for (const auto& p : range2) {
		BOOST_MESSAGE("Check whether the next file is in the expected result set, " << p);
		BOOST_CHECK(boost::find(expectedResult, p) != expectedResult.end());
	}
}

BOOST_AUTO_TEST_CASE( JustCppButNotFromDir1 )
{
	using namespace wc;

	std::vector<std::string> expectedResult {
			"./testDirs/DirectoryRangeTest/6.cpp"
			//,"./testDirs/DirectoryRangeTest/dir1/6.cpp"
	};

	Options op;
	op.path = "./testDirs/DirectoryRangeTest";
	op.pathIncludeRegexes.clear();
	op.pathIncludeRegexes.emplace_back(".*\\.cpp");
	op.pathExcludeRegexes.emplace_back(".*/dir1/.*");

	auto range = makeDirectoryRange(op);
	auto rangeSize = std::distance(range.begin(), range.end());
	BOOST_CHECK_EQUAL(rangeSize, expectedResult.size());

	auto range2 = makeDirectoryRange(op);
	for (const auto& p : range2) {
		BOOST_MESSAGE("Check whether the next file is in the expected result set, " << p);
		BOOST_CHECK(boost::find(expectedResult, p) != expectedResult.end());
	}
}


BOOST_AUTO_TEST_SUITE_END()
