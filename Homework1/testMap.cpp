#include "Map.h"

#include <iostream>
#include <cassert>

using namespace std;

int main()
{
    Map m;  // maps strings to ValueTypes
    
    cout << m.size() << endl;
    
    assert(m.empty());
    ValueType v = -1234;
    assert( !m.get("abc", v)  &&  v == -1234); // v unchanged by get failure
    m.insert("xyz", 9876);
    assert(m.size() == 1);
    KeyType k = "hello";
    assert(m.get(0, k, v)  &&  k == "xyz"  &&  v == 9876);
    
    Map gpas;
    gpas.insert("Fred", 2);
    gpas.insert("Ethel", 3);
    ValueType v0;
    string k1;
    assert(gpas.get(1,k1,v0)  &&  (k1 == "Fred"  ||  k1 == "Ethel"));
    string k2;
    assert(gpas.get(1,k2,v0)  &&  k2 == k1);


  Map mipe;

  mipe.insert("hit", 14);
  mipe.insert("hit2", 12);
  mipe.insert("hit3", 12);
  mipe.insert("hit4", 12);
  mipe.insert("hit5", 12);
  mipe.insert("hit6", 12);
  mipe.insert("hit7", 12);
  mipe.insert("hit8", 12);


  Map mm;

  mm = mipe;

  Map mn = mm;
    
    
    
}
