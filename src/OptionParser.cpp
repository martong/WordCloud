#include "wc/OptionParser.hpp"
#include "wc/cppKeyWords.hpp"

namespace wc {

namespace {

const char * const word_exclude_regex = "word_exclude_regex";
const char * const word_include_regex = "word_include_regex";
const char * const include_cpp_keywords = "include_cpp_keywords";
const char * const exclude_cpp_keywords = "exclude_cpp_keywords";
const char * const path_exclude_regex = "path_exclude_regex";
const char * const path_include_regex = "path_include_regex";

} // unnamed

OptionParser::OptionParser(int argc, const char* const* argv) :  argc(argc), argv(argv),
		desc("WordCount options")
{
	namespace po = boost::program_options;

	desc.add_options()
		("path", po::value<std::string>()->default_value(options.path), "path")
		("firstN", po::value<std::size_t>()->default_value(options.firstN), "firstN")
		(include_cpp_keywords, "include cpp keywords")
		(exclude_cpp_keywords, "exclude cpp keywords")
		(word_exclude_regex, po::value< std::vector<std::string> >(),
				"word exclude regex")
		(word_include_regex, po::value< std::vector<std::string> >(),
				"word include regex")
		(path_exclude_regex, po::value< std::vector<std::string> >(),
				"path exclude regex")
		(path_include_regex, po::value< std::vector<std::string> >(),
				"path include regex")
		;
}

void OptionParser::parse()
{
	namespace po = boost::program_options;

	po::parsed_options parsed =
	    po::command_line_parser(argc, argv).options(desc).allow_unregistered().run();
	store(parsed, vm);

	if (vm.count("path")) {
		options.path = vm["path"].as<std::string>();
	}

	if (vm.count("firstN")) {
		options.firstN = vm["firstN"].as<std::size_t>();
	}

	auto addCppKeyWords = [this](const char* key, Options::Regexes& regexes){
		if (vm.count(key)) {
			regexes.emplace_back(cppKeyWordsRegex);
		}
	};
	addCppKeyWords(exclude_cpp_keywords, options.wordExcludeRegexes);
	addCppKeyWords(include_cpp_keywords, options.wordIncludeRegexes);


	auto addRegex = [this](const char* key, Options::Regexes& regexes){
		if (vm.count(key)) {
			for (const std::string& s : vm[key].as< std::vector<std::string> >()) {
				regexes.emplace_back(s);
			}
		}
	};
	addRegex(word_exclude_regex, options.wordExcludeRegexes);
	addRegex(word_include_regex, options.wordIncludeRegexes);
	addRegex(path_exclude_regex, options.pathExcludeRegexes);
	addRegex(path_include_regex, options.pathIncludeRegexes);
}

} // namespace wc
