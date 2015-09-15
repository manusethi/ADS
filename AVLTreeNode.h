#ifndef AVLTreeNode_
#define AVLTreeNode_
#include <utility>
using namespace std ;

class AVLTreeNode
{
public : 
        pair<int, int> element ;
        AVLTreeNode *leftChild ;
        AVLTreeNode *rightChild ;
	int bf ;

        // Default constructor
        AVLTreeNode()
        {
                leftChild = NULL ;
                rightChild = NULL ;
		bf = 0 ;
        }

        // one argument constructor
        AVLTreeNode(const pair<int,int>& theElement) : element(theElement)
        {
                leftChild = NULL ;
                rightChild = NULL ;
		bf = 0 ;
        }

        // constructor
        AVLTreeNode(pair<int,int>& theElement , AVLTreeNode* theLeftChild , AVLTreeNode* theRightChild) :
        element(theElement) , leftChild(theLeftChild) , rightChild(theRightChild)
        {bf = 0 ;}

} ;

#endif

