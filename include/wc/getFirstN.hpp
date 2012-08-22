#ifndef WORDCLOUD_WC_GETFIRSTN_HPP_
#define WORDCLOUD_WC_GETFIRSTN_HPP_

#include "wc/CountMap.hpp"
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <more/range/adaptor/projected.hpp>
#include <more/range/adaptor/first_nd.hpp>

namespace wc {

namespace detail {

auto getFirstNImpl = [](const CountMap& cm, std::size_t N)
{
	struct ProjectFunc {
		typedef CountMap::left_const_iterator result_type;
		ProjectFunc(const CountMap& cm) : cm(cm) {}
		result_type operator()(const CountMap::right_const_iterator& it) const{
			return cm.project_left(it);
		}
		const CountMap& cm;
	};

	struct TransformFunc {
		typedef CountMap::left_value_type result_type;
		TransformFunc(const CountMap& cm) : cm(cm) {}
		result_type operator()(const CountMap::right_value_type& val) const{
			return result_type(val.second, val.first);
		}
		const CountMap& cm;
	};

	using namespace more::adaptors;
	using namespace boost::adaptors;
	auto n = cm.size() > N ? N : cm.size();
	// TODO find out, what is the problem with the reversed order
	//auto range = cm.right | first_nd(N) | projected(ProjectFunc(cm));
	//auto range = cm.right | projected(ProjectFunc(cm)) | first_nd(n);
	//auto range = cm.right | transformed(TransformFunc(cm)) | first_nd(n);
	auto range = cm.right | first_nd(n) | transformed(TransformFunc(cm));
	return range;
};

} // namespace detail

inline
auto getFirstN(const CountMap& cm, std::size_t N) -> decltype(detail::getFirstNImpl(cm, N))
{
	return detail::getFirstNImpl(cm, N);
}

} // namespace wc

#endif /* WORDCLOUD_WC_GETFIRSTN_HPP_ */
