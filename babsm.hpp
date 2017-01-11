#ifndef __BABSM__
	#define __BABSM__
#endif

#ifndef __CLOCK__
	#include "clock.hpp"
#endif

#ifndef __TAPE__
	#include "tape.hpp"
#endif

#include <vector>


class BorAbsMach{
	private:
		Tape *tpe; // tape is just readonly
		Cell cini; // initial Cell
		AbsClock *aclk; // clock's machine in theory can be changed from outside
		unsigned char EA; // Acepted elemet of tape's alphabet
		unsigned char MV; // actual Movement
		//Auxiliar variables and objects
		Cell ccur;
		std::vector<Cell> borderlist;
		std::vector<Cell> visitclist;
		// aux matrixs
		///////////////////////////////
		Cell *mpos; // position matrix
		//////////////
		char *mdat; // data matrix
		// matrix type
		unsigned char mt; 
		// lenght of mat
		unsigned char ln; 
		// position in matrix
		Cell m9c;
		// matrix flags
		
		//methods
		void genMPos(); // gen position matrix
		void genMDat(); // gen data matrix
		bool nullMDat(); // check data matrix is null (null == !1)
		bool blockMDat(); // check data matrix is blocked (No 0 for mov)
		bool movInMDat(); // movement in mdat with clock
	public:
		BorAbsMach(Tape *t, Cell ci,AbsClock *clk,unsigned char ea);
		~BorAbsMach();
		bool start(); // starts machine
		void reset(); // reset machine
		// especial 
		bool isBorderComplete(); // if complete the both sizes
		bool setBorders(int * dest); //SetBordes
		int getBorderlen(); //border length
};
