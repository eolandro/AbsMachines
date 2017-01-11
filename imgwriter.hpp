#ifndef __IMGWRITER__
	#define __IMGWRITER__
#endif

#include <iostream>
#include <fstream>

class ImgWriter{
	public:
		static bool savePlainPBM(const char * filename, int * src, int len, int width, int height);
};
