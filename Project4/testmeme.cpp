#include <cassert>
#include <iostream>
#include <string>

#include "MyHash.h"
#include "provided.h"


using namespace std;
          

int main()
{
    MyHash<string, double> hash;
    hash.associate("Hello", 5.0);
    cerr << hash.getNumItems() << endl;
    hash.associate("Yellow", 10.0);
    cerr << hash.getNumItems() << endl;
    cerr << *hash.find("Yellow") << endl;    
    cerr << hash.find("Yllow") << endl;    
    hash.associate("Yellow", 15.0);
    cerr << hash.getNumItems() << endl;
    cerr << *hash.find("Yellow") << endl;

    for (int i = 0; i < 1000; i++)
    {
        hash.associate(to_string(i), i);   
    }

    Tokenizer testToken(" :<;>,./*");
    vector<string> meme = testToken.tokenize("sidfuma gnp9r<F9>224 <F9>5u2<F9>2u4<F9 >r2<F9>4u98430h9h a a;:::adf::f::af:af:;adfas;dfijadsf  adsfiha dsf f asdfi adsf  asdfdli sadf ,,asdf,a,fd,asdf ,,.,.,.,, , ., . ,"); 
    for (int i = 0; i < meme.size(); i++)
        cout << meme[i] << endl;   

    WordList ayylmao;
    ayylmao.loadWordList("testWordList.txt");

    cout << ayylmao.contains("arbiter") << endl;    
    cout << ayylmao.contains("arBiTer") << endl;
        cout << ayylmao.contains("--tallat") << endl;

    cout << ayylmao.contains("This") << endl;

    cout << ayylmao.contains("is") << endl;

    cout << ayylmao.contains("a") << endl;

    cout << ayylmao.contains("word") << endl;

    cout << ayylmao.contains("ABCDEFB") << endl;


    cout << "-------------------------" << endl;


    WordList wl;
         if ( ! wl.loadWordList("wordlist.txt"))
         //if ( ! wl.loadWordList("testWordList.txt"))
         {
         cout << "Unable to load word list" << endl;
         }
         cout << "wordlist loaded" << endl;
         cout << "---------" << endl;
         if (wl.contains("onomatopoeia"))
            cout << "I found onomatopoeia!" << endl;
         else
            cout << "Onomatopoeia is not in the word list!" << endl;
         string cipher = "xyqbbq";
         string decodedSoFar = "?r????";
         vector<string> v = wl.findCandidates(cipher, decodedSoFar);
         if (v.empty())
            cout << "No matches found" << endl;
         else
         {
            cout << "Found these matches:" << endl;
            for (size_t k = 0; k < v.size(); k++)
            cout << v[k] << endl; // writes grotto and troppo
         }



         Translator t;
          cout << t.getTranslation("HDXXHDLDQYL") << endl; // writes RE?

 t.pushMapping("DHL", "ERD"); // DàE, HàR, LàD
 if ( ! t.pushMapping("QX", "RY")) // QàR, XàY
    cout << "Both H and Q would map to R!" << endl;
    // The current mapping is still DàE, HàR, LàD with no
    // mapping for Q or X
 cout << t.getTranslation("HDXXHDLDQYL") << endl; // writes RE?
 if ( ! t.pushMapping("H", "r")) // HàS
 cout << "H would map to both R and S!" << endl;

    cout << t.popMapping() << endl;
        cout << t.popMapping() << endl;
            cout << t.popMapping() << endl;
}
