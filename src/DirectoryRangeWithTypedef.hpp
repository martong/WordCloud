#ifndef WORLDCLOUD_WC_DIRECTORYRANGE_HPP_
#define WORLDCLOUD_WC_DIRECTORYRANGE_HPP_

#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>

#include <algorithm>
#include <array>
#include <boost/range/algorithm/find.hpp>

namespace wc {

namespace detail {

using namespace boost::filesystem;

struct IsAllowedExtension {
	std::array<std::string, 20> allowedExtensions =
		{ {".cpp", ".hpp", ".h", ".c", ".hh", ".cc" } };
	bool operator()(const directory_entry& e) {
		const auto& ext = e.path().extension();
		if (ext.empty()) return false;
		return boost::find(allowedExtensions, ext.string()) != allowedExtensions.end();
	}
};

struct GetString
{
	typedef const std::string& result_type;
	result_type operator()(const directory_entry& entry) const
	{
		return entry.path().string();
	}
};

typedef const boost::iterator_range<recursive_directory_iterator> FullDirectoryRange;
typedef boost::filtered_range<IsAllowedExtension, const FullDirectoryRange> FilteredDirectoryRange;
typedef boost::transformed_range<GetString, const FilteredDirectoryRange>
	FilteredDirectoryStringRange;

} // detail

detail::FilteredDirectoryStringRange
makeDirectoryRange(const boost::filesystem::path& directoryPath)
{
	using namespace boost::filesystem;
	using namespace boost::adaptors;
	using namespace detail;

	const auto range = boost::make_iterator_range(
			recursive_directory_iterator(directoryPath),
			recursive_directory_iterator());
	return range | filtered(IsAllowedExtension()) | transformed(GetString());
}

} // namespace wc

#endif /* WORLDCLOUD_WC_DIRECTORYRANGE_HPP_ */
