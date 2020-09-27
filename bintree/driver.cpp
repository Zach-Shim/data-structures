#include "bintree.h"
#include <fstream>
#include <iostream>
using namespace std;

const int ARRAYSIZE = 100;

//global function prototypes
void buildTree(BinTree<NodeData>&, ifstream&);     
void initArray(NodeData*[]);                      // initialize array to NULL

int main() {
   // create file object infile and open it
   // for testing, call your data file something appropriate, e.g., inputdata.txt
   ifstream infile("inputdata.txt");
   if (!infile) {
      cout << "File could not be opened." << endl;
      return 1;
   }

   // the NodeData class must have a constructor that takes a string
   NodeData blankND;
   NodeData notND("not");
   NodeData bND("b");
   NodeData andND("and");
   NodeData sssND("sss");
   NodeData ttttND("tttt");
   NodeData oooND("ooo");
   NodeData aND("a");
   NodeData yND("y");
   NodeData eND("e");
   NodeData mND("m");
   NodeData tND("t");
   
   // intialize tree and array
   BinTree<NodeData> T, T2, T3, dup;
   NodeData* ndArray[ARRAYSIZE];
   initArray(ndArray);
   
   // test isEmpty
   bool empty = T2.isEmpty();
   cout << "Tree T3 is  " << (empty ? "is empty" : "is not empty") << endl;
   cout << "Initial data:" << endl << "  ";
   
   buildTree(T, infile);              // builds and displays initial data
   cout << endl;
   BinTree<NodeData> first(T);                  // test copy constructor
   dup = dup = T;                     // test operator=, self-assignment
   
   while (!infile.eof()) {
      cout << "Tree Inorder:" << endl << T;             // operator<< does endl
      T.displaySideways();
      
      // test retrieve
      NodeData* p;                   // pointer of retrieved object
      bool found;                    // whether or not object was found in tree
      found = T.retrieve(andND, p);
      cout << "Retrieve --> and:  " << (found ? "found" : "not found") << endl;
      found = T.retrieve(notND, p);
      cout << "Retrieve --> not:  " << (found ? "found" : "not found") << endl;
      found = T.retrieve(sssND, p);
      cout << "Retrieve --> sss:  " << (found ? "found" : "not found") << endl;
      found = T.retrieve(bND, p);
      cout << "Retrieve --> bND:  " << (found ? "found" : "not found") << endl;
      found = T.retrieve(blankND, p);
      cout << "Retrieve --> blankND:  "
                                    << (found ? "found" : "not found") << endl;
      
      // test height
      cout << "The height of T is:    " << T.height() << endl;
      
      // test nodeHeight
      cout << "Height    --> b:    " << T.nodeHeight(bND) << endl;
      cout << "Height    --> and:  " << T.nodeHeight(andND) << endl;
      cout << "Height    --> not:  " << T.nodeHeight(notND) << endl;
      cout << "Height    --> sss:  " << T.nodeHeight(sssND) << endl;
      cout << "Height    --> tttt: " << T.nodeHeight(ttttND) << endl;
      cout << "Height    --> ooo:  " <<  T.nodeHeight(oooND) << endl;
      cout << "Height    --> y:    " << T.nodeHeight(yND) << endl;
      cout << "Height    --> c:  " << T.nodeHeight(notND) << endl;

      // test ==, and !=
      T2 = T;
      cout << "T == T2?     " << (T == T2 ? "equal" : "not equal") << endl;
      cout << "T != first?  " << (T != first ? "not equal" : "equal") << endl;
      cout << "T == dup?    " << (T == dup ? "equal" : "not equal") << endl;
      dup = T;
      
      // test bstreeToArray and arrayToBSTree
      T.bstreeToArray(ndArray);
      T.arrayToBSTree(ndArray);
      T.displaySideways();
      
      T.makeEmpty();                  // empty out the tree
      initArray(ndArray);             // empty out the array

      // test empty tree for bstreeToArray and arrayToBSTree
      T3.bstreeToArray(ndArray);
      T3.arrayToBSTree(ndArray);
      T3.displaySideways();
      
      T3.makeEmpty();                 // empty out the tree
      initArray(ndArray);             // empty out the array

      cout << "---------------------------------------------------------------"
         << endl;
      cout << "Initial data:" << endl << "  ";
      buildTree(T, infile);
      cout << endl;
   }

   return 0;
}

//------------------------------- buildTree ----------------------------------
// Description:
// Builds a tree by reading strings from a file, terminates when "$$" is read
// Since there is some work to do before the actual insert that is
// specific to the client problem,
// It's a global function.
// Preconditions:    T is an empty tree
// Postconditions:   T is has nodes according to the data in the infile stream

void buildTree(BinTree<NodeData>& T, ifstream& infile) {
   string s;

   for (;;) {
      infile >> s;
      cout << s << ' ';
      if (s == "$$") break;                // at end of one line
      if (infile.eof()) break;             // no more lines of data
      NodeData* ptr = new NodeData(s);     // NodeData constructor takes string
      // would do a setData if there were more than a string

      bool success = T.insert(ptr);
      if (!success)
         delete ptr;                       // duplicate case, not inserted
   }
}

//------------------------------- initArray ----------------------------------
// Description:
// initialize the array of NodeData* to NULL pointers
// Preconditions:    none
// Postconditions:   the NodeData* array is fully null

void initArray(NodeData* ndArray[]) {
   for (int i = 0; i < ARRAYSIZE; i++)
      ndArray[i] = NULL;
}


