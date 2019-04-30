#include "DummyChoosers.hpp"
#include <stdlib.h>
/**
	 * This function chooses a number randomaly 
	 * @return the choose string
	 */
std::string RandomChooser::choose(uint length) {
	std::string r="";
	for (uint i=0; i<length; ++i) {
		char c = '0' + (rand()%10);
		r += c;
	}
	//cout<<"chooser: "<<r<<endl;
	return r;
}
