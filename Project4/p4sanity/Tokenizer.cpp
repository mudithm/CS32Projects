#include "provided.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class TokenizerImpl
{
public:
    TokenizerImpl(string separators);
    vector<string> tokenize(const string& s) const;
private:
    vector<char> m_separators;
};

TokenizerImpl::TokenizerImpl(string separators)
{
    for (int i = 0; i < separators.size(); i++)
        m_separators.push_back(separators[i]);
}

vector<string> TokenizerImpl::tokenize(const string& s) const
{
    vector<string> tokenized;
    int beg = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (find(m_separators.begin(), m_separators.end(), s[i]) == m_separators.end())
            continue;
        else if ( i - beg >= 0 && find(m_separators.begin(), m_separators.end(), s[i-1]) == m_separators.end())
        {
            tokenized.push_back(s.substr(beg, i - beg));
            beg = i+1;
        }
        else
            beg++;
    }
    if (beg < s.size())
        tokenized.push_back(s.substr(beg, s.size() - beg));
    return tokenized;
}

//******************** Tokenizer functions ************************************

// These functions simply delegate to TokenizerImpl's functions.
// You probably don't want to change any of this code.

Tokenizer::Tokenizer(string separators)
{
    m_impl = new TokenizerImpl(separators);
}

Tokenizer::~Tokenizer()
{
    delete m_impl;
}

vector<string> Tokenizer::tokenize(const string& s) const
{
    return m_impl->tokenize(s);
}
