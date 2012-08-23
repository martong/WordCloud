#ifndef WORDCLOUD_WC_WORDCOUNT_HPP_
#define WORDCLOUD_WC_WORDCOUNT_HPP_

#include "wc/detail/CountMap.hpp"
#include "wc/detail/getFirstN.hpp"

namespace wc {

/**
 * This is the result type of the library.
 * This is a range, which's value_type is signature compatible with:
 * std::pair<std::string, wc::CountEntry>
 */
typedef decltype(detail::getFirstN(detail::CountMap(),0)) WordCount;

} // namespace wc

#endif /* WORDCLOUD_WC_WORDCOUNT_HPP_ */
