#include "Set.h"
#include <iostream>
Set::Set()
	:m_head(nullptr), m_size(0) //empty set definition
{}

Set::~Set()
{
	Node* current = m_head; //start from head
	while (current != nullptr) //as long as current pointer is pointing to an object continue
	{
		Node* next = current->m_next; //save next object pointer
		delete current; //delete current item
		current = next; //iterate to saved next item.
	}
}

Set::Set(const Set& other)
	:m_head(nullptr),m_size(0) // initialize as empty set
{
	if (other.m_head != nullptr) // if other is not empty set
	{
		Node* other_current = other.m_head; 
		m_head = new Node; // Create first node with value copied.
		m_head->m_prev = nullptr; //copy first node to head
		m_head->m_value = other_current->m_value;
		other_current = other_current->m_next; //iterate to second node to copy

		if (other_current == nullptr) 
			m_head->m_next = nullptr; // If there is no second node return
		else
		{
			Node* current = m_head; // create a poiner to iterate through current.
			while (other_current != nullptr) // continue until we copied the last node at the other
			{
				current->m_next = new Node; // add next element to list.
				current->m_next->m_prev = current; // make next element's prev to point current element
				current = current->m_next; //iterate to new added node

				current->m_value = other_current->m_value; //set new added node's value

				other_current = other_current->m_next; //iterate to next object to copy
			}
			current->m_next = nullptr; // set last nodes next to nullptr
		}
		//deep copy done
		m_size = other.m_size; // set size
	}
}

Set& Set::operator=(const Set& rhs)
{
	if (this != &rhs) // don't do anything if LHS == RHS
	{
		Set temp(rhs); //create a deep copy of rhs
		swap(temp); //swap with temp
	}
	return *this;// after this destructor is called for temp and old values of this are deleted.
}
bool Set::empty() const
{
	return m_size == 0; // returns true if there are no elements in the set
}

int Set::size() const
{
	return m_size; // returns size which is the number of elements in the set.
}

bool Set::insert(const ItemType& value)
{
	if (!contains(value)) { // check whether value is inserted before, if yes do not insert and return false.
		if (m_head == nullptr) // if list is empty insert to head.
		{
			m_head = new Node;
			m_head->m_next = nullptr;
			m_head->m_prev = nullptr;
			m_head->m_value = value;
			m_size++;
			return true;
		}
		else if (m_head->m_value >= value) // if value is the smallest value among set, insert to the beginning of the list.
		{

			Node* toBeInserted = new Node;
			toBeInserted->m_value = value;

			toBeInserted->m_next = m_head;
			toBeInserted->m_next->m_prev = toBeInserted;
			m_head = toBeInserted;
			toBeInserted->m_prev = nullptr;
			m_size++;
			return true;
		}
		else // Insert middle or at the end.
		{
			Node* current = m_head; // create an iterator

			while (current->m_next != nullptr && current->m_next->m_value < value)
			{
				current = current->m_next; // find node which you will insert after that node. This can be the last node.
			}

			Node* toBeInserted = new Node; //create new Node with given value
			toBeInserted->m_value = value;

			// current is now pointing to the Node with the biggest value but also smaller than the value.

			//make insertion
			toBeInserted->m_next = current->m_next; // if we are at the end, sets next  to nullptr

			if (current->m_next != nullptr) // if we are not inserting to the end, make prev of next node, new inserted node.
			{
				toBeInserted->m_next->m_prev = toBeInserted;
			}
			current->m_next = toBeInserted; // connect with next
			toBeInserted->m_prev = current; // connect with prev
			m_size++;
			return true;
		}
	}
	return false;
}

bool Set::erase(const ItemType& value)
{
	Node* toBeDeleted = m_head;

	while (toBeDeleted != nullptr && toBeDeleted->m_value != value)
	{
		toBeDeleted = toBeDeleted->m_next;  // search for the node with given value, if not found set to nullptr
	}
	// toBeDeleted is nullptr if value not found else has the address of the node which is going to be deleted

	if (toBeDeleted == nullptr)
		return false;// value does not exist inside the list
	
	//if we are going to delete the first node
	if (m_head == toBeDeleted)
		m_head = toBeDeleted->m_next;

	//set next node's prev to toBeDeleted's prev if we are not deleting a node at the end of the list
	if (toBeDeleted->m_next != nullptr)
		toBeDeleted->m_next->m_prev = toBeDeleted->m_prev;

	//set prev node's next to toBeDeleted's next if we are not deleting a node at the beginning of the list.
	if(toBeDeleted->m_prev != nullptr)
		toBeDeleted->m_prev->m_next = toBeDeleted->m_next;

	delete toBeDeleted;
	m_size--;
	return true;
}

bool Set::contains(const ItemType& value) const
{
	// Empty list, returns false

	for (Node* p = m_head; p != nullptr; p = p->m_next) // search through all list
		if (p->m_value == value)
			return true;
	return false;
}

bool Set::get(int pos, ItemType& value) const
{
	// Empty list, returns false, out of index returns false
	if (0 <= pos && pos < m_size)
	{
		int count = 0;
		for (Node* p = m_head; p != nullptr; p = p->m_next) { //iterate through all list until you reach position pos
			if (count == pos)
			{
				value = p->m_value;
				return true;
			}
			count++;
		}
	}
	return false;
}

void Set::swap(Set& other)
{
	if (this != &other)
	{
		Node* temp_p = other.m_head; // swap list
		other.m_head = m_head;
		m_head = temp_p;

		int temp_size = other.m_size; //swap size
		other.m_size = m_size;
		m_size = temp_size;
	}
}

void Set::dump() const
{
	std::cerr << "...Dumping Set with size " << size() << " ..." << std::endl;
	std::cerr << "Values: ";
	for (Node* p = m_head; p != nullptr; p = p->m_next)
		std::cerr << p->m_value << " ";
	std::cerr << std::endl;

}

void unite(const Set& s1, const Set& s2, Set& result) 
{

	if (&s1 != &result && &s2 != &result && &s1 != &s2) // all of them are different sets, do regular operation, clear result, add s1 items and s2 items to result
	{
		while (result.size() != 0) //empty result
		{
			ItemType temp;
			if (result.get(0, temp))
				result.erase(temp);
		}
		int idx = 0;
		while (s1.size() != idx) //add s1 elements to result
		{
			ItemType temp;
			if (s1.get(idx, temp))
				result.insert(temp);
			idx++;
		}
		idx = 0;
		while (s2.size() != idx) //add s2 elements to result, it will automatically unite since insertion checks whether value is in the set or not
		{
			ItemType temp;
			if (s2.get(idx, temp))
				result.insert(temp);
			idx++;
		}
		idx = 0;
	}
	else if (&s1 == &result && &s2 != &result && &s1 != &s2) // since result has s1 elements, you only need to add s2 elements to result
	{
		int idx = 0;
		while (s2.size() != idx)// add s2 elements to result
		{
			ItemType temp;
			if (s2.get(idx, temp))
				result.insert(temp);
			idx++;
		}
	}
	else if (&s1 != &result && &s2 == &result && &s1 != &s2) // since result has s2 elements, you only need to add s1 elements to result
	{
		int idx = 0;
		while (s1.size() != idx) // add s1 elements to result
		{
			ItemType temp;
			if (s1.get(idx, temp))
				result.insert(temp);
			idx++;
		}
	}
	else if (&s1 != &result && &s2 != &result && &s1 == &s2) // since s1 and s2 are same, just return s1 as result.
	{
		while (result.size() != 0) //empty result
		{
			ItemType temp;
			if (result.get(0, temp))
				result.erase(temp);
		}
		int idx = 0;
		while (s1.size() != idx) //add s1 elements to result
		{
			ItemType temp;
			if (s1.get(idx, temp))
				result.insert(temp);
			idx++;
		}
		idx = 0;
	}
	else if (&s1 == &result && &s2 == &result && &s1 == &s2)
	{
		return; // don't do anything they are all equal.
	}

}

void butNot(const Set& s1, const Set& s2, Set& result)
{

	if (&s1 != &result && &s2 != &result && &s1 != &s2) // they are all distinct do regular operation, delete result, add s1 to result, remove s2 items from result
	{
		while (result.size() != 0) // clear result
		{
			ItemType temp;
			if (result.get(0, temp))
				result.erase(temp);
		}
		int idx = 0;
		while (s1.size() != idx) // add s1 elements to result
		{
			ItemType temp;
			if (s1.get(idx, temp))
				result.insert(temp);
			idx++;
		}
		idx = 0;
		while (s2.size() != idx) // discard s2 elements from result
		{
			ItemType temp;
			if (s2.get(idx, temp))
				result.erase(temp);
			idx++;
		}
		idx = 0;
	}
	else if (&s1 == &result && &s2 != &result && &s1 != &s2) // since s1 = result, you only need to erase s2 elements.
	{
		int idx = 0;
		while (s2.size() != idx) // discard s2 elements from result
		{
			ItemType temp;
			if (s2.get(idx, temp))
				result.erase(temp);
			idx++;
		}
	}
	else if (&s1 != &result && &s2 == &result && &s1 != &s2) // since s2 = result, create a copy set of s2/result, empty result, add s1 elements, discard elements in the copy set.
	{
		Set copy_result(result); // copy s2 set

		while (result.size() != 0) // empty result
		{
			ItemType temp;
			if (result.get(0, temp))
				result.erase(temp);
		}
		int idx = 0;
		while (s1.size() != idx) // add s1 elements to result
		{
			ItemType temp;
			if (s1.get(idx, temp))
				result.insert(temp);
			idx++;
		}
		idx = 0;
		while (copy_result.size() != idx) // discard elements in copy_result from result.
		{
			ItemType temp;
			if (copy_result.get(idx, temp))
				result.erase(temp);
			idx++;
		}
		idx = 0;

	}
	else if (&s1 != &result && &s2 != &result && &s1 == &s2) 
	{
		while (result.size() != 0) // return empty set, s1 butNot s1 is empty set
		{
			ItemType temp;
			if (result.get(0, temp))
				result.erase(temp);
		}
	}
	else if (&s1 == &result && &s2 == &result && &s1 == &s2)
	{
		while (result.size() != 0) // return empty set, s1 butNot s1 is empty set
		{
			ItemType temp;
			if (result.get(0, temp))
				result.erase(temp);
		}
	}

}
