#ifndef WORLDCLOUD_WC_COUNTMAPIO_HPP_
#define WORLDCLOUD_WC_COUNTMAPIO_HPP_

#include "wc/CountMap.hpp"
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

} // namespace detail

//template <class Range>
//typename boost::enable_if_c<
//	std::is_same<
//		typename boost::range_iterator<Range>::type,
//		CountMap::left_map::iterator
//	>::value,
//	std::ostream&
//>::type
//operator<<(std::ostream& os, const Range& obj)
//{
//	for (const auto& element : obj) {
//		detail::print(os, element.first, element.second);
//	}
//	return os;
//}

// problem:
// some address at the end is also printed. In case of 4:
// const,106
// boost,98
// include,91
// 0x662dc8
//template <class Range>
//inline std::ostream& print(std::ostream& os, const Range& obj)
//{
//	//static_assert()
//	for (const auto& element : obj) {
//		detail::print(os, element.first, element.second);
//	}
//	return os;
//}

template <class Range>
inline void print(std::ostream& os, const Range& obj)
{
	//static_assert()
	for (const auto& element : obj) {
		detail::print(os, element.first, element.second);
	}
}

} // namespace wc

#endif /* WORLDCLOUD_WC_COUNTMAPIO_HPP_ */
