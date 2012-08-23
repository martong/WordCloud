#ifndef WORDCLOUD_WC_COUNTMAPIO_HPP_
#define WORDCLOUD_WC_COUNTMAPIO_HPP_

#include "wc/detail/CountMap.hpp"
#include "wc/getFirstN.hpp"
#include <iostream>
#include <type_traits>
#include <boost/utility/enable_if.hpp>

namespace wc {

namespace detail {

inline void print(std::ostream& os, const CountMap::left_map::key_type& word,
		const CountMap::left_map::mapped_type& entry)
{
	os << word << ',' << entry.count << '\n';
}

template <class Range>
inline std::ostream& print(std::ostream& os, const Range& obj)
{
	//static_assert()
	for (const auto& element : obj) {
		print(os, element.first, element.second);
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, const CountMap::left_map& obj)
{
	return detail::print(os, obj);
}

} // namespace detail
} // namespace wc

#endif /* WORDCLOUD_WC_COUNTMAPIO_HPP_ */
