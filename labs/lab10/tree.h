#ifndef TREE_H
#define TREE_H

#include "node.h"

struct Tree {
	Node *root;						//the root node of tree
	int nodecount;					

	int numNode;					//total number of nodes, changes by findNumNode function
	int numLeaf;					//total number of leaves, changes by findNumLeaf function

	void createTree();				//creates the random array and sends it to the tree create
	Node* btdAdd(int[], int, int);	//creates tree from array
	Node* newNode(int);				//creates new nodes for tree
	void removeTree(Node *);		//clears tree from memory
	void printPreorder(Node *);		//prints tree in preorder
	void printInorder(Node *);		//prints tree in inorder
	void printPostorder(Node *);	//prints tree in postorder
	int findMax();					//finds max value from tree by following always right node of the root node
	int findMin();					//finds min value from tree by following always left node of the root node
	void findNumNode(Node *);		//finds numbers of nodes in tree, includes leaves also
	void findNumLeaf(Node *);		//finds the leaves, which do not have any children
	int calculateDepth(Node *);		//calculates the depth of tree
	int calculateSum(Node *);		//sums all of the node's data
	float calculateAverage(Node *);	//calculates the average of node's data

};

#endif