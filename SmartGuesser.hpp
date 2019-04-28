#pragma once
#include "Guesser.hpp"
#include "iostream"
#include <stdbool.h>
using namespace std;
class SmartGuesser : public bullpgia::Guesser{
	 uint length = 0;
	 short checkedNumbers = -1;
	 uint fourBulls = 0;
	 string currectGuess = "";
	 string pattern = "";
	 uint bull = 0;
	 uint pgia = 0;
	 short location = 0;
	 short firstAttempt = -1;
	 short secondAttempt = -1;
	 short thirdAttempt = -1;
	 short firstBool = 1;
	 short secondBool = 1;
	 short thirdBool = 1;
	 void startNewGame(uint length);
	 string guess();
     void learn(string str);
	 string checkPattern();
	 void buildPattern(short numberOfBulls);
	 string buildSolution();
};
