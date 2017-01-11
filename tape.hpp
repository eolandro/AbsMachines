/*
 * This class means the basic struct Cell
 * which one defines one Cell of the Tape 
 */
 
#ifndef __TAPE__
	#define __TAPE__
#endif

#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
 
 union Cell{
	 struct {
		 int row;
		 int col;
	 }; 
	 int data[2];
 };
	 


/*
 * this class define the Tape of an abstract machine.
 * It is a bidimensional Tape 
 * The Tape is build it from a image
 * The basic suport is pbm image but pgm and pgm is comming
 */ 


class Tape{
	private:
		int c,r;
		int mc,mr;
		unsigned char *data;
	public:
		Tape();
		~Tape();
		bool fromPlainPBM(const char* filename);
		bool mov(int row,int col);
		bool mov(Cell c);
		unsigned char get();
		int limitcol();
		int limitrow();
};
