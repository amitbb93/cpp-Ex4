#pragma once
#include "Guesser.hpp"
using std::string;
using namespace bullpgia;
/**
 * ConstantGuesser is a guesser that always guesses the same string. 
 */
class ConstantGuesser: public Guesser {
	string myConstantString;
	public:
        ConstantGuesser(const string& constantString) { myConstantString = constantString; }
		string guess() override {
			return myConstantString;
		}
		void startNewGame(uint length) override;
		void learn(string str) override {};
};

/**
 * RandomGuesser is a guesser that guesses a random string.
 */
class RandomGuesser: public Guesser {
	string guess() override;
	void startNewGame(uint length) override;
    void learn(string str) override {};
};
