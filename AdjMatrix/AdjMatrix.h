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

class AdjMatrix {	//Works for multigraphs. In cpp you can define if this is a digraph or a simple graph (with half the elements of a digraph in memory)
public:
	AdjMatrix(int n);	//edges = 0
	AdjMatrix(const AdjMatrix& aM);
	AdjMatrix(int n, int k);	//every possible edge exists and it's value is k. Even (i,i) edges
	~AdjMatrix(){delete[] matrix;}

	void operator=(AdjMatrix aM);	
	void completeGraph();

	bool operator==(AdjMatrix aM);
	int& operator()(int x, int y);
	int operator()(int x, int y) const;


	void print() const;
	int size() const {return nodes;}

	//void shuffle();		//to create random isomorph graphs

	int edges();
	int indegree(int node);	//both are equal to degree if it's not a digraph.
	int outdegree(int node);
private:

	int* matrix;
	int nodes;
	bool digraph;

};

#endif
