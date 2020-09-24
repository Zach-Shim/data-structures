// Driver to test our class Array template
#include "array.h"
#include "nodedata.h"
#include <string>
#include <iostream>
using namespace std;

// To compile using g++, enter
//   g++ arraytemplatedriver.cpp nodedata.cpp

int main() {
   cout << "************* create int Array objects, test, print **************"
        << endl;
   Array<int> a(5), b(3), c;
   a[0] = 10;
   a[1] = 20;
   a[2] = 30;
   a[3] = 40;
   a[4] = 50;
   b[0] = 37;
   b[1] = 47;
   b[2] = 57;
   c = b;
   cout << "a contains:  " << a;
   cout << "b contains:  " << b;
   cout << "c contains:  " << c;

   // use overloaded equality (==) operator
   cout << "Evaluating  a == b:   "
        << (a == b ? "equal" : "not equal") << endl;
   cout << "Evaluating  b == c:   "
        << (b == c ? "equal" : "not equal") << endl << endl;

   cout << "************ create string Array objects, test, print ************"
        << endl;
   string s1= "hello", s2 = "world";
   Array<string> s(2);
   s[0] = s1;
   s[1] = s2;
   cout << "s contains:  " << s << endl;

   cout << "*********** create NodeData Array objects, test, print ***********"
        << endl;
   NodeData n1(5, 'x'), n2(6, 'y'), n3(7, 'z'), n4(8, 'w');
   Array<NodeData> stuff(3), morestuff(3);
   stuff[0] = morestuff[0] = n1;
   stuff[1] = morestuff[1] = n2;
   stuff[2] = morestuff[2] = n3;
   cout << "NodeData array called stuff contains:  " << stuff;
   cout << "NodeData array called morestuff contains:  " << morestuff;
   cout << "Evaluating  stuff == morestuff:   "
        << (stuff == morestuff ? "equal" : "not equal") << endl;
   cout << "Change the value of morestuff[2] from  " << morestuff[2];
   morestuff[2] = n4;
   cout << "  to  " << morestuff[2] << endl;
   cout << "morestuff contains:  " << morestuff;
   cout << "Evaluating  stuff == morestuff:   "
        << (stuff == morestuff ? "equal" : "not equal") << endl << endl;

   return 0;
}
