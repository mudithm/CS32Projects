// Map.cpp

#include "Map.h"

bool combine(const Map& m1, const Map& m2, Map& result)
{
	int counter = 0;
	bool returnVar = true;
	bool temp;
	Map aMap;
	int size1 = m1.size();
	int size2 = m2.size();
	KeyType key1;
	ValueType val1;
	KeyType key2;
	ValueType val2;
	bool equal = &m1 == &m2;
	if (equal)
	{
		result = m1;
		return returnVar;
	}
	while (counter < size1)
	{
		temp = m1.get(counter, key1, val1);
		temp = m2.contains(key1);
		if (temp)
		{
			bool temp2 = m2.get(key1, val2);
			if (val1 == val2)
			{
				temp2 = aMap.insert(key1, val1);
			}
			else 
			{
				returnVar = false;
			}
		}
		else
		{
			aMap.insert(key1, val1);
		}
		counter++;
	}
	counter = 0;
	while (counter < size2)
	{
		temp = m2.get(counter, key2, val2);
		temp = m1.contains(key2);
		if (temp)
		{
		}
		else
		{
			aMap.insert(key2, val2);
		}
		counter++;
	}
	counter = 0;
	result = aMap;
	return returnVar;
}
void subtract(const Map& m1, const Map& m2, Map& result)
{
	int counter;
	Map aMap;
	bool temp;
	int size2 = m2.size();

	KeyType key2;
	ValueType val2;
	bool equal = (&m1 == &m2);
	if (equal)
	{
		Map thisMap;
		result = thisMap;
	}
	else
	{
		aMap = m1;
		//add every item in m1 to result

		//if item that exists in result/m1 also exists in m2, we must delete the corresponding item from the result map
		counter = 0;
		while (counter < size2)
		{
			temp = m2.get(counter, key2, val2);
			temp = aMap.contains(key2);
			if (temp)
			{
				aMap.erase(key2);
			}
			counter++;
		}
		counter = 0;
		result = aMap;
	}
}
// Doubly Linked List methods
Map::DLinkedList::DLinkedList() // constructor
{
	m_head = nullptr;
	m_tail = nullptr;
}
Map::DLinkedList::~DLinkedList() // destructor
{
	if (m_head == nullptr && m_tail == nullptr)
	{
	}
	else if (m_head->m_nxt == nullptr)
	{
		delete m_head;
	}
	else
	{
		Node* p = m_head;
		while (p != nullptr)
		{
			Node* n = p->m_nxt;
			delete p;
			p = n;
		}
	}
}
bool Map::DLinkedList::addFront(const KeyType& key, const ValueType& val)
{
	if (m_head == nullptr && m_tail == nullptr)
	{
		Node* n = new Node;
		n->m_key = key;
		n->m_value = val;
		n->m_nxt = nullptr;
		n->m_prv = nullptr;
		m_head = n;
		m_tail = n;
		return true;
	}
	else if (m_head->m_nxt == nullptr)
	{
		Node* n = new Node;
		n->m_key = key;
		n->m_value = val;
		n->m_prv = nullptr;
		n->m_nxt = m_head;
		n->m_nxt->m_prv = n;
		m_head = n;
		return true;
	}
	else
	{
		Node* n = new Node;
		n->m_key = key;
		n->m_value = val;
		n->m_prv = nullptr;
		n->m_nxt = m_head;
		n->m_nxt->m_prv = n;
		m_head = n; 
		return true;
	}
	return false;
}
bool Map::DLinkedList::addEnd(const KeyType& key, const ValueType& val)
{
	if (m_head == nullptr && m_tail == nullptr)
	{
		return addFront(key, val);
	}
	else if (m_head->m_nxt == nullptr)
	{
		Node* n = new Node;
		n->m_key = key;
		n->m_value = val;
		n->m_nxt = nullptr;
		m_tail = n;
		m_head->m_nxt = n;
		n->m_prv = m_head;
		return true;
	}
	else
	{
		Node* n = new Node;
		n->m_key = key;
		n->m_value = val;
		n->m_nxt = nullptr;
		n->m_prv = m_tail;
		n->m_prv->m_nxt = n;
		m_tail = n;
		return true;
	}
	return false;
}

bool Map::DLinkedList::deleteNode(int location)
{
	if (m_head == nullptr && m_tail == nullptr)
	{
		return false;
	}
	else if (m_head->m_nxt == nullptr)
	{
		if (location == 0)
		{
			Node* n1 = m_head;
			m_head = nullptr;
			m_tail = nullptr;
			delete n1;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (location == 0)
		{
			Node* temp = m_head;
			m_head->m_nxt->m_prv = nullptr;
			m_head = m_head->m_nxt;
			delete temp;
			return true;
		}
		Node* p = m_head;
		int i = 0;
		//p will point to the node before the one we will be deleting
		while (p != nullptr)
		{
			if (p->m_nxt == nullptr || i != location - 1)
			{
				p = p->m_nxt;
				i++;
			}
			else
			{
				break;
			}
		}

		if (p->m_nxt->m_nxt == nullptr)
		{
			Node* temp = p->m_nxt;
			p->m_nxt = nullptr;
			m_tail = p;
			delete temp;
			return true;
		}
		else
		{
			Node* temp = p->m_nxt;
			temp->m_nxt->m_prv = p;
			p->m_nxt = temp->m_nxt;
			delete temp;
			return true;
		}
		
	}
	return false;
}
KeyType Map::DLinkedList::getKeyAt(int location) const
{
	Node* p = m_head;
	int counter = 0;
	while (counter < location && p->m_nxt != nullptr)
	{
		p = p->m_nxt;
		counter++;
	}
	return p->m_key;
}

ValueType Map::DLinkedList::getValAt(int location) const
{
	Node* p = m_head;
	int counter = 0;
	while (counter < location && p->m_nxt != nullptr)
	{
		p = p->m_nxt;
		counter++;
	}
	return p->m_value;
}
ValueType Map::DLinkedList::getValAt(const KeyType& key) const
{
	int location = findNode(key);
	if (location >= 0)
	{
		return getValAt(location);
	}
}
bool Map::DLinkedList::setKey(int location, const KeyType& key)
{
	if (location < 0)
	{
		return false;
	}
	else
	{ 
		Node* p = m_head;
		int counter = 0;
		while (counter < location && p->m_nxt != nullptr)
		{
			p = p->m_nxt;
			counter++;
		}
		p->m_key = key;
		return true;
	}
	
}
bool Map::DLinkedList::setVal(int location, const ValueType& val)
{
	if (location < 0)
	{
		return false;
	}
	else
	{
		Node* p = m_head;
		int counter = 0;
		while (counter < location && p->m_nxt != nullptr)
		{
			p = p->m_nxt;
			counter++;
		}
		p->m_value = val;
		return true;
	}
}
int Map::DLinkedList::findNode(const KeyType& key) const
{
	int i = 0;
	Node* p = m_head;

	while (p != nullptr)
	{
		if (p->m_key != key)
		{
			p = p->m_nxt;
		}
		else
		{
			return i;
		}
		i++;
	}
	return -1;

}

void Map::DLinkedList::getHead(Node*& n) const
{
	n = m_head;
}
void Map::DLinkedList::getTail(Node*& n) const
{
	n = m_tail;
}

void Map::DLinkedList::setHead(Node* n)
{
	m_head = n;
}
void Map::DLinkedList::setTail(Node* n)
{
	m_tail = n;
}
Map::Map()
{
	m_size = 0;
}
Map::~Map()             // Destructor
{
	//automatically calls the DLinkedList destructor
}
Map::Map(const Map& m)   // Copy Constructor
{
	m_size = 0;
	int copySize = m.m_size;
	KeyType key;
	ValueType val;
	bool holder;
	int counter = 0;
	while (counter < copySize)
	{
		holder = m.get(counter, key, val);
		holder = insert(key, val);
		counter++;
	}
	counter = 0;
}
Map& Map::operator=(const Map& m) // Assignment Operator
{
	if (this != &m)
	{
		Map temp(m);
		swap(temp);
	}
	return *this;
}
bool Map::erase(const KeyType& key)
{
	int location = m_data.findNode(key);
	if (location == -1)
	{
		return false;
	}
	else
	{
		bool test = false;
		test = m_data.deleteNode(location);
		if (test)
		{
			m_size--;
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool Map::get(const KeyType& key, ValueType& value) const
{
	int pos = m_data.findNode(key);
	if (pos == -1)  // not found
		return false;
	value = m_data.getValAt(pos);
	return true;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
	if (i < 0 || i >= m_size)
		return false;
	key = m_data.getKeyAt(i);
	value = m_data.getValAt(i);
	return true;
}

void Map::swap(Map& other)//***********************
{
	//switch map sizes
	int tempSize = m_size;
	m_size = other.m_size;
	other.m_size = tempSize;

	//switch heads
	Node* thisHead;
	Node* otherHead;
	other.m_data.getHead(otherHead);
	m_data.getHead(thisHead);
	other.m_data.setHead(thisHead);
	m_data.setHead(otherHead);
	

	//switch tails
	Node* thisTail;
	Node* otherTail;
	other.m_data.getTail(otherTail);
	m_data.getTail(thisTail);
	other.m_data.setTail(thisTail);
	m_data.setTail(otherTail);
	
}

int Map::find(const KeyType& key) const
{
	int location = m_data.findNode(key);
	return location;
}
int Map::size() const
{
	return m_size;
}
bool Map::empty() const
{
	return size() == 0;
}
bool Map::contains(const KeyType& key) const
{
	int location = m_data.findNode(key);
	if (location >= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Map::insert(const KeyType& key, const ValueType& value)
{
	int location = m_data.findNode(key);
	if (location == -1)
	{
		m_size++;
		return m_data.addFront(key, value);
	}
	else
	{
		return false;
	}
}
bool Map::update(const KeyType& key, const ValueType& value)
{
	int location = m_data.findNode(key);
	if (location == -1)
	{
		return false;
	}
	else if (location >= 0)
	{
		return m_data.setVal(location, value);
	}
	else
	{
		return false;
	}
}
bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
	int location = m_data.findNode(key);
	if (location >= 0)
	{
		m_data.setVal(location, value);
		return true;
	}
	else if (location == -1)
	{
		m_size++;
		return m_data.addFront(key, value);
	}
	else
	{
		return false;
	}
}
// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// If key is not equal to any key currently in the map, and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that the key is not already in the map and the map has a fixed
// capacity and is full).
