#include "newMap.h"

#include <iostream>
#include <cassert>

using namespace std;

int main(){
  
Map m;  // maps strings to doubles
    
    cout << m.size() << endl;
    
    assert(m.empty());
    ValueType v = -1234.5;
    assert( !m.get("abc", v)  &&  v == -1234.5); // v unchanged by get failure
    m.insert("xyz", 9876.5);
    assert(m.size() == 1);
    KeyType k = "hello";
    assert(m.get(0, k, v)  &&  k == "xyz"  &&  v == 9876.5);
    
    Map gpas;
    gpas.insert("Fred", 2.956);
    gpas.insert("Ethel", 3.538);
    double v0;
    string k1;
    assert(gpas.get(1,k1,v0)  &&  (k1 == "Fred"  ||  k1 == "Ethel"));
    string k2;
    assert(gpas.get(1,k2,v0)  &&  k2 == k1);
    

  Map mp(5);

  mp.insert("Meme", 4.1);

  std::cerr << "size: " << mp.size() << std::endl;
  mp.insert("Meme", 4.1);

  std::cerr << "size: " << mp.size() << std::endl;
  mp.insert("Meme2", 4.1);
  mp.insert("Meme3", 4.1);

  std::cerr << "size: " << mp.size() << std::endl;
  mp.insert("Meme4", 4.1);
  mp.insert("Meme5", 4.1);
  mp.insert("Meme6", 4.1);
  mp.insert("Meme7", 4.1);

  std::cerr << "size: " << mp.size() << std::endl;


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