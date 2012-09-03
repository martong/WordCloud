#ifndef WORDCLOUD_WC_DIRECTORYRANGE_HPP_
#define WORDCLOUD_WC_DIRECTORYRANGE_HPP_

#include <algorithm>
#include <array>
#include <type_traits>

#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm/find.hpp>

#include "wc/detail/RegexFilter.hpp"

namespace wc {

namespace detail {

auto makeDirectoryRangeImpl = [](const Options& options)
{
	using namespace boost::filesystem;
	using namespace boost::adaptors;

	struct AccessString	{
		typedef directory_entry value_type;
		typedef const std::string& result_type;
		result_type operator()(const value_type& entry) const
		{
			return entry.path().string();
		}
	};

	const auto range = boost::make_iterator_range(
			recursive_directory_iterator(options.path),
			recursive_directory_iterator());
	return range |
			filtered(makeRegexFilter(options.pathIncludeRegexes,
					options.pathExcludeRegexes, AccessString())) |
			transformed(AccessString());
};

} // detail

// Would be nice to make it templatized on Regexes type, but then auto couldn't be used.
auto inline makeDirectoryRange(const Options& options)
	-> decltype(detail::makeDirectoryRangeImpl(options))
{
	return detail::makeDirectoryRangeImpl(options);
}

} // namespace wc

#endif /* WORDCLOUD_WC_DIRECTORYRANGE_HPP_ */
