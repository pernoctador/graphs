#include "AdjMatrix.h"
#include <assert.h>

void testBasicGraph()
{
	AdjMatrix a(4);
	AdjMatrix a_res(4);
	a.nameElem();
	if(digraph)
	{
		int e[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
		a_res = e;
	}
	else
	{
		int e[] = {0,1,2,3,4,5,6,7,8,9};
		a_res = e;
	}

	assert(a == a_res);

	AdjMatrix b(6);
	b.completeGraph();

	for(int i = 0; i < 6; i++)
	{
		assert(b.indegree(i) == b.outdegree(i));
		assert(b.indegree(i) == 5);
	}

	if(digraph)
		assert(b.edges() == 30);
	else
		assert(b.edges() == 15);

	AdjMatrix c(a);
	assert(a == c);
}




int main(){
	if(digraph)
		cout << "Testing AdjMatrix for directed graphs:" << endl;
	else
		cout << "Testing AdjMatrix for no-directed graphs:" << endl;
	
	testBasicGraph();	
	return 0;
	}
