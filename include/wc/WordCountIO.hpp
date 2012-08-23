#ifndef WORDCLOUD_WC_WORDCOUNTIO_HPP_
#define WORDCLOUD_WC_WORDCOUNTIO_HPP_

#include "wc/WordCount.hpp"
#include "wc/detail/CountMapIO.hpp"

namespace wc {

std::ostream& operator<<(std::ostream& os, const WordCount& obj)
{
	return detail::print(os, obj);
}

}  // namespace wc


#endif /* WORDCLOUD_WC_WORDCOUNTIO_HPP_ */
