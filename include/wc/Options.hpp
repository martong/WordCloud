#ifndef WORDCLOUD_WC_OPTIONS_HPP_
#define WORDCLOUD_WC_OPTIONS_HPP_

#include <string>
#include <boost/regex.hpp>

namespace wc {

struct Options {
	bool debug = true;
	std::string path = ".";
	/**
	 * Retrieve the first N word from the most frequent words.
	 * Ordered by frequency, decreasing.
	 */
	std::size_t firstN = 200;
	boost::regex regex = boost::regex(".*");
	bool inverseMatch = false;
};

} // namespace wc

#endif /* WORDCLOUD_WC_OPTIONS_HPP_ */
