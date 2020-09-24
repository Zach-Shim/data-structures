#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
using namespace std;

//---------------------------------------------------------------------------
// Array class:  like an array (retains all functionality) but also
//   includes additional features:
//   -- allows input and output of the whole array
//   -- allows for comparison of 2 arrays, element by element
//   -- allows for assignment of 2 arrays
//   -- size is part of the class (so no longer needs to be passed)
//   -- includes range checking, program terminates for out-of-bound subscripts
//
// Assumptions:
//   -- size defaults to a fixed size of 10 if size is not specified
//   -- in <<, display 10 per line
//---------------------------------------------------------------------------

template <typename ItemType>
class Array {
friend ostream& operator<<(ostream &output, const Array<ItemType> &a) {
   int i;
   for (i = 0; i < a.arraySize; i++) {
      output << a.items[i] << ' ';
      if ((i + 1) % 10 == 0)           // display 10 per line
         output << endl;
   }

   if (i % 10 != 0) output << endl;
   return output;                      // e.g., enables cout << x << y;
}
friend istream& operator>>(istream &input, Array<ItemType> &a) {
   for (int i = 0; i < a.arraySize; i++)
      input >> a.items[i];
   return input;                        // e.g., enables cin >> x >> y;
}
public:
   Array(int = 0);            // default constructor
   Array(const Array&);       // copy constructor
   ~Array();                  // destructor
   
   // overloaded operators
   const Array<ItemType>& operator=(const Array&);    // assign Array objects
   bool operator==(const Array&) const;      // equality, arrays are identical
   bool operator!=(const Array&) const;      // inequality, array are unequal
   ItemType& operator[](int);                // subscript operator, mutator
   const ItemType& operator[](int) const;    // subscript operator, accessor
   
   // return size of array
   int size();
   
   // returns true if array contains anEntry
   bool contains(const ItemType& anEntry) const;
   
   // return the frequency of a anEntry
   int getFrequencyOf(const ItemType& anEntry) const;
   
   // converts this object to a vector
   vector<ItemType> toVector() const;
   
private:
   static const int DEFAULT_CAPCITY = 100;
   ItemType* items;              // array to hold objects of ItemType
   int arraySize;                // number of items in the array
   
   void copy(const Array&);      // copy constructor and operator= helper
};

//------------------------------ Constructor ----------------------------------
// Default constructor for class Array
template <typename ItemType>
Array<ItemType>::Array(int arrSize): arraySize(arrSize) {
   items = new ItemType[arrSize];
}

//------------------------------- Destructor ----------------------------------
template <typename ItemType>
Array<ItemType>::~Array() {
   delete [] items;
}

//--------------------------- Copy Constructor --------------------------------
// Copy constructor for class Array
template <typename ItemType>
Array<ItemType>::Array(const Array<ItemType>& right) {
   copy(right);
}

//---------------------------- Copy -------------------------------------------
// Copy constructor for class Array
template <typename ItemType>
void Array<ItemType>::copy(const Array<ItemType>& right) {
   arraySize = right.arraySize;
   items = new ItemType[arraySize];
   assert(items != nullptr);
   
   for(int i = 0; i < arraySize; i++) {
      items[i] = right.items[i];
   }
   
}

//---------------------------- operator= --------------------------------------
// Overloaded operator= for class Array
template <typename ItemType>
const Array<ItemType>& Array<ItemType>::operator=(const Array<ItemType>& right) {
   if(this != &right) {
      delete [] items;
      copy(right);
   }
   return *this;
}

//------------------------------  ==  -----------------------------------------
// Determine if two arrays are equal.
// The type or object ItemType has responsibility for overloading operator!=
template <typename ItemType>
bool Array<ItemType>::operator==(const Array& right) const {
   for(int i = 0; i < arraySize; i++) {
      if(items[i] != right.items[i]) {
         return false;
      }
   }
   return true;
}

//--------------------------------  !=  ---------------------------------------
// Determine if two arrays are not equal.
template <typename ItemType>
bool Array<ItemType>::operator!=(const Array& right) const {
   return !(*this == right);
}

//-------------------------------  []  ----------------------------------------
// [] mutator
// Overloaded subscript operator, mutator
// terminates if subscript out of range error
template <typename ItemType>
ItemType& Array<ItemType>::operator[](int subscript) {
   assert(0 <= subscript && subscript < arraySize);
   return items[subscript];
}

// ------------------------------- [] -----------------------------------------
// [] accessor
// Overloaded subscript operator, accessor
// terminates if subscript out of range error
template <typename ItemType>
const ItemType& Array<ItemType>::operator[](int subscript) const {
   // assert that the test is true, program terminates if false
   assert(0 <= subscript && subscript < arraySize);
   return items[subscript];
}

// ------------------------------ size ----------------------------------------
// return the size of the array (number of elements in array, not bit size)
template <typename ItemType>
int Array<ItemType>::size() {
   return arraySize;
}

// ---------------------------- contains --------------------------------------
// returns true if array contains anEntry; return false otherwise
template <typename ItemType>
bool Array<ItemType>::contains(const ItemType& anEntry) const {
   for(int i = 0; i < arraySize; i++) {
      if(items[i] == anEntry) {
         return true;
      }
   }
   return false;
}
// --------------------------- getFrequencyOf ---------------------------------
// return the frequency of a anEntry
template <typename ItemType>
int Array<ItemType>::getFrequencyOf(const ItemType& anEntry) const {
   int counter = 0;
   for(int i = 0; i < arraySize; i++) {
      if(items[i] == anEntry) {
         counter++;
      }
   }
}

// ---------------------------- toVector --------------------------------------
// converts this object to a vector
template <typename ItemType>
vector<ItemType> Array<ItemType>::toVector() const {
   vector<ItemType> v;
   for(int i = 0; i < arraySize; i++) {
      v.push_back(items[i]);
   }
   return v;
}

#endif
