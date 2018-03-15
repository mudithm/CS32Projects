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

//bool compareDecrypts(pair<string, string> p1, pair<string, string> p2);


bool DecrypterImpl::load(string filename)
{
	if ( ! m_wordList.loadWordList(filename))
		return false;
	
	return true;	
}

vector<string> DecrypterImpl::crack(const string& ciphertext)
{
	cout << "========================\nBeginning of a new iteration\n========================" << endl;
	vector<string> answers;

	Tokenizer tk(",;:.!()[]{}-\"#$%^&0123456789 ");
	vector<string> cipherWords = tk.tokenize(ciphertext);

	cout << "CipherWords, tokenized: " << endl;
	for (int i = 0; i < cipherWords.size(); i++)
		cout << cipherWords[i] << " | ";
	cout << endl;

	string largest = "";
	int numInLargest = 0, ct = 0;

	cout << "Translations of these words: " << endl;
	for (int i = 0; i < cipherWords.size(); i++)
	{
		string tl = m_tl.getTranslation(cipherWords[i]);
		cout << tl << " | " ;
		ct = count(tl.begin(), tl.end(), '?');
		if (ct > numInLargest && find(m_checked.begin(), m_checked.end(), cipherWords[i]) == m_checked.end())
		{
			largest = cipherWords[i];
			numInLargest = ct;
		}
	}
	cout << endl;
	cout << "Largest untranslated: " << largest << endl;

	cout << "===Adding " << largest << " to the check list" << endl;
	m_checked.push_back(largest);

	string partialTranslation = m_tl.getTranslation(largest);
	cout << "Partial Translation of " << largest << ": " << partialTranslation << endl;

	vector<string> candidates = m_wordList.findCandidates(largest, partialTranslation);

	cout << "Candidates for " << largest << " with translation " << partialTranslation << ": ";
	for (int i = 0; i < candidates.size(); i++)
		cout << candidates[i] << " ";
	cout << endl;

	if (candidates.empty())
	{
		cout << "^^^Returning and popping map. No candidates for this translation." << endl;
		m_tl.popMapping();
		return answers;
	}

	cout << "Beginning to check each candidate: " << endl;
	for (int i = 0; i < candidates.size(); i++)
	{
		cout << "Creating a temporary mapping with the candidate and cipherword..." << endl;

		if ( ! m_tl.pushMapping(largest, candidates[i]))
		{
			cout << "Mapping failed." << endl;
			continue;
		}

		cout << "Finding resulting plaintext message: " << endl;
		cout << ">>> ";

		cout << m_tl.getTranslation(ciphertext) << endl;

		vector<string> translatedCipherWords;
		for (int j = 0; j < cipherWords.size(); j++)
			translatedCipherWords.push_back(m_tl.getTranslation(cipherWords[j]));

		cout << "translatedCipherWords: ";
		for (int p = 0; p < translatedCipherWords.size(); p++)
			cout << translatedCipherWords[p] << " | " ;
		cout << endl;

		int numFullyTranslated = 0, numInList = 0;
		for (int k = 0; k < translatedCipherWords.size(); k++)
		{
			if (find(translatedCipherWords[k].begin(), translatedCipherWords[k].end(), '?') 
				== translatedCipherWords[k].end())
			{
				numFullyTranslated++;
				if (m_wordList.contains(translatedCipherWords[k]))
					numInList++;

			}


			cout << "	Word: " << translatedCipherWords[k] << " Status: " 
			<< m_wordList.contains(translatedCipherWords[k]) << endl;

		}
		cout << "Number of words fully translated: " << numFullyTranslated << endl;
		cout << "Number of translated words in list: " << numInList << endl;

		if (numFullyTranslated > numInList)
		{
			cout << ">>>>>Not all translated words found in list. Continuing..." << endl;
			m_tl.popMapping();
		}
		else if (numFullyTranslated == numInList)
		{
			if (numFullyTranslated < translatedCipherWords.size())
			{
				cout << "Not all words were translated, but all that were were in the list" << endl;
				cout << "vvvvvvvvvvvvvvvvGoing deeper...vvvvvvvvvvvvvvvvv" << endl;
				m_checked.pop_back();
				vector<string> deeper = crack(ciphertext);
				answers.insert(answers.end(), deeper.begin(), deeper.end());
			}else if (numFullyTranslated == translatedCipherWords.size())
			{
				cout << "Found a valid solution." << endl;
				string sol = m_tl.getTranslation(ciphertext);
				cout << ">>>>>>>>> " << sol << endl;
				answers.push_back(sol);
				m_tl.popMapping();
			}
		}




	}



	cout << "Reached the end of an iteration" << endl;
	cout << "===============================" << endl;
	m_tl.popMapping();
	return answers;
}


/*
bool compareDecrypts(pair<string, string> p1, pair<string, string> p2)
{
	string s1 = p1.second;
	string s2 = p2.second;
	int first = count(s1.begin(), s1.end(), '?');
	int second = count(s2.begin(), s2.end(), '?');

	return (first > second);
}
*/

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
