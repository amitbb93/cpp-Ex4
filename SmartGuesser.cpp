#include "SmartGuesser.hpp"
#include <string>
/**
*
*@param checkedNumbers - is the basic number we go over for example "0000", "1111", "2222"...
*@param fourBulls - condition to stop using checkedNumbers
*@param pattern - save the bull numbers
*@param currectGuess - the right string for now
*@param bull - last bull from calculate function
*@param pgia - last pgia from calculate function
*/
void SmartGuesser::startNewGame(uint length) {
	this->length=length;
	checkedNumbers = -1;
	fourBulls = 0;
	pattern = "";
	bull = 0;
	pgia = 0;
	location = 0;
	firstAttempt = -1;
	secondAttempt = -1;
	thirdAttempt = -1;
	firstBool = 1;
	secondBool = 1;
	thirdBool = 1;
}

string SmartGuesser::guess() {
	if(fourBulls + bull < 4) return checkPattern();
	else if(fourBulls!=4){
		bull=4-fourBulls;
		buildPattern(checkedNumbers);
		return buildSolution();
	}
	else return buildSolution();
}

void SmartGuesser::learn(string str) {
	bull = stoi(str.substr(0,1),nullptr,10);
	pgia = stoi(str.substr(2,2),nullptr,10);
}

string SmartGuesser::buildSolution(){
	if(firstAttempt > -1 && bull == 1) firstBool = 0;
	if(firstAttempt == 2 && bull != 1) {firstAttempt=3; firstBool = 0;}
	if(firstBool==1){
		switch(firstAttempt){
			case -1:{firstAttempt=0;return pattern.substr(0,1)+"xxx";}
			case 0:{firstAttempt=1;return "x"+pattern.substr(0,1)+"xx";}
			case 1:{firstAttempt=2;return "xx"+pattern.substr(0,1)+"x";}
		}
	}
	if(secondAttempt > -1 && bull == 1) secondBool = 0;
	if((secondBool = 1) && (firstAttempt == 0 || firstAttempt == 1) && secondAttempt == 2 && bull != 1) {secondAttempt=3; secondBool = 0;}
	if((secondBool = 1) && (firstAttempt == 2 || firstAttempt == 3) && secondAttempt == 1 && bull != 1) {secondAttempt=2; secondBool = 0;}
	if(secondBool==1){
		switch(firstAttempt){
			case 0:
					switch(secondAttempt){
							case -1:{secondAttempt=1;return "x"+pattern.substr(1,1)+"xx";}
							case 1:{secondAttempt=2;return "xx"+pattern.substr(1,1)+"x";}
					}		
			case 1:
					switch(secondAttempt){
							case -1:{secondAttempt=0;return pattern.substr(1,1)+"xxx";}
							case 0:{secondAttempt=2;return "xx"+pattern.substr(1,1)+"x";}
					}		
			case 2:
					switch(secondAttempt){
							case -1:{secondAttempt=0;return pattern.substr(1,1)+"xxx";}
							case 0:{secondAttempt=1;return "x"+pattern.substr(1,1)+"xx";}
					}		
			case 3:
					switch(secondAttempt){
							case -1:{secondAttempt=0;return pattern.substr(1,1)+"xxx";}
							case 0:{secondAttempt=1;return "x"+pattern.substr(1,1)+"xx";}
					}
		}
	}
	if(thirdAttempt > -1 && bull == 1) thirdBool = 0;
	if((thirdBool = 1) && (firstAttempt == 0 && secondAttempt == 1 && thirdAttempt == 2) && bull != 1) {thirdAttempt=3; thirdBool = 0;}
	if((thirdBool = 1) && (firstAttempt == 0 && secondAttempt == 2 && thirdAttempt == 1) && bull != 1) {thirdAttempt=3; thirdBool = 0;}
	if((thirdBool = 1) && (firstAttempt == 0 && secondAttempt == 3 && thirdAttempt == 1) && bull != 1) {thirdAttempt=2; thirdBool = 0;}
	if((thirdBool = 1) && (firstAttempt == 1 && secondAttempt == 0 && thirdAttempt == 2) && bull != 1) {thirdAttempt=3; thirdBool = 0;}
	if((thirdBool = 1) && (firstAttempt == 1 && secondAttempt == 2 && thirdAttempt == 0) && bull != 1) {thirdAttempt=3; thirdBool = 0;}
	if((thirdBool = 1) && (firstAttempt == 1 && secondAttempt == 3 && thirdAttempt == 0) && bull != 1) {thirdAttempt=2; thirdBool = 0;}
	if((thirdBool = 1) && (firstAttempt == 2 && secondAttempt == 0 && thirdAttempt == 1) && bull != 1) {thirdAttempt=3; thirdBool = 0;}
	if((thirdBool = 1) && (firstAttempt == 2 && secondAttempt == 1 && thirdAttempt == 0) && bull != 1) {thirdAttempt=3; thirdBool = 0;}
	if((thirdBool = 1) && (firstAttempt == 2 && secondAttempt == 3 && thirdAttempt == 0) && bull != 1) {thirdAttempt=1; thirdBool = 0;}
	if((thirdBool = 1) && (firstAttempt == 3 && secondAttempt == 0 && thirdAttempt == 1) && bull != 1) {thirdAttempt=3; thirdBool = 0;}
	if((thirdBool = 1) && (firstAttempt == 3 && secondAttempt == 1 && thirdAttempt == 0) && bull != 1) {thirdAttempt=2; thirdBool = 0;}
	if((thirdBool = 1) && (firstAttempt == 3 && secondAttempt == 2 && thirdAttempt == 0) && bull != 1) {thirdAttempt=2; thirdBool = 0;}
	if(thirdBool==1){
		switch(firstAttempt){
			case 0:
					switch(secondAttempt){
							case 1:{thirdAttempt=2;return "xx"+pattern.substr(2,1)+"x";}
							case 2:{thirdAttempt=1;return "x"+pattern.substr(2,1)+"xx";}
							case 3:{thirdAttempt=1;return "x"+pattern.substr(2,1)+"xx";}
					}		
			case 1:
					switch(secondAttempt){
							case 0:{thirdAttempt=2;return "xx"+pattern.substr(2,1)+"x";}
							case 2:{thirdAttempt=0;return pattern.substr(2,1)+"xxx";}
							case 3:{thirdAttempt=0;return pattern.substr(2,1)+"xxx";}
					}
			case 2:
					switch(secondAttempt){
							case 0:{thirdAttempt=1;return "x"+pattern.substr(2,1)+"xx";}
							case 1:{thirdAttempt=0;return pattern.substr(2,1)+"xxx";}
							case 3:{thirdAttempt=0;return pattern.substr(2,1)+"xxx";}
					}				
			case 3:
					switch(secondAttempt){
							case 0:{thirdAttempt=1;return "x"+pattern.substr(2,1)+"xx";}
							case 1:{thirdAttempt=0;return pattern.substr(2,1)+"xxx";}
							case 2:{thirdAttempt=0;return pattern.substr(2,1)+"xxx";}
					}
		}	
	}
	string finalSolution = "xxxx";
	finalSolution.replace(firstAttempt,1,pattern.substr(0,1));
	finalSolution.replace(secondAttempt,1,pattern.substr(1,1));
	finalSolution.replace(thirdAttempt,1,pattern.substr(2,1));
	for(int i=0; i<4; i++){
		if(finalSolution.at(i) == 'x'){
			finalSolution.replace(i,1,pattern.substr(3,1));
			break;
		}
	}
	//cout<<"finalSolution: "<<finalSolution<<endl;
	return finalSolution;	
}


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

void SmartGuesser::buildPattern(short numberOfBulls){
	uint howManyBulls = 0;
	fourBulls = fourBulls + bull;
	while(howManyBulls < bull){
		pattern += to_string(numberOfBulls);
		howManyBulls++;
	}
}