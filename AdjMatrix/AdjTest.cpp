#include "AdjMatrix.h"

void testCreateGraph(){
	AdjMatrix a(4);
	a.print();
	a(2,1) = 2;
	a.print();
	a(3,3) = 7;
	a.print();

}




int main(){
	
	testCreateGraph();	
	return 0;
	}
