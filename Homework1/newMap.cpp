#include "newMap.h"


Map::Map(int maxPairs){
	if (maxPairs < 0){
		std::cout << "Cannot initialize a map with a negative max size" << std::endl;
		std::exit(0);
	}
	m_size = 0;
	m_max_size = maxPairs;
	m_arr = new KeyValuePair[maxPairs];
}

Map::Map(const Map& mp){
	m_max_size = mp.m_max_size;
	m_size = mp.m_size;

	m_arr = new KeyValuePair[m_max_size];

	for (int i = 0; i < m_size; i++){
		m_arr[i] = mp.m_arr[i];
	}

}

Map& Map::operator=(const Map& mp){

	if (this != &mp){
		Map temp(mp);
		swap(temp);
	}

	return *this;
}

Map::~Map(){
	delete [] m_arr;
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
	if (contains(key) || m_size == m_max_size)
		return false;
	
	// adds new key value pair to the array
	m_arr[m_size].m_key = key;
	m_arr[m_size].m_value = value;
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
	
	// switch the sizes
	int tempSize = other.size();
	other.m_size = size();
	m_size = tempSize;

	// switch the max sizes
	int tempMax = other.m_max_size;
	other.m_max_size = m_max_size;
	m_max_size = tempMax;

	// switch the arrays
	KeyValuePair* tempArr = other.m_arr;
	other.m_arr = m_arr;
	m_arr = tempArr;

}
