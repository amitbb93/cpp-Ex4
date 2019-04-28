#pragma once
#include "iostream"

typedef unsigned int uint;
using namespace std;
namespace bullpgia {
    class Chooser {
    public:
        virtual string choose(uint) = 0;
    };
}

