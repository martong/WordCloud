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

	std::size_t rangeSize = std::distance(range.begin(), range.end());
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

BOOST_FIXTURE_TEST_CASE( RegexMatch, Fixture )
{
	op.regex = "ban.*";
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

	std::size_t rangeSize = std::distance(range.begin(), range.end());
	BOOST_CHECK_EQUAL(rangeSize, 1);
}

BOOST_FIXTURE_TEST_CASE( InverseRegexMatch, Fixture )
{
	op.regex = "(ban.*)|(\\w{1})|(.*f.*)";
	op.inverseMatch = true;
	auto range = m.getWordCount();
	auto it =
			boost::range::find_if(range,
					[](const WordCountItem& p){ return p.first == "apple"; });
	BOOST_CHECK(it != range.end());

	auto it2 =
			boost::range::find_if(range,
					[](const WordCountItem& p){ return p.first == "banana"; });
	BOOST_CHECK(it2 == range.end());

	std::size_t rangeSize = std::distance(range.begin(), range.end());
	BOOST_CHECK_EQUAL(rangeSize, 1);
}

BOOST_AUTO_TEST_SUITE_END()
