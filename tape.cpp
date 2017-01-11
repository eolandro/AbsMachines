/* 
 * implements Tape
 */ 

#include "tape.hpp"


using namespace std;

Tape::Tape(){
	c = 0;
	r = 0;
	mc = 0;
	mr = 0;
	data = NULL;
}

Tape::~Tape(){
	if (data){
		delete[] data;
	}
}
bool Tape::fromPlainPBM(const char* filename){
	//unsigned char buffer[70] = {0};
	unsigned char* buffer =  new unsigned char[70]();
	const char *ret = NULL; // reinterpret cast
	char *tmp = NULL; // simpli tempora
	unsigned char color = '\0';
	long b = 0;
	long l = 0;
	bool end = false;
	bool comment = false;
	ifstream img;
	
	
	img.open(filename);
	
	if (img.fail()){
		return false;
	}
	
	//look for magic identifier
	while (!end) {
		img >> noskipws >> color;
		if (isspace(color)){
			end = true;
			continue;
		}
		
		buffer[b] = color;
		b++;
		if (b == 70){
			end = true;
			continue;
		}
	}
	//check for magic
	ret = strstr(reinterpret_cast <const char* > (buffer),"P1");
	if (!ret){
		return false;
	}
	// if you are here everything is ok
	// reset the buffer
	fill(buffer, buffer+70, 0);
	// get the mc maximun columns
	end = false;
	b = 0;
	while (!end) {
		img >> noskipws >> color;
		if (color == '#'){
			comment = true;
		}
		
		if (!comment){
			if (isspace(color)){
				end = true;
				continue;
			}
			
			buffer[b] = color;
			b++;
			if (b == 70){
				end = true;
				continue;
			}
		}else{
			if (color == '\n' || color == '\r'){
				comment = false;
			}
		}
	}
	// save mc from buffer
	tmp = new char[b+1]();
	ret = reinterpret_cast <const char* > (buffer);
	strncpy(tmp,ret,b);
	mc = atoi(tmp);
	delete[] tmp;
	
	fill(buffer, buffer+70, 0);
	// get the mc maximun columns
	end = false;
	b = 0;
	while (!end) {
		img >> noskipws >> color;
		if (color == '#'){
			comment = true;
		}
		
		if (!comment){
			if (isspace(color)){
				end = true;
				continue;
			}
			
			buffer[b] = color;
			b++;
			if (b == 70){
				end = true;
				continue;
			}
		}else{
			if (color == '\n' || color == '\r'){
				comment = false;
			}
		}
	}
	// save mc from buffer
	tmp = new char[b+1]();
	ret = reinterpret_cast <const char* > (buffer);
	strncpy(tmp,ret,b);
	mr = atoi(tmp);
	delete[] tmp;
	delete[] buffer;
	
	data = new unsigned char[mr*mc];
	l = mr * mc;
	mr--;
	mc--;
	b = 0;
	end = false;
	while (!end){
		img >> noskipws >> color;
		if (!color){
			end = true;
			continue;
		}
		
		if (isspace(color)){
				continue;
		}
		data[b] = color;
		b++;
		if (b == l){
			end = true;
			continue;
		}
	}
	
	img.close();
	if (b != l){
		return false;
	}
	return true;
}

bool Tape::mov(int row,int col){
	bool valid = (col <= mc && col >=0) && (row <= mr && row >= 0);
	if (valid){
		c = col;
		r = row;
		return true;
	}
	return false;
}

bool Tape::mov(Cell c){
	return this->mov(c.row,c.col);
}

unsigned char Tape::get(){
	return data[(r * (mc+1)) + c];
}

int Tape::limitcol(){
	return mc;
}

int Tape::limitrow(){
	return mr;
}
