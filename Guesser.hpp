#pragma once
#include "iostream"
#include "calculate.hpp"
using namespace std;
typedef unsigned int uint;
namespace bullpgia {
    class Guesser {
    public:
		uint length;
        virtual string guess() = 0;
        virtual void startNewGame(uint length){this->length = length;};
        virtual void learn(string str){}; //check before upload to github
    };
}
