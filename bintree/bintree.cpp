// ------------------------------ BinTree.cpp --------------------------------

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

#include "bintree.h"

//----------------------- Default Constructor --------------------------------
// Preconditions:   None
// Postconditions:  root is set to nullptr
BinTree::BinTree(string s) {
   // if no constructor arguments are given
   if(s.length() == 0) {
      root = nullptr;
   }
   // if a string is given during intialization, create a new node/subtree
   else {
      root = new Node;
      root->data = new NodeData(s);
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
BinTree::~BinTree() {
   makeEmpty();
}

//----------------------------- makeEmpty ------------------------------------
// Description:
// deallocates all memory in *this BSTree
// uses helper function makeEmptyHelper for recursion
// Preconditions:   this* BinTree is a Binary Search Tree
// Postconditions:  *this is deallocated
//                  root is null
void BinTree::makeEmpty() {
   makeEmptyHelper(root);
}
//--------------------------- makeEmptyHelper --------------------------------
// Description:
// deallocates all memory in *this
// Preconditions:   this* BinTree is a Binary Search Tree
//                  current is pointing to the root of *this BSTree
// Postconditions:  *this is deallocated
//                  root is null
void BinTree::makeEmptyHelper(Node*& current) {
   if(current == nullptr) {
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
BinTree::BinTree(const BinTree& right) {
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
void BinTree::copyHelper(Node* &current, const Node* rightCurrent) {
   // create node, then recurisvely move through the left and right subtrees
   // the right BSTree in a preorder traversal
   if(rightCurrent != nullptr) {
      // create new node
      current = new Node;
      current->data = new NodeData(*rightCurrent->data);
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
BinTree& BinTree::operator=(const BinTree &right) {
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
bool BinTree::operator==(const BinTree & rightTree) const {
   return equalityHelper(root, rightTree.root);
}

//---------------------------- equalityHelper --------------------------------
// Description:
// two binary trees are equal if they have the same data and structure
// helper function for operator==
// Preconditions:   *this and rightTree are binary search trees
// Postconditions:  return true if trees have the same data
//                  return false otherwise
bool BinTree::equalityHelper(Node* current, Node* rightCurrent) const {
   // base case
   if(current == nullptr && rightCurrent == nullptr) {
      return true;
   }
   // if one tree has reached a leaf and the other has not, they are not equal
   else if((current != nullptr && rightCurrent == nullptr) ||
                            (current == nullptr && rightCurrent != nullptr)) {
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
bool BinTree::operator!=(const BinTree & rightTree) const {
   return !(*this == rightTree);
}

// ------------------------------ isEmpty ------------------------------------
// Description:
// tests whether a tree object (this) is empty
// Preconditions:   none
// Postconditions:  return true if tree is empty
//                  return false otherwise
bool BinTree::isEmpty() const {
   return (root == nullptr);
}

// ------------------------------ insert -------------------------------------
// Description:
// inserts a new node into the binary search tree
// Preconditions:   NodeData newData has been allocated and holds a string
// Postconditions:  the binary search tree has inserted a new leaf
bool BinTree::insert(NodeData* newData) {
   return insertHelper(newData, root);
}

//--------------------------- insertHelper -----------------------------------
// Description:
// inserts a new node into the binary search tree
// Preconditions:   NodeData newData has been allocated and holds a string
//                  current is pointing to the root of *this BSTree
// Postconditions:  the binary search tree has inserted a new leaf
bool BinTree::insertHelper(NodeData* newData, Node*& current) {
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
   // if the NodeData is already in the tree (duplicate data), do not insert
   else {
      return false;
   }
   return true;
}

//------------------------------- retrieve -----------------------------------
// Description:
// retrieve a node based on NodeData from the BSTree
// Preconditions:   p is NULL and
//                  target is a NodeData object with string data
// Postconditions:  return true if the target NodeData was found and p is
//                  pointing to the target data in the tree
//                  return false otherwise
bool BinTree::retrieve(const NodeData & target, NodeData* & p) const {
   return retrieveHelper(target, p, root);
}

//---------------------------- retrieveHelper --------------------------------
// Description:
// retrieve a node based on NodeData from the BSTree
// Preconditions:   p is NULL and
//                  target is a NodeData object with string data
//                  Node current is pointing to the root of *this tree
// Postconditions:  return true if the target NodeData was found and p is
//                  pointing to the target data in the tree
//                  return false otherwise
bool BinTree::retrieveHelper(const NodeData & target, NodeData*& p,
                                                       Node* current) const {
   // base case
   if(current == nullptr) {
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


//------------------------------- getHeight ----------------------------------
// Description:
// find the height of a given value (NodeData) in the tree
// Preconditions:   *this is either a binary tree or binary search tree
//                  NodeData target has been allocated string data
// Postconditions:  if the NodeData target is found, the height of the Node
//                  is returned
//                  return 0 otherwise (if target is not in tree/not found)
// NOTE: The height of a node at a leaf is 1, height of a node at the next
//          level is 2, and so on. The height of a value not found is zero.

int BinTree::getHeight(const NodeData &target) const {
   return getHeightHelper(target, root);
}
 
//--------------------------- getHeightHelper --------------------------------
// Description:
// find the height of a given value (NodeData) in the tree
// helper for getHeight
// Preconditions:   *this is either a binary tree or binary search tree
//                  NodeData target has been allocated string data
// Postconditions:  if the NodeData target is found, the height of the Node
//                  is returned
//                  return 0 otherwise
// NOTE: The height of a node at a leaf is 1, height of a node at the next
//          level is 2, and so on. The height of a value not found is zero.
int BinTree::getHeightHelper(const NodeData &target, Node* current) const {
   // base case
   if(current == nullptr) {
      return 0;
   }
   // target data is found
   else if(*current->data == target) {
      return getNodeHeight(current);
   }
   return max(getHeightHelper(target, current->left),
              getHeightHelper(target, current->right));
}

//----------------------------- getNodeHeight --------------------------------
// Description:
// need seperate method to count height starting from found node
// helper for getHeightHelper
// Preconditions:   Node* current is the Node of the target data if found in
//                  getHeightHelper for getHeight
// Postconditions:  the height of the target NodeData is returned
// NOTE: The height of a node at a leaf is 1, height of a node at the next
//          level is 2, and so on. The height of a value not found is zero.
int BinTree::getNodeHeight(Node* current) const {
   if(current == nullptr) {
      return 0;
   }
   // start counting height from leaf; takes the larger height of two subtrees
   return 1 + max(getNodeHeight(current->left), getNodeHeight(current->right));
}
 
//----------------------------- bstreeToArray --------------------------------
// Description:
// fills an array of Nodedata* by using an inorder traversal of *this tree
// Preconditions:   assumes toFill is a statically allocated array of 100
//                  NULL elements
// Postconditions:  NodeData* toFill is filled with the data/nodes of *this
//                  binary seach tree
//                  *this is empty; root is NULL
//                  EXAMPLE:
//                  After the call to bstreeToArray, the tree in Figure 1
//                  should be empty and the array should be filled with:
//      and, eee, ff, iii, jj, m, not, ooo, pp, r, sssss, tttt, y, z
//                           (in this order)
void BinTree::bstreeToArray(NodeData* arrToFill[]) {
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
// Postconditions:  NodeData* toFill is filled with the data/nodes of *this
//                  binary seach tree
//                  *this is empty; root is NULL
//                  EXAMPLE:
//                  After the call to bstreeToArray, the tree in Figure 1
//                  should be empty and the array should be filled with:
//      and, eee, ff, iii, jj, m, not, ooo, pp, r, sssss, tttt, y, z
//                           (in this order)
void BinTree::bstreeToArrayHelper(NodeData* arrToFill[], Node* current,
                                                                  int& index) {
   if(current == nullptr) {        // base case
      return;
   }
   
   bstreeToArrayHelper(arrToFill, current->left, index); // walk left subtree
   
   // insert data from tree into array according to the index
   arrToFill[index] = new NodeData(*current->data);
   index++;
   
   bstreeToArrayHelper(arrToFill, current->right, index); // walk right subtree
}


//----------------------------- arrayToBSTree --------------------------------
// Description:
// builds a balanced BinTree from a sorted array of NodeData*
// Preconditions:   The root in the array is at subscript 0
//                  toCopy is an empty, partially filled, or full array of
//                  NodeData*
// Postconditions:  *this is a Binary Search Tree with data from the array of
//                  NodeData* toCopy
//                  the NodeData* array is filled with NULLs
// NOTE: The root (recursively) is at (low+high)/2 where low is the lowest
//       subscript of the array range and high is the highest.
void BinTree::arrayToBSTree(NodeData* arrToCopy[]) {
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
// builds a balanced BinTree from a sorted array of NodeData*
// Preconditions:   The root in the array is at subscript 0
//                  toCopy is a non-empty, partially filled, or fully filled
//                  array of NodeData*
// Postconditions:  *this is a Binary Search Tree with data from the array of
//                  NodeData* toCopy
//                  the NodeData* array is filled with NULLs
// NOTE: The root (recursively) is at (low+high)/2 where low is the lowest
//       subscript of the array range and high is the highest.
void BinTree::arrayToBSTreeHelper(NodeData* arrToCopy[], Node*& current,
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
void BinTree::displaySideways() const {
   sideways(root, 0);
}

//---------------------------- sideways --------------------------------------
// Helper method for displaySideways
// uses inorder traversal to display sideways tree
// Preconditions:   Node* current is pointing to *this root
//                  the level of the root is 1
// Postconditions:  BinTree data has been output to the screen in a
//                  sideways binary tree
void BinTree::sideways(Node* current, int level) const {
   if(current == nullptr) {                     // base case
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
//                  NodeData class is responsible for displaying its own data
// Postconditions:  each node in *this BSTree is output onto the screen
ostream& BinTree::inorderHelper(ostream& output, Node* current) const {
   if(current == nullptr) {
      return output;
   }
   inorderHelper(output, current->left);     // walk through left subtree
   output << *current->data << " ";          // ouput data
   inorderHelper(output, current->right);    // walk through right subtree
   return output;
}

//--------------------------- operator<< ------------------------------------
// Description:
// displays the tree using inorder traversal
// Preconditions:   NodeData class is responsible for displaying its own data
// Postconditions:  each node in *this BSTree is output onto the screen
ostream& operator<<(ostream& output, const BinTree& treeDisplay) {
   BinTree::Node* current = treeDisplay.root;
   treeDisplay.inorderHelper(output, current);
   output << endl;
   return output;
}

int BinTree::play() const {

   int n = 0;

   return helper(root, n);

}

int BinTree::helper(Node* current, int n)const {

   if (current == NULL)

      return n;

   if (current->right != NULL || current->left != NULL)

      return 1 + helper(current->left, n+1) + helper(current->right, n+3);

   return 0;

}
