#include <boost/test/unit_test.hpp>
#include <boost/range/adaptor/sliced.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/assign.hpp>
#include <algorithm>
#include <iostream>
#include <vector>
#include <sstream>

BOOST_AUTO_TEST_SUITE( SliceTest )

BOOST_AUTO_TEST_CASE( Basic )
{
    using namespace boost::adaptors;
    using namespace boost::assign;

    std::vector<int> input;
    input += 1,2,3,4,5,6,7,8,9;

    std::stringstream s;
    boost::copy(
        input | sliced(2, 15),
        std::ostream_iterator<int>(s, ","));

    BOOST_MESSAGE(s.str());

}

BOOST_AUTO_TEST_SUITE_END()
