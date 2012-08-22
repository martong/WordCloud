#ifndef WORDCLOUD_WC_SIMPLE_LINE_BASED_COUNTER_HPP_
#define WORDCLOUD_WC_SIMPLE_LINE_BASED_COUNTER_HPP_

#include "wc/CountMap.hpp"

namespace wc {
namespace simple {

class LineBasedCounter {

public:

	LineBasedCounter() = default;
	LineBasedCounter(const LineBasedCounter& other) = delete;
	LineBasedCounter& operator=(const LineBasedCounter& other) = delete;
	~LineBasedCounter() = default;

	void operator()(const std::string& line, CountMap& countMap);
};

}  // namespace simple
} // namespace wc

#endif /* WORDCLOUD_WC_SIMPLE_LINE_BASED_COUNTER_HPP_ */
