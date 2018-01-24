#include "Map.h"

Map::Map() : m_size(0) {

}

bool Map::empty() const{
	// Checks if the KeyValuePair array is empty
	if (m_size == 0)
		return true;
	return false;
}

int Map::size() const{
	// returns the size of the KeyValuePair array
	return m_size;
}

bool Map::insert(const KeyType& key, const ValueType& value){
	// Checks if the function should insert
	if (contains(key) || m_size == DEFAULT_MAX_ITEMS)
		return false;
	
	// creates a new keyvaluepair and adds it to the array
	KeyValuePair pair;
	pair.m_key = key;
	pair.m_value = value;
	m_arr[m_size] = pair;
	m_size++;
	return true;
	

}

bool Map::update(const KeyType& key, const ValueType& value){
	// checks if the key exists in the array. if so, updates
	if (contains(key)){
		erase(key);
		insert(key, value);
		return true;
	}
	return false;

}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value){
	// if the key is in the array, updates. otherwise, if possible, 
	// inserts.
	if (contains(key))
		return update(key, value);
	return insert(key, value);
}

bool Map::erase(const KeyType& key){
	// checks if key is in array. If so, removes it
	if (! contains(key))
		return false;

	// finds index of key in array
	int index = 0;
	while (index < size() && m_arr[index].m_key != key)
		index++;

	// replaces key at index with last key in the array
	// Size is decremented, so if index is the last in the 
	// array, it is no longer accessed.
	m_arr[index] = m_arr[size() - 1];

	m_size--;
	return true;

}


bool Map::contains(const KeyType& key) const{
	// checks if the key is in the array
	for (int i = 0; i < size(); i++)
		if (m_arr[i].m_key == key)
			return true;
	return false;
}

bool Map::get(const KeyType& key, ValueType& value) const{
	// Checks if the key is in the array
	if (! contains(key))
		return false;

	// assigns value assoc with key to value variable
	int i = 0;
	while(m_arr[i].m_key != key)
		i++;

	value = m_arr[i].m_value;
	return true;
}


bool Map::get(int i, KeyType& key, ValueType& value) const{
	// checks if i is a valid index
	if (! (i >= 0 && i < size()))
		return false;

	// returns the values of the key value pair at index i
	key = m_arr[i].m_key;
	value = m_arr[i].m_value;
	return true;
}

void Map::swap(Map& other){
	int max_size = size();
	// finds the size of the larger array
	int other_size = other.size();
	if (other_size > max_size)
		max_size = other_size;
	
	// creates temp variables to store the other's key and value
	KeyType tempKey;
	ValueType tempValue;

	// switch each key and value
	for (int i = 0; i < max_size; i++){
		tempKey = other.m_arr[i].m_key;
		tempValue = other.m_arr[i].m_value;

		other.m_arr[i].m_key = m_arr[i].m_key;
		other.m_arr[i].m_value = m_arr[i].m_value;

		m_arr[i].m_key = tempKey;
		m_arr[i].m_value = tempValue;

	}

	// switch the size
	int tempSize = other.size();
	other.m_size = size();
	m_size = tempSize;
	
}
