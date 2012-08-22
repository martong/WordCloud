#ifndef WORDCLOUD_WC_OPTIONS_HPP_
#define WORDCLOUD_WC_OPTIONS_HPP_

#include <string>

namespace wc {

struct Options {
	bool debug = true;
	std::string path;
};

} // namespace wc

#endif /* WORDCLOUD_WC_OPTIONS_HPP_ */
