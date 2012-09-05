#ifndef WORDCLOUD_WC_OPTIONPARSER_HPP_
#define WORDCLOUD_WC_OPTIONPARSER_HPP_

#include <boost/noncopyable.hpp>
#include <boost/program_options.hpp>

#include "wc/Options.hpp"

namespace wc {

//struct OptionParserException : virtual std::exception, virtual boost::exception {};
//struct BadOption : OptionParserException{};
//typedef boost::error_info<struct tag_OptionParserError, std::string> EOptionParser;

class OptionParser : boost::noncopyable {
	const int argc;
	const char* const* argv;
	boost::program_options::variables_map vm;
	boost::program_options::options_description desc;
	Options options;
public:
	OptionParser(int argc, const char* const* argv);
	const Options& getOptions() const
	{
		return options;
	}
	const boost::program_options::options_description& getOptionsDescription() const
	{
		return desc;
	}
	void parse();
};

} // namespace wc

#endif /* WORDCLOUD_WC_OPTIONPARSER_HPP_ */
