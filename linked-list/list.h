////////////////////////////////////////////////////////////////////  listtemplate.h file  /////////////////////////////////////////////////////////////////
// Simple linked list, uses Node as linked list node

#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <fstream>
using namespace std;

//--------------------------  class List  ------------------------------------
// ADT List: Finite, ordered collection of zero or more items.
//           The ordering is determined by operator< of T class.
//           Ability to find union of two lists
//           Ability to find intersection of two lists
//           Ability to retrieve data from a list
//           Ability to remove data from a list
//
// Assumptions and Implementation:
//   -- Control of <, printing, etc. of T information is in the T class.
//   -- BuildList:
//   -- Data is linked inside a Node as a pointer
//    - Nodes are arragned in a sorted linked list
//   -- Head:
//    - There is no dummy head node, head points to first node.
//    - If the list is empty, head is nullptr.
//    - Head defaults to nullptr at initialization.
//   -- Insert Function:
//    - Allocates memory for a Node, ptr to the data is passed in.
//    - Allocating memory and setting data is the responsibility of the
        caller.
//   -- Intersect Function:
//    - At termination of the function, the two parameter lists are unchanged
//      unless one is also the current object.
//    - New memory is allocated if there is an intersection.
//   -- Merge Function:
//    - At termination of function, the two parameter lists are empty unless
//      one is also the current object
//    - Duplicate data is allowed
//    - No new memory is allocated.
// Note this definition is not a complete class and is not fully documented.
//----------------------------------------------------------------------------

template <typename T>
class List {

   // output operator for class List, print data,
   // responsibility for output is left to object stored in the list
   friend ostream& operator<<(ostream& output, const List<T>& thelist) {
      typename List<T>::Node* current = thelist.head;
      while (current != nullptr) {
         output << *current->data;
         current = current->next;
      }
      return output;
}

public:
   List();                               // default constructor
   ~List();                              // destructor
   List(const List<T>&);                 // copy constructor
   
   // operator overloads
   const List<T>& operator=(const List<T>&);  // =operator overload
   bool operator==(const List<T>&);            // ==operator overload
   bool operator!=(const List<T>&);            // !=operator overload
   
   void buildList(ifstream&);            // build a List from datafile

   //void merge(List<T>&, List<T>&);
   void intersect(const List<T>&, const List<T>&);
   
   bool insert(T*);                      // insert one Node into List
   bool isEmpty() const;                 // is list empty?
   //bool retrieve(const T&, T*&) const;   // retrieves a Node from the List
   //bool remove(const T&, T*&);           // removes an Node form the List
   void makeEmpty();             // deletes the current List


private:
   void copy(const List<T>&);    // copies the current list
   struct Node {                 // the node in a linked list
      T* data;                   // pointer to actual data, operations in T
      Node* next;
   };

   Node* head;                   // pointer to first node in list
};


//----------------------------------------------------------------------------
// Constructor
// deafults the head to a nullptr
template <typename T>
List<T>::List() {
   head = nullptr;
}

//----------------------------------------------------------------------------
// Copy Constructor
// copies a list into the current list
template <typename T>
List<T>::List(const List<T>& right) {
   copy(right);
}

//----------------------------------------------------------------------------
// Destructor
// empties a list
template <typename T>
List<T>::~List() {
   makeEmpty();
}


//----------------------------------------------------------------------------
// operator=
// copies a list into the current list
template <typename T>
const List<T>& List<T>::operator=(const List<T>& right) {
   if(this != &right) {          // if current list is same as argument
      makeEmpty();
      copy(right);
   }
   return *this;
}

//----------------------------------------------------------------------------
// copy
// copies a list into the current list
template <typename T>
void List<T>::copy(const List<T>& right) {
   if(right.head == nullptr) {return;}
   
   // walker pointers
   Node* rightCurrent = right.head;
   Node* thisCurrent = nullptr;
   
   // create head node
   head = new Node;
   head->data = new T;
   thisCurrent = head;
   *thisCurrent->data = *rightCurrent->data;
   rightCurrent = rightCurrent->next;
   
   while(rightCurrent != nullptr) {
      // create new node off the end of the list and walk
      thisCurrent->next = new Node;
      thisCurrent = thisCurrent->next;
      
      // create new data and copy the right list's data
      thisCurrent->data = new T;
      *thisCurrent->data = *rightCurrent->data;
      
      // walk right pointer
      rightCurrent = rightCurrent->next;
   }
   
   // assign the last next in the linked list to a nullptr
   thisCurrent->next = nullptr;
   
   // clean up pointers
   rightCurrent = nullptr;
   thisCurrent = nullptr;
}

//----------------------------------------------------------------------------
// makeEmpty
// empties the current object
template <typename T>
void List<T>::makeEmpty() {
   // if the list is already empty
   if(head == nullptr) {
      return;
   }
   else {
      // set walker pointers to iterate through list
      Node* previous = head;
      Node* current = nullptr;
      
      while(previous != nullptr) {
         
         current = previous->next;
         // delete current node
         delete previous->data;           // reclaim memory of data
         previous->data = nullptr;
         previous->next = nullptr;
         delete previous;                 // reclaim memory of node
         
         // update walker pointers
         previous = current;
      }
      
      // clean up pointers
      head = nullptr;
      previous = nullptr;
      current = nullptr;
   }
}

//----------------------------------------------------------------------------
// isEmpty
// check to see if List is empty as defined by a nullptr head
template <typename T>
bool List<T>::isEmpty() const {
   return head == nullptr;
}

//----------------------------------------------------------------------------
// insert
// insert an item into list; operator< of the T class
// has the responsibility for the sorting criteria
template <typename T>
bool List<T>::insert(T* dataptr) {

   Node* ptr= new Node;
   if (ptr == nullptr) return false;              // out of memory, bail
   ptr->data = dataptr;                           // link the node to data

   // if the list is empty or if the node should be inserted before
   // the first node of the list
   if (isEmpty() || *ptr->data < *head->data) {
      ptr->next = head;
      head = ptr;
   }
     
   // then check the rest of the list until we find where it belongs
   else {
      Node* current = head->next;          // to walk list
      Node* previous = head;               // to walk list, lags behind

      // walk until end of the list or found position to insert
      while (current != nullptr && *current->data < *ptr->data) {
            previous = current;                  // walk to next node
            current = current->next;
      }

      // insert new node, link it in
      ptr->next = current;
      previous->next = ptr;
   }
   return true;
}

//----------------------------------------------------------------------------
// buildList
// continually insert new items into the list
template <typename T>
void List<T>::buildList(ifstream& infile) {
   T* ptr;
   bool successfulRead;                            // read good data
   bool success = false;                           // successfully insert
   for (;;) {
      ptr = new T;
      successfulRead = ptr->setData(infile);       // fill the T object
      if (infile.eof()) {                          // reaches end of file
         delete ptr;
         ptr = nullptr;
         break;
      }

      // insert good data into the list, otherwise ignore it
      if (successfulRead) {
         success = insert(ptr);
      }
      else {
         delete ptr;
         ptr = nullptr;
      }
      if (!success) break;
   }
}

//----------------------------------------------------------------------------
// operator==
// finds if two lists are equal
template <typename T>
bool List<T>::operator==(const List<T>& right) {
   // if the current object is same as right
   if(this == &right) {
      return true;
   }
   
   // declare walker pointers
   Node* rightCurrent = right.head;
   Node* thisCurrent = head;
   
   // test if current and right list are equal
   while(thisCurrent != nullptr && rightCurrent != nullptr) {
      // if current list data is not equal to right list data
      if(*thisCurrent->data != *rightCurrent->data) {
         return false;
      }
      // walk the pointers
      else {
         thisCurrent = thisCurrent->next;
         rightCurrent = rightCurrent->next;
      }
   }
   
   // in case lists are different length
   if(thisCurrent != nullptr || rightCurrent != nullptr) {
      return false;
   }
   
   return true;
}

//----------------------------------------------------------------------------
// operator!=
// utilizes definition of == to find if two lists are not equal
template <typename T>
bool List<T>::operator!=(const List<T>& right) {
   return !(*this == right);
}

//----------------------------------------------------------------------------
// retrieve
// retrieves a data object from the linked list
template <typename T>
bool List<T>::retrieve(const T& target, T*& p) const {
   if(head == nullptr) {
      return false;
   }
   
   // walker pointer
   Node* current = head;
   
   while(current != nullptr) {
      if(*current->data == target) {     // if target is found
         p = current->data;              // assign object T to current data
         return true;
      }
      else {
         current = current->next;         // walk the list
      }
   }
   
   // clean up pointers
   current = nullptr;
   
   return false;
}
 

//----------------------------------------------------------------------------
// remove
// retrieves an object and removes it's Node from the List
template <typename T>
bool List<T>::remove(const T& target, T*& p) {
   if(head == nullptr) {
      return false;
   }
   
   // walker pointer
   Node* previous = head;
   Node* current = head->next;
   
   // head case
   if(*head->data == target) {
      // walk head to next Node
      head = current;
      
      // assign object to head's data
      p = previous->data;
      
      //reclaim memory
      previous->data = nullptr;
      previous->next = nullptr;
      delete previous;
      
      // clean up pointers
      previous = nullptr;
      current = nullptr;
      return true;
   }
   
   while(current != nullptr) {
      // if node is found
      if(*current->data == target) {
         // set object T equal to current Node's data
         p = current->data;
         
         // update current list
         previous->next = current->next;
         
         // clean up memory
         current->data = nullptr;
         current->next = nullptr;
         delete current;
      }
      else {
         // walk the pointers
         current = current->next;
         previous = previous->next;
      }
   }
   
   // clean up pointers
   previous = nullptr;
   current = nullptr;
   
   return false;
}
 
//----------------------------------------------------------------------------
// merge
// takes 2 sorted lists and merge into one long sorted list
// At termination of function, the two parameter lists are empty unless one
// is also the current object
template <typename T>
void List<T>::merge(List<T>& firstList, List<T>& secondList) {
   // if the calling object is the same as the two arguments
   // e.g. company1.intersect(company1, company1);
   if(this == &firstList && this == &secondList) {
      return;
   }

   // make the current list empty and attach the fake head's List
   if(&firstList != this || &secondList != this) {
      makeEmpty();
   }
   // declare a fake head pointer which have nodes attached to the end
   Node* fakeHead = nullptr;

   if(&firstList == &secondList) {
      fakeHead = firstList.head;
   }
   // if the first list is empty assign it to the second
   else if(firstList.head == nullptr) {
      fakeHead = secondList.head;
   }
   // if the second list is empty assign it to the first
   else if(secondList.head == nullptr) {
      fakeHead = firstList.head;
   }
   // find the intersection
   else {
      // declare walker pointers
      Node* firstCurrent = firstList.head;
      Node* secondCurrent = secondList.head;
      Node* thisCurrent = nullptr;
      
      // head case
      if(*firstCurrent->data <= *secondCurrent->data) {
         fakeHead = firstCurrent;
         thisCurrent = fakeHead;
         firstCurrent = firstCurrent->next;
      }
      else {
         fakeHead = secondCurrent;
         thisCurrent = fakeHead;
         secondCurrent = secondCurrent->next;
      }
      
      // walk each paraemter list finding which nodes have equal data
      while(firstCurrent != nullptr && secondCurrent != nullptr) {
         // if first list's data is less than or equal to second
         if(*firstCurrent->data <= *secondCurrent->data) {
            thisCurrent->next = firstCurrent;
            firstCurrent = firstCurrent->next;
            thisCurrent = thisCurrent->next;
         }
         // if second list's data is less than or equal to second
         else {
            thisCurrent->next = secondCurrent;
            secondCurrent = secondCurrent->next;
            thisCurrent = thisCurrent->next;
         }
      }
      
      // if one list is longer than the other
      if(firstCurrent == nullptr && secondCurrent != nullptr) {
         thisCurrent->next = secondCurrent;
      }
      else if(firstCurrent != nullptr && secondCurrent == nullptr) {
         thisCurrent->next = firstCurrent;
      }
      
      // clean up pointers
      firstCurrent = nullptr;
      secondCurrent = nullptr;
      thisCurrent = nullptr;
   
   }
   
   head = fakeHead;
   
   // clean up pointers
   fakeHead = nullptr;
   firstList.head = nullptr;
   secondList.head = nullptr;
}
 
//----------------------------------------------------------------------------
// intersect
// takes two sorted lists and finds the items in common in both lists
// at termination of the function, the two parameter lists are unchanged
// unless one is also the current object
template <typename T>
void List<T>::intersect(const List<T>& firstList, const List<T>& secondList) {
   // if the calling object is the same as the two arguments
   // e.g. company1.intersect(company1, company1);
   if(this == &firstList && this == &secondList) {
      return;
   }
   
   // declare a fake head pointer which have nodes attached to the end
   Node* fakeHead = nullptr;
   
   // declare walker pointers for first and second list paramters
   Node* firstCurrent = firstList.head;
   Node* secondCurrent = secondList.head;
   Node* thisCurrent = nullptr;
   
   // walk each list finding which nodes have equal data (intersect)
   while(firstCurrent != nullptr && secondCurrent != nullptr) {
      // if first list's data is less then second's data then walk
      if(*firstCurrent->data < *secondCurrent->data) {
         firstCurrent = firstCurrent->next;
      }
      // found two nodes in first and second list that intersect
      else if(*firstCurrent->data == *secondCurrent->data) {
         // head case if fakeHead has not been initialized
         if(fakeHead == nullptr) {
            fakeHead = new Node;
            fakeHead->data = new T;
            thisCurrent = fakeHead;
         }
         // creates a new node hanging off of the temp list
         else {
            thisCurrent->next = new Node;
            thisCurrent->next->data = new T;
            thisCurrent = thisCurrent->next;
         }
         
         // update the current list's data
         *thisCurrent->data = *firstCurrent->data;
         
         // set the last next in the list to a nullptr
         thisCurrent->next = nullptr;
         
         // walk the first and second list
         firstCurrent = firstCurrent->next;
         secondCurrent = secondCurrent->next;
      }
      // if second list's data is less then first then walk it
      else {
         secondCurrent = secondCurrent->next;
      }
   }
      
   // make the current list empty and attach the fake head's List
   makeEmpty();
   head = fakeHead;
   
   // clean up pointers
   fakeHead = nullptr;
   firstCurrent = nullptr;
   secondCurrent = nullptr;
   thisCurrent = nullptr;
   
}

#endif
