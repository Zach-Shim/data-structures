#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <vector>
using namespace std;

template <typename ItemType>
class MaxHeap {

friend ostream& operator<<(ostream& output, const MaxHeap<ItemType>& heap) {
   for(int i = 1; i <= heap.size; i++) {
      output << heap.items[i] << " ";
   }
   return output;
}
   
public:
   MaxHeap();
   ~MaxHeap();
   MaxHeap(const MaxHeap&);

   void clear();
   
   bool isEmpty() const;
   bool insert(const ItemType&);
   bool remove();
   
   int getHeight() const;
   ItemType peek() const;
private:
   static const int ROOT_INDEX = 0;
   vector<ItemType> items;
   int size;
   
   void rebuildHeap(int);
   int getHeightHelper(int) const;
};

//------------------------------- constructor ---------------------------------
template <typename ItemType>
MaxHeap<ItemType>::MaxHeap() {
   items.push_back(-1);
   assert(items.size() > 0);
   size = 0;
}

//------------------------------- destructor ----------------------------------
template <typename ItemType>
MaxHeap<ItemType>::~MaxHeap() {
   /*
   for(int i = 0; i < size; i++) {
      delete items[i];
      items[i] = nullptr;
   }
    */
}

//---------------------------- copy constructor -------------------------------
template <typename ItemType>
MaxHeap<ItemType>::MaxHeap(const MaxHeap& right) {
   size = right.size;
   items.push_back(nullptr);
   for(int i = 0; i < right.size; i++) {
      items.push_back(right.items[i]);
   }
}

//--------------------------------- isEmpty -----------------------------------
template <typename ItemType>
bool MaxHeap<ItemType>::isEmpty() const {
   return size == 0;
}
   
//---------------------------------- insert -----------------------------------
template <typename ItemType>
bool MaxHeap<ItemType>::insert(const ItemType& data) {
   // if(data == nullptr) return false;
   
   // avoid percolating up from root
   items[0] = data;
   
   // ensure there is room in the heap
   size++;
   if(size == items.size()) {
      items.push_back(-1);
   }
   
   // percolate up (see if parent is less than data that we inserted)
   int position = size;
   while(data > items[position / 2]) {
      items[position] = items[position / 2];
      position /= 2;
   }
   items[position] = data;
   items[0] = -1;
   return true;
}

//--------------------------------- remove ------------------------------------
template <typename ItemType>
bool MaxHeap<ItemType>::remove() {
   if(size == 0) return false;
   items[1] = items[size];             // replace root with last element
   items.pop_back();
   size--;
   
   rebuildHeap(1);
   return true;
}

//------------------------------- rebuildHeap ---------------------------------
template <typename ItemType>
void MaxHeap<ItemType>::rebuildHeap(int position) {
   if(size <= 1) return;
   
   // children are at i * 2 and i * 2 + 1 because we start the first index at 1
   int child = position * 2;
   while(child < size) {
      if(child != size && items[child] < items[child + 1]) child++;
      if(items[position] < items[child]) {
         // swap current position and child values
         ItemType temp = items[position];
         items[position] = items[child];
         items[child] = temp;
         
         // update where you are in the array
         position = child;
         child *= 2;
      }
      else {
         break;
      }
   }
}

//-------------------------------- getHeight ----------------------------------
template <typename ItemType>
int MaxHeap<ItemType>::getHeight() const {
   return getHeightHelper(1);
}
      
//----------------------------- getHeightHelper -------------------------------
template <typename ItemType>
int MaxHeap<ItemType>::getHeightHelper(int position) const {
   if(position > size) {
      return 0;
   }
   return 1 + max(getHeightHelper(position * 2), getHeightHelper(position * 2 + 1));
}
   
//--------------------------------- peekTop -----------------------------------
template <typename ItemType>
ItemType MaxHeap<ItemType>::peek() const {
   return items[1];
}

#endif
