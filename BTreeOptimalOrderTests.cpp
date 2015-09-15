#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <map>
#include <cstring>

#include "BTree.h"
#include "BTreeHash.h"

using namespace std ;

int main()
{

	vector<int> randVectKeys ;
	vector<pair<int,int> > tuple ;

	vector<int> order ; 
	/* order.push_back(3) ;
	order.push_back(7) ;
	order.push_back(11) ;
	order.push_back(15) ;
	order.push_back(17) ;
	order.push_back(40) ;
	order.push_back(100) ; */

	order.push_back(7) ;
	order.push_back(8) ;
	order.push_back(9) ;
	order.push_back(10) ;
	order.push_back(11) ;
	order.push_back(12) ;
	order.push_back(13) ;
	order.push_back(14) ;
	order.push_back(15) ;
	

	clock_t Start , btTimeInsert , btaveTimeInsert ;

	for (int i = 0 ; i < 1000000 ; i++)
		randVectKeys.push_back(i) ;

	random_shuffle(randVectKeys.begin() , randVectKeys.end()) ;

	tuple.clear() ;
	for (int i = 0 ; i < 1000000 ; i++)
		tuple.push_back(pair<int,int>(randVectKeys[i],2*randVectKeys[i])) ;

	for (int oc = 0 ; oc < order.size() ; oc++)
	{
		BTree bt(order.at(oc)) ;
		btaveTimeInsert = 0.0 ;

		Start = clock() ;
		for (int i = 0 ; i < 1000000 ; i++)
			bt.insert(tuple[i]) ;
		btTimeInsert = clock() - Start ;
		btaveTimeInsert += btTimeInsert ;
		cout << "order = " << order.at(oc) << "\tbtTimeInsert = " << btTimeInsert << endl ;
	}

	
	
	

	return 0 ;
}
