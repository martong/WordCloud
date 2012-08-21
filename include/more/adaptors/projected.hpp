#ifndef MORE_ADAPTORS_FIRST_N_HPP_
#define MORE_ADAPTORS_FIRST_N_HPP_

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/range/adaptor/argument_fwd.hpp>

namespace more {

namespace range_detail {

template <class BaseIterator, class ProjectedIterator, class UnaryFunction>
class project_iterator :
	public boost::iterator_adaptor<
		project_iterator<BaseIterator, ProjectedIterator, UnaryFunction>,
		BaseIterator,
		typename ProjectedIterator::value_type,
		boost::use_default,
		typename ProjectedIterator::reference
	>
{
	typedef typename boost::iterator_adaptor<
			project_iterator<BaseIterator, ProjectedIterator, UnaryFunction>,
				BaseIterator,
				typename ProjectedIterator::value_type,
				boost::use_default,
				typename ProjectedIterator::reference
			> super_t;
public:
	explicit project_iterator(const BaseIterator& it, UnaryFunction f)
			: project_iterator::iterator_adaptor_{it}, f{f} {}
private:
	friend class boost::iterator_core_access;

    typename super_t::reference dereference() const
    {
    	projectedIt = f(this->base());
    	return *projectedIt;
    }

	UnaryFunction f;
	mutable ProjectedIterator projectedIt;
};

template <class InputRange, class UnaryFunction>
struct ProjectFuncResult
{
	typedef typename boost::result_of<
		const UnaryFunction(typename boost::range_iterator<InputRange>::type)>::type type;
//	typedef typename std::result_of<
//		const UnaryFunction(typename boost::range_iterator<InputRange>::type)>::type type;

};

template<class InputRange, class UnaryFunction>
class projected_range
	: public
	boost::iterator_range<
		project_iterator <
			typename boost::range_iterator<InputRange>::type,
			typename ProjectFuncResult<InputRange, UnaryFunction>::type,
			UnaryFunction
		>
	>
{
    typedef
    boost::iterator_range<
    	project_iterator <
    		typename boost::range_iterator<InputRange>::type,
    		typename ProjectFuncResult<InputRange, UnaryFunction>::type,
    		UnaryFunction
    	>
    >
    base_t;
public:
    template<typename Rng, typename F>
    projected_range(Rng& r, F f)
        : base_t(boost::make_iterator_range(
//        		project_iterator<decltype(r.begin()), decltype(f(r.begin())), F>{r.begin(),f},
//        		project_iterator<decltype(r.begin()), decltype(f(r.begin())), F>{r.end(), f}))
        		project_iterator <
        			typename boost::range_iterator<InputRange>::type,
        			typename ProjectFuncResult<InputRange, UnaryFunction>::type,
        			F
        		>{r.begin(),f},
        		project_iterator <
        			typename boost::range_iterator<InputRange>::type,
        			typename ProjectFuncResult<InputRange, UnaryFunction>::type,
        			F
        		>{r.end(),f}
        		))
    {
    }
};

// The problem with this is that we need to spedify the template arguments of projected.
// Like this: const auto projectedRange = bm.left | projected<ProjectFuncL2R>(ProjectFuncL2R(bm));
//template <class UnaryFunction>
//struct projected {
//	projected(UnaryFunction f) : f(f) {}
//	UnaryFunction f;
//};
//
//template< class InputRange, class UnaryFunction >
//inline projected_range<InputRange, UnaryFunction>
//operator|(InputRange& r, const projected<UnaryFunction>& f)
//{
//    return projected_range<InputRange, UnaryFunction>(r, f.f);
//}
//
//template< class InputRange, class UnaryFunction >
//inline projected_range<const InputRange, UnaryFunction>
//operator|(const InputRange& r, const projected<UnaryFunction>& f)
//{
//    return projected_range<const InputRange, UnaryFunction>(r, f.f);
//}

template< class T >
struct project_holder : boost::range_detail::holder<T>
{
	project_holder( T r ) : boost::range_detail::holder<T>(r)
	{ }
};

template< class InputRange, class UnaryFunction >
inline projected_range<InputRange,UnaryFunction>
operator|( InputRange& r,
		   const project_holder<UnaryFunction>& f )
{
	return projected_range<InputRange,UnaryFunction>( r, f.val );
}

template< class InputRange, class UnaryFunction >
inline projected_range<const InputRange, UnaryFunction>
operator|( const InputRange& r,
		   const project_holder<UnaryFunction>& f )
{
   return projected_range<const InputRange, UnaryFunction>( r, f.val );
}

} // namespace range_detail

using range_detail::projected_range;

namespace adaptors {

namespace
{
    const boost::range_detail::forwarder<range_detail::project_holder>
            projected =
              boost::range_detail::forwarder<range_detail::project_holder>();
}

template <class InputRange, class UnaryFunction>
projected_range<InputRange, UnaryFunction>
project(InputRange& rng, UnaryFunction fn)
{
	return projected_range<InputRange, UnaryFunction>(rng, fn);
}

template <class InputRange, class UnaryFunction>
projected_range<const InputRange, UnaryFunction>
project(const InputRange& rng, UnaryFunction fn)
{
	return projected_range<const InputRange, UnaryFunction>(rng, fn);
}


} // namespace adaptors

} // namespace more


#endif /* MORE_ADAPTORS_FIRST_N_HPP_ */
