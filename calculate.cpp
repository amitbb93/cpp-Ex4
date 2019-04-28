#include "calculate.hpp"
#include <string>
/**
* This function calculates and returns a string of how many "bull" and "pgia" in the guesser string
* @param choose - the chooser string 
* @param guess - the guesser string in this specific guess (each time a different guess)
* @param array - array which store inside all the number that was pgia
*/
namespace bullpgia{
	string calculateBullAndPgia(string choose, string guess)
	{
		uint bull = 0;
		uint pgia = 0;
		short array [10] = {0};
		for(int i=0; i<choose.size();i++)
		{
			if(choose[i]==guess[i])
				bull++;
			else{
				for(int j=0; j<guess.size(); j++){
					if(array[j] == 0 && choose[i]==guess[j] && i!=j){
						pgia++;
						array[j] = 1;
					}
				}
			}
		}
		return to_string(bull)+","+to_string(pgia);
	}
}