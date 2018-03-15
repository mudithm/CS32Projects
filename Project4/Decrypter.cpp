#include "provided.h"
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>

using namespace std;

class DecrypterImpl
{
public:
	
    bool load(string filename);
    vector<string> crack(const string& ciphertext);
private:
	WordList m_wordList;
	Translator m_tl;
	string toPlowerCase(const string& s) const
    {
        string toLowerCase(const string& s);
        return toLowerCase(s);
    };
    vector<string> m_checked;
};

bool compareDecrypts(pair<string, string> p1, pair<string, string> p2);


bool DecrypterImpl::load(string filename)
{
	if ( ! m_wordList.loadWordList(filename))
		return false;
	
	return true;	
}

vector<string> DecrypterImpl::crack(const string& ciphertext)
{
	vector<string> answers;

	Tokenizer tk(",;:.!()[]{}- \"1234567890#$%^&");
	vector<string> list = tk.tokenize(ciphertext);
	vector<pair<string, string>> p;
	
	for (int i = 0; i < list.size(); i++)
	{
		pair<string, string> pa (list[i], m_tl.getTranslation(list[i]));
		p.push_back(pa);
	}

	sort(p.begin(), p.end(), compareDecrypts);

	string current;
	for (int i = 0; i < p.size(); i++)
	{
		if (find(m_checked.begin(), m_checked.end(), p[i].first) != m_checked.end())
			continue;
		else
		{
			current = p[i].first;
			break;
		}
	}

	m_checked.push_back(current);

	string tl = m_tl.getTranslation(current);
	vector<string> C = m_wordList.findCandidates(current, tl);


	if (C.size() == 0)
	{
			cout << "====reached the part where number of candidates is 0" << endl;

		m_tl.popMapping();
		return answers;
	}

	for (int i = 0; i < C.size(); i++)
	{
		if (!m_tl.pushMapping(current, C[i]))
			continue;
		cout << current << " " << C[i] << endl;
		vector<string> translatedVector;
		for (int k = 0; k < list.size(); k++)
		{
			translatedVector.push_back(m_tl.getTranslation(list[k]));
			cout << ">" << translatedVector[k] << endl;
		}

		int numberFullyTranslated = 0, numberInList = 0;
		for (int k = 0; k < translatedVector.size(); k++)
		{
			if (find(translatedVector[k].begin(), translatedVector[k].end(), '?') 
				== translatedVector[k].end())
			{
				numberFullyTranslated++;
				if (m_wordList.contains(translatedVector[k]))
					numberInList++;
			}
		}
		cout << "Number Fully Translated: " << numberFullyTranslated << " Number in List: " << numberInList << endl;

		if (numberFullyTranslated == 0)
		{
			m_tl.popMapping();
			cout << "====reached the part where numfully translated is 0" << endl;
			continue;
		}
		else if (numberFullyTranslated == numberInList)
		{
			if (numberFullyTranslated < translatedVector.size())
			{
				cout << "====reached the part where numberFullyTranslated < translatedVector size" << endl;

				vector<string> cracked = crack(ciphertext);
				answers.insert(answers.end(), cracked.begin(), cracked.end());
				m_tl.popMapping();
				continue;
			}
			else if (numberFullyTranslated == translatedVector.size())
			{
				cout << "====reached the part where numberFullyTranslated equals translatedVector size" << endl;

				string translatedString = m_tl.getTranslation(ciphertext);
				cout << translatedString << endl;
				answers.push_back(translatedString);
				m_tl.popMapping();

				continue;
			}
		}
		else
		{
			cout << "====reached the part where not all translated in list" << endl;

			m_tl.popMapping();
			continue;
		}

	}

	cout << "====reached the part where the function returns" << endl;
	m_tl.popMapping();
	return answers;
}




bool compareDecrypts(pair<string, string> p1, pair<string, string> p2)
{
	string s1 = p1.second;
	string s2 = p2.second;
	int first = count(s1.begin(), s1.end(), '?');
	int second = count(s2.begin(), s2.end(), '?');

	return (first > second);
}

//******************** Decrypter functions ************************************

// These functions simply delegate to DecrypterImpl's functions.
// You probably don't want to change any of this code.

Decrypter::Decrypter()
{
    m_impl = new DecrypterImpl;
}

Decrypter::~Decrypter()
{
    delete m_impl;
}

bool Decrypter::load(string filename)
{
    return m_impl->load(filename);
}

vector<string> Decrypter::crack(const string& ciphertext)
{
   return m_impl->crack(ciphertext);
}
