#ifndef WORLDCLOUD_WC_COUNTMAP_HPP_
#define WORLDCLOUD_WC_COUNTMAP_HPP_

#include <string>
#include <boost/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/bimap/multiset_of.hpp>

namespace wc {

struct CountEntry {
	typedef unsigned long Count;
	CountEntry(Count count = 0) : count(count) {}
	Count count;
	//bool language;
	//bool boost;
	//bool stl;

	~CountEntry() = default;
	CountEntry(const CountEntry& other) = default;
	CountEntry& operator=(const CountEntry& other) = default;
};

inline bool operator<(const CountEntry& l, const CountEntry& r) { return l.count < r.count; }

typedef boost::bimap<
			boost::bimaps::unordered_set_of<std::string>,
			boost::bimaps::multiset_of<CountEntry>
		> CountMap;

}

#endif /* WORLDCLOUD_WC_COUNTMAP_HPP_ */
