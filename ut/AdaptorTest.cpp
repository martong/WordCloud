#include <set>
#include <boost/test/unit_test.hpp>
#include <boost/range/numeric.hpp>
#include <more/adaptors/first_nd.hpp>

BOOST_AUTO_TEST_SUITE( AdaptorTest )

using namespace more::adaptors;

typedef std::set<int> IntSet;
typedef std::vector<int> IntV;

BOOST_AUTO_TEST_CASE( IteratorBasic )
{
	IntSet set1, set2, set3 = {1,2,3}, set4 = {1,2,3};
	BOOST_CHECK(first_n_iterator<IntSet::iterator>{set1.begin()} !=
			first_n_iterator<IntSet::iterator>{set2.begin()});
	BOOST_CHECK(first_n_iterator<IntSet::iterator>{set3.begin()} !=
			first_n_iterator<IntSet::iterator>{set4.begin()});
	BOOST_CHECK(first_n_iterator<IntSet::iterator>(set3.begin(),1) !=
			first_n_iterator<IntSet::iterator>(set4.begin(),1));
}

BOOST_AUTO_TEST_CASE( Iterator )
{
	IntSet set = { 1,2,3,4,5,6,7,8 };
	first_n_iterator<decltype(set.begin())> b{set.begin()};
	first_n_iterator<decltype(set.begin())> e{set.begin(), 3};
	auto range = boost::make_iterator_range(b, e);
	int result = boost::accumulate(range, 0);
	BOOST_CHECK_EQUAL(result, 1+2+3);
}

BOOST_AUTO_TEST_CASE( ConstRange )
{
	const IntSet set = { 1,2,3,4,5,6,7,8 };
	auto range = first_n(set, 3);
	int result = boost::accumulate(range, 0);
	BOOST_CHECK_EQUAL(result, 1+2+3);
}

BOOST_AUTO_TEST_CASE( MutableRange )
{
	IntV vec = { 1,2,3,4,5,6,7,8 };
	auto range = first_n(vec, 3);
	for (auto& v: vec) {
		v*=2;
	}
	int result = boost::accumulate(range, 0);
	BOOST_CHECK_EQUAL(result, 2+4+6);
}

BOOST_AUTO_TEST_CASE( ConstRangeWithOperator )
{
	const IntSet set = { 1,2,3,4,5,6,7,8 };
	auto range = set | first_nd(3);
	int result = boost::accumulate(range, 0);
	BOOST_CHECK_EQUAL(result, 1+2+3);
}

BOOST_AUTO_TEST_CASE( MutableRangeWithOperator )
{
	typedef std::vector<int> IntV;
	IntV vec = { 1,2,3,4,5,6,7,8 };
	auto range = vec | first_nd(3);
	for (auto& v: vec) {
		v*=2;
	}
	int result = boost::accumulate(range, 0);
	BOOST_CHECK_EQUAL(result, 2+4+6);
}

BOOST_AUTO_TEST_SUITE_END()
