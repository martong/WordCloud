#include <iostream>
#include <boost/lexical_cast.hpp>
#include "wc/Mediator.hpp"
#include "wc/CountMapIO.hpp"
#include "wc/getFirstN.hpp"

int main(int argc, char** argv)
{
	using namespace wc;

	if (argc < 3) {
		std::cout << "ERROR" << std::endl;
		return 1;
	}

	Options options;
	options.path = argv[1];
	options.firstN = boost::lexical_cast<size_t>(argv[2]);

	Mediator m(options);
	m();

	std::cout << getFirstN(m.getCountMap(), options.firstN) << std::flush;
	//std::cout << m.getCountMap().left << std::endl;

	return 0;
}
