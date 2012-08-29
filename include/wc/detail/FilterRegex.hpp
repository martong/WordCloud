#ifndef WORDCLOUD_WC_DETAIL_FILTERREGEX_HPP_
#define WORDCLOUD_WC_DETAIL_FILTERREGEX_HPP_

#include "wc/Options.hpp"
#include <boost/regex.hpp>

namespace wc {
namespace detail {

struct RegexFilter {
	RegexFilter(const Options& options) : options(options) {}
	bool operator()(const CountMap::left_value_type& p) const {
		const std::string& word = p.first;
		if (options.inverseMatch) {
			return !boost::regex_match(word, options.regex);
		}
		return boost::regex_match(word, options.regex);
	}
private:
	const Options& options;
};

}  // namespace detail
}  // namespace wc


#endif /* WORDCLOUD_WC_DETAIL_FILTERREGEX_HPP_ */
