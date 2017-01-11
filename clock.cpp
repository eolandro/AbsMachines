/*
 * implements AbsClock
 */ 


#include "clock.hpp"

AbsClock::AbsClock(){
	step = 0;
	clockwise = true;
}


void AbsClock::reset(){
	step = 0;
}

void AbsClock::setClockwise(bool wise){
	clockwise = wise;
}

bool AbsClock::getClockwise(){
	return clockwise;
}

char AbsClock::nextStep(){
	if (clockwise){
		// step is increment
		if (step == 4){
			step = 0;
		}
		return clk_hands[step++];
	}else{
		if (step == -1){
			step = 3;
		}
		return clk_hands[step--];
	}
}
