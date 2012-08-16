//TODO rename include guard!!!
#ifndef WORLDCLOUD_WC_SIMPLE_FILEPARSER_HPP_
#define WORLDCLOUD_WC_SIMPLE_FILEPARSER_HPP_

#include "../src/IFileParser.hpp"

namespace wc {
namespace simple {

class FileParser : public IFileParser {
public:
	virtual void parse(const std::string& fileName, CountMap& count);
	virtual ~FileParser() {};
};

} // namespace simple
} // namespace wc

#endif /* WORLDCLOUD_WC_SIMPLE_FILEPARSER_HPP_ */
