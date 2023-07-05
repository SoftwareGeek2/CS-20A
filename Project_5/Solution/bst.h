#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H


#include<functional>
#include<iostream>
#include<assert.h>
#include"bstnode.h"

template<typename Item>
class BinarySearchTree {

public:
	// Public Interface Functions: All of these are implemented
	BinarySearchTree();
	~BinarySearchTree();

	void	printInorder();
	void	printPostorder();
	void	printPreorder();
	void	insert(Item item);

	void	remove(Item item);

	Item	min() const;
	Item	max() const;
	int		height() const;
	bool	search(Item item) const;

	bool	empty() const;

	void	printTree() const;

private:

	// Member variable root
	Node<Item>* root;

	//Auxillary recursive bst functions
	//public interface functions call these
	//You will implement these functions.

	// Tree traversal, second parameter is a "function" with 
	// return type void and parameter Node*, i.e: 
	//					void process(Node* )
	void inorder(Node<Item>* node, std::function<void(Node<Item>*)> proc);
	void preorder(Node<Item>* node, std::function<void(Node<Item>*)> proc);
	void postorder(Node<Item>* node, std::function<void(Node<Item>*)> proc);

	Node<Item>* min(Node<Item> *node) const;
	Node<Item>* max(Node<Item> *node) const;
	int   height(Node<Item>* node) const;

	Node<Item>* insert(Node<Item> *node, Item item);
	bool  search(Node<Item> *node, Item item) const;

	Node<Item>* remove(Node<Item> *node, Item item);

	void  printTree(Node<Item> *node, int space) const;
};


//----------------------------------------------------------
//-------------- Binary Search Tree Function Implementations 
// 
//  Public Interface functions
// 		Completley Implemented, nothing to do.  These functions 
//      call the recursive helper functions you will implement
//		below.

// Constructor
template<typename Item>
BinarySearchTree<Item>::BinarySearchTree() :root(nullptr) {}

// Destructor
template<typename Item>
BinarySearchTree<Item>::~BinarySearchTree() {

	//Use the post order traversal to delete the nodes.
	//lambda function to delete a node n: 
	//				[](Node* n) {delete n; } 
	postorder(root, [](Node<Item>* n) {delete n; });
}
template<typename Item>
void BinarySearchTree<Item>::printInorder() {

	//Use inorder traversal to print items in a node in the tree.
	//lambda function to print the item in a node:
	//lambda to print->	"[](Node* n) {std::cout << n->item() << std::endl; }"
	inorder(root, [](Node<Item>* n) {std::cout << n->item() << " "; });

	std::cout << std::endl;
}
template<typename Item>
void BinarySearchTree<Item>::printPreorder() {

	//Use pre order traversal to print items in a node in the tree.
	//lambda function to print the item in a node:
	//lambda to print->	"[](Node* n) {std::cout << n->item() << std::endl; }"
	preorder(root, [](Node<Item>* n) {std::cout << n->item() << " "; });
	std::cout << std::endl;
}
template<typename Item>
void BinarySearchTree<Item>::printPostorder() {

	//Use post order traversal to print items in a node in the tree.
	//lambda function to print the item in a node:
	//lambda to print->	"[](Node* n) {std::cout << n->item() << std::endl; }"
	postorder(root, [](Node<Item>* n) {std::cout << n->item() << " "; });
	std::cout << std::endl;
}
template<typename Item>
void BinarySearchTree<Item>::insert(Item item) {
	root = insert(root, item);
}
template<typename Item>
void BinarySearchTree<Item>::remove(Item item) {
	root = remove(root, item);
}
template<typename Item>
Item	BinarySearchTree<Item>::min() const {

	assert(root != nullptr);

	Node<Item>* node = min(root);
	return node->item();
}
template<typename Item>
Item	BinarySearchTree<Item>::max() const {

	assert(root != nullptr);

	Node<Item>* node = max(root);
	return node->item();
}
template<typename Item>
int	BinarySearchTree<Item>::height() const {

	return height(root);
}
template<typename Item>
bool BinarySearchTree<Item>::search(Item item) const {
	return search(root, item);
}
template<typename Item>
bool BinarySearchTree<Item>::empty() const {
	return (root == nullptr);
}
template<typename Item>
void BinarySearchTree<Item>::printTree() const {
	printTree(root, 0);
}

//----------------------------------------------------------
//
// Private Recursive Functions: You Implement These.
//

// Inorder Traversal: Implemented so you can see how passing a function into 
// another function works, other traversals remain for you to implement.  the second
// parameter, proc, is a function and we see that its return type is void and it 
// has a Node* as a parameter.  Any function of that form passed into inorder will be
// called as seen below.  
// If we assume that we use the printing lambda defined above you can imagine that proc 
// is defined as:
//		void proc(Node<Item> * n){std::cout << n->item() << " "; }
template<typename Item>
void BinarySearchTree<Item>::inorder(Node<Item>* node, std::function<void(Node<Item>*)> proc) {
	if (node == nullptr)
		return;

	inorder(node->left(), proc);
	proc(node);
	inorder(node->right(), proc);

}

// This function is used to traverse and process a binary tree in post-order manner.
// Post-order traversal visits left subtree, right subtree, and the node itself, in that order.
template<typename Item>
void BinarySearchTree<Item>::postorder(Node<Item>* node, std::function<void(Node<Item>*)> proc) {
    // Base condition: if node is null, return
    if (node == nullptr)
        return;

    // First, recursively traverse the left subtree
    postorder(node->left(), proc);

    // Then, recursively traverse the right subtree
    postorder(node->right(), proc);

    // Finally, process the node
    proc(node);
}

// This function is used to traverse and process a binary tree in pre-order manner.
// Pre-order traversal visits the node itself, left subtree, and right subtree, in that order.
template<typename Item>
void BinarySearchTree<Item>::preorder(Node<Item>* node, std::function<void(Node<Item>*)> proc) {
    // Base condition: if node is null, return
    if (node == nullptr)
        return;

    // First, process the node
    proc(node);

    // Then, recursively traverse the left subtree
    preorder(node->left(), proc);

    // Finally, recursively traverse the right subtree
    preorder(node->right(), proc);
}


// BinarySearchTree::insert recursively inserts into the BST according 
// to the rules of the BST.  
// This function is used to insert a new node with the specified item into the binary search tree.
// The new node is always inserted at the leaf.
template<typename Item>
Node<Item>* BinarySearchTree<Item>::insert(Node<Item>* node, Item item) {
    // Base condition: if node is null, create a new node with the item and return
    if (node == nullptr)
        return new Node<Item>(item, nullptr, nullptr);

    // If item is less than the node's item, then insert it into the left subtree
    if (item < node->item())
        node->left(insert(node->left(), item));

    // If item is greater than the node's item, then insert it into the right subtree
    else if (item > node->item())
        node->right(insert(node->right(), item));

    // If item is equal to the node's item, ignore it (or replace, as per requirements)

    // Return the (possibly new) node
    return node;
}


// BinarySearchTree<Item>::search recursively searches the tree for item.
// This function searches for an item in the binary search tree.
// Returns true if found, false otherwise.
template<typename Item>
bool BinarySearchTree<Item>::search(Node<Item>* node, Item item) const {
    // Base condition: if node is null, item is not found
    if (node == nullptr)
        return false;

    // If item is equal to the node's item, item is found
    if (item == node->item())
        return true;

    // If item is less than the node's item, search in the left subtree
    if (item < node->item())
        return search(node->left(), item);

    // If item is greater than the node's item, search in the right subtree
    return search(node->right(), item);
}


// BinarySearchTree<Item>::height
// Height of a binary tree is the height of the largest subtree + 1
// An empty tree has height 0;
// This function calculates the height of a binary search tree.
// Height of a binary tree is the height of the largest subtree + 1.
// An empty tree has height 0.
template<typename Item>
int BinarySearchTree<Item>::height(Node<Item>* node) const {
    // Base condition: if node is null, height is 0
    if (node == nullptr)
        return 0;

    // Calculate the height of the left subtree
    int leftHeight = height(node->left());

    // Calculate the height of the right subtree
    int rightHeight = height(node->right());

    // Return the height of the largest subtree + 1
    return std::max(leftHeight, rightHeight) + 1;
}

// BinarySearchTree<Item>::min recursively obtain the node with the minimum item
// This function finds the node with the minimum item in the binary search tree.
// The node with the minimum item is the leftmost node.
template<typename Item>
Node<Item>* BinarySearchTree<Item>::min(Node<Item>* node) const {
    // Base condition: if node's left child is null, this node has the minimum item
    if (node->left() == nullptr)
        return node;

    // Otherwise, the node with the minimum item is in the left subtree
    return min(node->left());
}


// BinarySearchTree<Item>::max recursively obtain the node with the minimum item
// This function finds the node with the maximum item in the binary search tree.
// The node with the maximum item is the rightmost node.
template<typename Item>
Node<Item>* BinarySearchTree<Item>::max(Node<Item>* node) const {
    // Base condition: if node's right child is null, this node has the maximum item
    if (node->right() == nullptr)
        return node;

    // Otherwise, the node with the maximum item is in the right subtree
    return max(node->right());
}


// BinarySearchTree<Item>::printTree
// Prints the BST in a tree format rotated -90 degrees.  Uses space to 
// signify the space between levels of the tree. Uses the inorder 
// traversal but traverses right first, rather than left. Cannot use
// any of the other travel functions because of this.
//
// parameter space determines the number of spaces needed for each level.
// Example binary shows 5 spaces between levels. 
//
// i.e. traverse right 
//		print appropriate number of spaces 
//		print item 
//		traverse left
//
// It never makes sense to use loops to facilitate increasing recursive depth
// But that doesn't mean you should not use loops for other purposes that are
// not related to the actuall recursion.  
// This function prints the binary search tree in a tree format rotated -90 degrees.
// The space parameter determines the number of spaces needed for each level.
template<typename Item>
void BinarySearchTree<Item>::printTree(Node<Item>* node, int space) const {
    // Base condition: if node is null, return
    if (node == nullptr)
        return;

    // Increase distance between levels
    space += 5;

    // First print the right subtree
    printTree(node->right(), space);

    // Print current node after spaces
    std::cout << std::endl;
    for (int i = 5; i < space; i++)
        std::cout << ' ';
    std::cout << node->item();

    // Then print the left subtree
    printTree(node->left(), space);
}

//BinarySearchTree<Item>::remove
//
// Make sure you're comfortable with the iterative solution seen in the lecture slides
// before thinking about how to do it recursively.
//
// Recursively removes a node in the binary tree.  The recursive algorithm will 
// be different than the iterative algorithm.  The iterative algorithm conisted
// of first finding the node using two pointers so that we know how to rearrange
// the children of the deleted node. In recursion we are passing in the sub trees
// each recursive step, so by definition we already have a handle on each subtrees'
// parents (it is the node that is passed into the previous recursive step).
// After we search the node to remove (if it is in the tree) everything else is the same, we  
// handle the three cases: leaf, one child (which consist of two cases: left vs right),
// and two children.  With iterative algorithm there were subcases regardling if the 
// node was root or not, with recursion we get that for free.  
//
// In the iterative algorithm discussed in class, in dealing with a node with two children
// We swapped items from one of the nodes in either subtree.  For the recursive algorithm
// We just want to write the subtree node's item into the node to be deleted, not actually 
// swap. This way subtree remains a valid bst, so we can recurse on that subtree and 
// recursively call _deleteNode on that item (not the original) to remove that node.  
// 
// It takes a bit to wrap your head around this, use the 6 steps, draw lots of pictures.
// 
// Recursively removes a node from the binary search tree.
template<typename Item>
Node<Item>* BinarySearchTree<Item>::remove(Node<Item>* node, Item item) {
    // Base condition: if node is null, return null
    if (node == nullptr)
        return nullptr;

    // If item is less than node's item, it is in the left subtree
    if (item < node->item())
        node->left(remove(node->left(), item));
    // If item is greater than node's item, it is in the right subtree
    else if (item > node->item())
        node->right(remove(node->right(), item));
    else {
        // Case 1: Node to be deleted has no children (leaf node)
        if (node->left() == nullptr && node->right() == nullptr) {
            delete node;
            node = nullptr;
        }
        // Case 2: Node to be deleted has one child
        else if (node->left() == nullptr) {
            Node<Item>* temp = node;
            node = node->right();
            delete temp;
        }
        else if (node->right() == nullptr) {
            Node<Item>* temp = node;
            node = node->left();
            delete temp;
        }
        // Case 3: Node to be deleted has two children
        else {
            // Find the minimum node in the right subtree (successor)
            Node<Item>* temp = min(node->right());
            // Copy the successor's item to this node
            node->item(temp->item());
            // Recursively delete the successor
            node->right(remove(node->right(), temp->item()));
        }
    }
    return node;
}






































































// MMXM


























































#endif//BINARYSEARCHTREE_H_MMX