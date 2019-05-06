#pragma once
#include "Guesser.hpp"
#include "iostream"
#include <stdbool.h>
#include <string>
#include <sstream>
using namespace std;
class SmartGuesser : public bullpgia::Guesser{
	 uint length = 0;
	 short checkedNumbers = -1;
	 uint fourBulls = 0;
	 string currectGuess = "";
	 string pattern = "";
	 uint pgia = 0;
	 uint bull = 0;
	 short firstAttempt = -1;
	 short secondAttempt = -1;
	 short thirdAttempt = -1;
	 short fourthAttempt = -1;
	 short fifthAttempt = -1;
	 short index = 0;
	 short index2 = -1;
	 short index3 = 0;
	 void startNewGame(uint length);
	 string guess();
     void learn(string str);
	 string checkPattern();
	 void buildPattern(short numberOfBulls);
	 string buildSolution();
	 string checkPatternForTwo();
	 string checkPatternForThree();
};
