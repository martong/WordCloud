#include <boost/test/unit_test.hpp>
#include <boost/bimap.hpp>
#include <boost/bimap/multiset_of.hpp>

#include <more/adaptors/projected.hpp>
#include <boost/iterator/iterator_adaptor.hpp>

#include <type_traits>

BOOST_AUTO_TEST_SUITE( projectedTest )

using namespace boost;
using namespace more::adaptors;

typedef bimap<std::string, boost::bimaps::multiset_of<int,std::greater<int> > > BmType;

struct ProjectFuncL2R {
	typedef BmType::right_const_iterator result_type;
	ProjectFuncL2R(const BmType& bm) : bm(bm) {}
	result_type operator()(const BmType::left_const_iterator& it) const{
		return bm.project_right(it);
	}
	const BmType& bm;
};

struct ProjectFuncR2L {
	typedef BmType::left_const_iterator result_type;
	ProjectFuncR2L(const BmType& bm) : bm(bm) {}
	result_type operator()(const BmType::right_const_iterator& it) const{
		return bm.project_left(it);
	}
	const BmType& bm;
};

template <class InputRange, class UnaryFunction>
struct MyResult
{
	typedef typename boost::result_of<
		const UnaryFunction(typename boost::range_iterator<InputRange>::type)>::type type;
//	typedef typename boost::range_iterator<InputRange>::type ParamType;
//	static_assert( std::is_const<const ParamType>::value, "isconst" );
//	typedef typename std::result_of<
//		const UnaryFunction(const ParamType)>::type type;

};

static_assert( std::is_same<MyResult<BmType, ProjectFuncL2R>::type,
		BmType::right_const_iterator>::value , "vaze" );

struct Fixture
{
protected:

	BmType bm;

public:

	Fixture()
	{
		bm.insert( BmType::value_type("Mary" ,12) );
		bm.insert( BmType::value_type("John" ,34) );
		bm.insert( BmType::value_type("Peter",24) );
	}
};

BOOST_FIXTURE_TEST_CASE( ProjectIterator, Fixture )
{

	// Find the name of the next younger person after Peter
	BmType::left_const_iterator name_iter = bm.left.find("Peter");
	BmType::right_const_iterator years_iter = bm.project_right(name_iter);
	BOOST_CHECK_EQUAL(years_iter->second, "Peter");
	//++years_iter;
	//std::cout << "The next younger person after Peter is " << years_iter->second;

	auto val0 = ProjectFuncL2R(bm)(name_iter);
	BOOST_CHECK_EQUAL(val0->second, "Peter");

	using more::range_detail::project_iterator;
	project_iterator<decltype(name_iter), decltype(years_iter), ProjectFuncL2R>
		it{name_iter, ProjectFuncL2R(bm)};

	auto val1 = *it;
	BOOST_CHECK_EQUAL(val1.second, "Peter");

	BOOST_CHECK(*it == *years_iter);

	--it;
	BOOST_CHECK_EQUAL(it->second, "Mary");

}

BOOST_FIXTURE_TEST_CASE( ProjectRangeL2R, Fixture )
{
	const auto projectedRange = project(bm.left, ProjectFuncL2R(bm));
	int i = 1;
	// go over by the left view, but get the elements in a right view format
	for (const auto& e : projectedRange) {
		BmType::right_const_iterator rightIt;
		if (i == 1) {
			rightIt = bm.right.find(34); // John
		} else if (i == 2) {
			rightIt = bm.right.find(12); // Mary
		} else if (i == 3) {
			rightIt = bm.right.find(24); // Peter
		}
		BOOST_CHECK(*rightIt == e);
		++i;
	}
}

BOOST_FIXTURE_TEST_CASE( ProjectRangeR2L, Fixture )
{
	const auto projectedRange = project(bm.right, ProjectFuncR2L(bm));
	int i = 1;
	// go over by the right view, but get the elements in a left view format
	for (const auto& e : projectedRange) {
		BmType::left_const_iterator leftIt;
		if (i == 1) {
			leftIt = bm.left.find("John"); // 34
		} else if (i == 2) {
			leftIt = bm.left.find("Peter"); // 24
		} else if (i == 3) {
			leftIt = bm.left.find("Mary"); // 12
		}
		BOOST_CHECK(*leftIt == e);
		++i;
	}
}

BOOST_FIXTURE_TEST_CASE( ProjectRangeL2ROperator, Fixture )
{
	const auto projectedRange = bm.left | projected(ProjectFuncL2R(bm));
	int i = 1;
	// go over by the left view, but get the elements in a right view format
	for (const auto& e : projectedRange) {
		BmType::right_const_iterator rightIt;
		if (i == 1) {
			rightIt = bm.right.find(34); // John
		} else if (i == 2) {
			rightIt = bm.right.find(12); // Mary
		} else if (i == 3) {
			rightIt = bm.right.find(24); // Peter
		}
		BOOST_CHECK(*rightIt == e);
		++i;
	}
}

BOOST_AUTO_TEST_SUITE_END()
