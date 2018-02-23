// Map.cpp

#include "Map.h"

Map::Map()
 : m_size(0)
{
    m_head = nullptr;
}

// Copy Constructor
Map::Map(const Map& mp) : m_size(mp.size())
{
    if (m_size <= 0){
        m_head = nullptr;
        return;
    }
    
    m_head = new Pair;
    Pair* curr = m_head;
    Pair* previous = nullptr;
    
    // iterates through the argument map and copies values
    for (Pair* temp = mp.m_head; temp != nullptr; temp = temp->next){
        curr->next = nullptr;
        curr->prev = previous;
        curr->m_key = temp->m_key;
        curr->m_value = temp->m_value;
        if (temp->next != nullptr)
            curr->next = new Pair;
        previous = curr;
        curr = curr->next;
    }
    
}

// Assignment operator
Map& Map::operator=(const Map& mp){
    // Alias check
    if (&mp != this){
        // uses copy constructor
        Map temp = mp;
        swap(temp);
    }
    return *this;
}

// Destructor
Map::~Map(){
    
    Pair* nextItem = m_head;
    Pair* temp;
    // deletes each item in the list
    for (int i = 0; i < m_size; i++){
        temp = nextItem;
        nextItem = nextItem->next;
        delete temp;
    }
        
}

// erases a key from the map
bool Map::erase(const KeyType& key)
{
    // if m_head points to a pair with the right key
    if (m_head != nullptr && m_head->m_key == key){
        Pair* temp = m_head;
        m_head = m_head->next;
        if (m_head != nullptr)
            m_head->prev = nullptr;
        delete temp;
        m_size--;
        return true;
    }
    // else, iterate through to check if the map contains the key
    for (Pair* temp = m_head; temp != nullptr; temp = temp->next){
        if (temp->m_key == key){
            Pair* previous = temp->prev;
            Pair* proximo = temp->next;
            // if previous/next are legit pairs, change their pointers
            if (previous != nullptr)
                previous->next = proximo;
            if (proximo != nullptr)
                proximo->prev = previous;
            delete temp;
            m_size--;
            return true;
        }
    }
    return false;
}

// gets a value from the map
bool Map::get(const KeyType& key, ValueType& value) const
{
    // Iterate through array and check for key
    for (Pair* temp = m_head; temp != nullptr; temp = temp->next)
        if (temp->m_key == key){
            value = temp->m_value;
            return true;
        }
    return false;
}

// gets a key value pair from the map
bool Map::get(int i, KeyType& key, ValueType& value) const
{
    // if i is out of bounds, return false
    if (i < 0  ||  i >= m_size)
        return false;
    Pair* temp = m_head;
    
    // iterate through the list and assign arguments to 
    // an element of map
    for (int b = 0; b < i; b++, temp = temp->next)
        ;

    key = temp->m_key;
    value = temp->m_value;

    return true;
}

// swaps the contents of two maps
void Map::swap(Map& other)
{
      // Swap elements.  All we have to do is switch size and head
    Pair* temp = other.m_head;
    other.m_head = m_head;
    m_head = temp;

    int t = m_size;
    m_size = other.m_size;
    other.m_size = t;
}

// finds the position of a key in the map
int Map::find(const KeyType& key) const
{
      // Do a linear search through the array.
    Pair* temp = m_head;
    for (int i = 0; temp != nullptr; temp = temp->next, i++)
        if (temp->m_key == key)
            return i;
    return -1;
}

// inserts or updates values in the map
bool Map::doInsertOrUpdate(const KeyType& key, const ValueType& value,
                           bool mayInsert, bool mayUpdate)
{
    // if head is uninitialized and you can insert
    if (m_head == nullptr && mayInsert){
        m_head = new Pair;
        m_head->prev = nullptr;
        m_head->m_key = key;
        m_head->m_value = value;
        m_head->next = nullptr;
        m_size++;
        return true;
    }
    int pos = find(key);
    if (pos != -1)  // found
    {
        if (mayUpdate){
            Pair* temp = m_head;
            for (int i = 0; i < pos; i++, temp = temp->next)
                ;
            temp->m_key = key;
            temp->m_value = value;
        }
        return mayUpdate;
    }
    if (!mayInsert)  // not found, and not allowed to insert
        return false;
    
    Pair* temp;
    for (temp = m_head; temp->next != nullptr; temp = temp->next)
        ;
    temp->next = new Pair;
    temp->next->prev = temp;
    temp->next->m_key = key;
    temp->next->m_value = value;
    temp->next->next = nullptr;
    m_size++;
    return true;
    

}

// prints values in map to console
void Map::dump() const{
    std::cerr << "----------------" << std::endl;
    for (Pair* temp = m_head; temp != nullptr; temp = temp->next){
        std::cerr << "Key: " << temp->m_key << " Value: " << temp->m_value <<   std::endl;
    }
     std::cerr << "----------------" <<  std::endl;
}

//combines the contents of two maps
bool combine(const Map& m1, const Map& m2, Map& result){
    // Checks if the arguments refer to the same object
    if (&m1 == &m2){
        result = m1;
        return true;
    }
    
    bool output = true;

    // creates an empty array to store values
    Map temp;

    int m1Size = m1.size();
    int m2Size = m2.size();
    
    KeyType key;
    ValueType val1, val2;

    // checks values in first list against second
    for (int i = 0; i < m1Size; i++){
        m1.get(i, key, val1);
        if (m2.get(key, val2)){
            if(val1 == val2)
                temp.insert(key, val1);
            else
                output = false;
        }else
            temp.insert(key, val1);
    }
    
    // checks values in second list against first
    for (int i = 0; i < m2Size; i++){
        m2.get(i, key, val2);
        if (m1.get(key, val1)){
            if(val1 == val2)
                temp.insert(key, val1);
            else
                output = false;
        }else
            temp.insert(key, val2);
    }
    
    // assigns the value of temp to the result map
    result = temp;

    return output;
}

// subtracts the contents of map 2 from map 1
void subtract(const Map& m1, const Map& m2, Map& result){
    // Checks if the arguments refer to the same object
    if (&m1 == &m2){
        Map m;
        result = m;
        return;
    }
    
    // Makes an empty temp map to store values;
    Map temp;
    
    int size = m1.size();
    KeyType key;
    ValueType val;

    // checks which elements of array 1 are also in array 2
    for (int i = 0; i < size; i++){
        m1.get(i, key, val);
        if (! m2.contains(key)){
            temp.insert(key, val);
        }

    }
    
    // assigns the value of temp to the result map
    result = temp;

} 
