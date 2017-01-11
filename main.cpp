#include "clock.hpp"
#include "tape.hpp"
#include "dabsm.hpp"
#include "babsm.hpp"
#include "imgwriter.hpp"
#include <iostream>


using std::cout;
using std::endl;

int main(){
	AbsClock *clk = new AbsClock();
	//int c = 0;
	//int r = 0;
	bool found = false;
	bool dostar = false;
	// the Tape needs dinamic memory
	
	Tape *mt = new Tape();
	//mt->fromPlainPBM("test/test.pbm");
	//mt->fromPlainPBM("test/circle70.pbm");
	//mt->fromPlainPBM("test/surface.pbm");
	//mt->fromPlainPBM("test/trian.pbm");
	//mt->fromPlainPBM("test/ojo.pbm");
	mt->fromPlainPBM("test/ojo2.pbm");
	//c = mt->limitcol();
	//r = mt->limitrow();
	// initial Cell
	Cell initialCell;
	initialCell.row = 0;
	initialCell.col = 0;
	
	// discover abstract machine
	DisAbsMach *DiscoverMach = new DisAbsMach(mt,initialCell,"[AV][<>]","V>",'1');
	found = DiscoverMach->start();
	Cell border;
	if (found){
		cout << "Encontrado" << endl;
		
		DiscoverMach->getBorder(border);
		cout << "Columna" << endl;
		cout << border.col << endl;
		cout << "Fila" << endl;
		cout << border.row << endl;
	}else{
		cout << "No Encontrado" << endl;
	}
	//////////////////////////////////////////
	BorAbsMach *BorderMach = new BorAbsMach(mt,border,clk,'1');
	dostar = BorderMach->start();
	if (dostar){
		cout << "Inicio Correctamente la maquina de bordes" << endl;
		cout << "Longitud del borde" << endl;
		cout << BorderMach->getBorderlen() << endl;
		
		////////////////////////////////////////
		//write img
		int * data = new int[BorderMach->getBorderlen()]{};
		BorderMach->setBorders(data);
		ImgWriter::savePlainPBM("t.pbm",data,BorderMach->getBorderlen(),mt->limitcol()+1,mt->limitrow()+1);
		
	}else{
		cout << "No Inicio Correctamente la maquina de bordes" << endl;
	}
	
	
	delete BorderMach;
	delete DiscoverMach;
	delete mt;
	return 0;
}
