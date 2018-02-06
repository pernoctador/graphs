#ifndef _ADY_MATRIX_H_
#define _ADY_MATRIX_H_


#include <math.h>
#include <cmath> 	//better than math.h
#include <iostream>
#include <limits>       // std::numeric_limits
#include <iomanip>		//setw
#include <string>       // std::string
#include <sstream>      // std::ostringstream
#include <exception>

using namespace std;

class AdyMatrix {	//Works for multigraphs. In cpp you can define if this is a digraph or a simple graph (with half the elements of a digraph in memory)
public:
	AdyMatrix(int n);
	AdyMatrix(const AdyMatrix& aM);
	AdyMatrix(int n, int k);
	~AdyMatrix(){delete[] matrix;}
	
	void completeGraph();

	void print() const;
	int& operator()(int x, int y);
	int operator()(int x, int y) const;
//	void operator=(AdyMatrix aM);
	int size() const {return nodes;}
/*
	void shuffleViejo();
	void shuffle();
*/
	int edges();
	int nodeDegree(int node);
private:

	int* matrix;
	int nodes;
	bool digraph;

};

#endif
