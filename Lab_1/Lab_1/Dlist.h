
#pragma once


template <typename T>
class DList
{
public:

	// Node Structure
	struct Node
	{
		T data;
		Node *prev, *next;

		Node(T d, Node *p = nullptr, Node *n = nullptr)
		{
			data = d;
			prev = p;
			next = n;
		}
	};

	// Default Ctor
	DList();

	// Dtor
	~DList();

	// Methods
	void push_back(const T& info);
	void pop_back();
	bool empty() const;
	unsigned int size() const;
	T& operator[](int index);
	const T& operator[](int index) const;

	// 3 Methods from Lab Doc.
	void push_front(const T& info);
	void erase(int index);
	void clear();


private:

	// Data Members
	Node *first, *last;
	unsigned int m_size;
};

template <typename T>
DList<T>::DList()
{
	first = nullptr;
	last = nullptr;
	m_size = 0;
}

template <typename T>
DList<T>::~DList()
{
	clear();
}

template <typename T>
void DList<T>::push_back(const T& info)
{
	Node *newNode = new Node(info, last);

	if (first == nullptr)
	{
		first = newNode;
	}
	else
	{
		last->next = newNode;
	}

	last = newNode;
	m_size++;
}

template <typename T>
void DList<T>::pop_back()
{
	if (empty())
		return;

	Node *delNode = last;

	if (last == first)
	{
		first = last = nullptr;
	}
	else
	{
		last = last->prev;
		last->next = nullptr;
	}

	delete delNode;

	m_size--;
}

template <typename T>
bool DList<T>::empty() const
{
	return m_size == 0;
}

template <typename T>
unsigned int DList<T>::size() const
{
	return m_size;
}

template <typename T>
T& DList<T>::operator[](int index)
{
	Node *travNode = first;

	for (int i = 0; i < index; i++) travNode = travNode->next;

	return travNode->data;
}

template <typename T>
const T& DList<T>::operator[](int index) const
{
	Node *travNode = first;

	for (int i = 0; i < index; i++) travNode = travNode->next;

	return travNode->data;
}

// 3 Methods from Lab Doc*******************************************************************************************

// Like push_back() except the new node will be the first in the list
template <typename T>
void DList<T>::push_front(const T& info)
{
	Node *newNode = new Node(info, nullptr, first);

	if (last == nullptr)
	{
		last = newNode;
	}
	else
	{
		first->prev = newNode;
	}

	first = newNode;
	m_size++;
}

// Accept an index (like the [] operators) and if it's invalid return false. 
// Otherwise, eliminates the node at that position in the list and return true
template <typename T>
void DList<T>::erase(int index)
{
	if (index < 0)
	{
		return;
	}
	else
	{
		Node *temp = first;

		for (int i = 0; i < index; i++)
		{
			temp = temp->next;
		}

		if (m_size == 1)
		{
			clear();
		}
		else if (temp == first)
		{
			temp->next->prev = nullptr;
			first->next = first;
			delete temp;
			m_size--;
		}
		else if (temp == last)
		{
			temp->prev->next = nullptr;
			last = last->prev;
			delete temp;
			m_size--;
		}
		else
		{
			temp->next->prev = temp->prev;
			temp->prev->next = temp->next;
			delete temp;
			m_size--;
		}
	}
}

// Clear: Remove all the nodes and make the list empty
template <typename T>
void DList<T>::clear()
{
	while (m_size > 0)
	{
		Node* delNode = first;

		first = first->next;

		delete delNode;

		m_size--;
	}
	last = nullptr;
}