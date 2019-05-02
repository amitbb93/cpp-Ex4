#include "calculate.hpp"
#include <string>
/**
* This function calculates and returns a string of how many "bull" and "pgia" in the guesser string
* @param choose - the chooser string 
* @param guess - the guesser string in this specific guess (each time a different guess)
* @param array - array which store inside all the number that was pgia
*/
using namespace std;
	string bullpgia::calculateBullAndPgia(string choose, string guess)
	{
		uint bull = 0;
		uint pgia = 0;
		short chooseArray [10] = {0};
		short guessArray [10] = {0};
		for(int i=0; i<choose.size();i++)
		{
			if(choose.at(i)==guess.at(i))
				bull++;
			else{
				chooseArray[choose.at(i) - '0'] ++;
				guessArray[guess.at(i) - '0'] ++;
			}
		}
		for(int i=0; i<10; i++){
			if(chooseArray[i] == guessArray[i])pgia=pgia+chooseArray[i];
			else{
				if(!(chooseArray[i] == 0 && guessArray[i] != 0)||(chooseArray[i] != 0 && guessArray[i] == 0)){
					if(chooseArray[i]<guessArray[i])pgia=pgia+chooseArray[i];
					else pgia=pgia+guessArray[i];
				}
			}
		}
		return to_string(bull)+","+to_string(pgia);
	}