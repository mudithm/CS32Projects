/*#include "Map.h"
#include <iostream>
#include <stdio.h>
#include <cassert>
using namespace std;

int main()
{
    KeyType k;
    ValueType v;
    Map m1;
    
    assert(m1.empty());             //checks that empty function works
    m1.insert("a",1);
    assert(!m1.empty());
    
    assert((m1.size())==1);         //checks size function
    
    assert(!(m1.insert("a",1)));    //checks insert function returns false for same key, diff value
    assert((m1.size())==1);         //size doesn't change
    m1.insert("b",2);               //checks insert function
    assert((m1.size())==2);
    
    m1.insert("c",2);               //checks erase function
    m1.erase("c");
    assert((m1.size())==2 && !(m1.contains("c")));
    
    assert(m1.contains("b"));       //checks contains function
    
    m1.insertOrUpdate("a",3);       //checks insertOrUpdate function
    m1.get("a",v);                  //checks get function
    assert(v==3);
    m1.insertOrUpdate("c",2);
    assert((m1.size())==3);
    m1.get(2,k,v);                  //check get function with i
    assert(k=="c" && v==2);
    
    
    assert(!(m1.get(4,k,v)));
    Map m2;
    m2.insert("d", 1);
    m2.insert("e", 2);
    m2.insert("f", 3);
    m2.insert("a", 3);
    
    Map m3=m2;                      //checks copy constructor
    assert(m1.get(0,k,v)==m2.get(0,k,v));
    
    m3=m1;                          //check assignment operator
    assert(m1.get(0,k,v)==m3.get(0,k,v));
    
    combine(m1, m2, m3);            //check combine function
    for (int i=0; i<m1.size(); i++)
    {
        m1.get(i,k,v);
        cout<<k<<"  "<<v<<endl;
    }
    cout<<endl;
    for (int i=0; i<m2.size(); i++)
    {
        m2.get(i,k,v);
        cout<<k<<"  "<<v<<endl;
    }
    cout<<endl;
    for (int i=0; i<m3.size(); i++)
    {
        m3.get(i,k,v);
        cout<<k<<"  "<<v<<endl;
    }
    
    m2.insertOrUpdate("a", 2);
    combine(m1, m2, m3);            //checks that differing value keys dont get copied over
    
    cout<<endl;
    for (int i=0; i<m3.size(); i++)
    {
        m3.get(i,k,v);
        cout<<k<<"  "<<v<<endl;
    }
    
    subtract(m1,m2,m3);             //check that subtract function worksf
    cout<<endl;
    for (int i=0; i<m3.size(); i++)
    {
        m3.get(i,k,v);
        cout<<k<<"  "<<v<<endl;
    }
}
*/
#include "Map.h"

#include <iostream>
#include <cassert>

using namespace std;

int main()
{
    
	 
//		For an empty map:
   							


    // default constructor

    Map m;
    
    // member functions

    assert(m.size() == 0);			// test size
    assert(m.empty());				// test empty
    assert(! m.contains(" "));		// test contains
    assert(m.insert("hello", 1));	// test insert
    assert(m.erase("hello"));		// test erase
    assert( ! m.update("hello", 4));// test update

    ValueType value;
    assert( ! m.get("hello", value)); // test get
    assert(m.insertOrUpdate("hello", 56)); // test insertOrUpdate
    assert(m.insertOrUpdate("hello", 57)); // test insertOrUpdate

    assert(m.get("hello", value) && value == 57.0); // test insertOrUpdate
    assert(m.erase("hello"));		// test erase

    // Copy and Assignment

    Map mp = m;
    assert(mp.size() == m.size()); 	// test copy constructor
    m.insert("Test", 55);
    int sz = m.size();
    mp.swap(m);						// test swap function
    assert(mp.size() == sz);		// test swap function
    assert(mp.get("Test", value) && value == 55); // test swap function
    m = mp;

    assert(mp.size() == m.size()); 	// test assignment operator
    assert(m.size() == sz);			// test assignment operator
    assert(m.erase("Test")); 	

    assert(! m.erase("Ricky")); 	// nothing to erase

    // Algorithm Functions
    Map out;
    assert(combine(m, mp, out));	// test combine
    assert(out.size() == m.size() + mp.size());	// test subtract
    subtract(m, mp, out);			
    assert(out.size() == m.size());	// test subtract


    // aliasing

    assert(combine(m, m, m));		// test combine w/ aliasing
    subtract(mp, mp, mp);
    assert(mp.size() == 0);			// test subtract w/ aliasing

    cerr << "Empty Map tests passed" << endl;


    Map d;		  // emptying lists
    m = d;


		//For an one pair map:

    
    // member functions

    assert(m.insert("a", 1));


    assert(m.size() == 1);			// test size
    assert( ! m.empty());				// test empty
    assert(m.contains("a"));		// test contains
    assert(m.insert("hello", 2));	// test insert
    assert(m.erase("hello"));		// test erase
    assert( ! m.update("hello", 4));// test update

    assert( ! m.get("hello", value)); // test get
    assert(m.insertOrUpdate("hello", 56)); // test insertOrUpdate
    assert(m.insertOrUpdate("hello", 57)); // test insertOrUpdate

    assert(m.get("hello", value) && value == 57.0); // test insertOrUpdate
    assert(m.erase("hello"));		// test erase

    // Copy and Assignment

    mp = m;
    assert(mp.size() == m.size()); 	// test copy constructor
    m.insert("Test", 55);
    sz = m.size();
    mp.swap(m);						// test swap function
    assert(mp.size() == sz);		// test swap function
    assert(mp.get("Test", value) && value == 55); // test swap function
    
    m = mp;
    assert(mp.size() == m.size()); 	// test assignment operator
    assert(m.size() == sz);			// test assignment operator
    assert(m.erase("Test")); 	

    assert(! m.erase("Ricky")); 	// nothing to erase

    // Algorithm Functions


    m = d;  // emptying lists
    mp = d;

    m.insert("thing1", 345);
    m.insert("thing2", 346);
    m.insert("thing3", 347);

    mp.insert("thing4", 348);
    mp.insert("thing5", 349);
    mp.insert("thing6", 350);

    assert(combine(m, mp, out));	// test combine
    assert(out.size() == m.size() + mp.size());	// test subtract
    subtract(m, mp, out);			
    assert(out.size() == m.size());	// test subtract


    // aliasing

    assert(combine(m, m, m));		// test combine w/ aliasing
    subtract(mp, mp, mp);
    assert(mp.size() == 0);			// test subtract w/ aliasing

    cerr << "Single Pair Map tests passed" << endl;



//		For a multiple pair map:


   	m = d;	// emptying lists	
    mp = d;
    
    // member functions

    assert(m.insert("a", 1));
    assert(m.insert("b", 2));
    assert(m.insert("c", 3));




    assert(m.size() == 3);			// test size
    assert( ! m.empty());				// test empty
    assert(m.contains("a"));		// test contains
    assert(m.contains("b"));		// test contains
    assert(m.contains("c"));		// test contains
    assert(m.insert("hello", 2));	// test insert
    assert(m.erase("hello"));		// test erase
    assert( ! m.update("hello", 4));// test update

    assert( ! m.get("hello", value)); // test get
    assert(m.insertOrUpdate("hello", 56)); // test insertOrUpdate
    assert(m.insertOrUpdate("hello", 57)); // test insertOrUpdate

    assert(m.get("hello", value) && value == 57.0); // test insertOrUpdate
    assert(m.erase("hello"));		// test erase

    // Copy and Assignment

    mp = m;
    assert(mp.size() == m.size()); 	// test copy constructor
    m.insert("Test", 55);
    sz = m.size();
    mp.swap(m);						// test swap function
    assert(mp.size() == sz);		// test swap function
    assert(mp.get("Test", value) && value == 55); // test swap function
    
    m = mp;
    assert(mp.size() == m.size()); 	// test assignment operator
    assert(m.size() == sz);			// test assignment operator
    assert(m.erase("Test")); 	

    assert(! m.erase("Ricky")); 	// nothing to erase

    // Algorithm Functions
    m = d;
    mp = d;

    m.insert("thing1", 345);
    m.insert("thing2", 346);
    m.insert("thing3", 347);

    mp.insert("thing4", 348);
    mp.insert("thing5", 349);
    mp.insert("thing6", 350);

    assert(combine(m, mp, out));	// test combine
    assert(out.size() == m.size() + mp.size());	// test subtract
    subtract(m, mp, out);			
    assert(out.size() == m.size());	// test subtract


    // aliasing

    assert(combine(m, m, m));		// test combine w/ aliasing
    subtract(mp, mp, mp);
    assert(mp.size() == 0);			// test subtract w/ aliasing

    cerr << "Multiple Pair Map tests passed" << endl;



}

/*
 #include "Map.h"
        #include <type_traits>
        
        #define CHECKTYPE(f, t) { auto p = static_cast<t>(f); (void)p; }
        
        static_assert(std::is_default_constructible<Map>::value,
                "Map must be default-constructible.");
        static_assert(std::is_copy_constructible<Map>::value,
                "Map must be copy-constructible.");

        void ThisFunctionWillNeverBeCalled()
        {
            CHECKTYPE(&Map::operator=,      Map& (Map::*)(const Map&));
            CHECKTYPE(&Map::empty,          bool (Map::*)() const);
            CHECKTYPE(&Map::size,           int  (Map::*)() const);
            CHECKTYPE(&Map::insert,         bool (Map::*)(const KeyType&, const ValueType&));
            CHECKTYPE(&Map::update,         bool (Map::*)(const KeyType&, const ValueType&));
            CHECKTYPE(&Map::insertOrUpdate, bool (Map::*)(const KeyType&, const ValueType&));
            CHECKTYPE(&Map::erase,          bool (Map::*)(const KeyType&));
            CHECKTYPE(&Map::contains,       bool (Map::*)(const KeyType&) const);
            CHECKTYPE(&Map::get,            bool (Map::*)(const KeyType&, ValueType&) const);
            CHECKTYPE(&Map::get,            bool (Map::*)(int, KeyType&, ValueType&) const);
            CHECKTYPE(&Map::swap,           void (Map::*)(Map&));
            
            CHECKTYPE(combine,  bool (*)(const Map&, const Map&, Map&));
            CHECKTYPE(subtract, void (*)(const Map&, const Map&, Map&));
        }
        
        int main()
        {}

 #include "Map.h"
        #include <iostream>
        #include <cassert>
        using namespace std;

        void test()
        {
            Map m;
            assert(m.insert("Fred", 123));
            assert(m.insert("Ethel", 456));
            assert(m.size() == 2);
            ValueType v = 42;
            assert(!m.get("Lucy", v)  &&  v == 42);
            assert(m.get("Fred", v)  &&  v == 123);
            v = 42;
            KeyType x = "Lucy";
            assert(m.get(0, x, v)  &&
                   ((x == "Fred"  &&  v == 123)  ||  (x == "Ethel"  &&  v == 456)));
            KeyType x2 = "Ricky";
            assert(m.get(1, x2, v)  &&
                   ((x2 == "Fred"  &&  v == 123)  ||  (x2 == "Ethel"  &&  v == 456))  &&
                   x != x2);
        }

        int main()
        {
            test();
            cout << "Passed all tests" << endl;
        }


#include "Map.h"
        #include <iostream>
        #include <cassert>
        using namespace std;

        void test()
        {
            Map m;
            assert(m.insert(10, "diez"));
            assert(m.insert(20, "veinte"));
            assert(m.size() == 2);
            ValueType v = "cuarenta y dos";
            assert(!m.get(30, v)  &&  v == "cuarenta y dos");
            assert(m.get(10, v)  &&  v == "diez");
            v = "cuarenta y dos";
            KeyType x = 30;
            assert(m.get(0, x, v)  &&
                   ((x == 10  &&  v == "diez")  ||  (x == 20  &&  v == "veinte")));
            KeyType x2 = 40;
            assert(m.get(1, x2, v)  &&
                   ((x2 == 10  &&  v == "diez")  ||  (x2 == 20  &&  v == "veinte"))  &&
                   x != x2);
        }

        int main()
        {
            test();
            cout << "Passed all tests" << endl;
        }					
        }*/

