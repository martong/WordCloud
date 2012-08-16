#include <boost/test/unit_test.hpp>
#include "../src/simple/LineBasedCounter.hpp"

BOOST_AUTO_TEST_SUITE( Simple_LineBasedCounterTest )

BOOST_AUTO_TEST_CASE( Basic )
{
	using namespace wc;
	using namespace wc::simple;
	CountMap cm;
	LineBasedCounter c;
	std::string test("apple banana");
	c(test, cm);

	BOOST_CHECK_EQUAL(cm.size(), 2);
	BOOST_CHECK_EQUAL(cm.left.at("apple").count, 1);
	BOOST_CHECK_EQUAL(cm.left.at("banana").count, 1);
}

BOOST_AUTO_TEST_SUITE_END()
