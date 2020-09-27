// -------------------------------- BinTree.h --------------------------------

// Zach Shim
// CSS 343
// Created: June 5th, 2020
// Last Modified: July 18th, 2020

// ---------------------------------------------------------------------------

// BinTree class:    A binary search tree is a special type of binary tree.
//                   - For each node n in a binary search tree, the value of
//                     n is > all of the values in the left subtree and < all
//                     values in the right subtree.
//                   - All subtrees are binary search trees.
//                   - Useful for performing fast lookup (like binary search)
//                     and can be used to sort arrays/lists

// ---------------------------------------------------------------------------

// Notes on specifications, special algorithms, and assumptions.

//   -- operator<< dislplays the nodes of the BinTree in an inorder fashion
//   -- all functions use recursive helpers except the default constructor and
//      isEmpty
//   -- getHeight is implemented in a way works for both Binary Search Trees
//      and general Binary Trees where data could be stored anywhere.
//    - getHeight is implemented using this height definition:
//          The height of a node at a leaf is 1, height of a node at the next
//          level is 2, and so on. The height of a value not found is zero.
//   -- An empty tree has 0 nodes

// ---------------------------------------------------------------------------

#ifndef BINTREE_H
#define BINTREE_H
#include <iostream>
#include <string>
#include "nodedata.h"
using namespace std;

template <typename ItemType>
class BinTree {
//--------------------------- operator<< ------------------------------------
// Description:
// displays the tree using inorder traversal
// Preconditions:   ItemType class is responsible for displaying its own data
// Postconditions:  each node in *this BSTree is output onto the screen
friend ostream& operator<<(ostream& output, const BinTree<ItemType>& treeDisplay) {
   typename BinTree<ItemType>::Node* current = treeDisplay.root;
   treeDisplay.inorderHelper(output, current);
   output << endl;
   return output;
}

public:
   BinTree(string = "");        // constructor
   BinTree(const BinTree &);    // copy constructor
   ~BinTree();                  // destructor, calls makeEmpty
   
   // overloaded operators
   BinTree& operator=(const BinTree &);
   bool operator==(const BinTree &) const;
   bool operator!=(const BinTree &) const;
   
   // make the tree empty so isEmpty returns true
   void makeEmpty();
   
   // true if tree is empty, otherwise false
   bool isEmpty() const;
   
   // true if a node is inserted into the BSTree based on NodeData, else false
   bool insert(ItemType*);
   
   // retrieve a node based on NodeData from the BSTree
   bool retrieve(const ItemType &, ItemType* &) const;
   
   // remove a node based on NodeData from the BSTree
   bool erase(const ItemType &);
   
   // get the current height of a node in the BSTree
   int nodeHeight(const ItemType &) const;
   
   // get the current height of a BSTree
   int height() const;
   
   // get the total number of nodes in a BSTree
   int getCount() const;
   
   // remove all leaves in a BSTree
   void removeLeaves();
   
   // fill an array of Nodedata*
   void bstreeToArray(ItemType* []);

   // builds a balanced BinTree from a sorted array of NodeData*
   void arrayToBSTree(ItemType* []);
   
   // displays the tree sideways
   void displaySideways() const;
   
private:
   struct Node {
      ItemType* data;                  // pointer to data object
      Node* left;                      // left subtree pointer
      Node* right;                     // right subtree pointer
   };
   Node* root;                         // root of the tree

   //   --------------------------------
   //      revursive helper functions
   //   --------------------------------
   
   // helper for operator= and copy constructor
   void copyHelper(Node* &, const Node*);
   
   // destructor/makeEmpty helper
   void makeEmptyHelper(Node*&);
   
   // helper for operator==
   bool equalityHelper(Node*, Node*) const;
   
   // helper for insert
   bool insertHelper(ItemType*, Node*&);
   
   // helper for retrieve
   bool retrieveHelper(const ItemType&, ItemType*&, Node*) const;
   
   // height recursive helper function
   int heightHelper(Node*) const;
   
   int getCountHelper(Node*) const;
   
   // getHeightHelper is helper for getHeight,
   // getNodeHeight is helper for getHeightHelper
   int nodeHeightHelper(const ItemType &, Node*) const;
   int getNodeHeight(Node*) const;
   
   // erase recursive helper functions
   bool eraseHelper(Node*&, const ItemType&);
   bool eraseRoot(Node*&);
   ItemType* findAndDeleteSmallest(Node*&);
   
   void removeLeavesHelper(Node*&);
      
   // helper for bstreeToArray
   void bstreeToArrayHelper(ItemType* [], Node*, int &);
   
   // helper for arrayToBSTree
   void arrayToBSTreeHelper(ItemType* [], Node*&, int, int);
   
   // helper for displaySideways
   void sideways(Node*, int) const;
   
   // helper for operator<<
   ostream& inorderHelper(ostream&, Node*) const;
   
   int helper(Node* current, int n) const;
   
};

//----------------------- Default Constructor --------------------------------
// Preconditions:   None
// Postconditions:  root is set to nullptr
template <typename ItemType>
BinTree<ItemType>::BinTree(string s) {
   // if no constructor arguments are given
   if(s.length() == 0) {
      root = nullptr;
   }
   // if a string is given during intialization, create a new node/subtree
   else {
      root = new Node;
      root->data = new ItemType(s);
      root->left = root->right = nullptr;
   }
}

//---------------------------- Destructor ------------------------------------
// Description:
// deallocates all memory in *this
// uses helper function makeEmpty
// Preconditions:   this* BinTree is a Binary Search Tree
// Postconditions:  *this is deallocated
//                  root is null
template <typename ItemType>
BinTree<ItemType>::~BinTree() {
   makeEmpty();
}

//----------------------------- makeEmpty ------------------------------------
// Description:
// deallocates all memory in *this BSTree
// uses helper function makeEmptyHelper for recursion
// Preconditions:   this* BinTree is a Binary Search Tree
// Postconditions:  *this is deallocated
//                  root is null
template <typename ItemType>
void BinTree<ItemType>::makeEmpty() {
   makeEmptyHelper(root);
}
//--------------------------- makeEmptyHelper --------------------------------
// Description:
// deallocates all memory in *this
// Preconditions:   this* BinTree is a Binary Search Tree
//                  current is pointing to the root of *this BSTree
// Postconditions:  *this is deallocated
//                  root is null
template <typename ItemType>
void BinTree<ItemType>::makeEmptyHelper(Node*& current) {
   if(!current) {
      return;
   }
   // recursively move down tree and delete nodes in a postorder traversal
   makeEmptyHelper(current->left);
   makeEmptyHelper(current->right);
   
   // delete node
   delete current->data;
   current->data = nullptr;
   current->right = current->left = nullptr;
   delete current;
   current = nullptr;
}

//------------------------- Copy Constructor ---------------------------------
// Description:
// deep copies a Binary Search Tree into *this
// Preconditions:   BinTree right is a Binary Search Tree
// Postconditions:  *this is a copy of BinTree right
template <typename ItemType>
BinTree<ItemType>::BinTree(const BinTree<ItemType>& right) {
   copyHelper(root, right.root);
}

//---------------------------- copyHelper ------------------------------------
// Description:
// deep copies a Binary Search Tree into *this
// preorder traversal of the tree
// Preconditions:   copyNode is pointing to right is a Binary Search Tree
//                  Node current is pointing to *this root node
//                  Node rightCurrent is pointing to the root of the the
//                  BSTree to copy
// Postconditions:  *this is a copy of BinTree right
template <typename ItemType>
void BinTree<ItemType>::copyHelper(Node* &current, const Node* rightCurrent) {
   // create node, then recurisvely move through the left and right subtrees
   // the right BSTree in a preorder traversal
   if(rightCurrent) {
      // create new node
      current = new Node;
      current->data = new ItemType(*rightCurrent->data);
      current->left = current->right = nullptr;
      
      // recursively traverse left and right subtrees
      copyHelper(current->left, rightCurrent->left);
      copyHelper(current->right, rightCurrent->right);
   }
}

//----------------------------- operator= ------------------------------------
// Description:
// deep copies a Binary Search Tree into *this
// Preconditions:   BinTree right is a Binary Search Tree
// Postconditions:  *this is a copy of BinTree right
template <typename ItemType>
BinTree<ItemType>& BinTree<ItemType>::operator=(const BinTree<ItemType> &right) {
   // if the right tree is the same as *this, return, else, copy right tree
   if(&right != this) {
      makeEmpty();
      copyHelper(root, right.root);
   }
   return *this;
}

//----------------------------- operator== -----------------------------------
// Description:
// Determine if two BSTrees are equal
// Preconditions:   *this and rightTree are binary search trees
// Postconditions:  return true if trees have the same data
//                  return false otherwise
template <typename ItemType>
bool BinTree<ItemType>::operator==(const BinTree<ItemType> & rightTree) const {
   return equalityHelper(root, rightTree.root);
}

//---------------------------- equalityHelper --------------------------------
// Description:
// two binary trees are equal if they have the same data and structure
// helper function for operator==
// Preconditions:   *this and rightTree are binary search trees
// Postconditions:  return true if trees have the same data
//                  return false otherwise
template <typename ItemType>
bool BinTree<ItemType>::equalityHelper(Node* current, Node* rightCurrent) const {
   // base case
   if(!current && !rightCurrent) {
      return true;
   }
   // if one tree has reached a leaf and the other has not, they are not equal
   else if((current && !rightCurrent) || (!current && rightCurrent)) {
      return false;
   }
   // if *this current node is != to the rightcurrent node, trees are unequal
   else if(*current->data != *rightCurrent->data) {
      return false;
   }
   return equalityHelper(current->left, rightCurrent->left);
   return equalityHelper(current->right, rightCurrent->right);
}

//----------------------------- operator!= -----------------------------------
// Description:
// Determine if two BSTrees are inequal
// Utilizes the already built operator==
// Preconditions:   *this and rightTree are binary search trees
// Postconditions:  return false if trees have the same data
//                  return true otherwise
template <typename ItemType>
bool BinTree<ItemType>::operator!=(const BinTree<ItemType> & rightTree) const {
   return !(*this == rightTree);
}

// ------------------------------ isEmpty ------------------------------------
// Description:
// tests whether a tree object (this) is empty
// Preconditions:   none
// Postconditions:  return true if tree is empty
//                  return false otherwise
template <typename ItemType>
bool BinTree<ItemType>::isEmpty() const {
   return (root == nullptr);
}

// ------------------------------ insert -------------------------------------
// Description:
// inserts a new node into the binary search tree
// Preconditions:   ItemType newData has been allocated and holds a string
// Postconditions:  the binary search tree has inserted a new leaf
template <typename ItemType>
bool BinTree<ItemType>::insert(ItemType* newData) {
   return insertHelper(newData, root);
}

//--------------------------- insertHelper -----------------------------------
// Description:
// inserts a new node into the binary search tree
// Preconditions:   ItemType newData has been allocated and holds a string
//                  current is pointing to the root of *this BSTree
// Postconditions:  the binary search tree has inserted a new leaf
template <typename ItemType>
bool BinTree<ItemType>::insertHelper(ItemType* newData, Node*& current) {
   // once we hit a leaf (bottom of the tree), insert the data
   if(current == nullptr) {
      current = new Node;
      current->data = newData;
      current->left = current->right = nullptr;
      return true;
   }
   // if item is less than current item, insert in left subtree
   else if(*current->data > *newData) {
      return insertHelper(newData, current->left);
   }
   // otherwise insert in right subtree
   else if(*current->data < *newData) {
      return insertHelper(newData, current->right);
   }
   // if the ItemType is already in the tree (duplicate data), do not insert
   else {
      return false;
   }
   return true;
}

//------------------------------- retrieve -----------------------------------
// Description:
// retrieve a node based on ItemType from the BSTree
// Preconditions:   p is NULL and
//                  target is a ItemType object with string data
// Postconditions:  return true if the target ItemType was found and p is
//                  pointing to the target data in the tree
//                  return false otherwise
template <typename ItemType>
bool BinTree<ItemType>::retrieve(const ItemType & target, ItemType* & p) const {
   return retrieveHelper(target, p, root);
}

//---------------------------- retrieveHelper --------------------------------
// Description:
// retrieve a node based on ItemType from the BSTree
// Preconditions:   p is NULL and
//                  target is a ItemType object with string data
//                  Node current is pointing to the root of *this tree
// Postconditions:  return true if the target ItemType was found and p is
//                  pointing to the target data in the tree
//                  return false otherwise
template <typename ItemType>
bool BinTree<ItemType>::retrieveHelper(const ItemType & target, ItemType*& p,
                                                       Node* current) const {
   // base case
   if(!current) {
      return false;
   }
   // if target is found, assign p to data
   else if(*current->data == target) {
      p = current->data;
      return true;
   }
   // move right if the target data is greater than the current nodes data
   else if(*current->data < target) {
      return retrieveHelper(target, p, current->right);
   }
   // move left is the target data is less than the current nodes data
   return retrieveHelper(target, p, current->left);
}

//---------------------------------- erase ------------------------------------
// Description:
// If the node has zero or one children, we can delete the node easily and
// replace the pointer to it (with the child if one exists.)
// If the node containing the item has two children, we must find a replacement
// item to place in the node. This replacement item is either the largest
// descendant of the left child or the smallest descendant of the right child
// Precondition: root is not nullptr
// Postcondition: return true if the node with node with target input data has
//                been erased
//                return false otherwise
template <typename ItemType>
bool BinTree<ItemType>::erase(const ItemType& target) {
   eraseHelper(root, target);
}

//------------------------------- eraseHelper ---------------------------------
// find the node with target data in the tree
// return false if not found
template <typename ItemType>
bool BinTree<ItemType>::eraseHelper(Node*& current, const ItemType& target) {
   if(current == nullptr) {
      return false;
   }
   else if(*current->data == target) {
      return eraseRoot(current);
   }
   else if(current->data < target) {
      return eraseHelper(current->right);
   }
   else {
      return eraseHelper(current->left);
   }
}

//------------------------------- eraseRoot -----------------------------------
template <typename ItemType>
bool BinTree<ItemType>::eraseRoot(Node*& current) {
   if(!current->left && !current->right) {
      // delete the current nodes data
      delete current->data;
      current->data = nullptr;
      delete current;
      current = nullptr;
   }
   else if(!current->right) {
      // move next pointer from previous node to the current node's next node
      Node* temp = current;
      current = current->left;
      
      // delete the current node's data
      delete temp->data;
      temp->data = nullptr;
      delete temp;
      temp = nullptr;
   }
   else if(!current->left) {
      // move next pointer from previous node to the current node's next node
      Node* temp = current;
      current = current->right;
      
      // delete the current node's data
      delete temp->data;
      temp->data = nullptr;
      delete temp;
      temp = nullptr;
   }
   else {
      delete current->item;
      root->item = findAndDeleteSmallest(current);
   }
}

//------------------------- findAndDeleteSmallest -----------------------------
// finds and deletes the smallest node in the left subtree of the original
// target node that we want to delete
// Postconditions: retuns the data (ItemType) that the samllest node in the
//                 left subtree of the original target node stores
template <typename ItemType>
ItemType* BinTree<ItemType>::findAndDeleteSmallest(Node*& current) {
   if(current->left == nullptr) {
      // create temporary data for the smallest node in the left subtree
      ItemType* item = current->data;
      Node* temp = current;
      current = current->right;
      
      // delete the smallest node in the left subtree
      current->data = nullptr;
      delete temp;
      current = nullptr;
      return item;
   }
   findAndDeleteSmallest(current->left);
}

//--------------------------------- height ------------------------------------
// Description:
// find the height of the current Binary Search Tree
// Preconditions:   *this is either a binary tree or binary search tree
//                  ItemType target has been allocated string data
// Postconditions:  the height of the binary search tree is returned
//                  return 0 if head is null
template <typename ItemType>
int BinTree<ItemType>::height() const {
   return heightHelper(root);
}

//------------------------------ heightHelper ---------------------------------
// Description:
// find the height of the current Binary Search Tree
// Preconditions:   *this is either a binary tree or binary search tree
//                  ItemType target has been allocated string data
// Postconditions:  the height of the binary search tree is returned
//                  return 0 if head is null
template <typename ItemType>
int BinTree<ItemType>::heightHelper(Node* current) const {
   if(current == nullptr) {
      return 0;
   }
   return 1 + max(heightHelper(current->left), heightHelper(current->right));
}

//------------------------------- getCount ------------------------------------
// Description:
// Find the total number of nodes in a binary search tree
// Preconditions: none
// Postconditions: return the number of nodes in the bstree
template <typename ItemType>
int BinTree<ItemType>::getCount() const {
   return getCountHelper(root);
}

//----------------------------- getCountHelper --------------------------------
// Description:
// Find the total number of nodes in a binary search tree
// Preconditions: none
// Postconditions: return the number of nodes in the bstree
template <typename ItemType>
int BinTree<ItemType>::getCountHelper(Node* current) const {
   if(current == nullptr) {
      return 0;
   }
   return getCountHelper(current->left) + getCountHelper(current->right) + 1;
}
      
//------------------------------- nodeHeight ----------------------------------
// Description:
// find the height of a given value (ItemType) in the tree
// Preconditions:   *this is either a binary tree or binary search tree
//                  ItemType target has been allocated string data
// Postconditions:  if the ItemType target is found, the height of the Node
//                  is returned
//                  return 0 otherwise (if target is not in tree/not found)
// NOTE: The height of a node at a leaf is 1, height of a node at the next
//          level is 2, and so on. The height of a value not found is zero.
template <typename ItemType>
int BinTree<ItemType>::nodeHeight(const ItemType &target) const {
   return nodeHeightHelper(target, root);
}
 
//--------------------------- nodeHeightHelper --------------------------------
// Description:
// find the height of a given value (ItemType) in the tree
// helper for getHeight
// Preconditions:   *this is either a binary tree or binary search tree
//                  ItemType target has been allocated string data
// Postconditions:  if the ItemType target is found, the height of the Node
//                  is returned
//                  return 0 otherwise
// NOTE: The height of a node at a leaf is 1, height of a node at the next
//          level is 2, and so on. The height of a value not found is zero.
template <typename ItemType>
int BinTree<ItemType>::nodeHeightHelper(const ItemType &target, Node* current) const {
   // base case
   if(current == nullptr) {
      return 0;
   }
   // target data is found
   else if(*current->data == target) {
      return getNodeHeight(current);
   }
   return max(nodeHeightHelper(target, current->left),
              nodeHeightHelper(target, current->right));
}

//----------------------------- getNodeHeight --------------------------------
// Description:
// need seperate method to count height starting from found node
// helper for getHeightHelper
// Preconditions:   Node* current is the Node of the target data if found in
//                  getHeightHelper for getHeight
// Postconditions:  the height of the target ItemType is returned
// NOTE: The height of a node at a leaf is 1, height of a node at the next
//          level is 2, and so on. The height of a value not found is zero.
template <typename ItemType>
int BinTree<ItemType>::getNodeHeight(Node* current) const {
   if(current == nullptr) {
      return 0;
   }
   // start counting height from leaf; takes the larger height of two subtrees
   return 1 + max(getNodeHeight(current->left), getNodeHeight(current->right));
}

//------------------------------ removeLeaves ---------------------------------
// Description:
// Removes all leaves in a BSTree
template <typename ItemType>
void BinTree<ItemType>::removeLeaves(){
   removeLeavesHelper(root);
}

//--------------------------- removeLeavesHelper ------------------------------
// Description:
// Removes all leaves in a BSTree
template <typename ItemType>
void BinTree<ItemType>::removeLeavesHelper(Node*& current){
   if(current == nullptr){
        return;
    }
    else if(current->left == nullptr && current->right == nullptr){
        delete current->data;
        current->data = nullptr;
        delete current;
        current = nullptr;
    }
   removeLeavesHelper(current->left);
   removeLeavesHelper(current->right);
}
 
//----------------------------- bstreeToArray --------------------------------
// Description:
// fills an array of ItemType* by using an inorder traversal of *this tree
// Preconditions:   assumes toFill is a statically allocated array of 100
//                  NULL elements
// Postconditions:  ItemType* toFill is filled with the data/nodes of *this
//                  binary seach tree
//                  *this is empty; root is NULL
//                  EXAMPLE:
//                  After the call to bstreeToArray, the tree in Figure 1
//                  should be empty and the array should be filled with:
//      and, eee, ff, iii, jj, m, not, ooo, pp, r, sssss, tttt, y, z
//                           (in this order)
template <typename ItemType>
void BinTree<ItemType>::bstreeToArray(ItemType* arrToFill[]) {
   int subscript = 0;
   bstreeToArrayHelper(arrToFill, root, subscript);   // fill array
   makeEmpty();         // empty tree
}
 
//------------------------ bstreeToArrayHelper -------------------------------
// Description:
// Array size of a tree with height h: 2^h
// 1) Store the root at index 0
// 2) Children of a node at position i at positions 2i+1 and 2i+2
// Preconditions:   assumes toFill is a statically allocated array of 100
//                  NULL elements
//                  Node* current is pointing to *this root
//                  index is 0
// Postconditions:  ItemType* toFill is filled with the data/nodes of *this
//                  binary seach tree
//                  *this is empty; root is NULL
//                  EXAMPLE:
//                  After the call to bstreeToArray, the tree in Figure 1
//                  should be empty and the array should be filled with:
//      and, eee, ff, iii, jj, m, not, ooo, pp, r, sssss, tttt, y, z
//                           (in this order)
template <typename ItemType>
void BinTree<ItemType>::bstreeToArrayHelper(ItemType* arrToFill[], Node* current,
                                                                     int& index) {
   if(current == nullptr) {        // base case
      return;
   }
   
   bstreeToArrayHelper(arrToFill, current->left, index); // walk left subtree
   
   // insert data from tree into array according to the index
   arrToFill[index] = new ItemType(*current->data);
   index++;
   
   bstreeToArrayHelper(arrToFill, current->right, index); // walk right subtree
}


//----------------------------- arrayToBSTree --------------------------------
// Description:
// builds a balanced BinTree from a sorted array of ItemType*
// Preconditions:   The root in the array is at subscript 0
//                  toCopy is an empty, partially filled, or full array of
//                  ItemType*
// Postconditions:  *this is a Binary Search Tree with data from the array of
//                  ItemType* toCopy
//                  the ItemType* array is filled with NULLs
// NOTE: The root (recursively) is at (low+high)/2 where low is the lowest
//       subscript of the array range and high is the highest.
template <typename ItemType>
void BinTree<ItemType>::arrayToBSTree(ItemType* arrToCopy[]) {
   // see where the highest index in the array is with data initialized
   int low = 0, high = -1;
   for(int i = low; i < 100; i++) {
      if(arrToCopy[i] != nullptr) {
         high = i;
      }
      else {
         break;
      }
   }
   // if there is data initialized, convert it to a tree
   if (high > -1) {
      arrayToBSTreeHelper(arrToCopy, root, low, high);
   }
}

//------------------------ arrayToBSTreeHelper -------------------------------
// Description:
// builds a balanced BinTree from a sorted array of ItemType*
// Preconditions:   The root in the array is at subscript 0
//                  toCopy is a non-empty, partially filled, or fully filled
//                  array of ItemType*
// Postconditions:  *this is a Binary Search Tree with data from the array of
//                  ItemType* toCopy
//                  the ItemType* array is filled with NULLs
// NOTE: The root (recursively) is at (low+high)/2 where low is the lowest
//       subscript of the array range and high is the highest.
template <typename ItemType>
void BinTree<ItemType>::arrayToBSTreeHelper(ItemType* arrToCopy[], Node*& current,
                                                               int low, int high) {
   // return if you've reached the beginning or end of the array (with data)
   if(high < low) {
      return;
   }
   
   int midpoint = (low + high) / 2;
   
   // create new node (should already be at leaf, takes O(1) time)
   insert(arrToCopy[midpoint]);
   
   // recursively walk through the array
   arrayToBSTreeHelper(arrToCopy, current->left, low, midpoint - 1);
   arrayToBSTreeHelper(arrToCopy, current->right, midpoint + 1, high);
}

//------------------------- displaySideways ----------------------------------
// Description:
// Displays a sideways binary tree based on *this data
// Preconditions:   NONE
// Postconditions:  BinTree data has been output to the screen in a
//                  sideways binary tree
template <typename ItemType>
void BinTree<ItemType>::displaySideways() const {
   sideways(root, 0);
}

//---------------------------- sideways --------------------------------------
// Helper method for displaySideways
// uses inorder traversal to display sideways tree
// Preconditions:   Node* current is pointing to *this root
//                  the level of the root is 1
// Postconditions:  BinTree data has been output to the screen in a
//                  sideways binary tree
template <typename ItemType>
void BinTree<ItemType>::sideways(Node* current, int level) const {
   if(!current) {                     // base case
      return;
   }
   
   level++;                                     // update level
   sideways(current->right, level);             // walk through left subtree
   
   for(int i = 0; i < level+1; i++) {           // output spaces
      cout << "    ";
   }
   cout << *current->data << endl;              // ouput data
   
   sideways(current->left, level);              // walk through right subtree
}

//----------------------------- inorderHelper --------------------------------
// Description
// helper for operator<< (output operator)
// displays the tree using inorder traversal
// Preconditions:   current is pointing to the root of the *this BSTree
//                  ItemType class is responsible for displaying its own data
// Postconditions:  each node in *this BSTree is output onto the screen
template <typename ItemType>
ostream& BinTree<ItemType>::inorderHelper(ostream& output, Node* current) const {
   if(!current) {
      return output;
   }
   inorderHelper(output, current->left);     // walk through left subtree
   output << *current->data << " ";          // ouput data
   inorderHelper(output, current->right);    // walk through right subtree
   return output;
}

#endif
