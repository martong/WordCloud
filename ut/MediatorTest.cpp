#include <boost/test/unit_test.hpp>
#include <boost/range/algorithm.hpp>
#include "wc/Mediator.hpp"

BOOST_AUTO_TEST_SUITE( MediatorTest )

using namespace wc;

namespace tc_detail {
struct OptionsInit {
	OptionsInit(Options& op) {
		op.path = "./testDirs/MediatorTest";
	}
};
Options op;
OptionsInit opinit(op);
} // tc_detail

struct Fixture {
	Fixture() : op(tc_detail::op), m(op)
	{
		m();
	}
protected:
	Options op;
	Mediator m;
};

BOOST_FIXTURE_TEST_CASE( GetFirstN, Fixture )
{
	op.firstN = 3;
	auto range = m.getWordCount();

	for (const auto& e : range) {
		BOOST_MESSAGE(e.first << ' ' << e.second.count);
	}

	auto rangeSize = std::distance(range.begin(), range.end());
	BOOST_CHECK_EQUAL(rangeSize, 3);

	int i = 1;
	for (const auto& e : range) {
		if (i==1) {
			BOOST_CHECK_EQUAL(e.first, "asdf");
			BOOST_CHECK_EQUAL(e.second.count, 6);
		} else if (i==2) {
			BOOST_CHECK_EQUAL(e.first, "ff");
			BOOST_CHECK_EQUAL(e.second.count, 5);
		} else if (i==3) {
			BOOST_CHECK_EQUAL(e.first, "f");
			BOOST_CHECK_EQUAL(e.second.count, 4);
		}
	++i;
	}
}

BOOST_FIXTURE_TEST_CASE( DefaultRegex, Fixture )
{
	auto range = m.getWordCount();
	auto it =
			boost::range::find_if(range,
					[](const WordCountItem& p){ return p.first == "apple"; });
	BOOST_CHECK(it != range.end());
	BOOST_CHECK_EQUAL(it->second.count, 2);
}

BOOST_FIXTURE_TEST_CASE( IncludeRegexMatch, Fixture )
{
	op.includeRegexes.emplace_back("ban.*");
	auto range = m.getWordCount();
	auto it =
			boost::range::find_if(range,
					[](const WordCountItem& p){ return p.first == "apple"; });
	BOOST_CHECK(it == range.end());

	auto it2 =
			boost::range::find_if(range,
					[](const WordCountItem& p){ return p.first == "banana"; });
	BOOST_CHECK(it2 != range.end());
	BOOST_CHECK_EQUAL(it2->second.count, 2);

	auto rangeSize = std::distance(range.begin(), range.end());
	BOOST_CHECK_EQUAL(rangeSize, 1);
}

BOOST_FIXTURE_TEST_CASE( ExcludeRegexMatch, Fixture )
{
	op.excludeRegexes.emplace_back("(ban.*)|(\\w{1})|(.*f.*)");
	auto range = m.getWordCount();
	auto it =
			boost::range::find_if(range,
					[](const WordCountItem& p){ return p.first == "apple"; });
	BOOST_CHECK(it != range.end());

	auto it2 =
			boost::range::find_if(range,
					[](const WordCountItem& p){ return p.first == "banana"; });
	BOOST_CHECK(it2 == range.end());

	auto rangeSize = std::distance(range.begin(), range.end());
	BOOST_CHECK_EQUAL(rangeSize, 1);
}

BOOST_FIXTURE_TEST_CASE( ExcludeAndIncludeRegexMatch, Fixture )
{
	op.excludeRegexes.emplace_back("ban.*");
	op.includeRegexes.emplace_back("\\w{1}");
	auto range = m.getWordCount();
	auto it =
			boost::range::find_if(range,
					[](const WordCountItem& p){ return p.first == "apple"; });
	BOOST_CHECK(it == range.end());

	auto it2 =
			boost::range::find_if(range,
					[](const WordCountItem& p){ return p.first == "banana"; });
	BOOST_CHECK(it2 == range.end());

	auto it3 =
			boost::range::find_if(range,
					[](const WordCountItem& p){ return p.first == "f"; });
	BOOST_CHECK(it3 != range.end());

	auto rangeSize = std::distance(range.begin(), range.end());
	BOOST_CHECK_EQUAL(rangeSize, 4);
}

BOOST_FIXTURE_TEST_CASE( MultipleIncludeRegexMatch, Fixture )
{
	op.includeRegexes.emplace_back("ban.*");
	op.includeRegexes.emplace_back("app.*");
	auto range = m.getWordCount();
	auto rangeSize = std::distance(range.begin(), range.end());
	BOOST_CHECK_EQUAL(rangeSize, 2);
}

BOOST_FIXTURE_TEST_CASE( MultipleExcludeRegexMatch, Fixture )
{
	op.excludeRegexes.emplace_back("ban.*");
	op.excludeRegexes.emplace_back("app.*");
	op.excludeRegexes.emplace_back("\\w{1}");
	auto range = m.getWordCount();
	auto rangeSize = std::distance(range.begin(), range.end());
	BOOST_CHECK_EQUAL(rangeSize, 2);

	auto it =
			boost::range::find_if(range,
					[](const WordCountItem& p){ return p.first == "ff"; });
	BOOST_CHECK(it != range.end());
	auto it2 =
			boost::range::find_if(range,
					[](const WordCountItem& p){ return p.first == "asdf"; });
	BOOST_CHECK(it2 != range.end());

}

BOOST_FIXTURE_TEST_CASE( MultipleExcludeAndIncludeRegexMatch, Fixture )
{
	{
		op.includeRegexes.emplace_back("ban.*");
		op.includeRegexes.emplace_back("app.*");
		op.excludeRegexes.emplace_back("\\w{2}");
		op.excludeRegexes.emplace_back("\\w{1}");
		auto range = m.getWordCount();

		auto rangeSize = std::distance(range.begin(), range.end());
		BOOST_CHECK_EQUAL(rangeSize, 2);
	}

	{
		op.includeRegexes.emplace_back("ban.*");
		op.includeRegexes.emplace_back("app.*");
		op.excludeRegexes.emplace_back("app.*");
		op.excludeRegexes.emplace_back("\\w{2}");
		op.excludeRegexes.emplace_back("\\w{1}");
		auto range = m.getWordCount();

		auto rangeSize = std::distance(range.begin(), range.end());
		BOOST_CHECK_EQUAL(rangeSize, 1);
	}
}

BOOST_AUTO_TEST_SUITE_END()
