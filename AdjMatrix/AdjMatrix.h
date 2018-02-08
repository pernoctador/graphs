#ifndef _ADJ_MATRIX_H_
#define _ADJ_MATRIX_H_

#define digraph true	//optative. set to false if you don't need a digraph. If it's false, will save almost half of _matrix memory (because [1,2] = [2,1])

#if digraph
	#define _totElem (_nodes * _nodes)
	#define _elem( x , y ) \
		((x) * _nodes + (y))
#else
	#define _totElem ((_nodes * (_nodes+1))/2)
	#define _elem( x , y ) \
		((max((x),(y)) * (max((x),(y)) + 1) / 2) + (min((x),(y))))
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

class zeroRowsOrCols: public exception
{
  virtual const char* what() const throw()
  {
    return "Error: ammount of rows and columns must be greater than 0.";
  }
} zeroCells;

class wrongDimensions: public exception
{
  virtual const char* what() const throw()
  {
    return "Error: wrong dimensions in _matrix operation.";
  }
} wrongDim;


class outOfBounds: public exception
{
  virtual const char* what() const throw()
  {
    return "Error: out of bound access.";
  }
} wrongBounds;

template <class T>
class AdjMatrix {	//Weighted graphs. At the top of the file you can define if this is a digraph or a simple graph (with half the elements of a digraph in memory)
public:
	AdjMatrix(unsigned n);	//edges = 0
	AdjMatrix(const AdjMatrix<T>& aM);
	AdjMatrix(unsigned n, T k);	//every edge value is k, except main diagonal
	~AdjMatrix(){delete[] _matrix;}

	void operator=(AdjMatrix<T> aM);
	void operator=(T aM[]); 		//for fast asignment. beware, i can't check aM size
	void operator=(vector<T> aM);	//for fast asignment.
	void completeGraph();
	void nameElem();/*
	void path();
	void circuit();
	//maybe in the future: hammilton and euler's path and circuit.*/

	bool operator==(AdjMatrix<T> aM);
	T& operator()(unsigned x, unsigned y);
	T operator()(unsigned x, unsigned y) const;


	void print() const;
	unsigned size() const {return _nodes;}

	//void isomorph();		//to create random isomorph graphs

	unsigned edges();
	unsigned indegree(unsigned node);	//both are equal to the node degree if it's not a digraph.
	unsigned outdegree(unsigned node);
private:

	T* _matrix;
	unsigned _nodes;
};

template<typename T>
inline string tostr(T value) {
    ostringstream s;
    s.precision(numeric_limits<T>::digits10);
    s << value;
    return s.str();
}

template <class T>
AdjMatrix<T>::AdjMatrix(unsigned n)
{
	if(n < 1)
		throw zeroCells;

	_nodes = n;

 	_matrix = new T[_totElem];
 	for(unsigned i = 0; i < _totElem; i++)
	{
		_matrix[i] = 0;
	}
}

template <class T>
AdjMatrix<T>::AdjMatrix(const AdjMatrix& aM) 
{
	_nodes = aM._nodes;

	_matrix = new T[_totElem];
 	for(unsigned i = 0; i < _totElem; i++)
	{
		_matrix[i] = aM._matrix[i];
	}
}

template <class T>
AdjMatrix<T>::AdjMatrix(unsigned n, T k)
{
	if(n < 1)
		throw zeroCells;

	_nodes = n;

	_matrix = new T[_totElem];
 	for(unsigned i = 0; i < _nodes; i++)
	{
		for(unsigned j = 0; j < _nodes; j++)
		{
			if(i != j)
				(*this)(i,j) = k;
		}
	}
}

template <class T>
void AdjMatrix<T>::operator=(AdjMatrix<T> aM)
{
	if(_nodes != aM._nodes)
		throw wrongDim;

	for(unsigned i = 0; i < _totElem; i++)
	{
		_matrix[i] = aM._matrix[i];
	}
}

template <class T>
void AdjMatrix<T>::operator=(T aM[]) //for fast asignment. beware, i can't check aM size
{
	for(unsigned i = 0; i < _totElem; i++)
	{
		_matrix[i] = aM[i];
	}
}

template <class T>
void AdjMatrix<T>::operator=(vector<T> aM) 	//for fast asignment.
{
	if(aM.size() != _totElem)
		throw wrongDim;

	for(unsigned i = 0; i < _nodes; i++)
	{
		_matrix[i] = aM[i];
	}
}

template <class T>
void AdjMatrix<T>::completeGraph()
{
	for(unsigned i = 0; i < _nodes; i++)
	{
		for(unsigned j = 0; j < _nodes; j++)
		{
			(*this)(i,j) = (i!=j); // every elem is 1 except the diagonal
		}
	}
}

template <class T>
void AdjMatrix<T>::nameElem()
{
	for(unsigned i = 0; i < _totElem; i++)
	{
		_matrix[i] = i;
	}
}

template <class T>
bool AdjMatrix<T>::operator==(AdjMatrix<T> aM)
{
	if(_nodes != aM._nodes)
		return false;

	for(unsigned i = 0; i < _totElem; i++)
	{
		if(_matrix[i] != aM._matrix[i])
			return false;
	}
	return true;
}

template <class T>
T& AdjMatrix<T>::operator() (unsigned x, unsigned y)
{
	if(x >= _nodes || y >= _nodes)
		throw wrongBounds;
	
	return _matrix[_elem(x,y)];
}

template <class T>
T AdjMatrix<T>::operator() (unsigned x, unsigned y) const
{
	if(x >= _nodes || y >= _nodes)
		throw wrongBounds;
	
	return _matrix[_elem(x,y)];
}

template <class T>
void AdjMatrix<T>::print() const
{
	int maxSize = 1;
	int elemSize;
	for(unsigned i = 0; i < _nodes; i++)
	{
		for(unsigned j = 0; j < _nodes; j++)
		{
			elemSize = tostr((*this)(i,j)).size();
			maxSize = max(maxSize, elemSize);
		}
	}

	cout << "╭";

	for (unsigned j = 0; j < _nodes - 1; j++) {
		cout << setw(maxSize) << (*this)(0, j) << ", ";
	}

	cout << setw(maxSize) << (*this)(0, _nodes-1) << "╮" << endl;

	for (unsigned i = 1; i < _nodes - 1; i++) {
		cout << "│";

		for (unsigned j = 0; j < _nodes - 1; j++) {
			cout << setw(maxSize) << (*this)(i, j) << ", ";
		}

		cout << setw(maxSize) << (*this)(i, _nodes-1) << "│" << endl;
	}

	cout << "╰";

	for (unsigned j = 0; j < _nodes - 1; j++) {
		cout << setw(maxSize) << (*this)(_nodes-1, j) << ", ";
	}

	cout << setw(maxSize) << (*this)(_nodes-1, _nodes-1) << "╯" << endl<< endl;
}

template <class T>
unsigned AdjMatrix<T>::edges()
{
	int edges = 0;
	for(unsigned i = 0; i < _totElem; i++)
	{
		edges += (_matrix[i] != 0);
	}
	
	return edges;
}

template <class T>
unsigned AdjMatrix<T>::indegree(unsigned node)
{
	if(node < 0 || node >= _nodes)
		throw wrongBounds;

	unsigned res = 0;
	for(unsigned i = 0; i <_nodes; i++)
	{
		if((*this)(i,node) != 0)
			res++;
	}
	
	return res;
}

template <class T>
unsigned AdjMatrix<T>::outdegree(unsigned node)
{
	if(node < 0 || node >= _nodes)
		throw wrongBounds;

	unsigned res = 0;
	for(unsigned i = 0; i < _nodes; i++)
	{
		if((*this)(node,i) != 0)
			res++;
	}
	
	return res;
}

#endif
