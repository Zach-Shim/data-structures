#include <iostream>
using namespace std;

#include "list.h"
#include "nodedata.h"
#include "employee.h"

//---------------------- testCopyConstructor --------------------------------
// Not a member function, pass by value forces a copy to be made.
// After makeEmpty, the pass by reference list will be empty, while
// the pass by value list will be the original list as in main.
// Also tests destructor behind the scenes.
//---------------------------------------------------------------------------

template <typename Object>
void testCopyConstructor(List<Object>& byRefList, List<Object> byValList) {
   cout << "Test Copy Constructor and Destructor" << endl;
   cout << "------------------------------------" << endl;
   byRefList.makeEmpty();
   cout << "after emptying, byRefList is: " << endl << byRefList << endl;
   cout << "byValList is: " << endl << byValList << endl;
}

int main() {

   List<Employee> company1;
   ifstream infile1("data33.txt");

   company1.buildList(infile1);
   cout << "company 1" << endl << company1 << endl;
   company1.printBackwards();
/*
   // list of NodeData, to be sorted by numerical value, then char
   List<NodeData> mylist, mylist2, mylist3;
   NodeData* p = new NodeData(20, 'n');  mylist.insert(p);
   p = new NodeData(10, 'f');  mylist.insert(p);
   p = new NodeData(16, 'u');  mylist.insert(p);
   p = new NodeData(25, '!');  mylist.insert(p);

   p = new NodeData(16, 'u');  mylist2.insert(p);
   p = new NodeData(15, 't');  mylist2.insert(p);
   p = new NodeData(19, 'f');  mylist2.insert(p);
   p = new NodeData(14, 's');  mylist2.insert(p);
   p = new NodeData(25, '!');  mylist2.insert(p);
   p = new NodeData(18, 'f');  mylist2.insert(p);
   cout << "mylist:" << endl << mylist << endl;
   cout << "mylist2:" << endl << mylist2 << endl;
   mylist3.intersect(mylist, mylist2);
   cout << "mylist3:" << endl << mylist3 << endl;

   // Many lists of employees,
   // to be sorted alphabetically by last name, then first.
   // Vary the data files to test your list code.

   List<Employee> company1, company2, company3, company4, company5, company6,
                  company7, company8, company9, company10, company11;
   ifstream infile1("data31.txt"), infile2("data32.txt"),
            infile3("data33.txt"), infile4("data34.txt");

   company1.buildList(infile1);
   company2.buildList(infile2);
   company3.buildList(infile3);
   company4.buildList(infile4);
   company6 = company4;
   company7 = company1;
   company8 = company2;
   company10 = company11 = company3;

   cout << "test intersect 1 and 2 into 3" << endl;
   cout << "----------------------------" << endl;
   cout << "Company1:" << endl << company1 << endl;
   cout << "Company3:" << endl << company4 << endl;
   company3.intersect(company1, company2);
   cout << "company1 is " << (company1.isEmpty() ? "empty" : "not empty")
        << endl;
   cout << "company3 is " << (company3.isEmpty() ? "empty" : "not empty")
        << endl;
   cout << "Company3:" << endl << company3 << endl;

   cout << "test intersect 1 and 1 into 3" << endl;
   cout << "------------------------------------------------" << endl;
   cout << "Company1:" << endl << company1 << endl;
   cout << "Company1:" << endl << company1 << endl;
   company3.intersect(company1, company1);
   cout << "Company3:" << endl << company3 << endl;

   cout << "test intersect 4 and 4 into 4" << endl;
   cout << "----------------------------" << endl;
   cout << "Company4:" << endl << company4 << endl;
   cout << "Company4:" << endl << company4 << endl;
   company4.intersect(company4, company4);
   cout << "company4 is " << (company4.isEmpty() ? "empty" : "not empty")
        << endl;
   cout << "Company4:" << endl << company4 << endl;

   cout << "test intersect 4 and 3 into 4" << endl;
   cout << "--------------------------------------------------" << endl;
   cout << "Company3:" << endl << company3 << endl;
   cout << "Company4:" << endl << company4 << endl;
   company4.intersect(company3, company4);
   cout << "Company4:" << endl << company4 << endl;

   cout << "test intersect 5 and 5 (both empty) into 3" << endl;
   cout << "Company5:" << endl << company5 << endl;
   cout << "Company5:" << endl << company5 << endl;
   cout << "--------------------------------------------------" << endl;
   company3.intersect(company5, company5);
   cout << "Company3" << endl << company3 << endl;

   cout << "test intersect 7 and 3 into 2" << endl;
   cout << "----------------------------------" << endl;
   cout << "Company7:" << endl << company7 << endl;
   cout << "Company3:" << endl << company3 << endl;
   company2.intersect(company1, company2);
   cout << "company1 is " << (company7.isEmpty() ? "empty" : "not empty")
        << endl;
   cout << "company3 is " << (company3.isEmpty() ? "empty" : "not empty")
        << endl;
   cout << "Company2:" << endl << company2 << endl;

   testCopyConstructor(company10, company10);
   cout << "back in main, Company10:" << endl << company10 << endl;
*/
   return 0;
}
