#ifndef WORDCLOUD_WC_IFILEPARSER_HPP_
#define WORDCLOUD_WC_IFILEPARSER_HPP_

#include "wc/CountMap.hpp"
#include <string>
#include <memory>

namespace wc {

class IFileParser {
public:
	virtual void parse(const std::string& fileName, CountMap& count) = 0;
	virtual ~IFileParser() {};
};

typedef std::unique_ptr<IFileParser> IFileParserPtr;

} // namespace wc

#endif /* WORDCLOUD_WC_IFILEPARSER_HPP_ */
