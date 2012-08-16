#ifndef WORLDCLOUD_WC_FIRSTNRANGE_HPP_
#define WORLDCLOUD_WC_FIRSTNRANGE_HPP_

#include "wc/CountMap.hpp"
#include <boost/iterator/iterator_adaptor.hpp>

namespace wc {

class FirstNIterator : public boost::iterator_adaptor<FirstNIterator,
	CountMap::left_map::reverse_const_iterator>
{

};

} // namespace wc

#endif /* WORLDCLOUD_WC_FIRSTNRANGE_HPP_ */
