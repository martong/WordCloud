#ifndef WORDCLOUD_WC_DIRECTORYRANGE_HPP_
#define WORDCLOUD_WC_DIRECTORYRANGE_HPP_

#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>

#include <algorithm>
#include <array>
#include <boost/range/algorithm/find.hpp>

#include <type_traits>

namespace wc {

namespace detail {

auto makeDirectoryRangeImpl = [](const boost::filesystem::path& directoryPath)
{
	using namespace boost::filesystem;
	using namespace boost::adaptors;

	struct IsAllowedExtension {
		bool operator()(const directory_entry& e) {
			static const std::array<std::string, 20> allowedExtensions =
				{ {".cpp", ".hpp", ".h", ".c", ".hh", ".cc" } };
			const auto& ext = e.path().extension();
			if (ext.empty()) return false;
			return boost::find(allowedExtensions, ext.string()) != allowedExtensions.end();
		}
	};

	struct AccessMember	{
		typedef const path& result_type;
		result_type operator()(const directory_entry& entry) const
		{
			return entry.path();
		}
	};

	const auto range = boost::make_iterator_range(
			recursive_directory_iterator(directoryPath),
			recursive_directory_iterator());
	return range | filtered(IsAllowedExtension()) | transformed(AccessMember());
};

} // detail

auto makeDirectoryRange(const boost::filesystem::path& directoryPath)
	-> decltype(detail::makeDirectoryRangeImpl(directoryPath))
{
	return detail::makeDirectoryRangeImpl(directoryPath);
}

} // namespace wc

#endif /* WORDCLOUD_WC_DIRECTORYRANGE_HPP_ */
