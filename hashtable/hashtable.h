// ------------------------------ hashtable.h ---------------------------------

// CSS 343
// Created:
// Last Modified: August 21st, 2020

// ----------------------------------------------------------------------------

// HashTable Class: A hash table is a data structure that is used to store keys
//                  It uses a hash function to compute an index into an array
//                  in which an element will be inserted or searched.
// ----------------------------------------------------------------------------

// Notes on specifications, special algorithms, and assumptions.

// - Implmements hashing through separate chaining
// - Only assumes that Item* are Customer objects, but can change to handle
//   different types of data (i.e. changing MAX_SIZE or overloading another
//   hash key function)

//
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include "customer.h"
#include "hashnode.h"
using namespace std;

const int MAX_SIZE = 51;

template <typename Key, typename Item>
class HashTable {
   
public:
   //-------------------------- default constructor ---------------------------
   // Description:     Sets all indexes in the hashtable to null
   //
   // Preconditions:   none
   //
   // Postconditions:  every bucket in table is set to null
   //
   HashTable() {
      for(int i = 0; i < MAX_SIZE; i++) {
        table[i] = nullptr;
      }
   }
   
   //------------------------------- destructor -------------------------------
   // Description:     Deallocates all memory in *this hashtable
   //
   // Preconditions:   none
   //
   // Postconditions:  all memory has been deallocated in hashtable
   //
   ~HashTable() {
      for(int i = 0; i < MAX_SIZE; i++) {
         makeEmpty(table[i]);        // deletes all hashnodes in current bucket
         table[i] = nullptr;         // bucket is null
      }
   }
    
   //--------------------------------- insert ---------------------------------
   // Description:     Adds an Item to the hashtable
   //
   // Preconditions:   Key rawKey is not have a duplicate 4 digit integer
   //                  (customer ID) already in the hashtable
   //
   // Postconditions:  Item* itemData is inserted into the hashtable
   //
   void insert(Key rawKey, Item* itemData) {
      int index = getHashIndex(rawKey);
      
      HashNode<Key, Item>* newNode = new HashNode<Key, Item>(rawKey, itemData);
      
      // if current bucket is empty, insert HashNode
      if(table[index] == nullptr) {
         table[index] = newNode;
         table[index]->setNext(nullptr);
      }
      // if collision, inserts new customer to the beginning of the linked-list
      else {
         newNode->setNext(table[index]->getNext());
         table[index]->setNext(newNode);
      }
   }
   
   //------------------------------- retrieve ---------------------------------
   // Description:     Retrieve item from hashtable based on it's key
   //
   // Preconditions:   rawKey is a four digit integer
   //
   // Postconditions:  return pointer to Item (Customer) if found in hashtable
   //                  otherwise, return nullptr
   //
   Item* retrieve(Key rawKey) {
      int index = getHashIndex(rawKey);       // find item's key
      
      HashNode<Key, Item>* current = table[index];
      
      while(current != nullptr) {
         if(current->getKey() == rawKey) {
            return current->getItem();
         }
         current = current->getNext();
      }
      return nullptr;
   }

private:
   HashNode<Key, Item>* table[MAX_SIZE];     // Array of pointers to entries
   
   //---------------------------- getHashIndex --------------------------------
   // Description:     Creates a hash index based on a raw data
   //
   // Preconditions:   Takes a 4-digit integer
   //
   // Postconditions:  returns hash index of rawKey
   //
   int getHashIndex(int rawKey) {
      return rawKey % MAX_SIZE;
   }
   
   //---------------------------- getHashIndex --------------------------------
   // Description:     Creates a hash index based on a raw data
   //
   // Preconditions:   Takes in an arbritrary length string
   //
   // Postconditions:  returns hash index of rawKey
   //
   int getHashIndex(string rawKey) {
      hash<string> hasher;
      auto hashed = hasher(rawKey);
      cout << hashed << endl;
      return hashed % MAX_SIZE;
   }
   
   //----------------------------- makeEmpty ----------------------------------
   // Description:     Deallocates all memory in *this hashtable
   //                  recursive helper for destructor
   //
   // Preconditions:   HashNode<Key, Item>* current is pointing to a bucket
   //
   // Postconditions:  The entire hashnode linked chain is deallocated
   //
   void makeEmpty(HashNode<Key, Item>* current) {
      if(current == nullptr) {
         return;
      }
      
      makeEmpty(current->getNext());
   
      // free memory
      delete current;
      current = nullptr;
   }
};

#endif
