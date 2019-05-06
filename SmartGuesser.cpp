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
//using namespace std;
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


void SmartGuesser::learn(string str) {
	bull = stoi(str.substr(0,1),nullptr,10);
	pgia = stoi(str.substr(2,1),nullptr,10);
}

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
	//cout<<"finalSolution: "<<finalSolution<<endl;
	return finalSolution;
}

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

string SmartGuesser::checkPatternForThree(){
	while(index < 5){
		switch(index)
		{
			case 0:{index++;return "012";}
			case 1:{firstAttempt=bull+pgia;index++;return "345";}
			case 2:{secondAttempt=bull+pgia;index++;return "678";}
			case 3:{thirdAttempt=bull+pgia;index++;if(firstAttempt+secondAttempt+thirdAttempt!=3)return "999";}
			default:{if (bull!=0)fourthAttempt=bull;index++;}
		}
	}
	short array [] = {firstAttempt,firstAttempt,firstAttempt,secondAttempt,secondAttempt,secondAttempt,thirdAttempt,thirdAttempt,thirdAttempt,fourthAttempt};
	cout<<"bull:"<<bull<<endl;    
	if(pattern.size()<3){
		while(index2>=0 && bull>0){
			pattern+=to_string(index2);
			bull--;
			cout<<"pt:"<<pattern<<endl;
		}
		while(index2<10){
			index2++;
			if(array[index2]>0){
			cout<<"index:"<<index2<<endl;
				return to_string(index2)+to_string(index2)+to_string(index2);
			}
		}
	}
			cout<<"----------------:"<<endl;
	/*if(pattern.size()<3){
		while(index2>=0 && bull>0){
			pattern+=to_string(index2);
			bull--;
			switch (index2){
				case 0:case 1:case 2: if (bull==1 && firstAttempt>0)firstAttempt--;
				case 3:case 4:case 5: if (bull==1 && secondAttempt>0)secondAttempt--;
				case 6:case 7:case 8: if (bull==1 && thirdAttempt>0)thirdAttempt--;
				default :if (bull==1 && fourthAttempt>0)fourthAttempt--;
			}
		}
		while(index2<10){
			index2++;
			if(array[index2]>0){
				switch (index2){
				case 0:case 1:case 2: if (firstAttempt!=0)return to_string(index2)+to_string(index2)+to_string(index2);
				case 3:case 4:case 5: if (secondAttempt!=0){ return to_string(index2)+to_string(index2)+to_string(index2);}
				case 6:case 7:case 8: if (thirdAttempt!=0)return to_string(index2)+to_string(index2)+to_string(index2);
				default :if (fourthAttempt!=0)return to_string(index2)+to_string(index2)+to_string(index2);
				}
			}
		}
	}*/
	/*if (firstAttempt+secondAttempt+thirdAttempt+fourthAttempt==0){
	string final = "";
	for (int i=0;i<2;i++){
		if (i=0)
		return pattern.substr(i,1)+"aa";
		if (i=1)  
		return "a"+ pattern.substr(i,1) +"a";
		if (i=2)
		return "aa"+ pattern.substr(i,1);
		if (bull==1)
			final+=pattern.substr(i,1);
	}*/
	return "000";
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