// MyHash.h

// Skeleton for the MyHash class template.  You must implement the first seven
// member functions; we have implemented the eighth.
#ifndef MYHASH_INCLUDED
#define MYHASH_INCLUDED

#include <iostream>
#include <cassert>
using namespace std;

template<typename KeyType, typename ValueType>
class MyHash
{
public:
    MyHash(double maxLoadFactor = 0.5);
    ~MyHash();
    void reset();
    void associate(const KeyType& key, const ValueType& value);
    int getNumItems() const;
    double getLoadFactor() const;

      // for a map that can't be modified, return a pointer to const ValueType
    const ValueType* find(const KeyType& key) const;

      // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyHash*>(this)->find(key));
    }

      // C++11 syntax for preventing copying and assignment
    MyHash(const MyHash&) = delete;
    MyHash& operator=(const MyHash&) = delete;

private:
    
    struct Node
    {
        Node() : next(nullptr) {}
        KeyType key;
        ValueType value;
        Node* next;
    };
    
    struct Bucket
    {
        Bucket() : head(nullptr) {}
        int addPair(const KeyType& key, const ValueType& value)
        {
            Node* iter = head;
            for (; iter != nullptr; iter = iter->next)
            {
                if (iter->key == key)
                {
                    if (iter->value != value)
                        iter->value = value;
                    return 0;
                }
            }
            
            Node* temp = new Node;
            temp->key = key;
            temp->value = value;
            temp->next = head;
            head = temp;
            
            return 1;
        }        
        Node* head;
    };
    
    unsigned int getBucketNumber(const KeyType& key, int size) const
    {
        unsigned int hash(const KeyType& key);
        return (hash(key) % size);
    }

    void emptyTable();

    double m_loadFactor;
    Bucket* m_hashtable;
    int m_tableSize;
    int m_numItems;
};


template<typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::MyHash(double maxLoadFactor) : m_tableSize(100), m_numItems(0)
{
    if (maxLoadFactor <= 0)
        m_loadFactor = 0.5;
    else if (maxLoadFactor > 2)
        m_loadFactor = 2.0;
    else
        m_loadFactor = maxLoadFactor;
    m_hashtable = new Bucket[100];
}

template<typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::~MyHash()
{
    emptyTable();
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::reset()
{
    emptyTable();
    m_hashtable = new Bucket[100];
    m_tableSize = 100;
    m_numItems = 0;
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::associate(const KeyType& key, const ValueType& value)
{
    // If key is not in the map and adding a new pair will make the load factor too big 
    if (find(key) == nullptr && (((double)m_numItems + 1.0) / (double)m_tableSize) > m_loadFactor)
    {
        // create a new bucket array with the new size
        Bucket* temp = new Bucket[m_tableSize * 2]();
        
        // iterate through the old array and move its values to the new one
        for (int i = 0; i < m_tableSize; i++)
            for (Node* iter = m_hashtable[i].head; iter != nullptr; iter = iter->next)
            {
                unsigned int num = getBucketNumber(iter->key, m_tableSize * 2);
                temp[num].addPair(iter->key, iter->value);
            }
        // delete the items in the old array and set it to the new array
        emptyTable();
        m_hashtable = temp;

        m_tableSize *= 2;
    }
    
    unsigned int bucketNumber = getBucketNumber(key, m_tableSize);
    
    
    m_numItems += m_hashtable[bucketNumber].addPair(key, value);
}

template<typename KeyType, typename ValueType>
const ValueType* MyHash<KeyType, ValueType>::find(const KeyType& key) const
{
    for (int i = 0; i < m_tableSize; i++)
    {
        for (Node* iter = m_hashtable[i].head; iter != nullptr; iter = iter->next)
        {
            if (iter->key == key)
                return &(iter->value);
        } 
    }
    return nullptr;
}

template<typename KeyType, typename ValueType>
int MyHash<KeyType, ValueType>::getNumItems() const
{
    return m_numItems;
}

template<typename KeyType, typename ValueType>
double MyHash<KeyType, ValueType>::getLoadFactor() const
{
    return ((double)m_numItems / (double)m_tableSize);
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::emptyTable()
{
    for (int i = 0; i < m_tableSize; i++)
    { 
        for (Node* iter = m_hashtable[i].head; iter != nullptr;)
        {
            Node* temp = iter;
            iter = iter->next;
            delete temp;
        }
    }
    delete[] m_hashtable;
}

#endif


