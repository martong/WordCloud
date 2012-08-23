#ifndef WORDCLOUD_WC_MEDIATOR_HPP_
#define WORDCLOUD_WC_MEDIATOR_HPP_

#include "wc/Options.hpp"
#include "wc/detail/CountMap.hpp"
#include "wc/WordCount.hpp"

namespace wc {

class Mediator {

	const Options& options;
	detail::CountMap countMap;

public:

	Mediator(const Options& options) : options(options) {}
	void operator()();
	WordCount getWordCount() const { return detail::getFirstN(countMap, options.firstN); }

	~Mediator() = default;
	Mediator(const Mediator&) = delete;
	Mediator& operator=(const Mediator&) = delete;

};

} // namespace wc

#endif /* WORDCLOUD_WC_MEDIATOR_HPP_ */
