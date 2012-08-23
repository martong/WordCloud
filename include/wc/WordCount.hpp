#ifndef WORDCLOUD_WC_WORDCOUNT_HPP_
#define WORDCLOUD_WC_WORDCOUNT_HPP_

#include "wc/CountMap.hpp"
#include "wc/getFirstN.hpp"

namespace wc {

typedef decltype(getFirstN(CountMap(),0)) WordCount;

} // namespace wc

#endif /* WORDCLOUD_WC_WORDCOUNT_HPP_ */
