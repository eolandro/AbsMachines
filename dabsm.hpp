#ifndef __DABSM__
	#define __DABSM__
#endif

#ifndef __CLOCK__
	#include "clock.hpp"
#endif

#ifndef __TAPE__
	#include "tape.hpp"
#endif

#include <regex>
#include <cstring>

/*
 * This is the discover abstract machine
 * 
 * it is kind of useless but important, it is the base of 
 *  border abstract machine
 * 
 * this machine require one valid tape, one Cell of that tape,
 * the regular languaje string (regex), a movement string (acepted by 
 * the regular languaje) and the acepted simbol of the tape 
 * (almost the time is "1" but can be changed)
 * 
 * 
 */ 


class DisAbsMach{
	private:
		Tape *tpe;
		Cell cini; // initial Cell
		Cell ccur; // current Cell
		const char* LRMV; // Regular Languaje of movement
		const char* MV; // Movement string
		char* CM; // Current Movement string
		unsigned char EA; // Acepted elemet of tape's alphabet
		bool foundit; // We found the border
		int ind;
		char lcm;  // last char of movement
		void trans(); // transition function
	public:
		DisAbsMach(Tape *tp, Cell ci,const char * lenreg, const char* movi,unsigned char ea);
		~DisAbsMach();
		bool start(); // start machine
		void reset(); // reset machine
		// especial
		bool getBorder(Cell &b); // get value of border
};
