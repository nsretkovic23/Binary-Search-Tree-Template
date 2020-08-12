#include<iostream>
#include "Node.h"
#include"BSTree.h"


void main()
{
	Node<int>* n1 = new Node<int>();
	BSTree<int> tree;
	tree.addLeaf(5);
	tree.addLeaf(15);
	tree.addLeaf(1);
	tree.addLeaf(70);
	tree.printInOrder(); 
	std::cout<<std::endl;

	n1 = tree.findMeNode(70); 
	n1->printData();
	std::cout << std::endl;

	tree.printChildren(15);
	std::cout << std::endl;

	tree.deleteNode(70);
	tree.printInOrder();
	

	




}