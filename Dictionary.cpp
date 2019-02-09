// Dictionary.cpp

#include "Dictionary.h"
#include <string>
#include <list>
#include <cctype>
#include <utility>  // for swap
#include <functional>
using namespace std;

void removeNonLetters(string& s);

  // This class does the real work of the implementation.

class DictionaryImpl
{
  public:
    DictionaryImpl() {}
    ~DictionaryImpl() {}
    void insert(string word);
	unsigned int myHashFunction(const string &hashMe);
	int getValue(string letters);
    void lookup(string letters, void callback(string));
  private:
	list<string> mylist[49999]; 
};

void DictionaryImpl::insert(string word)
{
    removeNonLetters(word);
	if (!word.empty())
	{
		int whichBucket = myHashFunction(word);
		mylist[whichBucket].push_front(word);
		
	}
}

//hash for placing words into buckets
unsigned int DictionaryImpl::myHashFunction(const string & hashMe)
{
	unsigned int hashValue = 0;
	int addend = 0;
	for (int i = 0; i < hashMe.length(); i++)
	{
		switch (hashMe[i])
		{
		case 'a':
			addend = 767;
			break;
		case 'b':
			addend = 3071;
			break;
		case 'c':
			addend = 786431;
			break;
		case 'd':
			addend = 6291455;
			break;
		case 'e':
			addend = 12287;
			break;
		case 'f':
			addend = 95;
			break;
		case 'g':
			addend = 191;
			break;
		case 'h':
			addend = 386;
			break;
		case 'i':
			addend = 1535;
			break;
		case 'j':
			addend = 5;
			break;
		case 'k':
			addend = 201326591;
			break;
		case 'l':
			addend = 6143;
			break;
		case 'm':
			addend = 50331647;
			break;
		case 'n':
			addend = 100663295;
			break;
		case 'o':
			addend = 25165823;
			break;
		case 'p':
			addend = 12582911;
			break;
		case 'q':
			addend = 23;
			break;
		case 'r':
			addend = 3145727;
			break;
		case 's':
			addend = 1572863;
			break;
		case 't':
			addend = 232;
			break;
		case 'u':
			addend = 393215;
			break;
		case 'v':
			addend = 11;
			break;
		case 'w':
			addend = 196607;
			break;
		case 'x':
			addend = 98303;
			break;
		case 'y':
			addend = 49151;
			break;
		case 'z':
			addend = 24575;
			break;
		default:
			addend = 0;
			break;
		}
		hashValue += (addend);
	}
	unsigned int bucketNum = (hashValue) % 49999;
	return bucketNum;
}

//hash for retrieving words since multiple sets of acronyms 
int DictionaryImpl::getValue(string letters)
{
	int total = 0;
	int addend = 0;
	for (int i = 0; i < letters.length(); i++)
	{
		switch (letters[i])
		{
		case 'a':
			addend = 6145;
			break;
		case 'b':
			addend = 3073;
			break;
		case 'c':
			addend = 97;
			break;
		case 'd':
			addend = 12289;
			break;
		case 'e':
			addend = 786433;
			break;
		case 'f':
			addend = 769;
			break;
		case 'g':
			addend = 6;
			break;
		case 'h':
			addend = 388;
			break;
		case 'i':
			addend = 193;
			break;
		case 'j':
			addend = 201326593;
			break;
		case 'k':
			addend = 1537;
			break;
		case 'l':
			addend = 6291457;
			break;
		case 'm':
			addend = 50331649;
			break;
		case 'n':
			addend = 12582913;
			break;
		case 'o':
			addend = 98305;
			break;
		case 'p':
			addend =  393219;
			break;
		case 'q':
			addend = 25;
			break;
		case 'r':
			addend = 3145728;
			break;
		case 's':
			addend = 1572866;
			break;
		case 't':
			addend = 234;
			break;
		case 'u':
			addend = 100663297;
			break;
		case 'v':
			addend = 11;
			break;
		case 'w':
			addend = 24577;
			break;
		case 'x':
			addend =  196609;
			break;
		case 'y':
			addend = 49153;
			break;
		case 'z':
			addend = 25165825;
			break;
		}
		total += addend;
	}
	return total;
}

void DictionaryImpl::lookup(string letters, void callback(string))
{
	if (callback == nullptr)
		return;

	removeNonLetters(letters);
	if (letters.empty())
		return;

	int bucketToGo = myHashFunction(letters);
	int valueNeeded = getValue(letters);
	for (list<string>::iterator it = mylist[bucketToGo].begin(); it != mylist[bucketToGo].end(); ++it)
	{
		if (getValue(*it) == valueNeeded)
		{
			callback(*it);
		}
	}
}
    
void removeNonLetters(string& s)
{
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop everything off from "to" to end.
} 



//******************** Dictionary functions ********************************

// These functions simply delegate to DictionaryImpl's functions.
// You probably don't want to change any of this code

Dictionary::Dictionary()
{
    m_impl = new DictionaryImpl;
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters,callback);
}
