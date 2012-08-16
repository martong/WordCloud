#ifndef WORLDCLOUD_WC_COUNTMAPIO_HPP_
#define WORLDCLOUD_WC_COUNTMAPIO_HPP_

#include "wc/CountMap.hpp"
#include <iostream>

namespace wc {

namespace detail {

inline void print(std::ostream& os, const CountMap::left_map::key_type& word,
		const CountMap::left_map::mapped_type& entry)
{
	os << word << ',' << entry.count << '\n';
}

} // namespace detail

inline std::ostream& operator<<(std::ostream& os, const CountMap& obj)
{
	for (const auto& element : obj.left) {
		detail::print(os, element.first, element.second);
	}
	return os;
}

class FirstN
{
	const CountMap& cm;
	const size_t n;
public:
	explicit FirstN(const CountMap& cm, size_t n) : cm(cm), n(n) {}
	void print(std::ostream& os) const
	{
		const auto& right = cm.right;
		size_t i = 0;
		for (auto it = right.rbegin(); i < n && it != right.rend(); ++i, ++it) {
			detail::print(os, it->second, it->first);
		}
	}
};

inline std::ostream& operator<<(std::ostream& os, const FirstN& obj)
{
	obj.print(os);
	return os;
}

} // namespace wc

#endif /* WORLDCLOUD_WC_COUNTMAPIO_HPP_ */
