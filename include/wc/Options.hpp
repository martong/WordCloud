#ifndef WORDCLOUD_WC_OPTIONS_HPP_
#define WORDCLOUD_WC_OPTIONS_HPP_

#include <string>

namespace wc {

struct Options {
	bool debug = true;
	std::string path;
	/**
	 * Retrieve the first N word from the most frequent words.
	 * 0 means unlimited.
	 */
	std::size_t firstN;
};

} // namespace wc

#endif /* WORDCLOUD_WC_OPTIONS_HPP_ */
