#ifndef BTreeHash_
#define BTreeHash_

#include <cmath>
#include <vector>
#include "BTree.h"

using namespace std ;

class BTreeHash
{
public:
	// constructors
	BTreeHash() ; 
	BTreeHash(int BTreeOrder , int theTableSize) ;
	BTreeHash(const BTreeHash &rhs) ;

	// destructor
	~BTreeHash() ;

	const BTreeHash & operator=(const BTreeHash & rhs) ;
	
	pair<int , int>* search(int theKey) const ; 
	void insert(const pair<int , int>& thePair) ;
	void levelOrder(ostream&) ;
	void sortedOrder(ostream&) ; 
private:
	int s ;
	vector<BTree*> myHashTable ; 
	
} ;

BTreeHash::BTreeHash() 
{	s = 0 ;
	myHashTable.reserve(0) ;
} 

BTreeHash::BTreeHash(int BTreeOrder , int theTableSize)
{
	s = theTableSize ;
	myHashTable.reserve(theTableSize) ; // change made here
	for (int i = 0 ; i < theTableSize ; i++)
		myHashTable.push_back(new BTree(BTreeOrder)) ;
}

BTreeHash::BTreeHash(const BTreeHash &rhs)
{
	s = rhs.s ;
	myHashTable.reserve(s) ;
	for (int i = 0 ; i < s ; i++)
		myHashTable.push_back(new BTree(rhs.at(i))) ;
	
}

BTreeHash::~BTreeHash()
{
	for (int i = s-1 ; i >= 0 ; i--) {
		delete myHashTable.at(i) ;
		myHashTable.at(i) = NULL ;
	}
}

const BTreeHash & BTreeHash::operator=(const BTreeHash & rhs) 
{	
	if (this != &rhs)
	{	
		for (int i = s-1 ; i >= 0 ; i++) {
			delete myHashTable.at(i) ;
			myHashTable.at(i) = NULL ;
		}
		s = rhs.s ;
		myHashTable.resize(s) ;
		for (int i  = 0 ; i < s ; i++) {
			myHashTable.at(i) = new BTree(rhs.at(i)) ;
		}
	}
}

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
	// check the initial size of hash table
	if (s == 0) {
		s += 1 ;
		myHashTable.push_back(new BTree(2)) ; // insert BTree of order 2
		myHashTable.at(0)->insert(thePair) ;
	}

	// find the bucket
	int bucket = thePair.first % s ;
	myHashTable.at(bucket)->insert(thePair) ;
}
#endif
