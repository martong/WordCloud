#ifndef WORDCLOUD_WC_COUNTMAP_HPP_
#define WORDCLOUD_WC_COUNTMAP_HPP_

#include <string>
#include <boost/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/bimap/multiset_of.hpp>

#include "wc/CountEntry.hpp"

namespace wc {
namespace detail {

typedef boost::bimap<
			boost::bimaps::unordered_set_of<std::string>,
			boost::bimaps::multiset_of<CountEntry, std::greater<CountEntry>>
		> CountMap;

}  // namespace detail
} // namespace wc

#endif /* WORDCLOUD_WC_COUNTMAP_HPP_ */
