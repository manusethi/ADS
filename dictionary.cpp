// Dictionary file

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <map>
#include <cstring>

#include "AVL.h"
#include "AVLHash.h"
#include "RBHash.h"
#include "BTree.h"
#include "BTreeHash.h"

using namespace std ;

int main(int argc , char* argv[])
{
	cout << argv[0] << "\t" << argv[1] << endl ;
	if (!strcmp(argv[1] , "-r")) // random mode
	{
		// random mode
		int s = atoi(argv[2]) ;
		int b_tree_order = atoi(argv[3]) ;
		vector<int> randVectKeys ;
		vector<pair<int,int> > tuple ;
		int NN ;
		cout << "Enter the number of elements n" << endl ;
		cin >> NN ;
		clock_t Start , AVLTimeInsert , AVLTimeSearch ,
			BTreeTimeInsert , BTreeTimeSearch , 
			BTreeHashTimeInsert , BTreeHashTimeSearch, 
			AVLHashTimeInsert, AVLHashTimeSearch , 
			RBTimeInsert , RBTimeSearch , 
			RBHashTimeInsert , RBHashTimeSearch ;

		for (int i = 0 ; i < NN ; i++)
			randVectKeys.push_back(i) ;

		
			AVL myAVLTree ;
			AVLHash AH3(s) ;
			map<int,int> myMap ;
			map<int,int>::iterator it ;
			RBHash RBH3(s) ;
			BTree myBTree(b_tree_order) ;
			BTreeHash BTH(b_tree_order,s) ;
			// randVectKeys.clear() ;
			tuple.clear() ;


			// randomize 
			random_shuffle(randVectKeys.begin() , randVectKeys.end()) ;


			for (int i = 0 ; i < NN; i++)
				tuple.push_back(pair<int,int>(randVectKeys[i],2*randVectKeys[i])) ;

			pair<int,int>* p  ;

			// B Tree
			cout << "========= BTree Inserts =================" << endl ;
			Start = clock() ;
			for (int i = 0 ; i < NN ; i++)
				myBTree.insert(tuple[i]) ;
			BTreeTimeInsert = clock() - Start ;
			

			// AVL tree
			cout << "========= AVL Tree Inserts ==============" << endl ;
			Start = clock() ;
			for (int i = 0 ; i < NN ; i++)
				myAVLTree.insert(tuple[i]) ;
			AVLTimeInsert = clock() - Start ;
			


			cout << "===========AVL Tree Searches============" << endl ;

			Start = clock() ;
			for (int i = 0 ; i < NN ; i++)
			{
				p = myAVLTree.find(randVectKeys[i]) ;
				// cout << p->first << "\t" << p->second << "\n" ;
			}
			cout << endl ;
			AVLTimeSearch = clock() - Start ;
			




			// ---- code for AVLHash ------------

			cout << "================AVLHash inserts =================" << endl ;
			Start = clock() ;
			for (int i = 0 ; i < NN ; i++)
				AH3.insert(tuple[i]) ;
			AVLHashTimeInsert = clock() - Start ;
			


			cout << "===========AVLHash Searches============" << endl ;

			Start = clock() ;
			for (int i = 0 ; i < NN ; i++)
			{
				p = AH3.search(randVectKeys[i]) ;
				// cout << p->first << "\t" << p->second << "\n" ;
			}
			cout << endl ;
			AVLHashTimeSearch = clock() - Start ;
			




			// ---------- code for using RedBlack Trees (STL Map) -----------
			cout << "================RB inserts =================" << endl ;
			Start = clock() ;
			for (int i = 0 ; i < NN ; i++)
				myMap.insert(tuple[i]) ;
			RBTimeInsert = clock() - Start ;
			


			cout << "===========RB Searches============" << endl ;
			// pair<int,int>* p  ;
			Start = clock() ;
			for (int i = 0 ; i < NN ; i++)
			{
				it = myMap.find(randVectKeys[i]) ;
				// cout << it->first << "\t" << it->second << "\n" ;
			}
			cout << endl ;
			RBTimeSearch = clock() - Start ;





			// ---------- code for using RB Hash  -----------
			cout << "================RBHash  inserts =================" << endl ;
			Start = clock() ;
			for (int i = 0 ; i < NN ; i++)
				RBH3.insert(tuple[i]) ;
			RBHashTimeInsert = clock() - Start ;
			


			cout << "===========RBHash Searches============" << endl ;
			// pair<int,int>* p  ;
			Start = clock() ;
			for (int i = 0 ; i < NN ; i++)
			{
				it = RBH3.find(randVectKeys[i]) ;
				// cout << it->first << "\t" << it->second << "\n" ;
			}
			cout << endl ;
			RBHashTimeSearch = clock() - Start ;
			

	
	} 

	else if (!strcmp(argv[1] , "-u")) // user input mode
	{ 
		ifstream inFile(argv[2]) ;

		AVL myAVLTree ;
		AVLHash AH(3) ;
		/*map<int,int> myMap ;
		map<int,int>::iterator it ;
		RBHash RBH(3) ;*/
		BTree myBTree(3) ;
		BTreeHash BTH(3,3) ;

		pair<int,int> p ;

		// read the number of lines 
		int nLines ;
		inFile >> nLines ;
		
		// read the pairs and perform inserts in all data structures
		for (int i = 0 ; i < nLines ; i++)
		{
			inFile >> p.first ;
			inFile >> p.second ;
			myAVLTree.insert(p) ;
			AH.insert(p) ;
			/*myMap.insert(p) ;
			RBH.insert(p) ;*/
			myBTree.insert(p) ;
			BTH.insert(p) ;
		}

		// generate output
		ofstream avlInOrder("AVL_inorder.out") ;
		if (avlInOrder.is_open())
		{
			myAVLTree.inOrder(avlInOrder) ;
			avlInOrder.close() ;
		}
		else cout << "Unable to open file" << endl ;
		ofstream avlPostOrder("AVL_postorder.out") ;
		if (avlPostOrder.is_open())
		{
			myAVLTree.postOrder(avlPostOrder) ;
			avlPostOrder.close() ;
		}
		ofstream avlHashInOrder("AVLHash_inorder.out") ;
		if (avlHashInOrder.is_open())
		{
			AH.inOrder(avlHashInOrder) ;
			avlHashInOrder.close() ;
		}

		ofstream btreeSortedOrder("BTree_sorted.out") ;
		if (btreeSortedOrder.is_open())
		{
			myBTree.sortedOrder(btreeSortedOrder) ;
			btreeSortedOrder.close() ;
		}
		ofstream btreeLevelOrder("BTree_level.out") ;
		if (btreeLevelOrder.is_open())
		{
			myBTree.levelOrder(btreeLevelOrder) ;
			btreeLevelOrder.close() ;
		}
		ofstream btreeHashLevelOrder("BTreeHash_level.out") ;
		if (btreeHashLevelOrder.is_open())
		{
			BTH.levelOrder(btreeHashLevelOrder) ;
			btreeHashLevelOrder.close() ;
		}


	}
	else
		cout << "Bad arguments! Please try again. Program exited." << endl ;


	return 0 ;

}
