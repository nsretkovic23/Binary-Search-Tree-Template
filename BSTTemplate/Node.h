#pragma once
#include<iostream>
template<class T>
class Node
{
public:
	T key; //data
	Node* left;
	Node* right;
public:
	Node() { left = right = NULL; }
	Node(T el);
	Node(T el, Node* l, Node* r);
	T NodeData();
	void printData();

};

template<class T>
inline Node<T>::Node(T key)
{
	this->key = key;
	left = right = NULL;
}

template<class T>
inline Node<T>::Node(T el, Node* l, Node* r)
{
	this->key = el;
	left = l;
	right = r;
}

template<class T>
T Node<T>::NodeData()
{
	return key;
}
template<class T>
void Node<T>::printData()
{
	std::cout << key; //if using custom types, << overload needed
}


