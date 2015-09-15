#ifndef BTree_
#define BTree_

#include <utility>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>
#include <iostream>
#include "BTreeNode.h"

/*namespace std 
{
	// overloading == for pair
	bool operator==(const pair<int,int>& p1 , const pair<int,int>& p2)
	{return p1.first == p2.first ;}

	// overloading != for pair
	bool operator!=(const pair<int,int>& p1 , const pair<int,int>& p2)
	{return p1.first != p2.first ;}

	// comparison operators if overloaded must be overlaoded in pairs ??

	// overloading < for pair
	bool operator<(const pair<int,int>& p1 , const pair<int,int>& p2)
	{return p1.first < p2.first ;}

	// overloading > for pair
	bool operator>(const pair<int,int>& p1 , const pair<int,int>& p2)
	{return p1.first > p2.first ;}
} */

using namespace std ;

class BTree
{
	public:
		BTree() {root = NULL ; } 
		BTree(int m) {root = NULL ; mWay = m ;} // check this
		void insert(const pair<int,int>& thePair) ;
		void levelOrder(ostream&) ;
		void sortedOrder(ostream&) ;
		pair<int,int>* search(int theKey) const ;
	private:
		BTreeNode* root ;
		int mWay ; // what to do with this in the node field??
		void insertInParent(const pair<int,int>& thePair , BTreeNode* splitChild2 , stack<BTreeNode*>& ppstack) ;
		void sortedOrderInside(ostream& out , BTreeNode* t) ;
} ;

// pair<int,int>* BTree::search(int theKey) const {}
// implementation of find function
pair<int,int>* BTree::search(int theKey) const
{
	BTreeNode* p = root ;
	while (p != NULL)
	{
//	cout << "not NULL" << endl ;	
		// TODO: put a check for BadInput for equal key
		// find where the pair lies
		if (p->element.size() == 1)
		{
			
			if (theKey < p->element[0].first)
			{
				
				p = p->child[0] ;
			}
			else if (theKey > p->element[0].first)
			{
				
				p = p->child[1] ;
				
			}
			else
				return &(p->element[0]) ;
		}
		
		else
		{
			for (int i = 0 ; i < p->element.size()-1 ; i++)
			{

				if (theKey < p->element[i].first)
				{
				// cout << "element size " << p->element.size() << endl ;
; p = p->child[i] ; break ;}
				else if ((theKey > p->element[i].first) && 
						(theKey < p->element[i+1].first))
				{  p = p->child[i+1] ; break ;}
				else if (theKey == p->element[i].first)
					return &(p->element.at(i)) ;
			}
		
			if (p != NULL && theKey == p->element[p->element.size()-1].first)
				return &(p->element[p->element.size()-1]) ;		
			if (p != NULL && theKey > p->element[p->element.size()-1].first) // check does that happen or do I have to advance i by i++ or do I need ++i in for loop.
			{p = p->child[p->element.size()] ;} // do I need to check whether thePair.first > p->element[i].first??
		}

	// cout << "hiiiii " << endl ;
// if (p == NULL) cout << "p is NULL " << endl ;	
	}
	return NULL ;
	


}

// implementation of level order traversal
void BTree::levelOrder(ostream& out) 
{
	cout << "starting level order traversal" << endl ;
	cout << "=============================================" << endl ;
	queue<BTreeNode*> q ;
	BTreeNode* t = root ;
	while (t != NULL)
	{
		for (int i = 0 ; i < t->element.size() ; i++)
			out << t->element[i].second << " " ;
		// cout << endl ;


		// put t's children on queue
		for (int i = 0 ; i < t->child.size() ; i++) // check that child.size  = element.size()+1
		{/*cout << t->child[i]->element[0].first << "\t" ;*/	q.push(t->child[i]) ; /*cout << endl ;*/}
		
		t = q.front() ;
	/*	if (t == NULL)
			cout << "t is NULL" << endl ;*/
		q.pop() ;
	}
cout << endl ;
out << endl ;
}

// implementation of sorted order traversal 
void BTree::sortedOrder(ostream& out)
{
	cout << "starting sorted order traversal" << endl ;
	cout << "================================================" << endl ;
	BTreeNode* t = root ;
	sortedOrderInside(out,t) ;
	cout << endl ;
	out << endl ;
}

void BTree::sortedOrderInside(ostream& out , BTreeNode* t) 
{
	if (t != NULL)
	{
		sortedOrderInside(out,t->child[0]) ;
		for (int i = 1 ; i < t->child.size() ; i++)
		{
			out << t->element[i-1].second << " " ;
			sortedOrderInside(out,t->child[i]) ;
		}
	}
	
}

// implementation of insertInParent function
void BTree::insertInParent(const pair<int,int>& thePair , BTreeNode* splitChild2 , stack<BTreeNode*>& ppstack)
{
	int ind , i = 0 ;
	if (ppstack.empty()) 
	{
		// get a node and assign that as root
		
		BTreeNode* newNode = new BTreeNode() ;
		newNode->element.push_back(thePair) ;
		newNode->child.push_back(root) ;
		newNode->child.push_back(splitChild2) ;
		root = newNode ;

		/*for (int j = 0 ; j < root->element.size() ; j++)
				cout << root->element.at(j).first << "\t" ;
			cout << endl ;*/
		

		
	}
	else 
	{	
		BTreeNode* parent = ppstack.top() ; 
		ppstack.pop() ; // TODO: if the stack is not empty

			vector<pair<int,int> >::iterator it ;
			vector<BTreeNode* >::iterator it2 ;

			
			
			parent->element.push_back(thePair)  ; // is this operation correct??
			
			sort(parent->element.begin() , parent->element.end()) ;
			
			it = find(parent->element.begin() , parent->element.end() , thePair) ;
			
			
			// get the index
			ind = it - parent->element.begin() ;
//			cout << "ind " << ind << endl ;
			it2 = parent->child.begin();
			
			it2 = it2+ ind + 1;
/*if (splitChild2 == NULL) cout << "yes NULL" << endl ;
			cout << "it2-begin " << it2 - parent->child.begin() << endl ;
			cout << "parent->child.size() " << parent->child.size() << endl ;
			cout << "parent->element.size() " << parent->element.size() << endl ;
			cout << "mWay " << mWay << endl ;*/
			parent->child.insert(it2 , splitChild2) ;
			
			

		/*	for (int j = 0 ; j < parent->element.size() ; j++)
				cout << parent->element.at(j).first << "\t" ;
			cout << endl ;

			for (int j = 0 ; j < parent->child.size() ; j++)
				if (parent->child.at(j)==NULL) cout << "NULL" << "\t" ;
				else cout << "NOT NULL" << "\t" ;
			cout << endl ;*/
		// }
		if (parent->element.size() == mWay) // node became overfull after above insertion
		{
			
			int d = ceil((double)mWay / 2) ;
/*cout << "m " << mWay << endl ;
cout << "d " << d << endl ;*/
			// create the overfull node
			//parent->element.push_back(thePair) ;
			//sort(parent->element.begin() , parent->element.end()) ;
			
			// now split at index d
			vector<pair<int,int> >::iterator it = parent->element.begin() ;
			vector<BTreeNode*>::iterator it2 = parent->child.begin() ;
			
			it = it + d - 1 ;
		// cout << "*it" << it->first<< endl ;
			it2 = it2 + d ;
			
			pair<int,int> pairToBePassedUp = *it ; 
			
			// it++ ;
			
			BTreeNode* newSplitChild2 = new BTreeNode() ;
			
			for (it=parent->element.begin()+d ; it != parent->element.end() ; it++)
				newSplitChild2->element.push_back(*it) ;

/*for (int i = 0 ; i < parent->element.size() ; i++)
	cout << "parent->element" << parent->element[i].first << endl ;
for (int i = 0 ; i < newSplitChild2->element.size() ; i++)
	cout << "splitchild->element" << newSplitChild2->element[i].first << endl ;*/
			//copy(it , parent->element.end() , newSplitChild2->element.begin()) ;
			
			for (it2 = parent->child.begin()+d ; it2 != parent->child.end() ; it2++)
				newSplitChild2->child.push_back(*it2) ;
			// copy(it2 , parent->child.end() , newSplitChild2->child.begin()) ;
			parent->element.erase(parent->element.begin()+d-1 , parent->element.end()) ;
			parent->child.erase(parent->child.begin()+d , parent->child.end()) ;
			
			insertInParent(pairToBePassedUp , newSplitChild2 , ppstack) ;

		}

	}
}

// implementation of insert function
void BTree::insert(const pair<int,int>& thePair) // check the correctness of this function
{
	// cout << "going to insert this Pair " << thePair.first << endl ;
	// find where to insert this
	BTreeNode* p = root ; 
	stack<BTreeNode*> ppstack ;
	
	while (p != NULL)
	{
//	cout << "not NULL" << endl ;	
		// TODO: put a check for BadInput for equal key
		// find where the pair lies
		if (p->element.size() == 1)
		{
			
			if (thePair.first < p->element[0].first)
			{
				
				ppstack.push(p) ;
				p = p->child[0] ;
			}
			else
			{
				
				ppstack.push(p) ;
				p = p->child[1] ;
				
			}
		}
		
		else
		{
		for (int i = 0 ; i < p->element.size()-1 ; i++)
		{
			
			if (thePair.first == p->element.at(i).first)
			{// throw Bad Input exception
				cout << "here you go" << endl ;
			}
			else if (thePair.first < p->element[i].first)
			{  ppstack.push(p) ; p = p->child[i] ; break ;}
			else if ((thePair.first > p->element[i].first) && 
					(thePair.first < p->element[i+1].first))
			{ ppstack.push(p) ; p = p->child[i+1] ; break ;}
		}
		
		
		if (p != NULL && thePair.first > p->element[p->element.size()-1].first) // check does that happen or do I have to advance i by i++ or do I need ++i in for loop.
		{ppstack.push(p) ; p = p->child[p->element.size()] ;} // do I need to check whether thePair.first > p->element[i].first??
		}
	// cout << "hiiiii " << endl ;
// if (p == NULL) cout << "p is NULL " << endl ;	
	}
	
	insertInParent(thePair , NULL , ppstack) ;

}

#endif
