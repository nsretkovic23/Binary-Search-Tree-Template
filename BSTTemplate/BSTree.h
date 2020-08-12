#pragma once
#include<iostream>
#include"Node.h"
template<class T>
class BSTree
{
private:
	Node<T>* root;

	void addLeafPrivate(T data, Node<T>* ptr);
	void printInOrderPrivate(Node<T>* ptr);
	Node<T>* findMeNodePrivate(T data, Node<T>* ptr);
	void deleteNodePrivate(T data, Node<T>* ptr);
	T findSmallestInSubtreePriv(Node<T>* ptr);
	void removeNodeMatch(Node<T>* parent, Node<T>* match, bool left); //removing match, boolean is relationship between parent and match
public:
	BSTree(){root = NULL; numel = 0;};
	Node<T>* newLeaf(T data);
	void addLeaf(T data);
	void printInOrder(); //recursive way
	Node<T>* findMeNode(T data);
	void printChildren(T data);
	T findSmallestInSubtree();
	void deleteNode(T data);
	void deleteRoot();
};

template<class T>
inline Node<T>* BSTree<T>::newLeaf(T data)
{
	Node<T>* leaf = new Node<T>;
	leaf->key = data;
	leaf->left = NULL;
	leaf->right = NULL;
	return leaf;
}

template<class T>
inline void BSTree<T>::addLeaf(T data)
{
	addLeafPrivate(data, root);
}

template<class T>
inline void BSTree<T>::addLeafPrivate(T data, Node<T>* ptr)
{
	if (root == NULL)
	{
		root = newLeaf(data);
	}
	else if (data < ptr->key)
	{
		if (ptr->left != NULL)
		{
			addLeafPrivate(data, ptr->left);
		}
		else
		{
			ptr->left = newLeaf(data);
		}
	}
	else if (data > ptr->key)
	{
		if (ptr->right != NULL)
		{
			addLeafPrivate(data, ptr->right);
		}
		else 
		{
			ptr->right = newLeaf(data);
		}
	}
	else //case if equals
	{
		std::cout << "Node with this value is already added to the tree!" << std::endl;
	}
}

template<class T>
inline T BSTree<T>::findSmallestInSubtree()
{
	return findSmallestInSubtreePriv(root);
}

template<class T>
inline T BSTree<T>::findSmallestInSubtreePriv(Node<T>* ptr)
{
	if (root != NULL)
	{
		if (ptr->left != NULL)
		{
			return findSmallestInSubtreePriv(ptr->left);
		}
		else
		{
			return ptr->key;
		}
	}
	else
	{
		std::cout << "Can not fint smallest value in a subree, tree is empty!" << std::endl;
		return NULL;
	}
}

template<class T>
inline void BSTree<T>::printInOrder()
{
	printInOrderPrivate(root);
}

template<class T>
inline void BSTree<T>::printInOrderPrivate(Node<T>* ptr)
{
	if (root != NULL)
	{
		if (ptr->left != NULL)
		{
			printInOrderPrivate(ptr->left);
		}
		std::cout << ptr->key << std::endl; //could use a printData() from Node class too
		if (ptr->right != NULL)
		{
			printInOrderPrivate(ptr->right);
		}
	}
	else
	{
		std::cout << "Thre tree is empty!"<<std::endl;
		return;
	}
}

template<class T>
inline Node<T>* BSTree<T>::findMeNode(T data)
{
	return findMeNodePrivate(data, root);
}

template<class T>
inline Node<T>* BSTree<T>::findMeNodePrivate(T data, Node<T>* ptr)
{
	if (ptr != NULL)
	{
		if (ptr->key == data)
		{
			return ptr;
		}
		else
		{
			if (data < ptr->key) //for custom types, operators like <,>,== etc. have to be overloaded
			{
				return findMeNodePrivate(data, ptr->left);
			}
			else
			{
				return findMeNodePrivate(data, ptr->right);
			}
		}
	}
	else
		return NULL;
}


template<class T>
void BSTree<T>::printChildren(T data)
{
	Node<T>* ptr = findMeNode(data);

	if (ptr != NULL)
	{
		std::cout << "Parent Node value: " << ptr->key<<std::endl;

		ptr->left == NULL ? std::cout << "Doesn't have left child"<<std::endl : std::cout << "Left child value: " << ptr->left->key << std::endl;
		ptr->right == NULL ? std::cout << "Doesn't have right child"<<std::endl : std::cout << "Right child value: " << ptr->right->key << std::endl;

	}
	else
	{
		std::cout << "Node with key " << data << " doesn't exist in the tree!" << std::endl;
	}
}

template<class T>
void BSTree<T>::removeNodeMatch(Node<T>* parent, Node<T>* match, bool left)
{
	if (root != NULL)
	{
		Node<T>* helpPtr;
		T matchKey = match->key;
		T smallestInRightSub; //if node has 2 children, find smallest in right subtree and replace

		if (match->left == NULL && match->right == NULL) //0 children case
		{
			helpPtr = match;
			left == true ? parent->left = NULL : parent->right = NULL;
			std::cout << "Deleted node with 0 children" << std::endl;
		}
		else if (match->left == NULL && match->right != NULL) //1 child case(right)
		{
			left == true ? parent->left = match->right : parent->right = match->right;
			match->right = NULL;
			helpPtr = match;
			delete helpPtr;
			std::cout << "Deleted node with 1 child(right)" << std::endl;
		}
		else if (match->left != NULL && match->right == NULL) //1 child case(right)
		{
			left == true ? parent->left = match->left : parent->right = match->left;
			match->left = NULL;
			helpPtr = match;
			delete helpPtr;
			std::cout << "Deleted node with 1 child(left)" << std::endl;
		}
		else
		{
			smallestInRightSub = findSmallestInSubtreePriv(match->right);
			deleteNodePrivate(smallestInRightSub, match);
			match->key = smallestInRightSub;
		}
	}
	else
	{
		std::cout << "Can not remove match, tree is empty!" << std::endl;
	}
}

template<class T>
inline void BSTree<T>::deleteRoot()
{
	if (root != NULL)
	{
		Node<T>* helpPtr = root;
		T rootkey = root->key;
		T smallestRight; //smallest value in right subtree which will replace deleted root

		if (root->left == NULL && root->right == NULL) //0 children case
		{
			root = NULL;
			delete helpPtr;
		}
		else if (root->left != NULL && root->right == NULL) //1 child case(left), have to do separate cases for left and right child
		{
			root = root->left;
			helpPtr->left = NULL;
			delete helpPtr;
			std::cout << "Root with only left child removed, new root is: " << root->key<<std::endl;
		}
		else if (root->left == NULL && root->right != NULL)//1 child case(right)
		{
			root = root->right;
			helpPtr->right = NULL;
			delete helpPtr;
			std::cout << "Root with only right child removed, new root is: " << root->key << std::endl;
		}
		else
		{
			smallestRight = findSmallestInSubtreePriv(root->right);
			deleteNodePrivate(smallestRight, root); // don't have to delete root, just delete node and overwrite root value
			root->key = smallestRight;
			std::cout << "Root with 2 childs now has value: " << smallestRight << std::endl;
		}
	}
	else
	{
		std::cout << "Can not delete root, three is empty!" << std::endl;
	}

}

template<class T>
inline void BSTree<T>::deleteNode(T data)
{
	deleteNodePrivate(data, root);
}

template<class T>
inline void BSTree<T>::deleteNodePrivate(T data, Node<T>* ptr)
{
	if (root != NULL)
	{
		if (root->key == data)
		{
			deleteRoot();
		}
		else
		{
			if (data < ptr->key && ptr->left != NULL)
			{
				ptr->left->key == data ? removeNodeMatch(ptr, ptr->left, true) : deleteNodePrivate(data, ptr->left);
			}
			else if (data > ptr->key && ptr->right != NULL)
			{
				ptr->right->key == data ? removeNodeMatch(ptr, ptr->right, false) : deleteNodePrivate(data, ptr->right);
			}
			else
			{
				std::cout << "Node with given value is not in the tree!";
			}

		}
	}
	else
	{
		std::cout << "The tree is empty!" << std::endl;
	}
}



