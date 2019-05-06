/**
 * A demo program for bull-pgia.
 * 
 * @author Erel Segal-Halevi
 * @since  2019-04
 */


#include <iostream>
using namespace std;

#include "play.hpp"
#include "calculate.hpp"
#include "DummyChoosers.hpp"
#include "DummyGuessers.hpp"
#include "SmartGuesser.hpp"
#include "badkan.hpp"
#define COMMA ,

using namespace bullpgia;

int main() {

	badkan::TestCase testcase;
	int grade=0;
	int signal = setjmp(badkan::longjmp_buffer);
	if (signal == 0) {

		// BASIC TESTS - DO NOT CHANGE
		ConstantChooser c0{"0"}, c1{"3456"}, c1234{"1234"}, c12345{"12345"}, c9999{"9999"}, c5678{"5678"}, c55555{"55555"},c01234{"01234"}, c155{"155"};
		ConstantGuesser g0{"0"}, g1{"3456"}, g1234{"1234"}, g12345{"12345"}, g9999{"9999"}, g5678{"5678"}, g55555{"55555"},g01234{"01234"};


		testcase.setname("Calculate bull and pgia")
		.CHECK_OUTPUT(calculateBullAndPgia("1234","1234"), "4,0")      // 4 bull, 0 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("1234","4321"), "0,4")      // 0 bull, 4 pgia
		;

		testcase.setname("Play with dummy choosers and guessers")
		.CHECK_EQUAL(play(c1234, g1234, 4, 100), 1)      // guesser wins in one turn.
		.CHECK_EQUAL(play(c1234, g9999, 4, 100), 101)    // guesser loses by running out of turns 
		.CHECK_EQUAL(play(c1234, g12345, 4, 100), 101)   // guesser loses technically by making an illegal guess (too long).
		.CHECK_EQUAL(play(c12345, g1234, 4, 100), 0)     // chooser loses technically by choosing an illegal number (too long).
		;
	
		testcase.setname("Play with smart guesser");
		RandomChooser randy;
		SmartGuesser smarty;
		for (uint i=0; i<100; ++i) {
			testcase.CHECK_EQUAL(play(randy, smarty, 4, 100)<=100, true);  // smarty should always win in at most 10 turns!
		}
		
		//Our tests:
		//test digits that arent found in the guesse string
		//test repeated digit in the guesse string
		//test repeated digit that are not found in the guesse string
		//more casual tests
		
		testcase.setname("<4 length")
		.CHECK_OUTPUT(calculateBullAndPgia("9","8"), "0,0")
		.CHECK_OUTPUT(calculateBullAndPgia("1","1"), "1,0")
		.CHECK_OUTPUT(calculateBullAndPgia("45","45"), "2,0")
		.CHECK_OUTPUT(calculateBullAndPgia("87","79"), "0,1")
		.CHECK_OUTPUT(calculateBullAndPgia("75","57"), "0,2")
		.CHECK_OUTPUT(calculateBullAndPgia("8977", "7970"), "2,1")
		.CHECK_OUTPUT(calculateBullAndPgia("1211", "2111"), "2,2")
		.CHECK_OUTPUT(calculateBullAndPgia("8977", "7908"), "1,2")
		.CHECK_OUTPUT(calculateBullAndPgia("9999","9999"), "4,0")
		.CHECK_OUTPUT(calculateBullAndPgia("1573","1875"), "2,1")
		.CHECK_OUTPUT(calculateBullAndPgia("1223","1213"), "3,0")
		.CHECK_OUTPUT(calculateBullAndPgia("0000", "1000"), "3,0")
		.CHECK_OUTPUT(calculateBullAndPgia("1110", "1010"), "3,0")
		;

		testcase.setname(">4 length")  
		.CHECK_OUTPUT(calculateBullAndPgia("23456", "44444"), "1,0")
		.CHECK_OUTPUT(calculateBullAndPgia("56789", "55555"), "1,0")
		.CHECK_OUTPUT(calculateBullAndPgia("15973", "99999"), "1,0")
		.CHECK_OUTPUT(calculateBullAndPgia("56789", "98675"), "0,5")
		.CHECK_OUTPUT(calculateBullAndPgia("56789", "58796"), "2,3")
		.CHECK_OUTPUT(calculateBullAndPgia("12345", "12345"), "5,0")
		.CHECK_OUTPUT(calculateBullAndPgia("12345", "21436"), "0,4")
		.CHECK_OUTPUT(calculateBullAndPgia("12345", "99129"), "0,2")
		.CHECK_OUTPUT(calculateBullAndPgia("84592", "84952"), "3,2")
		.CHECK_OUTPUT(calculateBullAndPgia("56789", "56789"), "5,0")
		.CHECK_OUTPUT(calculateBullAndPgia("85258", "11111"), "0,0")
		.CHECK_OUTPUT(calculateBullAndPgia("3456789","3456789"), "7,0")
		.CHECK_OUTPUT(calculateBullAndPgia("789654","000124"), "1,0")
		.CHECK_OUTPUT(calculateBullAndPgia("0002000","1112111"), "1,0")
		.CHECK_OUTPUT(calculateBullAndPgia("11548491111","00100000076"), "0,1")
		.CHECK_OUTPUT(calculateBullAndPgia("987632100","001236789"), "1,8") 
		.CHECK_OUTPUT(calculateBullAndPgia("852852857","852852857"), "9,0")
		;
		
		testcase.setname("play test")
		.CHECK_EQUAL(play(c1234, g1234, 4, 5), 1)
		.CHECK_EQUAL(play(c0, g0, 1, 5), 1)
		.CHECK_EQUAL(play(c1234, g0, 1, 5), 0)
		.CHECK_EQUAL(play(c0, g12345, 1, 100), 101)
		.CHECK_EQUAL(play(c5678, g5678, 4, 100), 1)
		.CHECK_EQUAL(play(c1, g9999, 4, 100), 101)    
		.CHECK_EQUAL(play(c12345, g55555, 4, 100), 0)  	
		.CHECK_EQUAL(play(c1234, g55555, 4, 100), 101)   
		.CHECK_EQUAL(play(c0, g55555, 4, 100), 0)   
		.CHECK_EQUAL(play(c9999, g9999, 4, 100), 1)  
		.CHECK_EQUAL(play(c01234, g01234, 4, 100), 0)
		.CHECK_EQUAL(play(c12345, g01234, 4, 100), 0)    
		;
		
		ConstantChooser myRandy{"8950"};
		testcase.CHECK_EQUAL(play(myRandy, smarty, 4, 100)<=100, true);

		for (uint i=0; i<50; ++i) {
			testcase.CHECK_EQUAL(play(randy, smarty, 4, 100)<=20, true);  
		}	

		for (uint i=0; i<20; ++i) {
			testcase.CHECK_EQUAL(play(randy, smarty, 1, 10)<=10, true);  
		}	
		
		for (uint i=0; i<20; ++i) {
			testcase.CHECK_EQUAL(play(randy, smarty, 2, 10)<=10, true);  
		}
		
		for (uint i=0; i<20; ++i) {
			testcase.CHECK_EQUAL(play(randy, smarty, 3, 10)<=20, true);  
		}
					//testcase.CHECK_EQUAL(play(c155, smarty, 3, 10)<=20, true);  

			
    grade = testcase.grade();
	} else {
		testcase.print_signal(signal);
		grade = 0;
	}
	cout << "Your grade is: "  << grade << endl;
	return 0;
}

