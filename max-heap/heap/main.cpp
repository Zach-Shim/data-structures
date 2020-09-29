#include <iostream>
#include "max_heap.h"
int main() {
   cout << "hello" << endl;
   
   MaxHeap<int> myHeap;
   myHeap.insert(2);
   myHeap.insert(12);
   myHeap.insert(5);
   myHeap.insert(30);
   myHeap.insert(25);
   myHeap.insert(42);
   myHeap.insert(17);
   myHeap.insert(8);
   myHeap.insert(14);
   myHeap.insert(9);
   cout << "After insertions: " << myHeap << endl << endl;
   
   cout << "Remove top index 2 times: " << endl;
   myHeap.remove();
   cout << "Remove 1: " << myHeap << endl;
   myHeap.remove();
   cout << "Remove 2: " << myHeap << endl << endl;
   
   cout << "Height: " << myHeap.getHeight() << endl;
   cout << "Top Index: " << myHeap.peek() << endl;
}
