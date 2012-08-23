#ifndef WORDCLOUD_WC_COUNTENTRY_HPP_
#define WORDCLOUD_WC_COUNTENTRY_HPP_

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
inline bool operator>(const CountEntry& l, const CountEntry& r) { return l.count > r.count; }

} // namespace wc


#endif /* WORDCLOUD_WC_COUNTENTRY_HPP_ */
