#include <boost/test/unit_test.hpp>
#include "../src/simple/FileParser.hpp"

BOOST_AUTO_TEST_SUITE( Simple_FileParserTest )

BOOST_AUTO_TEST_CASE( Basic )
{
	using namespace wc;
	using namespace wc::simple;
	CountMap cm;
	FileParser parser;
	BOOST_CHECK_NO_THROW( parser.parse("./simple/FileParserTest.input", cm) );

	BOOST_CHECK_EQUAL(cm.size(), 2);
	BOOST_CHECK_EQUAL(cm.left.at("apple").count, 2);
	BOOST_CHECK_EQUAL(cm.left.at("banana").count, 2);
}

BOOST_AUTO_TEST_SUITE_END()
