#include <boost/test/unit_test.hpp>

#include "wc/detail/FilterFirstNWhile.hpp"

BOOST_AUTO_TEST_SUITE( FilterFirstNWhileTest )

struct Predicate {
	typedef int value_type;
	bool operator()(value_type) { return true; }
};

BOOST_AUTO_TEST_CASE( Zero )
{
	using namespace wc::detail;
	auto obj = makeFilterFirstNWhile(Predicate(),0);
	BOOST_CHECK_EQUAL(obj(1), false);
}

BOOST_AUTO_TEST_CASE( One )
{
	using namespace wc::detail;
	auto obj = makeFilterFirstNWhile(Predicate(),1);
	BOOST_CHECK_EQUAL(obj(1), true);
	BOOST_CHECK_EQUAL(obj(1), false);
}

BOOST_AUTO_TEST_SUITE_END()
