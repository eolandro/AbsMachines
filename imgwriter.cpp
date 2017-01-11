#include "imgwriter.hpp"

using namespace std;

bool ImgWriter::savePlainPBM(const char * filename, int * src, int len, int width, int height){
	int lndata = width * height;
	if (width == 0){
		return false;
	}
	
	if (height == 0){
		return false;
	}
	
	char *data = new char[ lndata ]{'0'};
	int i = 0;
	
	
	for (i = 0; i < lndata; i++){
		data[i] = '0';
	}
	for (i = 0; i < len; i+=2){
		data[ ( ( src[i] * width ) + src[ i + 1] )] = '1';
	}
	
	/////////////////////////////////////////
	ofstream img;
	img.open (filename);
	if (img.fail()){
		return false;
	}
	
	
	img << "P1" << endl;
	img << "#eolan chart" << endl;
	img <<  width << " " << height <<endl;
	
	
	int j = 0;
	for (i = 0; i < lndata; i++){
		img << data[i];
		j++;
		if(j == 70){
			img << endl;
			j = 0;
		}
	}
	img << endl;
	img.close();
	
	
	
	return true;
}
