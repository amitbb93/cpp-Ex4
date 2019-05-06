#include "SmartGuesser.hpp"
#include <string>
/**
*This class is responsible for guesseing the right choosers string
*/
void SmartGuesser::startNewGame(uint length) {
	this->length=length;
	checkedNumbers = -1;
	fourBulls = 0;
	pattern = "";
	pgia = 0;
	bull = 0;
	firstAttempt = -1;
	secondAttempt = -1;
	thirdAttempt = -1;
	fourthAttempt = -1;
	fifthAttempt = -1;
	index = 0;
	index2 = -1;
	index3 = 0;
}

/**
* This function returns for the "play" class the guess string every iteration
*@param fourBulls - condition to stop using checkedNumbers
*@param index - helps to initialize the guesses for the function that guesseing the numbers
*/
string SmartGuesser::guess() {
	switch (this->length){
	case 4:{
		if(fourBulls + bull < 4)return checkPattern();
		else if(fourBulls < 4){
			bull=4-fourBulls;
			buildPattern(checkedNumbers);
			return buildSolution();
		}
		else{
			if(bull==1){index=0;fourBulls++;}
			return buildSolution();
		}
	}
	case 3:{return checkPatternForThree();}
	case 2:{return checkPatternForTwo();}
	default:{firstAttempt++; return to_string(firstAttempt);}
	}
}

/**
* This function update for each guess how many bulls and pgias it has
*@param bull - last bull from calculate function
*@param pgia - last pgia from calculate function
*/
void SmartGuesser::learn(string str) {
	bull = stoi(str.substr(0,1),nullptr,10);
	pgia = stoi(str.substr(2,1),nullptr,10);
}

/**
* ( 4 numbers length ) This function finds the right location for each number that we ensured that actually exist in the choosers string
*@param fourBulls - a counter,every time we find the location of the number it raise by one
*@param index - helps to initialize the guesses for the function that guesseing the numbers
*@param pattern - save the right numbers of the choosers string (not in the right location) from min to max.
*@param firstAttempt, secondAttempt, thirdAttempt- saves the index of the number's location
*@param temp - a temporary string that we are sending for the calculate for checking the numbers.
*for example if the pattern is "123" we will start with sending "1aaa", than "a1aa" untill well find the right location of "1" and so on.
*@param finalSolution - the right guess
*@return : the final guess string  
*/
string SmartGuesser::buildSolution(){
	string temp = "aaaa";
	if (fourBulls==4){
		for(int i=index; i<3; i++){
			firstAttempt=i;
			index++;
			return temp.replace(i,1,pattern.substr(0,1));
		}
		index= 0;firstAttempt=3;fourBulls++;
	}
	
	if (fourBulls==5){
		for(int i=index; i<3; i++){
			secondAttempt=i;
			index++;
			if (i!=firstAttempt)return temp.replace(i,1,pattern.substr(1,1));
		}
		index=0;secondAttempt=3;fourBulls++;
	}

	if (fourBulls==6){
		for(int i=index; i<3; i++){
			thirdAttempt=i; 
			index++;
			if ((i!=firstAttempt) && (i!=secondAttempt))return temp.replace(i,1,pattern.substr(2,1));
		}
		index=0;thirdAttempt=3;fourBulls++;
	}
	string finalSolution = "bbbb";
	finalSolution.replace(firstAttempt,1,pattern.substr(0,1));
	finalSolution.replace(secondAttempt,1,pattern.substr(1,1));
	finalSolution.replace(thirdAttempt,1,pattern.substr(2,1));
	for(int i=0; i<4; i++){
		if(finalSolution.at(i) == 'b'){
			finalSolution.replace(i,1,pattern.substr(3,1));
			break;
		}
	}
	return finalSolution;
}

/**
* ( 2 numbers length )This function finds the right location for each number that we ensured that actually exist in the choosers string
*@param index - stop condition for the switch case
*@param index2 - index for run the array 
*@param pattern - save the right numbers of the choosers string (not in the right location) from min to max.
*@param firstAttempt, secondAttempt, thirdAttempt- saves the index of the number's location
*@param array - saves which group ofnumbers we need to check.
*@return : the final guess string  
*/
string SmartGuesser::checkPatternForTwo(){
	while(index < 5){
		switch(index)
		{
			case 0:{index++;return "01";}
			case 1:{firstAttempt=bull+pgia;index++;return "23";}
			case 2:{secondAttempt=bull+pgia;index++;return "45";}
			case 3:{thirdAttempt=bull+pgia;index++;return "67";}
			default:{fourthAttempt=bull+pgia;index++;}
		}
	}
	if(firstAttempt+secondAttempt+thirdAttempt+fourthAttempt==0)fifthAttempt=2;
	if(firstAttempt+secondAttempt+thirdAttempt+fourthAttempt==1)fifthAttempt=1;
	short array [] = {firstAttempt,firstAttempt,secondAttempt,secondAttempt,thirdAttempt,thirdAttempt,fourthAttempt,fourthAttempt,fifthAttempt,fifthAttempt};
	if(pattern.size()<2){
		while(index2>=0 && bull>0){
			pattern+=to_string(index2);
			bull--;
		}
		index2++;
		while(index2<10){
			if(array[index2]>0){
				return to_string(index2)+to_string(index2);
			}
			index2++;
		}
	}
	if(index == 5){index++; return pattern;}
	else return pattern.substr(1,1) + pattern.substr(0,1);
}

/**
* ( 3 numbers length ) This function finds the right location for each number that we ensured that actually exist in the choosers string
*@param index - helps to initialize the guesses for the function that guesseing the numbers
*@param index2 - index for run the array 
*@param index3 - using for finding the right numbers from the group
*@param pattern - save the right numbers of the choosers string (not in the right location) from min to max.
*@param firstAttempt, secondAttempt, thirdAttempt, fourthAttempt - saves the index of the number's location
*@param temp - a temporary string that we are sending for the calculate for checking the numbers.
*for example if the pattern is "123" we will start with sending "1aa", than "a1a" untill well find the right location of "1" and so on.
*@param finalSolution - the right guess
*@return : the final guess string  
*/
string SmartGuesser::checkPatternForThree(){
	while(index < 5){
		switch(index)
		{
			case 0:{index++;return "012";}
			case 1:{firstAttempt=bull+pgia;index++;return "345";}
			case 2:{secondAttempt=bull+pgia;index++;return "678";}
			case 3:{thirdAttempt=bull+pgia;index++;if(firstAttempt+secondAttempt+thirdAttempt!=3)return "999";else index++;break;}
			case 4:{if (bull!=0)fourthAttempt=bull;index++;}
		}
	}
	short array [] = {firstAttempt,firstAttempt,firstAttempt,secondAttempt,secondAttempt,secondAttempt,thirdAttempt,thirdAttempt,thirdAttempt,fourthAttempt};
	if(pattern.size()<3){
		while(index2>=0 && bull>0){
			pattern+=to_string(index2);
			bull--;
		}
		while(index2<9){
			index2++;
			if(array[index2]>0){
				return to_string(index2)+to_string(index2)+to_string(index2);
			}
		}
	}
	if(bull>0){index++;index3=0;}
	string temp = "aaa";
	if (index==5){
		for(int i=index3; i<2; i++){
			firstAttempt=i;
			index3++;
			return temp.replace(i,1,pattern.substr(0,1));
		}
		index3=0;firstAttempt=2;index++;
	}
	if (index==6){
		for(int i=index3; i<2; i++){
			secondAttempt=i;
			index3++;
			if (i!=firstAttempt)return temp.replace(i,1,pattern.substr(1,1));
		}
		index3=0;secondAttempt=2;index++;
	}
	string finalSolution = "bbb";

	finalSolution.replace(firstAttempt,1,pattern.substr(0,1));
	finalSolution.replace(secondAttempt,1,pattern.substr(1,1));
	for(int i=0; i<3; i++){
		if(finalSolution.at(i) == 'b'){
			finalSolution.replace(i,1,pattern.substr(2,1));
			break;
		}
	}
	return finalSolution;
}

/**
* This function uses for 4 length of string, it checks which number is in the choosers string
*@param checkedNumbers - is the basic number we go over for example "0000", "1111", "2222"...
*@param fourBulls - stop condition,once it gets to 4 bulls it stops
*/
string SmartGuesser::checkPattern(){
	switch (checkedNumbers){
		case -1:{checkedNumbers = 0;return "0000";}	
		case 0:{if(bull == 0){checkedNumbers = 1;return "1111";}
				else{buildPattern(0);checkedNumbers = 1;return "1111";}}
		case 1:{if(bull == 0){checkedNumbers = 2;return "2222";}
				else{buildPattern(1);checkedNumbers = 2;return "2222";}}	
		case 2:{if(bull == 0){checkedNumbers = 3;return "3333";}
				else{buildPattern(2);checkedNumbers = 3;return "3333";}}
		case 3:{if(bull == 0){checkedNumbers = 4;return "4444";}
				else{buildPattern(3);checkedNumbers = 4;return "4444";}}	
		case 4:{if(bull == 0){checkedNumbers = 5;return "5555";}
				else{buildPattern(4);checkedNumbers = 5;return "5555";}}
		case 5:{if(bull == 0){checkedNumbers = 6;return "6666";}
				else{buildPattern(5);checkedNumbers = 6;return "6666";}}	
		case 6:{if(bull == 0){checkedNumbers = 7;return "7777";}
				else{buildPattern(6);checkedNumbers = 7;return "7777";}}
		case 7:{if(bull == 0){checkedNumbers = 8;return "8888";}
				else{buildPattern(7);checkedNumbers = 8;return "8888";}}	
		case 8:{if(bull == 0){checkedNumbers = 9;bull=4-fourBulls;buildPattern(9);return buildSolution();}
				else{buildPattern(8);checkedNumbers=9;if(fourBulls!=4){bull=4-fourBulls;buildPattern(9);}return buildSolution();}}
	}
	return "xxxx";
}


/**
* This function uses for 4 length of string,it build the pattern(a string that saves the right numbers of the choosers string (not in the right location) from min to max.)
*@param checkedNumbers - is the basic number we go over for example "0000", "1111", "2222"...
*@param fourBulls - stop condition,once it gets to 4 bulls it stops
*/
void SmartGuesser::buildPattern(short numberOfBulls){
	uint howManyBulls = 0;
	fourBulls = fourBulls + bull;
	while(howManyBulls < bull){
		pattern += to_string(numberOfBulls);
		howManyBulls++;
	}
}