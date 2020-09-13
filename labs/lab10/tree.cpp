#include "tree.h"
#include "node.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define N 10		// N, array size and random limits

using namespace std;

void Tree::createTree() {
	root = NULL;
	nodecount = 0;

	int array[N] = { 0 };
	bool isHere;
	int i = 0;

	srand(time(NULL));
	for (int i = 0; i < N; i++) { //create array randomly
		int x;
		x = 1 + (rand() % N);
		array[i] = x;
	}

	int temp;

	for (int a = 0; a < (N - 1); a++){
		for (int b = 0; b < N - a - 1; b++){
			if (array[b] > array[b + 1]){
				temp = array[b];
				array[b] = array[b + 1];
				array[b + 1] = temp;
			}
		}
	}

	int k = 0;
	int l = 1;
	while (l < N){
		if (array[l] == array[k]){
			l++;
		}
		else{
			array[++k] = array[l++];
		}
	}
	int *exactArray;
	exactArray = new int[k + 1];
	for (int x = 0; x < k + 1; x++){
		exactArray[x] = array[x];
	}

	int n = k + 1;

	/*int exactArray[] = { 1, 2, 3, 4 }; DENEME

	int n = sizeof(exactArray) / sizeof(exactArray[0]);*/
	root = btdAdd(exactArray, 0, n - 1);

}

Node* Tree::btdAdd(int arr[], int start, int end){
	Node *exactRoot;
	if (start > end){
		return NULL;
	}

	int mid = (start + end) / 2;
	exactRoot = newNode(arr[mid]);

	exactRoot->left = btdAdd(arr, start, mid - 1);
	exactRoot->right = btdAdd(arr, mid + 1, end);

	return exactRoot;

}

Node* Tree::newNode(int data){
	Node *newnode;
	newnode = new Node;
	newnode->data = data;
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
}

void Tree::removeTree(Node *p) {
	if (p) {
		if (p->left != NULL) {
			removeTree(p->left);
			p->left = NULL;
		}
		if (p->right != NULL) {
			removeTree(p->right);
			p->right = NULL;
		}
		delete p;
	}
}

void Tree::printPreorder(Node *p) {
	if (p) {
		cout << p->data << " ";
		printPreorder(p->left);
		printPreorder(p->right);
	}
}

void Tree::printInorder(Node *p) {
	
	if (p) {
		printInorder(p->left);
		cout << p->data << " ";
		printInorder(p->right);
	}
}

void Tree::printPostorder(Node *p) {
	if (p) {
		printPostorder(p->left);
		printPostorder(p->right);
		cout << p->data << " ";
	}
}

int Tree::findMax() {
	Node *traverse;
	traverse = root;

	if (traverse == NULL){
		return 0;
	}

	while (traverse) {
		if (traverse->right) {
			traverse = traverse->right;
		}
		else {
			break;
		}
	}

	return traverse->data;
}

int Tree::findMin() {
	Node *traverse;
	traverse = root;
	
	if (traverse == NULL){
		return 0;
	}

	while (traverse) {
		if (traverse->left) {
			traverse = traverse->left;
		}
		else {
			break;
		}
	}

	return traverse->data;
}

void Tree::findNumNode(Node *p) {
	if (p == NULL){
		return;
	}
	if (p) { // post order
		findNumNode(p->left);
		findNumNode(p->right);
		numNode++;
	}
}

void Tree::findNumLeaf(Node *p){
	if (p == NULL){
		return;
	}

	if (p){
		findNumLeaf(p->left);
		findNumLeaf(p->right);
		if (p->left == NULL && p->right == NULL){
			numLeaf++;
		}
	}
}

int Tree::calculateDepth(Node *p){
	if (p == NULL){
		return 0;
	}
	else{
		int depthOfLeft = calculateDepth(p->left);
		int depthOfRight = calculateDepth(p->right);

		if (depthOfLeft > depthOfRight){
			return (depthOfLeft + 1);
		}
		else{
			return (depthOfRight + 1);
		}
	}
}

int Tree::calculateSum(Node *p){
	if (p == NULL){
		return 0;
	}
	else{
		return (p->data) + calculateSum(p->left) + calculateSum(p->right);
	}
}

float Tree::calculateAverage(Node *p){
	if (p == NULL){
		return 0;
	}
	else{
		numNode = 0;
		findNumNode(p);
		return (float) calculateSum(p) / numNode;
	}
}