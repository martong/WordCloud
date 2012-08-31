#ifndef WORDCLOUD_WC_DETAIL_FILTERREGEX_HPP_
#define WORDCLOUD_WC_DETAIL_FILTERREGEX_HPP_

#include "wc/Options.hpp"
#include <boost/regex.hpp>
#include <numeric>

namespace wc {
namespace detail {

struct RegexFilter {
	RegexFilter(const Options& options) : options(options) {}
	bool operator()(const CountMap::left_value_type& p) const {
		const std::string& word = p.first;
		for (auto re : options.excludeRegexes) {
			if (boost::regex_match(word, re)) {
				return false;
			}
		}
		if (options.includeRegexes.size() == 0) {
			return true;
		}
		return std::accumulate(options.includeRegexes.begin(),	options.includeRegexes.end(), false,
				[&word](bool value, const boost::regex& re) {
					return value || boost::regex_match(word, re);
				}
		);
	}
private:
	const Options& options;
};

}  // namespace detail
}  // namespace wc


#endif /* WORDCLOUD_WC_DETAIL_FILTERREGEX_HPP_ */
