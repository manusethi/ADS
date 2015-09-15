#ifndef RBHash_
#define RBHash_

#include <cmath>
#include <vector>
#include <map>

using namespace std ;

class RBHash
{
public:
	// constructor
	RBHash(int theTableSize)
	{
		s = theTableSize ;
		//myHashTable(theTableSize) ;
		for (int i = 0 ; i < theTableSize ; i++)
			myHashTable.push_back(new map<int,int>()) ;
	}
	map<int,int>::iterator find(int theKey) const ; 
	void insert(const pair<int , int>& thePair) ; 
private:
	int s ;
	vector<map<int,int>* > myHashTable ; 
	
} ;

map<int,int>::iterator RBHash::find(int theKey) const
{
	// find the bucket
	int bucket = theKey % s ;
	map<int,int>::iterator it ;
	it = myHashTable.at(bucket)->find(theKey) ;
	return it ;
}

void RBHash::insert(const pair<int , int>& thePair)
{
	// find the bucket
	int bucket = thePair.first % s ;
	myHashTable.at(bucket)->insert(thePair) ;
}
#endif