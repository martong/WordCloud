#include "wc/Mediator.hpp"
#include "wc/CountMapIO.hpp"
#include <iostream>
#include <boost/lexical_cast.hpp>

int main(int argc, char** argv)
{
	using namespace wc;

	if (argc < 3) {
		std::cout << "ERROR" << std::endl;
		return 1;
	}

	Options options;
	options.path = argv[1];
	Mediator m(options);
	m();

	size_t firstN = boost::lexical_cast<size_t>(argv[2]);
	std::cout << FirstN(m.getCountMap(), firstN) << std::endl;
	//std::cout << m.getCountMap() << std::endl;

	return 0;
}
