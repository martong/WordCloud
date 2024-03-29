#include "LineBasedCounter.hpp"
#include <boost/regex.hpp>
//#include <regex> 4.7.1 unimplemented

namespace wc {
namespace simple {

void LineBasedCounter::operator()(const std::string& line, detail::CountMap& countMap)
{
	using namespace boost;
	regex regex("(\\w+)");
	sregex_token_iterator i(line.begin(), line.end(), regex, 1 /* match for the first group */);
	sregex_token_iterator j;
	while (i != j) {
		auto& left = countMap.left;
		auto it = left.find(*i);
		if (it != left.end()) {
			//++(left.at(*i).count);
			CountEntry e(it->second);
			++e.count;
			left.replace_data(it, e);
		} else {
			countMap.insert(detail::CountMap::value_type(*i, 1));
		}
		++i;
	}
}

} // namespace simple
} // namespace wc
