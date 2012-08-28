#ifndef WORDCLOUD_WC_MEDIATOR_HPP_
#define WORDCLOUD_WC_MEDIATOR_HPP_

#include "wc/Options.hpp"
#include "wc/detail/CountMap.hpp"
#include "wc/detail/getFirstN.hpp"

namespace wc {

class Mediator {

	const Options& options;
	detail::CountMap countMap;

public:

	Mediator(const Options& options) : options(options) {}
	void operator()();
	auto getWordCount() const -> decltype(detail::getFirstN(countMap, 0))
	{
		return detail::getFirstN(countMap, options.firstN);
	}

	~Mediator() = default;
	Mediator(const Mediator&) = delete;
	Mediator& operator=(const Mediator&) = delete;

};

/**
 * This is the result type of the library.
 * This is a range, which's value_type is signature compatible with:
 * std::pair<std::string, wc::CountEntry>
 */
typedef decltype(Mediator(Options()).getWordCount()) WordCount;

} // namespace wc

#endif /* WORDCLOUD_WC_MEDIATOR_HPP_ */
