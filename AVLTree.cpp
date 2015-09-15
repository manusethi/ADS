#include <iostream>
#include <utility>
#include "AVL.h"

using namespace std ;

int main()
{
	AVL y ;
	pair<int,int> q(1,1) ;
	y.insert(q) ; // check for const
	pair<int , int> *p = y.find(1) ; // check for const
	cout << "search for 1 succeeds " << endl ;
	cout << p->first << ' ' << p->second << endl ;

	pair<int,int> q1(5,6) ;
	y.insert(q1) ; // check for const
	p = y.find(5) ; // check for const
	cout << "search for 5 succeeds " << endl ;
	cout << p->first << ' ' << p->second << endl ;
	
	y.insert(pair<int,int>(2,3)) ; // check for const
	p = y.find(6) ; // check for const
	cout << "search for 1 succeeds " << endl ;
	cout << p->first << ' ' << p->second << endl ;
	
	return 0 ;
}
