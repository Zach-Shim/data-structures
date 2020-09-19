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

class BinTree {
   friend ostream& operator<<(ostream&, const BinTree&);
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
   bool insert(NodeData*);
   
   // retrieve a node based on NodeData from the BSTree
   bool retrieve(const NodeData &, NodeData* &) const;
   
   // get the current height of the BSTree
   int getHeight (const NodeData &) const;
   
   // fill an array of Nodedata*
   void bstreeToArray(NodeData* []);

   // builds a balanced BinTree from a sorted array of NodeData*
   void arrayToBSTree(NodeData* []);
   
   // displays the tree sideways
   void displaySideways() const;
   
   int play() const;
   
private:
   struct Node {
      NodeData* data;                  // pointer to data object
      Node* left;                      // left subtree pointer
      Node* right;                     // right subtree pointer
   };
   Node* root;                         // root of the tree

   //   ----------------------
   //      helper functions
   //   ----------------------
   
   // helper for operator= and copy constructor
   void copyHelper(Node* &, const Node*);
   
   // destructor/makeEmpty helper
   void makeEmptyHelper(Node*&);
   
   // helper for operator==
   bool equalityHelper(Node*, Node*) const;
   
   // helper for insert
   bool insertHelper(NodeData*, Node*&);
   
   // helper for retrieve
   bool retrieveHelper(const NodeData&, NodeData*&, Node*) const;
   
   // getHeightHelper is helper for getHeight,
   // getNodeHeight is helper for getHeightHelper
   int getHeightHelper(const NodeData &, Node*) const;
   int getNodeHeight(Node* current) const;
   
   // helper for bstreeToArray
   void bstreeToArrayHelper(NodeData* [], Node*, int &);
   
   // helper for arrayToBSTree
   void arrayToBSTreeHelper(NodeData* [], Node*&, int, int);
   
   // helper for displaySideways
   void sideways(Node*, int) const;
   
   // helper for operator<<
   ostream& inorderHelper(ostream&, Node*) const;
   
   int helper(Node* current, int n) const;
   
};

#endif
