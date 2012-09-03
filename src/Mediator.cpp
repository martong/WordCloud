#include "wc/Mediator.hpp"
#include "make_unique.hpp"
#include "DirectoryRange.hpp"
#include "simple/FileParser.hpp"

namespace wc {

void Mediator::operator()()
{
	using namespace wc;
	auto range = makeDirectoryRange(options);
	for (const auto& fileName : range) {
		IFileParserPtr fileParser = make_unique<simple::FileParser>();
		fileParser->parse(fileName, countMap);
	}
}

//WordCount Mediator::getWordCount() const
//{
//
//}

} // namespace wc
