#ifndef WORDCLOUD_WC_DETAIL_FILTERFIRSTNWHILE_HPP_
#define WORDCLOUD_WC_DETAIL_FILTERFIRSTNWHILE_HPP_

namespace wc {
namespace detail {

/**
 * Returns true only if the predicate is true, and previously
 * the predicate has been true less than N times.
 */
template <class UnaryPredicate>
struct FilterFirstNWhile {
	FilterFirstNWhile(const UnaryPredicate& predicate, std::size_t N) :
		predicate(predicate), N(N) {}
	bool operator()(const typename UnaryPredicate::value_type& value) {
		if (predicate(value)) {
			++count;
			return count <= N;
		}
		return false;
	}
private:
	UnaryPredicate predicate;
	const std::size_t N;
	std::size_t count = 0;
};

template <class UnaryPredicate>
FilterFirstNWhile<UnaryPredicate>
makeFilterFirstNWhile(const UnaryPredicate& predicate, std::size_t N)
{
	return FilterFirstNWhile<UnaryPredicate>(predicate, N);
}


} // namespace detail
} // namespace wc

#endif /* WORDCLOUD_WC_DETAIL_FILTERFIRSTNWHILE_HPP_ */
