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
//      caller.
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
   List();                              // default constructor
   ~List();                             // destructor
   List(const List<T>&);                // copy constructor
   
   void makeEmpty();                    // deletes the current List
   void buildList(ifstream&);            // build a List from datafile

   void merge(List<T>&, List<T>&);
   void intersect(const List<T>&, const List<T>&);
   
   bool insert(T*);                      // insert one Node into List
   bool isEmpty() const;                 // is list empty?
   bool retrieve(const T&, T*&) const;   // retrieves a Node from the List
   bool remove(const T&, T*&);           // removes an Node form the List

   void moveToEnd(const T& target);
   void removeEveryOther();
   void printBackwards() const;
   
   // operator overloads
   const List<T>& operator=(const List<T>&);        // =operator overload
   bool operator==(const List<T>&) const;           // ==operator overload
   bool operator!=(const List<T>&) const;           // !=operator overload

private:
   void copy(const List<T>&);    // copies the current list
   struct Node {                 // the node in a linked list
      T* data;                   // pointer to actual data, operations in T
      Node* next;
   };

   Node* head;                   // pointer to first node in list

   void copyHelper(Node*&, const Node*);      // copies the current list
   void makeEmptyHelper(Node*&);              // deletes the current List
   void buildListHelper(ifstream&);            // build a List from datafile
   bool insertHelper(Node*&, Node*);          // insert one Node into List
   
   bool equalityHelper(const Node*, const Node*) const;
   bool retrieveHelper(const Node*, const T&, T*&) const;
   bool removeHelper(const Node*, const T&, T*&);
   /*
   void mergeHelper(List<T>&, List<T>&);
   void intersectHelper(const List<T>&, const List<T>&);

   
   
   void printHelper(Node*) const;
   void removeEveryOtherHelper(Node*) const;
   void moveToEndHelper(Node*) const;
    */
   void printBackwardsHelper(Node*) const;
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
   copyHelper(head, right.head);
}

//----------------------------------------------------------------------------
template <typename T>
void List<T>::copyHelper(Node*& current, const Node* rightCurrent) {
   if(rightCurrent == nullptr) {
      return;
   }
   current = new Node;
   current->data = new T(*rightCurrent->data);
   current->next = nullptr;
   copyHelper(current->next, rightCurrent->next);
}

//----------------------------------------------------------------------------
// makeEmpty
// empties the current object
template <typename T>
void List<T>::makeEmpty() {
   makeEmptyHelper(head);
}

//----------------------------------------------------------------------------
// makeEmptyHelper
// empties the current object
template <typename T>
void List<T>::makeEmptyHelper(Node*& current) {
   if(current == nullptr) {
      return;
   }
   
   makeEmptyHelper(current->next);
   
   delete current->data;
   current->data = nullptr;
   delete current;
   current = nullptr;
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

   // if the list is empty or node ptr should be inserted before head
   if (isEmpty() || *ptr->data < *head->data) {
      ptr->next = head;
      head = ptr;
   }
   // then check the rest of the list until we find where it belongs
   else {
      return insertHelper(head, ptr);
   }
   return true;
}

//----------------------------------------------------------------------------
// insertHelper
// insert an item into list; operator< of the T class
// has the responsibility for the sorting criteria
template <typename T>
bool List<T>::insertHelper(Node*& current, Node* dataptr) {
   if(current == nullptr || *current->data > *dataptr->data) {
      Node* temp = current;
      current = dataptr;
      current->next = temp;
      return true;
   }
   return insertHelper(current->next, dataptr);
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
bool List<T>::operator==(const List<T>& right) const {
   // if the current object is same as right
   if(this == &right) return true;
   else return equalityHelper(head, right.head);
   
}

//----------------------------------------------------------------------------
// equalityHelper
// finds if two lists are equal
template <typename T>
bool List<T>::equalityHelper(const Node* current, const Node* rightCurrent) const {
   if(!rightCurrent && current) return false;
   else if(rightCurrent && !current) return false;
   else if(!rightCurrent && !current) return true;
   return (*current->data == *rightCurrent->data && equalityHelper(current->next, rightCurrent->next));
}

//----------------------------------------------------------------------------
// operator!=
// utilizes definition of == to find if two lists are not equal
template <typename T>
bool List<T>::operator!=(const List<T>& right) const {
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
   
   return retrieveHelper(head, target, p);
}
 
//----------------------------------------------------------------------------
// retrieve
// retrieves a data object from the linked list
template <typename T>
bool List<T>::retrieveHelper(const Node* current, const T& target, T*& p) const {
   if(current == nullptr) {
      p = nullptr;
      return false;
   }
   else if(*current->data == target) {
      p = current->data;
      return true;
   }
   return retrieveHelper(current->next, target, p);
}

//----------------------------------------------------------------------------
// remove
// retrieves an object and removes it's Node from the List
template <typename T>
bool List<T>::remove(const T& target, T*& p) {
   if(head == nullptr) {
      return false;
   }
   
   return removeHelper(head, target, p);
}
 
//----------------------------------------------------------------------------
// remove
// retrieves an object and removes it's Node from the List
template <typename T>
bool List<T>::removeHelper(const Node* current, const T& target, T*& p) {
   if(current == nullptr) {
      p = nullptr;
      return false;
   }
   else if(*current->data == target) {
      p = current->data;
      current = current->next;
      return true;
   }
   return removeHelper(current->next, target, p);
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

//----------------------------------------------------------------------------
template <typename T>
void List<T>::moveToEnd(const T& target) {
   if(head == nullptr) {
      return;
   }
   
   // previous will hold the target node if found
   Node* previous = head;
   Node* current = head->next;
   bool found = false;
   
   // head case
   if(*head->data == target) {
      head = current;
      previous->next = nullptr;
   }
   else {
      
      while(current != nullptr) {
         if(*current->data == target) {
            previous->next = current>next;
            previous = current;
            found = true;
            break;
         }
         else {
            previous = current;
            current = current->next;
         }
      }
      
      if(found) {
         while(current->next != nullptr) {
            current = current->next;
         }
         current->next = previous;
      }
   }
}

//----------------------------------------------------------------------------
template <typename T>
void List<T>::removeEveryOther() {
   if(isEmpty()) {
      return;
   }
   else {
      Node* previous = head;
      Node* current = head->next;

      // head case
      head = head->next;
      delete previous->data;
      previous->data = nullptr;
      previous->next = nullptr;
      delete previous;
      previous = current;

      while(current != nullptr && current->next != nullptr) {
         current = current->next;
         previous->next = current->next;
         previous = current;
         current = current->next;
         delete previous->data;
         
         previous->data = nullptr;
         previous->next = nullptr;
         delete previous;
         previous = current;
      }
   }
}

//----------------------------------------------------------------------------
// printBackwards
template <typename T>
void List<T>::printBackwards() const {
   printBackwardsHelper(head);
}
//----------------------------------------------------------------------------
// printBackwardsHelper
template <typename T>
void List<T>::printBackwardsHelper(Node* current) const {
   if(current == nullptr) {
      return;
   }
   
   printBackwardsHelper(current->next);
   cout << *current->data;
}

#endif
