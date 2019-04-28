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
		ConstantChooser c0{"0"}, c1{"3456"}, c1234{"1234"}, c12345{"12345"}, c9999{"9999"};
		ConstantGuesser g0{"0"}, g1{"3456"}, g1234{"1234"}, g12345{"12345"}, g9999{"9999"};

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
		
		ConstantChooser c0000{"8950"};
		testcase.CHECK_EQUAL(play(c0000, smarty, 4, 100)<=10, true);
		
		
		testcase.setname("<4 length")
		.CHECK_OUTPUT(calculateBullAndPgia("9","8"), "0,0")
		.CHECK_OUTPUT(calculateBullAndPgia("1","1"), "1,0")
		.CHECK_OUTPUT(calculateBullAndPgia("45","45"), "2,0")
		.CHECK_OUTPUT(calculateBullAndPgia("87","79"), "0,1")
		.CHECK_OUTPUT(calculateBullAndPgia("75","57"), "0,2")
		.CHECK_OUTPUT(calculateBullAndPgia("9999","9999"), "4,0")
		.CHECK_OUTPUT(calculateBullAndPgia("1573","1875"), "2,1")
		.CHECK_OUTPUT(calculateBullAndPgia("1223","1213"), "3,1");
		testcase.setname(">4 length")
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
		;
		

    grade = testcase.grade();
	} else {
		testcase.print_signal(signal);
		grade = 0;
	}
	cout << "Your grade is: "  << grade << endl;
	return 0;
}

