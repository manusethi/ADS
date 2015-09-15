#ifndef BTreeNode_
#define BTreeNode_

#include <utility> // for pair
#include <vector> // for vector
#include <cstddef> // for NULL

using namespace std ;

struct BTreeNode
{
	// int M ; // for M -way tree // do I need this or something else or nothing??
	vector<pair<int,int> > element ;
	vector<BTreeNode*> child ;

	// no argument constructor
	BTreeNode()
	{	
		element.clear() ;
		child.clear() ;
		// child.push_back(NULL) ; // child has one more element initially
		
		/*// child(M+1) ;
		for (int i = 0 ; i < element.size() + 1 ; i++)
			child[i] = NULL ;*/
	}
} ;

#endif 
