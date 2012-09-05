#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/exception/all.hpp>
#include "wc/Mediator.hpp"
#include "wc/WordCountIO.hpp"
#include "wc/OptionParser.hpp"

int main(int argc, char** argv)
{
	namespace po = boost::program_options;

	try {
		po::options_description general("General options");
		general.add_options()
			("debug,d", "turn on debug")
			("help,h", /*po::bool_switch(&dohelp),*/ "produce help message");

		wc::OptionParser optionsParser(argc, argv);
		optionsParser.parse();

		po::options_description all("Allowed options");
		all.add(general).add(optionsParser.getOptionsDescription());

		po::variables_map vm;
		store(parse_command_line(argc, argv, all), vm);
		po::notify(vm);

		if (vm.count("help")) {
			std::cout << all << "\n";
			return 0;
		}

		wc::Mediator m(optionsParser.getOptions()); m();
		std::cout << m.getWordCount() << std::flush;
	} catch (std::exception& e) {
		std::cerr << boost::diagnostic_information(e) << std::endl;
		return 1;
	}

	return 0;
}
