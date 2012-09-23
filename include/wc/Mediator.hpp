#ifndef WORDCLOUD_WC_MEDIATOR_HPP_
#define WORDCLOUD_WC_MEDIATOR_HPP_

#include "wc/Options.hpp"
#include "wc/detail/CountMap.hpp"
#include "wc/detail/TransformR2L.hpp"
#include "wc/detail/FilterFirstNWhile.hpp"
#include "wc/detail/RegexFilter.hpp"
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <functional>

namespace wc {

namespace detail {

auto getWordCountImpl = [](const CountMap& cm, const Options& options)
{
	using namespace boost::adaptors;

	auto n = cm.size() > options.firstN ? options.firstN : cm.size();

	struct AccessLeftFirst	{
		typedef CountMap::left_value_type value_type;
		typedef const CountMap::left_key_type& result_type;
		result_type operator()(const value_type& entry) const
		{
			return entry.first;
		}
	};

	// internal compiler error, todo gcc bug report
//	struct AccessLeftFirst	{
//		typedef CountMap::left_value_type value_type;
//		auto operator()(const value_type& entry) const -> decltype(entry.first)
//		{
//			return entry.first;
//		}
//	};

	return cm.right |
			transformed(TransformR2L<CountMap>()) | // transform Right type to Left type
			filtered(
					makeFilterFirstNWhile(
							// filter with the regexes
							makeRegexFilter(options.wordIncludeRegexes,
									options.wordExcludeRegexes, AccessLeftFirst()),
							n // get not more than n elements
					)
			);
};

} // namespace detail

class Mediator {

	const Options& options;
	detail::CountMap countMap;

public:

	Mediator(const Options& options) : options(options) {}
	void operator()();

	auto getWordCount() const -> decltype(detail::getWordCountImpl(countMap, options))
	{
		return detail::getWordCountImpl(countMap, options);
	}

	~Mediator() = default;
	Mediator(const Mediator&) = delete;
	Mediator& operator=(const Mediator&) = delete;

};

/**
 * One item of a WordCount.
 * Signature compatible with:
 * std::pair<std::string, wc::CountEntry>
 */
typedef detail::CountMap::left_value_type WordCountItem;

/**
 * This is the result type of the library.
 * This is a range, which's value_type is equal to WordCountItem.
 */
typedef decltype(Mediator(Options()).getWordCount()) WordCount;

} // namespace wc

#endif /* WORDCLOUD_WC_MEDIATOR_HPP_ */
