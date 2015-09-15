#ifndef BTreeHash_
#define BTreeHash_

#include <cmath>
#include <vector>
#include "BTree.h"

using namespace std ;

class BTreeHash
{
public:
	// constructor
	BTreeHash(int BTreeOrder , int theTableSize)
	{
		s = theTableSize ;
		//myHashTable(theTableSize) ;
		for (int i = 0 ; i < theTableSize ; i++)
			myHashTable.push_back(new BTree(BTreeOrder)) ;
	}
	pair<int , int>* search(int theKey) const ; 
	void insert(const pair<int , int>& thePair) ;
	void levelOrder(ostream&) ;
	void sortedOrder(ostream&) ; 
private:
	int s ;
	vector<BTree*> myHashTable ; 
	
} ;

void BTreeHash::levelOrder(ostream& out)
{
	for (int i = 0 ; i < s ; i++)
		if (myHashTable.at(i) != NULL)
			myHashTable.at(i)->levelOrder(out) ;
}

void BTreeHash::sortedOrder(ostream& out)
{
	for (int i = 0 ; i < s ; i++)
		if (myHashTable.at(i) != NULL)
			myHashTable.at(i)->sortedOrder(out) ;
}

pair<int,int>* BTreeHash::search(int theKey) const
{
	// find the bucket
	int bucket = theKey % s ;
	pair<int,int>* returnedPair ;
	returnedPair = myHashTable.at(bucket)->search(theKey) ;
	return returnedPair ;
}

void BTreeHash::insert(const pair<int , int>& thePair)
{
	// find the bucket
	int bucket = thePair.first % s ;
	myHashTable.at(bucket)->insert(thePair) ;
}
#endif
