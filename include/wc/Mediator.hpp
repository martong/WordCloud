#ifndef WORDCLOUD_WC_MEDIATOR_HPP_
#define WORDCLOUD_WC_MEDIATOR_HPP_

#include "wc/Options.hpp"
#include "wc/detail/CountMap.hpp"
#include "wc/detail/TransformR2L.hpp"
#include "wc/detail/FilterRegex.hpp"
#include <more/range/adaptor/first_nd.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>

namespace wc {

namespace detail {

auto getWordCountImpl = [](const CountMap& cm, const Options& options)
{
	using namespace boost::adaptors;
	using namespace more::adaptors;

	auto n = cm.size() > options.firstN ? options.firstN : cm.size();

	// TODO When OvenToBoost accepted by boost, then replace first_nd to boost::taken(n)
	return cm.right | first_nd(n) |
			transformed(TransformR2L<CountMap>(cm)) | filtered(RegexFilter(options));
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
