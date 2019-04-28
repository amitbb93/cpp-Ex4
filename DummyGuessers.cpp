#include "DummyGuessers.hpp"
#include <stdlib.h>
/**
	 * This function guesses a number randomaly 
	 * @return the guess string
	 */
std::string RandomGuesser::guess() {
	std::string r="";
	for (uint i=0; i<this->length; ++i) {
		char c = '0' + (rand()%10);
		r += c;
	}
	return r;
}
/**
* This function initialize the length of how many numbers the guesser should choose for his guess
*/
void RandomGuesser::startNewGame(uint length) {
    this->length = length;
}

/**
* This function initialize the length of how many numbers the guesser should choose for his guess
*/
void ConstantGuesser::startNewGame(uint length) {
    this->length = length;
}
