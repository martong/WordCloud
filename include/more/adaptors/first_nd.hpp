#ifndef MORE_ADAPTORS_FIRST_N_HPP_
#define MORE_ADAPTORS_FIRST_N_HPP_

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/range/iterator_range.hpp>

namespace more {
namespace adaptors {

template <class Iterator>
class first_n_iterator : public boost::iterator_adaptor<first_n_iterator<Iterator>,	Iterator>
{
public:
	explicit first_n_iterator(Iterator it)
			: first_n_iterator::iterator_adaptor_{it}, initial{it} {}
	explicit first_n_iterator(Iterator it, std::size_t n)
			: first_n_iterator::iterator_adaptor_{it}, initial{it}, count{n} {}
private:
	friend class boost::iterator_core_access;
	void increment() { ++(this->base_reference()); ++count; }
	bool equal(first_n_iterator const& other) const
	{
		return this->initial == other.initial && this->count == other.count;
	}

	Iterator initial;
	std::size_t count = 0;
};

struct first_nd {
	first_nd(std::size_t n) : n(n) {}
	std::size_t n;
};

template<class ForwardRange>
class first_nd_range
	: public boost::iterator_range< first_n_iterator <
	  	  typename boost::range_iterator<ForwardRange>::type> >
{
    typedef boost::iterator_range< first_n_iterator <
  	  	  typename boost::range_iterator<ForwardRange>::type> > base_t;
public:
    template<typename Rng, typename T>
    first_nd_range(Rng& r, T t)
        : base_t(boost::make_iterator_range(
        		first_n_iterator<decltype(r.begin())>{r.begin()},
        		first_n_iterator<decltype(r.begin())>{r.begin(), t}))
    {
    }
};

template <class ForwardRange>
inline first_nd_range<ForwardRange>
first_n(ForwardRange& r, std::size_t n)
{
	return first_nd_range<ForwardRange>(r,n);
}

template <class ForwardRange>
inline first_nd_range<ForwardRange>
first_n(const ForwardRange& r, std::size_t n)
{
	return first_nd_range<ForwardRange>(r,n);
}

template< class ForwardRange >
inline first_nd_range<ForwardRange>
operator|(ForwardRange& r, const first_nd& f)
{
    return first_nd_range<ForwardRange>(r, f.n);
}

template< class ForwardRange >
inline first_nd_range<const ForwardRange>
operator|(const ForwardRange& r, const first_nd& f)
{
    return first_nd_range<const ForwardRange>(r, f.n);
}

} // namespace adaptors
} // namespace more


#endif /* MORE_ADAPTORS_FIRST_N_HPP_ */
