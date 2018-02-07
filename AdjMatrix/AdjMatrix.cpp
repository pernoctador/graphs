#include "AdjMatrix.h"

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

template<typename T>
inline string tostr(T value) {
    ostringstream s;
    s.precision(numeric_limits<T>::digits10);
    s << value;
    return s.str();
}

AdjMatrix::AdjMatrix(int n)
{
	if(n < 1)
		throw zeroCells;

	_nodes = n;

 	_matrix = new int[_totElem];
 	for(int i = 0; i < _totElem; i++)
	{
		_matrix[i] = 0;
	}
}

AdjMatrix::AdjMatrix(const AdjMatrix& aM) 
{
	_nodes = aM._nodes;

	_matrix = new int[_totElem];
 	for(int i = 0; i < _totElem; i++)
	{
		_matrix[i] = aM._matrix[i];
	}
}

AdjMatrix::AdjMatrix(int n, int k)
{
	if(n < 1)
		throw zeroCells;

	_nodes = n;

	_matrix = new int[_totElem];
 	for(int i = 0; i < _nodes; i++)
	{
		for(int j = 0; j < _nodes; j++)
		{
			if(i != j)
				(*this)(i,j) = k;
		}
	}
}

void AdjMatrix::operator=(AdjMatrix aM)
{
	if(_nodes != aM._nodes)
		throw wrongDim;

	for(int i = 0; i < _totElem; i++)
	{
		_matrix[i] = aM._matrix[i];
	}
}

void AdjMatrix::operator=(int aM[]) //for fast asignment. beware, i can't check aM size
{
	for(int i = 0; i < _totElem; i++)
	{
		_matrix[i] = aM[i];
	}
}

void AdjMatrix::operator=(vector<int> aM) 	//for fast asignment.
{
	if(aM.size() != (unsigned)_totElem)
		throw wrongDim;

	for(int i = 0; i < _nodes; i++)
	{
		_matrix[i] = aM[i];
	}
}

void AdjMatrix::completeGraph()
{
	for(int i = 0; i < _nodes; i++)
	{
		for(int j = 0; j < _nodes; j++)
		{
			(*this)(i,j) = (i!=j); // every elem is 1 except the diagonal
		}
	}
}

void AdjMatrix::nameElem()
{
	for(int i = 0; i < _totElem; i++)
	{
		_matrix[i] = i;
	}
}

bool AdjMatrix::operator==(AdjMatrix aM)
{
	if(_nodes != aM._nodes)
		return false;

	for(int i = 0; i < _totElem; i++)
	{
		if(_matrix[i] != aM._matrix[i])
			return false;
	}
	return true;
}

int& AdjMatrix::operator() (int x, int y)		//check for improvement
{
	if(min(x,y) < 0 || max(x,y) >= _nodes)
		throw wrongBounds;
	
	return _matrix[_elem(x,y)];
}

int AdjMatrix::operator() (int x, int y) const	//check for improvement
{
	if(min(x,y) < 0 || max(x,y) >= _nodes)
		throw wrongBounds;
		
	return _matrix[_elem(x,y)];
}

void AdjMatrix::print() const
{
	int maxSize = 1;
	int elemSize;
	for(int i = 0; i < _nodes; i++)
	{
		for(int j = 0; j < _nodes; j++)
		{
			elemSize = tostr((*this)(i,j)).size();
			maxSize = max(maxSize, elemSize);
		}
	}

	cout << "╭";

	for (int j = 0; j < _nodes - 1; j++) {
		cout << setw(maxSize) << (*this)(0, j) << ", ";
	}

	cout << setw(maxSize) << (*this)(0, _nodes-1) << "╮" << endl;

	for (int i = 1; i < _nodes - 1; i++) {
		cout << "│";

		for (int j = 0; j < _nodes - 1; j++) {
			cout << setw(maxSize) << (*this)(i, j) << ", ";
		}

		cout << setw(maxSize) << (*this)(i, _nodes-1) << "│" << endl;
	}

	cout << "╰";

	for (int j = 0; j < _nodes - 1; j++) {
		cout << setw(maxSize) << (*this)(_nodes-1, j) << ", ";
	}

	cout << setw(maxSize) << (*this)(_nodes-1, _nodes-1) << "╯" << endl<< endl;
}

int AdjMatrix::indegree(int node)
{
	if(node < 0 || node >= _nodes)
		throw wrongBounds;

	int res = 0;
	for(int i = 0; i <_nodes; i++)
	{
		if((*this)(i,node) != 0)
			res++;
	}
	
	return res;
}

int AdjMatrix::outdegree(int node)
{
	if(node < 0 || node >= _nodes)
		throw wrongBounds;

	int res = 0;
	for(int i = 0; i < _nodes; i++)
	{
		if((*this)(node,i) != 0)
			res++;
	}
	
	return res;
}

int AdjMatrix::edges()
{
	int edges = 0;
	for(int i = 0; i < _totElem; i++)
	{
		edges += (_matrix[i] != 0);
	}
	
	return edges;
}