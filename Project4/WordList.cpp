#include "provided.h"
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "MyHash.h"


using namespace std;


string toLowerCase(const string& s);


class WordListImpl
{
public:
    bool loadWordList(string filename);
    bool contains(string word) const;
    vector<string> findCandidates(string cipherWord, string currTranslation) const;
private:
    MyHash<string, vector<string>> m_wordMap;
    string getLetterPattern(const string& s) const;
    int matches(string a, string b, string c) const;
    int size()
    {
        return m_wordMap.getNumItems();
    }
    
};

bool WordListImpl::loadWordList(string filename)
{
    m_wordMap.reset();

    ifstream words(filename);
    if ( ! words)
        return false;
 
    string s;
    while (getline(words, s))
    {
        s = toLowerCase(s);
        int check = s.find_first_not_of("abcdefghijklmnopqrstuvwxyz'");
        if (check == -1)
        {
            vector<string>* wordArray = m_wordMap.find(getLetterPattern(s));
            if (wordArray == nullptr)
            {
                vector<string> temp;
                temp.push_back(s);
                m_wordMap.associate(getLetterPattern(s), temp);
            }
            else if (find(wordArray->begin(), wordArray->end(), s) == wordArray->end())
            {    
                wordArray->push_back(s);
            }
        }
    }
    return true;
}



bool WordListImpl::contains(string word) const
{
    const vector<string> *wordArray = m_wordMap.find(getLetterPattern(word));
    if (wordArray != nullptr)
        for (int i = 0; i < wordArray->size(); i++)
            if (wordArray->at(i) == toLowerCase(word))
                return true;
    return false;
}

vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
{
    vector<string> candidates;
    if (cipherWord.size() != currTranslation.size())
        return candidates;
    
    cipherWord = toLowerCase(cipherWord);
    currTranslation = toLowerCase(currTranslation);

    int check1 = cipherWord.find_first_not_of("abcdefghijklmnopqrstuvwxyz'");
    int check2 = currTranslation.find_first_not_of("abcdefghijklmnopqrstuvwxyz'?");
    
    if (check1 != -1 || check2 != -1)
        return candidates;


    const vector<string>* words = m_wordMap.find(getLetterPattern(cipherWord));
    if (words != nullptr)
    {
        for (int i = 0; i < words->size(); i++)
        {
            string x = words->at(i);
            switch (matches(x, cipherWord, currTranslation))
            {
                case 0:
                    candidates.push_back(x);
                    break;
                case 1:
                    break;
                case 2:
                    vector<string> failure;
                    return failure;
                    break;
            }
        }

    }

    return candidates;

    
}

string WordListImpl::getLetterPattern(const string& s) const
{
    string letters = "", pattern = "";
    char first = 'A';
    for (int i = 0; i < s.size(); i++)
    {
        int pos = letters.find(s[i]);
        if ( pos == -1 )
        {
            letters += s[i];
            pattern += first + letters.size() - 1;
        }
        else
            pattern += first + pos;
    }
    return pattern;
}


int WordListImpl::matches(string a, string b, string c) const
{
    // a is word
    // b is cipher
    // c is translation
    int out = 0;
    for (int i = 0; i < a.size(); i++)
    {
        char word = a[i];
        char cipher = b[i];
        char translation = c[i];

        if (isalpha(translation))
	{
            if (! isalpha(cipher))
                return 2;
            else if (translation != word)
                return 1;
        }
	else if (translation == '?')
        {
	    if (! isalpha(cipher))
                return 2;
            else if (! isalpha(word))
                return 1;
        }
	else if (translation == '\'')
        {
	    if (cipher != '\'')
                return 2;
            else if (word != '\'')
                return 1;
        }
    }
    return out;
}

//***** hash functions for string, int, and char *****

unsigned int hash(const std::string& s)
{
    return std::hash<std::string>()(s);
}

unsigned int hash(const int& i)
{
    return std::hash<int>()(i);
}

unsigned int hash(const char& c)
{
    return std::hash<char>()(c);
}



string toLowerCase(const string& s) 
{
    string out = "";
    for (int i = 0; i < s.size(); i++)
    {
        out += tolower(s[i]);
    }
    return out;
}


//******************** WordList functions ************************************

// These functions simply delegate to WordListImpl's functions.
// You probably don't want to change any of this code.

WordList::WordList()
{
    m_impl = new WordListImpl;
}

WordList::~WordList()
{
    delete m_impl;
}

bool WordList::loadWordList(string filename)
{
    return m_impl->loadWordList(filename);
}

bool WordList::contains(string word) const
{
    return m_impl->contains(word);
}

vector<string> WordList::findCandidates(string cipherWord, string currTranslation) const
{
   return m_impl->findCandidates(cipherWord, currTranslation);
}
