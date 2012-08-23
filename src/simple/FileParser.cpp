#include "FileParser.hpp"
#include "LineBasedCounter.hpp"

#include <fstream>

namespace wc {
namespace simple {

void FileParser::parse(const std::string& fileName, detail::CountMap& count)
{
	using std::ifstream;
	ifstream stream(fileName);
	stream.exceptions(ifstream::badbit);
	LineBasedCounter counter;
	while (!stream.eof()) {
		std::string line;
		getline(stream, line);
		counter(line, count);
	}
	stream.close();
}

} // namespace simple
} // namespace wc
