#include "babsm.hpp"

#include <iostream>


using std::cout;
using std::endl;


BorAbsMach::BorAbsMach(Tape *t, Cell ci,AbsClock *clk,unsigned char ea){
	tpe = t;
	cini = ci;
	aclk = clk;
	EA = ea;
	mt = 0;
	ln = 0;
	ccur = ci;
	MV = '\0';
	mpos = new Cell[1];
	mpos[0].row = 0;
	mpos[0].col = 0;
	mdat = new char[1];
	mdat[0] = '\0';
}

BorAbsMach::~BorAbsMach(){
	borderlist.clear();
	visitclist.clear();
}

void BorAbsMach::reset(){
	ccur = cini;
	borderlist.clear();
	visitclist.clear();
}

void BorAbsMach::genMPos(){
	if (mpos){
		delete[] mpos;
	}
	
	if (ccur.col == 0 && 0 == ccur.row){
		// matrix 2x2
		/*
		 * PC
		 * CC
		 */ 
		mpos = new Cell[4];
		mt = 1;
		//
		mpos[0].row = ccur.row;
		mpos[0].col = ccur.col;
		//
		mpos[1].row = ccur.row;
		mpos[1].col = ccur.col + 1;
		//
		mpos[2].row = ccur.row + 1;
		mpos[2].col = ccur.col;
		//
		mpos[3].row = ccur.row + 1;
		mpos[3].col = ccur.col + 1;
		///////////////////////////
		m9c.row = 0;
		m9c.col = 0;
	}else if(ccur.row == tpe->limitrow() && ccur.col == tpe->limitcol() ){
		// matrix 2x2
		/*
		 * CP
		 * CC
		 */ 
		mpos = new Cell[4];
		mt = 2;
		//
		mpos[0].row = ccur.row;
		mpos[0].col = ccur.col - 1;
		//
		mpos[1].row = ccur.row;
		mpos[1].col = ccur.col;
		//
		mpos[2].row = ccur.row + 1;
		mpos[2].col = ccur.col - 1;
		//
		mpos[3].row = ccur.row + 1;
		mpos[3].col = ccur.col;
		///////////////////////////
		m9c.row = 0;
		m9c.col = 1;
	}else if(ccur.row == tpe->limitrow() && ccur.col == 0 ){
		// matrix 2x2
		/*
		 * CC
		 * PC
		 */ 
		mpos = new Cell[4];
		mt = 3;
		//
		mpos[0].row = ccur.row - 1;
		mpos[0].col = ccur.col;
		//
		mpos[1].row = ccur.row - 1;
		mpos[1].col = ccur.col + 1;
		//
		mpos[2].row = ccur.row;
		mpos[2].col = ccur.col;
		//
		mpos[3].row = ccur.row;
		mpos[3].col = ccur.col + 1;
		///////////////////////////
		m9c.row = 1;
		m9c.col = 0;
	}else if(ccur.row == tpe->limitrow() && ccur.col == 0 ){
		// matrix 2x2
		/*
		 * CC
		 * CP
		 */ 
		mpos = new Cell[4];
		mt = 4;
		//
		mpos[0].row = ccur.row - 1;
		mpos[0].col = ccur.col - 1;
		//
		mpos[1].row = ccur.row - 1;
		mpos[1].col = ccur.col;
		//
		mpos[2].row = ccur.row;
		mpos[2].col = ccur.col - 1;
		//
		mpos[3].row = ccur.row;
		mpos[3].col = ccur.col;
		///////////////////////////
		m9c.row = 1;
		m9c.col = 1;
	}else if (0 == ccur.row){
		/// matrix  2x3
		/*
		 * CPC
		 * CCC
		 */ 
		mpos = new Cell[6];
		mt = 5;
		//----------------------------
		mpos[0].row = ccur.row;
		mpos[0].col = ccur.col - 1;
		//
		mpos[1].row = ccur.row;
		mpos[1].col = ccur.col;
		//
		mpos[2].row = ccur.row;
		mpos[2].col = ccur.col + 1;
		//----------------------------
		mpos[3].row = ccur.row + 1;
		mpos[3].col = ccur.col - 1;
		//
		mpos[4].row = ccur.row + 1;
		mpos[4].col = ccur.col;
		//
		mpos[5].row = ccur.row + 1;
		mpos[5].col = ccur.col + 1;
		
		///////////////////////////
		m9c.row = 0;
		m9c.col = 1;
	}else if(ccur.col == 0){
		/// matrix  3x2
		/*
		 * CC
		 * PC
		 * CC
		 */ 
		mpos = new Cell[6];
		mt = 6;
		//----------------------------
		mpos[0].row = ccur.row - 1;
		mpos[0].col = ccur.col;
		
		mpos[1].row = ccur.row - 1;
		mpos[1].col = ccur.col + 1;
		//----------------------------
		mpos[2].row = ccur.row;
		mpos[2].col = ccur.col;
		
		mpos[3].row = ccur.row;
		mpos[3].col = ccur.col + 1;
		//----------------------------
		mpos[4].row = ccur.row + 1;
		mpos[4].col = ccur.col;
		
		mpos[5].row = ccur.row + 1;
		mpos[5].col = ccur.col + 1;
		///////////////////////////
		m9c.row = 1;
		m9c.col = 0;
	}else if (ccur.row == tpe->limitrow()){
		/// matrix  2x3
		/*
		 * CCC
		 * CPC
		 */ 
		mpos = new Cell[6];
		mt = 7;
		//----------------------------
		mpos[0].row = ccur.row - 1;
		mpos[0].col = ccur.col - 1;
		//
		mpos[1].row = ccur.row - 1;
		mpos[1].col = ccur.col;
		//
		mpos[2].row = ccur.row - 1;
		mpos[2].col = ccur.col + 1;
		//----------------------------
		mpos[3].row = ccur.row;
		mpos[3].col = ccur.col - 1;
		//
		mpos[4].row = ccur.row;
		mpos[4].col = ccur.col;
		//
		mpos[5].row = ccur.row;
		mpos[5].col = ccur.col + 1;
		
		///////////////////////////
		m9c.row = 1;
		m9c.col = 1;
	}else if (ccur.col == tpe->limitcol()){
		/// matrix  3x2
		/*
		 * CC
		 * CP
		 * CC
		 */ 
		mpos = new Cell[6];
		mt = 8;
		//----------------------------
		mpos[0].row = ccur.row - 1;
		mpos[0].col = ccur.col - 1;
		
		mpos[1].row = ccur.row - 1;
		mpos[1].col = ccur.col;
		//----------------------------
		mpos[2].row = ccur.row;
		mpos[2].col = ccur.col - 1;
		
		mpos[3].row = ccur.row;
		mpos[3].col = ccur.col;
		//----------------------------
		mpos[4].row = ccur.row + 1;
		mpos[4].col = ccur.col - 1;
		
		mpos[5].row = ccur.row + 1;
		mpos[5].col = ccur.col;
		///////////////////////////
		m9c.row = 1;
		m9c.col = 1;
	}else{
		/// matrix  3x3
		mpos = new Cell[9];
		mt = 9;
		//----------------------------
		mpos[0].row = ccur.row - 1;
		mpos[0].col = ccur.col - 1;
		
		mpos[1].row = ccur.row - 1;
		mpos[1].col = ccur.col;
		
		mpos[2].row = ccur.row - 1;
		mpos[2].col = ccur.col + 1;
		//----------------------------
		mpos[3].row = ccur.row;
		mpos[3].col = ccur.col - 1;
		
		mpos[4].row = ccur.row;
		mpos[4].col = ccur.col;
		
		mpos[5].row = ccur.row;
		mpos[5].col = ccur.col + 1;
		//----------------------------
		mpos[6].row = ccur.row + 1;
		mpos[6].col = ccur.col - 1;
		
		mpos[7].row = ccur.row + 1;
		mpos[7].col = ccur.col;
		
		mpos[8].row = ccur.row + 1;
		mpos[8].col = ccur.col + 1;
		//----------------------------
		///////////////////////////
		m9c.row = 1;
		m9c.col = 1;
	}
}

void BorAbsMach::genMDat(){
	int c = 0;
	unsigned char tmpc = '\0';
	if (mdat){
		delete[] mdat;
	}
	
	if (mt == 0){
		return;
	}else if(mt <= 4){
		ln = 4;
		mdat = new char[4];
	}else if(mt >= 5 && mt <= 8){
		ln = 6;
		mdat = new char[6];
	}else{
		ln = 9;
		mdat = new char[9];
	}
	
	for (c = 0; c < ln; c++){
		tpe->mov(mpos[c]);
		tmpc = tpe->get();
		mdat[c] = (EA == tmpc) ? 1 : 0;
	}
	
	// we need the last visit point for that we use the mpos
	// and mdat at the same time
	int cnt = 0;
	int i = 0;
	int vlt = visitclist.size();
	Cell tmp;
	/*
	 
	 */ 
	 
	if(vlt > 0){
		for(cnt = 0; cnt < vlt; cnt++){
			tmp = visitclist.at(cnt);
			for (i = 0; i < ln; i++){
				if (mpos[i].col == tmp.col && mpos[i].row == tmp.row){
					mdat[i] = -1;
				}
			}
		}
	}
}

bool BorAbsMach::nullMDat(){
	int c = 0;
	int i = 0;
	for (i = 0; i < ln; i++){
		if (mdat[i] == 1){
			c++;
		}
	}
	return (c == 0)? true : false; 
}


bool BorAbsMach::blockMDat(){
	int aux1 = 0;
	int aux2 = 0;
	int aux3 = 0;
	int aux4 = 0;
	switch(mt){
		case 0:
			return true;
		break;
		/////////////////////////////////////////
		case 1:
			// matrix 2x2
			/*
			 * PC
			 * CC
			 */ 
			//  M[f,c-1] M[f-1,c]
			aux1 = ((m9c.row)* 2 ) + m9c.col + 1;
			aux2 = ((m9c.row +1 )* 2  ) + m9c.col;
			if (mdat[aux1] == 0 || mdat[aux2] == 0){
				return false;
			}
		break;
		/////////////////////////////////////////
		case 2:
			// matrix 2x2
			/*
			 * CP
			 * CC
			 */ 
			//  M[f,c-1] M[f-1,c]
			aux1 = ((m9c.row)* 2 ) + m9c.col - 1;
			aux2 = ((m9c.row +1 )* 2 ) + m9c.col;
			if (mdat[aux1] == 0 || mdat[aux2] == 0){
				return false;
			}
		break;
		/////////////////////////////////////////
		case 3:
			// matrix 2x2
			/*
			* CC
			* PC
			*/ 
			aux1 = ((m9c.row)* 2 ) + m9c.col + 1;
			aux2 = ((m9c.row -1 )* 2 ) + m9c.col;
			if (mdat[aux1] == 0 || mdat[aux2] == 0){
				return false;
			}
			
		break;
		/////////////////////////////////////////
		case 4:
			// matrix 2x2
			/*
			 * CC
			 * CP
			 */ 
			aux1 = ((m9c.row)* 2 ) + m9c.col - 1;
			aux2 = ((m9c.row -1 )* 2 ) + m9c.col;
			if (mdat[aux1] == 0 || mdat[aux2] == 0){
				return false;
			}
		break;
		/////////////////////////////////////////
		case 5:
			/// matrix  2x3
			/*
			 * CPC
			 * CCC
			 */ 
			aux1 = ((m9c.row)* 2 ) + m9c.col - 1;
			aux2 = ((m9c.row)* 2 ) + m9c.col + 1;
			aux3 = ((m9c.row + 1 )* 2 ) + m9c.col;
			if (mdat[aux1] == 0 || mdat[aux2] == 0 || mdat[aux3] == 0){
				return false;
			}
		break;
		/////////////////////////////////////////
		case 6:
			/// matrix  3x2
			/*
			* CC
			* PC
			* CC
			*/ 
			aux1 = ((m9c.row ) * 3 ) + m9c.col + 1;
			aux2 = ((m9c.row +1 )* 3 ) + m9c.col;
			aux3 = ((m9c.row -1 )* 3 ) + m9c.col;
			if (mdat[aux1] == 0 || mdat[aux2] == 0 || mdat[aux3] == 0){
				return false;
			}
		break;
		/////////////////////////////////////////
		case 7:
			/// matrix  2x3
			/*
			 * CCC
			 * CPC
			 */ 
			aux1 = ((m9c.row) * 2 ) + m9c.col - 1;
			aux2 = ((m9c.row) * 2 ) + m9c.col + 1;
			aux3 = ((m9c.row -1 ) * 2 ) + m9c.col;
			if (mdat[aux1] == 0 || mdat[aux2] == 0 || mdat[aux3] == 0){
				return false;
			}
			
		break;
		/////////////////////////////////////////
		case 8:
			/// matrix  3x2
			/*
			 * CC
			 * CP
			 * CC
			 */ 
			aux1 = ((m9c.row)* 3 ) + m9c.col - 1;
			aux2 = ((m9c.row +1 )* 3 ) + m9c.col;
			aux3 = ((m9c.row -1 )* 3 ) + m9c.col;
			if (mdat[aux1] == 0 || mdat[aux2] == 0 || mdat[aux3] == 0){
				return false;
			}
		break;
		/////////////////////////////////////////
		case 9:
			/// matrix  3x3
			aux1 = ((m9c.row)* 3 ) + m9c.col - 1;
			aux4 = ((m9c.row)* 3 ) + m9c.col + 1;
			aux2 = ((m9c.row +1 )* 3 ) + m9c.col;
			aux3 = ((m9c.row -1 )* 3 ) + m9c.col;
			if (mdat[aux1] == 0 || mdat[aux2] == 0 || mdat[aux3] == 0 || mdat[aux4] == 0){
				return false;
			}
		break;
	}
	return true;
}

bool BorAbsMach::movInMDat(){
	bool isnullMat = false;
	bool isblckMat = false;
	
	
	isnullMat = nullMDat();
	isblckMat = blockMDat();
	
	if(isnullMat || isblckMat){
		return false; // false by block or null state
	}
	
	int aux = 0;
	int mr = 0;
	int mc = 0;
	switch(mt){
		case 0:
			return true;
		break;
		case 1:
		case 2:
		case 3:
		case 4:
			mr = 1; // maximun row in 2x2
			mc = 1; // maximun col in 2x2
		break;
		
		case 5:
		case 7:
			mr = 1;
			mc = 2;
		break;
		
		case 6:
		case 8:
			mr = 2;
			mc = 1;
		break;
		default:
			mc = 2;
			mr = 2;
	}
	
	if (MV == 'A'){
		if (m9c.row == 0){
			return false;
		}else{
			//if M[f+1,c] == 0 or M[f,c+1] == 0:
			aux = ((m9c.row - 1 )*( mr + 1) ) + m9c.col;
			if (mdat[aux] == -1 || mdat[aux] == 1){
				return false;
			}
			m9c.row--;
			ccur.row--;
		}
	}
	if (MV == 'V'){
		if (m9c.row == mr){
			return false;
		}else{
			//if DT[f+1][c] == -1 or DT[f+1][c] == 1 :
			aux = ((m9c.row + 1)*( mr + 1) ) + m9c.col;
			if (mdat[aux] == -1 || mdat[aux] == 1){
				return false;
			}
			m9c.row++;
			ccur.row++;
		}
	}
	if (MV == '<'){
		if (m9c.col == 0){
			return false;
		}else{
			//if DT[f][c-1] == -1 or DT[f][c-1] == 1:
			aux = ((m9c.row )*( mr + 1) ) + m9c.col -1 ;
			if (mdat[aux] == -1 || mdat[aux] == 1){
				return false;
			}
			m9c.col--;
			ccur.col--;
		}
			
	}
	if (MV == '>'){
		if (m9c.col == mc){
			return false;
		}else{
			//if DT[f][c+1] == -1 or DT[f][c+1] == 1:
			aux = ((m9c.row )*( mr + 1) ) + m9c.col +1 ;
			if (mdat[aux] == -1 || mdat[aux] == 1){
				return false;
			}
			m9c.col++;
			ccur.col++;
		}
	}
	return true;
}

bool BorAbsMach::start(){
	
	bool isnullMat = false;
	bool isblckMat = false;
	// No tape no start
	if (!tpe){
		return false;
	}
	
	
	// check for valid cini
	if (cini.col < 0 || cini.row < 0){
		return false;
	}else if(cini.col > tpe->limitcol() || cini.row > tpe->limitrow() ){
		return false;
	}
	
	//clock ready
	aclk->reset();
	
	ccur.row =  cini.row;
	ccur.col =  cini.col;
	
	this->genMPos();
	this->genMDat();
	
	isnullMat = nullMDat();
	isblckMat = blockMDat();
	
	if(isnullMat || isblckMat){
		return false; // false by block or null state
	}
	
	
	MV = aclk->nextStep();
	///////////////////////////////////////
	bool rollback = false;
	/////////////////////////////
	
	while (true){
		int dblock = 0; // block detector
		int dnull = 0;
		int fromback = 0; // carri positon of border from back
		bool movEnded = false; // Movement ended
		Cell tmp;
		//save last current cell
		tmp.col = ccur.col;
		tmp.row = ccur.row;
		
		// this is loop of movement on block matrix ended with true
		while (!movEnded){
			// we try to move with the clock
			if(movInMDat()){
				movEnded = true;
			}else{ 
				// if can not move we check if we are in a block or null
				//cout << m9c.row << " " << m9c.col << endl;
				isblckMat = blockMDat();
				isnullMat = nullMDat();
				// if we are in block
				if(isblckMat){ 
					if(dblock == 0){ //  check if it is first block
						// and add to visit points
						visitclist.push_back(ccur);
					}
					
					// we take last one the first time
					// and the element before last one second time
					// and element before before last one third time
					// and so on we soport many rollbacks
					if (dblock == 0){
						fromback = borderlist.size() -1 ;
					}else{
						fromback--;
					}
					
					// can not rollback from negative
					// there is not enogth elements
					if (fromback < 0){
						return true;
					}else{
						//back to another point
						ccur = borderlist.at(fromback);
						// recover to older matrix
						this->genMPos();
						this->genMDat();
						//activate rollback control
						rollback = true;
						MV = aclk->nextStep();
						MV = aclk->nextStep();
					}
					// incremente the times in block
					dblock++;
				}
				// if we are in null
				// null is special it can done only a single rollback
				
				if (isnullMat){
					//reset block just for give some chances
					//dblock = 0; 
					// rollback simple
					// and add to visit points
					visitclist.push_back(ccur);
					// take the last one
					if (dnull == 0){
						fromback = borderlist.size() -1 ;
					}else{
						fromback--;
					}
					// can not rollback from negative
					if (fromback < 0){
						return true;
					}else{
						//back to another point
						ccur = borderlist.at(fromback);
						// recover to older matrix
						this->genMPos();
						this->genMDat();
						//activate rollback control
						rollback = true;
						MV = aclk->nextStep();
						MV = aclk->nextStep();
					}
					dnull++;
				}
				// five block continues means we are stock
				if (dblock > 4){
					return true;
				}
				// five null continues means we are stock
				if (dnull > 4){
					return true;
				}
			}
			// we try another movement
			MV = aclk->nextStep();
		}
		// if we are here we could move
		if (!rollback){
			borderlist.push_back(tmp);
			visitclist.push_back(tmp);
		}else{
			rollback = false;
		}
		
		/////////////////////////////////////////////////
		/////////////////////////////////////////////////////////
		// if we arrive to we start done
		if (cini.col == ccur.col && cini.row == ccur.row){
			return true;
		}
		// if we arrive to we start done
		//if (tmp.col == ccur.col && tmp.row == ccur.row){
		//	return true;
		//}
		// we generate the new matrix
		this->genMPos();
		this->genMDat();
		
		isnullMat = nullMDat();
		isblckMat = blockMDat();

	}
	//maybe we never go here
	return true; 
}

bool BorAbsMach::isBorderComplete(){
	int l = borderlist.size();
	int dc = 0;
	int dr = 0;
	if (l==0){
		return false;
	}
	Cell beg, end;
	beg = borderlist.at(0);
	end = borderlist.at(l-1);
	
	dc = beg.col - end.col;
	dc = (dc > 0)? dc : dc * -1;
	dr = beg.row - end.row;
	dr = (dr > 0)? dr : dr * -1;
	if (dc >= 2 || dr >= 2){
		return false;
	}
	return true;
}

bool BorAbsMach::setBorders(int * dest){
	int l = borderlist.size();
	if (l==0){
		return false;
	}
	
	// we need the last visit point for that we use the mpos
	// and mdat at the same time
	int i = 0;
	int j = 0; // for row in dest
	int k = 1; // for col in dest
	int blt = borderlist.size();
	Cell tmp;
	
	for (i = 0; i < blt; i++){
		tmp = borderlist.at(i);
		dest[j] = tmp.row;
		dest[k] = tmp.col;
		j+=2;
		k+=2;
	}
	
	return true;
}
int BorAbsMach::getBorderlen(){
	return borderlist.size()*2;
}
