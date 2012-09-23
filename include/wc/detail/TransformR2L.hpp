#ifndef WORDCLOUD_WC_DETAIL_TRANSFORML2R_HPP_
#define WORDCLOUD_WC_DETAIL_TRANSFORML2R_HPP_

namespace wc {
namespace detail {

/**
 * Transforms a boost::bimap's right_value_type to left_value_type.
 */
template <class BiMap>
struct TransformR2L {
	typedef typename BiMap::left_value_type result_type;
	result_type operator()(const typename BiMap::right_value_type& val) const{
		return result_type(val.second, val.first);
	}
};

} // namespace detail
} // namespace wc

#endif /* WORDCLOUD_WC_DETAIL_TRANSFORML2R_HPP_ */
