/*
 * this class define the clock of an abstract machine.
 * The clocks have severals functions on the abstract machice, for 
 * example 
 * the clock permits the movement of the machine
 */ 

#ifndef __CLOCK__
	#define __CLOCK__
#endif


class AbsClock {
	private:
		unsigned char clk_hands[4] =  {'A','>','V','<'};
		int step;
		bool clockwise;
	public:
		AbsClock();
		void reset();
		void setClockwise(bool wise);
		bool getClockwise();
		char nextStep();
};
