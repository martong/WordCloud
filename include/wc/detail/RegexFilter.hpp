#ifndef WORDCLOUD_WC_DETAIL_FILTERREGEX_HPP_
#define WORDCLOUD_WC_DETAIL_FILTERREGEX_HPP_

#include "wc/Options.hpp"
#include <boost/regex.hpp>
#include <numeric>

namespace wc {
namespace detail {

template <class AccessString, class RegexForwardRange>
struct RegexFilter {
	typedef typename AccessString::value_type value_type;
	RegexFilter(const RegexForwardRange& includeRegexes,
			const RegexForwardRange& excludeRegexes,
			const AccessString& accessString) :
				includeRegexes(includeRegexes), excludeRegexes(excludeRegexes),
				accessString(accessString)
	{}
	bool operator()(const value_type& value) const {
		return filter(accessString(value));
	}
	bool filter(const std::string& word) const {
		for (const auto& re : excludeRegexes) {
			if (boost::regex_match(word, re)) {
				return false;
			}
		}
		if (includeRegexes.size() == 0) {
			return true;
		}
		return std::accumulate(includeRegexes.begin(),	includeRegexes.end(), false,
				[&word](bool value, const boost::regex& re) {
					return value || boost::regex_match(word, re);
				}
		);
	}
private:
	const RegexForwardRange& includeRegexes;
	const RegexForwardRange& excludeRegexes;
	AccessString accessString;
};

template <class AccessString, class RegexForwardRange>
RegexFilter<AccessString, RegexForwardRange>
makeRegexFilter(const RegexForwardRange& includeRegexes,
			const RegexForwardRange& excludeRegexes,
			const AccessString& accessString)
{
	return RegexFilter<AccessString, RegexForwardRange>(includeRegexes,
			excludeRegexes, accessString);
}


}  // namespace detail
}  // namespace wc


#endif /* WORDCLOUD_WC_DETAIL_FILTERREGEX_HPP_ */
