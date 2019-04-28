#include "calculate.hpp"
#include <string>
namespace bullpgia{
	string calculateBullAndPgia(string choose, string guess)
	{
		uint bull = 0;
		uint pgia = 0;
		for(int i=0; i<choose.size();i++)
		{
			if(choose[i]==guess[i])
				bull++;
			else{
				for(int j=0; j<guess.size(); j++){
					if(choose[i]==guess[j] && i!=j)
						pgia++;
				}
			}
		}
		return to_string(bull)+","+to_string(pgia);
	}
}