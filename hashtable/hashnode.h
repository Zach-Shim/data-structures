// ------------------------------ hashnode.h ---------------------------------

// CSS 343
// Created: August 5th, 2020
// Last Modified: August 21st, 2020

// ----------------------------------------------------------------------------

// HashNode Class: A HashNode holds data as a placeholder inside a HashTable

// ----------------------------------------------------------------------------

// Notes on specifications, special algorithms, and assumptions.

// - Implmements hashing through separate chaining

//

#ifndef HASHNODE_H
#define HASHNODE_H

#include <iostream>
using namespace std;

template <typename Key, class Item>
class HashNode {
public:
   //-------------------------- default constructor ---------------------------
   // Description:     intentionally left empty
   //
   // Preconditions:   none
   //
   // Postconditions:  none
   //
   HashNode() {}
   
   //----------------------------- constructor --------------------------------
   // Description:     intentionally left empty
   //
   // Preconditions:   searchKey is a 4 digit integer
   //                  newItem is pointing to initialized data (Customer)
   //
   // Postconditions:  none
   //
   HashNode(Key searchKey, Item* newItem) {
      item = newItem;
      key = searchKey;
   }
   
   //------------------------------- destructor -------------------------------
   // Description:     all memory id deallocated
   //
   // Preconditions:   none
   //
   // Postconditions:  all memory id deallocated
   //
   ~HashNode() {
      delete item;
      item = nullptr;
      next = nullptr;
   }

   //-------------------------------- getItem ---------------------------------
   // Description:     Returns the current HashNode's Item
   //
   // Preconditions:   none
   //
   // Postconditions:  returns a pointer to the current HashNode's Item
   //                                                           (Customer)
   Item* getItem() const {
      return item;
   }
   
   //--------------------------------- getKey ---------------------------------
   // Description:     Returns the current HashNode's key
   //
   // Preconditions:   none
   //
   // Postconditions:  returns the current HashNode's key
   //
   Key getKey() const {
      return key;
   }
   
   //-------------------------------- getNext ---------------------------------
   // Description:     Returns the next HashNode in the linked list
   //
   // Preconditions:   none
   //
   // Postconditions:  returns a pointer to the next linked HashNode from the
   //                  current HashNode
   //
   HashNode* getNext() const {
      return next;
   }
   
   //-------------------------------- setNext ---------------------------------
   // Description:     Sets the HashNodes next HashNode in the list
   //
   // Preconditions:   (1) Inserting a new HashNode into the HashTable
   //                  (2) There was a collision in the hashtable, and another
   //                  HashNode with the same key must be added to the index
   //                  the current HashNode is in
   //
   // Postconditions:  The current HashNode's next pointer is pointing to a
   //                  new HashNode
   //
   void setNext(HashNode* nextNode) {
      next = nextNode;
   }
   
   //-------------------------------- setItem ---------------------------------
   // Description:     Sets the current HashNode's Item
   //
   // Preconditions:   Item* newEntry is initialized with data
   //
   // Postconditions:  The current HashNode's Item is set
   //
   void setItem(Item* newEntry) {
      item = newEntry;
   }
   
   //--------------------------------- setKey ---------------------------------
   // Description:     Sets the current HashNode's key
   //
   // Preconditions:   Key newKey is a 4 digit integer
   //
   // Postconditions:  The current HashNode's key is set
   //
   void setKey(Key newKey) {
      key = newKey;
   }
   
private:
   Item* item;             // templatde Item (Customer)
   Key key;                // hash key
   HashNode* next;         // next HashNode in linked list
};

#endif

