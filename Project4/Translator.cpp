#include "provided.h"
#include <string>
#include <stack>

#include <iostream>

using namespace std;


class TranslatorImpl
{
public:
    TranslatorImpl();
    bool pushMapping(string ciphertext, string plaintext);
    bool popMapping();
    string getTranslation(const string& ciphertext) const;
private:
    stack<string> m_mappingTables;
    string toPlowerCase(const string& s) const
    {
        string toLowerCase(const string& s);
        return toLowerCase(s);
    };
    int m_numPushes;

};

TranslatorImpl::TranslatorImpl() : m_numPushes(0)
{
    string initArray(36, '?');
    m_mappingTables.push(initArray);
}

bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{
    if (ciphertext.size() != plaintext.size())
        return false;
    
    string table = m_mappingTables.top();

    string ciph = toPlowerCase(ciphertext);
    string plain = toPlowerCase(plaintext);

    for (int i = 0; i < ciph.size(); i++)
    {
        
        if (! isalpha(ciph[i]) || ! isalpha(plain[i]))
            return false;
        else if (((table[ciph[i] - 'a'] != '?' ) && (table[ciph[i] - 'a'] != plain[i]))  
                    || ( table[ciph[i] - 'a'] == '?' && table.find(plain[i]) != -1))
            return false;
        else
        {
            if (table[ciph[i] - 'a'] == '?')
                table[ciph[i] - 'a'] = plain[i];
        }

    }

    
    m_mappingTables.push(table);
    m_numPushes++;
    return true;  // This compiles, but may not be correct
}

bool TranslatorImpl::popMapping()
{
    if (m_numPushes <= 0)
        return false;
    m_numPushes--;
    return true;  // This compiles, but may not be correct
}

string TranslatorImpl::getTranslation(const string& ciphertext) const
{
    string out = "";
    string table = m_mappingTables.top();
    

    for (int i = 0; i < ciphertext.size(); i++)
    {
        if (isupper(ciphertext[i]))
        {
            char temp = tolower(ciphertext[i]);
            out += toupper(table[temp - 'a']);
        }
        else if (islower(ciphertext[i]))
            out += table[ciphertext[i] - 'a'];
        else
            out += '?';
    }

    return out;

}

//******************** Translator functions ************************************

// These functions simply delegate to TranslatorImpl's functions.
// You probably don't want to change any of this code.

Translator::Translator()
{
    m_impl = new TranslatorImpl;
}

Translator::~Translator()
{
    delete m_impl;
}

bool Translator::pushMapping(string ciphertext, string plaintext)
{
    return m_impl->pushMapping(ciphertext, plaintext);
}

bool Translator::popMapping()
{
    return m_impl->popMapping();
}

string Translator::getTranslation(const string& ciphertext) const
{
    return m_impl->getTranslation(ciphertext);
}
