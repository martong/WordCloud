#ifndef WORDCLOUD_WC_WORDCOUNT_HPP_
#define WORDCLOUD_WC_WORDCOUNT_HPP_

#include "wc/detail/CountMap.hpp"
#include "wc/getFirstN.hpp"

namespace wc {

typedef decltype(detail::getFirstN(detail::CountMap(),0)) WordCount;

} // namespace wc

#endif /* WORDCLOUD_WC_WORDCOUNT_HPP_ */
