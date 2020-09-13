#include "tree.h"
#include "node.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

Tree forest;

bool doOperation(char);		//wait operation from user
void printMenu();			//prints whole menu
bool isCreated = false;

int main() {
	bool exit = false;
	char op;

	//forest.createTree();

	while (!exit) {
		printMenu();
		cin >> op;
		exit = doOperation(op);
	}
	return EXIT_SUCCESS;
}

void printMenu() {
	cout << "Select one of the commands given below:" << endl;
	cout << "1: Create new tree" << endl;
	cout << "P: Print Preorder" << endl;
	cout << "I: Print Inorder" << endl;
	cout << "O: Print Postorder" << endl;
	cout << "M: Find MAX" << endl;
	cout << "N: Find MIN" << endl;
	cout << "R: Find total number of nodes" << endl;
	cout << "W: Find total numbmer of leaves" << endl;
	cout << "C: Calculate depth of tree" << endl;
	cout << "S: Calculate sum of all nodes" << endl;
	cout << "A: Calculate the average of all nodes" << endl;
	cout << "X: Exit the application" << endl;
	cout << "Enter operation: ";
}

bool doOperation(char operation) {
	bool returnValue;
	char op;
	switch (operation) {
	case '1':
		if (isCreated){
			forest.removeTree(forest.root);
		}
		forest.createTree();
		isCreated = true;
		returnValue = false;
		break;
	case 'P': case 'p':
		forest.printPreorder(forest.root);
		returnValue = false;
		break;
	case 'I': case 'i':
		forest.printInorder(forest.root);
		returnValue = false;
		break;
	case 'O': case 'o':
		forest.printPostorder(forest.root);
		returnValue = false;
		break;
	case 'M': case 'm':
		int maxValue;
		maxValue = forest.findMax();
		cout << endl << "Max node is " << maxValue << endl;
		returnValue = false;
		break;
	case 'N': case 'n':
		int minValue;
		minValue = forest.findMin();
		cout << endl << "Min node is " << minValue << endl;
		returnValue = false;
		break;
	case 'R': case 'r':
		forest.findNumNode(forest.root);
		cout << endl << "Num of nodes is " << forest.numNode << endl;
		returnValue = false;
		break;
	case 'W': case 'w':
		forest.findNumLeaf(forest.root);
		cout << endl << "Num of leaves is " << forest.numLeaf << endl;
		returnValue = false;
		break;
	case 'C': case 'c':
		cout << endl << "Depth is " << forest.calculateDepth(forest.root) << endl;
		returnValue = false;
		break;
	case 'S': case 's':
		cout << endl << "Sum of all nodes is " << forest.calculateSum(forest.root) << endl;
		returnValue = false;
		break;
	case 'A': case 'a':
		cout << endl << "Average of all nodes is " << forest.calculateAverage(forest.root) << endl;
		returnValue = false;
		break;
	case 'X': case 'x':
		forest.removeTree(forest.root);
		returnValue = true;
		break;
	default:
		cout << endl << "Entered wrong operation." << endl;
		cout << "Try again: ";
		cin >> op;
		returnValue = doOperation(op);
	}

	return returnValue;
}