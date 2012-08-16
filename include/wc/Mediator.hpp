#ifndef WORLDCLOUD_WC_MEDIATOR_HPP_
#define WORLDCLOUD_WC_MEDIATOR_HPP_

#include "wc/Options.hpp"
#include "wc/CountMap.hpp"

namespace wc {

class Mediator {

	const Options& options;
	CountMap countMap;

public:

	Mediator(const Options& options) : options(options) {}
	void operator()();
	const CountMap& getCountMap() const { return countMap; }

	~Mediator() = default;
	Mediator(const Mediator&) = delete;
	Mediator& operator=(const Mediator&) = delete;

};

} // namespace wc

#endif /* WORLDCLOUD_WC_MEDIATOR_HPP_ */
