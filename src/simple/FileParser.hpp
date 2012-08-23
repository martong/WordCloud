//TODO rename include guard!!!
#ifndef WORDCLOUD_WC_SIMPLE_FILEPARSER_HPP_
#define WORDCLOUD_WC_SIMPLE_FILEPARSER_HPP_

#include "../src/IFileParser.hpp"

namespace wc {
namespace simple {

class FileParser : public IFileParser {
public:
	virtual void parse(const std::string& fileName, detail::CountMap& count);
	virtual ~FileParser() {};
};

} // namespace simple
} // namespace wc

#endif /* WORDCLOUD_WC_SIMPLE_FILEPARSER_HPP_ */
