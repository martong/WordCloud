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
	Mediator m(options);
	m();
	const CountMap& cm = m.getCountMap();

	size_t firstN = boost::lexical_cast<size_t>(argv[2]);
	const auto range = getFirstN(cm, firstN);
	print(std::cout, range);
	//std::cout << m.getCountMap().left << std::endl;

	return 0;
}
