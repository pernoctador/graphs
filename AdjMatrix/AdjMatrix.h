#ifndef _ADY_MATRIX_H_
#define _ADY_MATRIX_H_

#define digraph false	//optative. set to false if you don't need a digraph. If it's false, will save almost half of _matrix memory (because [1,2] = [2,1])

#if digraph
	#define _totElem (_nodes * _nodes)
	#define _elem( x , y ) \
		((x) * _nodes + (y))
	//#define _posEquivX( x ) ((x)/4)
	//#define _posEquivY( x ) ((x) % 4)
#else
	#define _totElem ((_nodes * (_nodes+1))/2)
	#define _elem( x , y ) \
		((max((x),(y)) * (max((x),(y)) + 1) / 2) + (min((x),(y))))
	//#define _posEquivX( x ) (((sqrt((x) * 8 + 1) - 1)/2))
	//#define _posEquivY( x ) ()
#endif

#include <cmath> 	//better than math.h
#include <iostream>
#include <limits>       // std::numeric_limits
#include <iomanip>		//setw
#include <string>       // std::string
#include <sstream>      // std::ostringstream
#include <vector>
#include <exception>

using namespace std;

class AdjMatrix {	//Works for multigraphs. In cpp you can define if this is a digraph or a simple graph (with half the elements of a digraph in memory)
public:
	AdjMatrix(int n);	//edges = 0
	AdjMatrix(const AdjMatrix& aM);
	AdjMatrix(int n, int k);	//every edge value is k, except main diagonal
	~AdjMatrix(){delete[] _matrix;}

	void operator=(AdjMatrix aM);
	void operator=(int aM[]); 		//for fast asignment. beware, i can't check aM size
	void operator=(vector<int> aM);	//for fast asignment.
	void completeGraph();
	void nameElem();/*
	void path();
	void circuit();
	//maybe in the future: hammilton and euler's path and circuit.*/

	bool operator==(AdjMatrix aM);
	int& operator()(int x, int y);
	int operator()(int x, int y) const;


	void print() const;
	int size() const {return _nodes;}

	//void shuffle();		//to create random isomorph graphs

	int edges();
	int indegree(int node);	//both are equal to the node degree if it's not a digraph.
	int outdegree(int node);
private:

	int* _matrix;
	int _nodes;
};
/*
AdjMatrix completeGraph(int size);
AdjMatrix path(int size);
AdjMatrix circuit(int size);
*/

#endif
