#include "dabsm.hpp"

DisAbsMach::DisAbsMach(Tape *cta, Cell ci,const char * lenreg, const char* movi,unsigned char ea){
	tpe = cta;
	ccur = ci;
	cini = ci;
	LRMV = lenreg;
	MV = movi;
	CM = new char[strlen(movi)]{};
	strcpy(CM,movi);
	lcm = movi[0];
	EA = ea;
	ind = 0;
	foundit = false;
}

DisAbsMach::~DisAbsMach(){
	if (CM){
		delete[] CM;
	}
	LRMV = NULL;
	tpe = NULL;
	MV = NULL;
	EA = 0;
	foundit = false;
	ind = 0;
	lcm = 0;
}

void DisAbsMach::trans(){
	//////////////////
	if(ind ==  2){
		ind = 0;
	}
	///////////
	lcm = CM[ind];
	
	switch(lcm){
		case 'A':
			if (ccur.row == 0){
				CM[ind] = 'V';
			}else{
				ccur.row--;
			}
		break;
		case 'V':
			if (ccur.row == tpe->limitrow()){
				CM[ind] = 'A';
			}else{
				ccur.row++;
			}
		break;
		case '>':
			if (ccur.col == tpe->limitcol()){
				CM[ind] = '<';
			}else{
				ccur.col++;
			}
		break;
		case '<':
			if (ccur.col == 0){
				CM[ind] = '>';
			}else{
				ccur.col--;
			}
		break;
	}
	ind++;
}


bool DisAbsMach::start(){
	if (!tpe){
		return false;
	}
	
	std::regex lang(LRMV);
	bool Terminado = false;
	
	// languaje and movement string are not valid
	if (!std::regex_match(MV,lang)){
		return foundit = false;
	}
	
	// check for valid cini
	if (cini.col < 0 || cini.row < 0){
		return foundit = false;
	}else if(cini.col > tpe->limitcol() || cini.row > tpe->limitrow() ){
		return foundit = false;
	}
	
	// movement to initial cel
	tpe->mov(ccur);
	if (tpe->get()== EA){
		return foundit = true;
	}
	// if not will get stock
	while(!Terminado){
		this->trans();
		tpe->mov(ccur);
		if (tpe->get()== EA){
			Terminado = true;
		}
	}
	
	return foundit = true;
}

void DisAbsMach::reset(){
	ccur = cini;
	delete[] CM;
	CM = new char[strlen(MV)]{};
	strcpy(CM,MV);
	foundit = false;
	ind = 0;
	lcm = CM[0];
}

bool DisAbsMach::getBorder(Cell &b){
	if (!foundit){
		return false;
	}
	
	// copy values
	b.row = ccur.row;
	b.col = ccur.col;
	
	switch (lcm){
		case 'A':
			b.row++;
		break;
		case 'V':
			b.row--;
		break;
		case '<':
			b.col++;
		break;
		case '>':
			b.col--;
		break;
	}
	return true;
}
