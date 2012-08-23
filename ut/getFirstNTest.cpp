#include <boost/test/unit_test.hpp>
#include "wc/getFirstN.hpp"
#include "../src/simple/FileParser.hpp"

BOOST_AUTO_TEST_SUITE( getFirstNTest )

BOOST_AUTO_TEST_CASE( Basic )
{
	using namespace wc;
	using namespace wc::simple;
	using namespace wc::detail;
	CountMap cm;
	FileParser parser;
	BOOST_CHECK_NO_THROW( parser.parse("./getFirstNTest.input", cm) );

	BOOST_CHECK_EQUAL(cm.size(), 8);
	BOOST_CHECK_EQUAL(cm.left.at("apple").count, 2);
	BOOST_CHECK_EQUAL(cm.left.at("banana").count, 2);

	auto range = getFirstN(cm, 3);

	for (const auto& e : range) {
		BOOST_MESSAGE(e.first << ' ' << e.second.count);
	}

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

BOOST_AUTO_TEST_SUITE_END()
