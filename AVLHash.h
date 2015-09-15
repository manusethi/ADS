#ifndef AVLHash_
#define AVLHash_

#include <cmath>
#include <vector>
#include "AVL.h"

using namespace std ;

class AVLHash
{
public:
	// constructor
	AVLHash(int theTableSize)
	{
		s = theTableSize ;
		//myHashTable(theTableSize) ;
		for (int i = 0 ; i < theTableSize ; i++)
			myHashTable.push_back(new AVL()) ;
	}
	pair<int , int>* search(int theKey) const ; 
	void insert(const pair<int , int>& thePair) ;
	void inOrder(ostream&) const ;
private:
	int s ;
	vector<AVL*> myHashTable ; 
	
} ;

void AVLHash::inOrder(ostream& out) const
{
	for (int i = 0 ; i < s ; i++)
		if (myHashTable.at(i) != NULL)
			myHashTable.at(i)->inOrder(out) ;
}

pair<int,int>* AVLHash::search(int theKey) const
{
	// find the bucket
	int bucket = theKey % s ;
	pair<int,int>* returnedPair ;
	returnedPair = myHashTable.at(bucket)->find(theKey) ;
	return returnedPair ;
}

void AVLHash::insert(const pair<int , int>& thePair)
{
	// find the bucket
	int bucket = thePair.first % s ;
	myHashTable.at(bucket)->insert(thePair) ;
}
#endif
