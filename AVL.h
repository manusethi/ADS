#ifndef AVL_
#define AVL_
#include <utility>
#include "AVLTreeNode.h"

using namespace std ;

namespace std 
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
}

class AVL
{
public : 
	AVL() {root = NULL ; } 
	pair<int , int>* find(int theKey)  ; // returning int* so as to get the iterator
	void insert(const pair<int , int>& thePair) ; // I have made the element const int since no duplicate keys are there
	void inOrder(ostream&) const ;
	void postOrder(ostream&) ;

private :
	AVLTreeNode* root ;
	void adjustBFA2N(AVLTreeNode* parentNode , AVLTreeNode* newNode) ;
	void inOrderInside(ostream& out , AVLTreeNode* t) const ;
	void postOrderInside(ostream& out , AVLTreeNode* t) ;

} ;

// implementation of inOrder
void AVL::inOrder(ostream& out) const  
{
	cout << "starting inOrder traversal" << endl ;
	cout << "================================================" << endl ;
	AVLTreeNode* t = root ;
	inOrderInside(out,t) ;
	cout << endl ;
	out << endl ;
}

void AVL::inOrderInside(ostream& out , AVLTreeNode* t) const
{
	if (t != NULL)
    {
      inOrderInside(out,t->leftChild) ;
      out << t->element.second << " " ;
      inOrderInside(out,t->rightChild) ;
	}
}

// implementation of postOrder
void AVL::postOrder(ostream& out)
{
	cout << "starting postOrder traversal" << endl ;
	cout << "================================================" << endl ;
	AVLTreeNode* t = root ;
	postOrderInside(out,t) ;
	cout << endl ;
}

void AVL::postOrderInside(ostream& out , AVLTreeNode* t)
{
	if (t != NULL)
    {
      postOrderInside(out,t->leftChild) ;
      out << t->element.second << " " ;
      postOrderInside(out,t->rightChild) ;
	}
}

// implementation of find function
pair<int , int>* AVL::find(int theKey) 
{
	// start searching recursively from the root
	AVLTreeNode* node = root ; // root defined to be null earlier
	// cout << "I am here" << endl ;
	while (node != NULL)
		if (theKey < node->element.first)
			node = node->leftChild ;
		else if (theKey > node->element.first)
			node = node->rightChild ;
		else 
			return &(node->element) ;
		return NULL ;
}
// TODO: overlaod pair
// implementation of adjustBFA2N() function
void AVL::adjustBFA2N(AVLTreeNode* someAncestor , AVLTreeNode* newNode)
{

	// start fromt the ancestor
	while (someAncestor != newNode)
		if (newNode->element.first < someAncestor->element.first) // I can just use .first, this is not the same as BTree
		{
			someAncestor->bf = 1 ;
			someAncestor = someAncestor->leftChild ;
		}
		else
		{
			someAncestor->bf = -1 ;
			someAncestor = someAncestor->rightChild ;
		}
}


// implementation of insert function
void AVL::insert(const pair<int , int>& thePair)
{
	// allocate memory for the new incoming node
	AVLTreeNode* newNode = new AVLTreeNode(thePair) ;

	// Now find where to place this. 
	// Start from the root. Place it where you fall off.
	AVLTreeNode* node = root , *parentNode = NULL,
		*ANode = NULL, *pANode = NULL ;
	while (node != NULL)
	{
		// find the candidate for ANode
		if (node->bf)
		{
			ANode = node ;
			pANode = parentNode ;
		}

		// keep a track of current(or previous) node by
		//  assigning parentNode to node
		parentNode = node ;
		if (thePair.first < (node->element).first)
			node  = node->leftChild ;
		else if (thePair.first > (node->element).first)
			node = node->rightChild ;
		else return ; // what to do here??
	}

	// now place the node
	if (root != NULL)
		if (thePair.first < (parentNode->element).first)
			parentNode->leftChild = newNode ;
		else
			parentNode->rightChild = newNode ;
	else
		root = newNode ;

	// Now we need to adjust balance factors which were 0 earlier 
	// and then do rotation if required

	if (ANode == NULL) // when no ANode exists everynode gets affected till the root logn time
		adjustBFA2N(root , newNode) ; // TODO !!!!

	else if (ANode != NULL && ANode->bf == -1)
		if (thePair.first < ANode->element.first)
		{
			ANode->bf = 0 ;
			adjustBFA2N(ANode->leftChild , newNode) ;
		}
		else
		{
			AVLTreeNode* BNode = ANode->rightChild ;
			if (thePair.first > BNode->element.first)
			{
				// adjust BF before rotation 
				adjustBFA2N(BNode->rightChild , newNode) ;
				// RRrotation
				ANode->rightChild = BNode->leftChild ;
				BNode->leftChild = ANode ;
				if (pANode != NULL)
					// cout << "after pANode RRrotation " ; 
					if (ANode == pANode->leftChild)
						pANode->leftChild = BNode ;
					else
						pANode->rightChild = BNode ;
				else 
					root = BNode ;
				// cout << BNode->bf ;
				// if (BNode != NULL ) cout << "Hi 1" << endl ; 
				ANode->bf = 0 ; 
				// if (ANode != NULL) cout << "Hi 2" << endl ;
				BNode->bf = 0 ;

			}
			else
			{
				// adjust BF before rotation 
				adjustBFA2N(BNode->leftChild , newNode) ;
				//RL rotation
				AVLTreeNode* CNode = BNode->leftChild ;

				ANode->rightChild = CNode->leftChild ;
				BNode->leftChild = CNode->rightChild ;
				CNode->leftChild = ANode ;
				// cout << "check here --Cnode" << endl ;
				CNode->rightChild = BNode ;

				// if (ANode != NULL) cout << "RL: after Cnode = BNode "-- check
				if (ANode != root)
					if (ANode == pANode->leftChild)
						pANode->leftChild = CNode ;
					else
						pANode->rightChild = CNode ;
				else
					root = CNode ;

				if (CNode->bf == 1)
				{
					BNode->bf = -1 ;
					ANode->bf = 0 ;
				}
				else if (CNode->bf == -1)
				{
					BNode->bf = 0 ;
					ANode->bf = 1 ;
				}
				else
				{
					BNode->bf = 0 ;
					ANode->bf = 0 ;
				}
				CNode->bf = 0 ;

			}

		}
	else if (ANode != NULL && ANode->bf == 1)
		if (thePair.first > ANode->element.first)
		{
			ANode->bf = 0 ;
			adjustBFA2N(ANode->rightChild , newNode) ;
		}
		else
		{
			AVLTreeNode* BNode = ANode->leftChild ;
			if (thePair.first < BNode->element.first)
			{
				adjustBFA2N(BNode->leftChild , newNode) ;
				/* if (ANode == NULL !! BNode == NULL) cout << "after CNode LL"
				*/
				// LL rotation
				ANode->leftChild = BNode->rightChild ;
				BNode->rightChild = ANode ;
				if (pANode != NULL)
					if (ANode == pANode->leftChild)
						pANode->leftChild = BNode ;
					else 
						pANode->rightChild = BNode ;
				else 
					root = BNode ;

				ANode->bf = 0 ;
				BNode->bf = 0 ;
			}
			else
			{
				adjustBFA2N(BNode->rightChild , newNode) ;
				// LR rotation
				AVLTreeNode* CNode = BNode->rightChild ;
				ANode->leftChild = CNode->rightChild ;
				BNode->rightChild = CNode->leftChild ;
				CNode->leftChild = BNode ;
				CNode->rightChild = ANode ;

				if (pANode != NULL)
					if (ANode == pANode->leftChild)
						pANode->leftChild = CNode ;
					else
						pANode->rightChild = CNode ;
				else root = CNode ;
				/* if (ANode == NULL !! BNode == NULL) cout << "after CNode LR"
				*/
				if (CNode->bf == 1)
				{
					BNode->bf = 0 ;
					ANode->bf = -1 ;
				}
				else if (CNode->bf == -1)
				{
					BNode->bf = 1 ;
					ANode->bf = 0 ;
				}
				else
				{
					BNode->bf = 0 ;
					ANode->bf = 0 ;
				}
				CNode->bf = 0 ;
			}
		}





}

#endif
