#include "AdyMatrix.h"

#define digraph true	//optative. set to false if you don't need a digraph. If it's false, will save almost half of matrix memory (because [1,2] = [2,1])

#if digraph
	#define _totElem (nodes * nodes)
	#define _elem( x , y ) \
		((x) * nodes + (y))
	//#define _posEquivX( x ) ((x)/4)
	//#define _posEquivY( x ) ((x) % 4)
#else
	#define _totElem ((nodes * (nodes+1))/2)
	#define _elem( x , y ) \
		((max((x),(y)) * (max((x),(y)) + 1) / 2) + (min((x),(y))))
	//#define _posEquivX( x ) (((sqrt((x) * 8 + 1) - 1)/2))
	//#define _posEquivY( x ) ()
#endif

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
    return "Error: wrong dimensions in matrix operation.";
  }
} wrongDim;

template<typename T>
inline string tostr(T value) {
    ostringstream s;
    s.precision(numeric_limits<T>::digits10);
    s << value;
    return s.str();
}

AdyMatrix::AdyMatrix(int n)
{
	if(n < 1)
		throw zeroCells;

	nodes = n;

 	matrix = new int[_totElem];
 	for(int i = 0; i < _totElem; i++)
	{
		matrix[i] = 0;
	}
}

AdyMatrix::AdyMatrix(const AdyMatrix& aM) 
{
	nodes = aM.nodes;

	matrix = new int[_totElem];
 	for(int i = 0; i < _totElem; i++)
	{
		matrix[i] = aM.matrix[i];
	}
}

AdyMatrix::AdyMatrix(int n, int k)
{
	if(n < 1)
		throw zeroCells;

	nodes = n;

	matrix = new int[_totElem];
 	for(int i = 0; i < _totElem; i++)
	{
		matrix[i] = k;
	}
}

void AdyMatrix::completeGraph()
{
	for(int i = 0; i < nodes; i++)
	{
		for(int j = 0; j < nodes; j++)
		{
			(*this)(i,j) = (i!=j); // every elem is 1 except the diagonal
		}
	}
}

int& AdyMatrix::operator() (int x, int y)		//check for improvement
{
	if(min(x,y) < 0 || max(x,y) >= nodes)
	{
		throw wrongDim;
	}
	
	return matrix[_elem(x,y)];
}

int AdyMatrix::operator() (int x, int y) const	//check for improvement
{
	if(min(x,y) < 0 || max(x,y) >= nodes)
	{
		throw wrongDim;
	}
	
	return matrix[_elem(x,y)];
}

void AdyMatrix::print() const
{
	int maxSize = 1;
	int elemSize;
	for(int i = 0; i < nodes; i++)
	{
		for(int j = 0; j < nodes; j++)
		{
			elemSize = tostr((*this)(i,j)).size();
			maxSize = max(maxSize, elemSize);
		}
	}

	cout << "╭";

	for (int j = 0; j < nodes - 1; j++) {
		cout << setw(maxSize) << (*this)(0, j) << ", ";
	}

	cout << setw(maxSize) << (*this)(0, nodes-1) << "╮" << endl;

	for (int i = 1; i < nodes - 1; i++) {
		cout << "│";

		for (int j = 0; j < nodes - 1; j++) {
			cout << setw(maxSize) << (*this)(i, j) << ", ";
		}

		cout << setw(maxSize) << (*this)(i, nodes-1) << "│" << endl;
	}

	cout << "╰";

	for (int j = 0; j < nodes - 1; j++) {
		cout << setw(maxSize) << (*this)(nodes-1, j) << ", ";
	}

	cout << setw(maxSize) << (*this)(nodes-1, nodes-1) << "╯" << endl<< endl;
}

int AdyMatrix::nodeDegree(int node)
{
	if(node >= nodes)
		throw wrongDim;

	int res = 0;
	for(int i = 0; i <= node; i++)
	{
		if((*this)(node,i) != 0)
			res++;
	}
	
	return res;
}

int AdyMatrix::edges()
{
	int edges = 0;
	for(int i = 0; i < _totElem; i++)
	{
		edges =matrix[i] == 1;
	}
	
	return edges;
};