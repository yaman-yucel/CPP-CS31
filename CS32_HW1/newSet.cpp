#include "newSet.h"
#include <iostream>
#include <cstdlib>

Set::Set()
	:m_size(0), m_max_size(DEFAULT_MAX_ITEMS), m_set(new ItemType[DEFAULT_MAX_ITEMS])
{}

Set::Set(int size)
	:m_size(0), m_max_size(size), m_set(nullptr)
{
	if (size < 0)
	{
		std::cout << "Size is given as a negative number. Exiting..." << std::endl;
		std::exit(1);
	}
	else if (size > 0)
	{
		m_set = new ItemType[size];
	}	
}

Set::Set(const Set& other)
	:m_size(other.m_size),m_max_size(other.m_max_size),m_set(nullptr)
{
	if (other.m_set != nullptr)
	{
		m_set = new ItemType[other.m_max_size];
		for (int i = 0; i < m_size; i++)
		{
			m_set[i] = other.m_set[i];
		}
	}
}

Set::~Set()
{
	delete [] m_set;
}

Set& Set::operator=(const Set& rhs)
{
	if (&rhs == this)
		return *this;
	if (m_set == nullptr)
	{
		if (rhs.m_set == nullptr)
		{
			return *this;
		}
		else {
			m_max_size = rhs.m_max_size;
			m_size = rhs.m_size;
			m_set = new ItemType[m_max_size];
			for (int i = 0; i < m_size; i++)
			{
				m_set[i] = rhs.m_set[i];
			}
			return *this;
		}
	}
	else
	{
		if (rhs.m_set == nullptr)
		{
			m_max_size = rhs.m_max_size;
			m_size = rhs.m_size;
			delete[] m_set;
			m_set = nullptr;
			return *this;
		}
		else
		{
			m_max_size = rhs.m_max_size;
			m_size = rhs.m_size;
			delete[] m_set;
			m_set = new ItemType[m_max_size];
			for (int i = 0; i < m_size; i++)
			{
				m_set[i] = rhs.m_set[i];
			}
			return *this;
		}
	}
}

bool Set::empty() const
{
	return m_size == 0;
}

int Set::size() const
{
	return m_size;
}

bool Set::insert(const ItemType& value)
{
	if (m_set == nullptr)
		return false;

	if (m_size == m_max_size || contains(value))
	{
		return false;
	}

	int index = 0; //position that insertion will be made

	// Find the position of insertion
	for (int i = 0; i < m_size; i++)
	{
		if (m_set[i] <= value) // although = will not be executed, used to preserve order
		{
			index = i + 1;
		}
	}
	m_size++;

	// Shift all elements which are after index by one right, starting from end
	for (int i = m_size - 2; i >= index; i--)
	{
		m_set[i + 1] = m_set[i];
	}

	m_set[index] = value;

	return true;
}

bool Set::erase(const ItemType& value)
{
	if (m_set == nullptr)
		return false;

	if (contains(value))
	{
		int index = 0;

		for (int i = 0; i < m_size; i++)
		{
			if (m_set[i] == value)
			{
				index = i;
				break;
			}
		}

		for (int i = index; i < m_size - 1; i++)
		{
			m_set[i] = m_set[i + 1];
		}

		m_size--;
		return true;
	}
	return false;
}

bool Set::contains(const ItemType& value) const
{
	if (m_set == nullptr)
		return false;

	for (int i = 0; i < m_size; i++)
	{
		if (m_set[i] == value)
			return true;
	}
	return false;
}

bool Set::get(int i, ItemType& value) const
{
	if (m_set == nullptr)
		return false;

	if (0 <= i && i < m_size)
	{
		value = m_set[i];
		return true;
	}
	return false;
}

void Set::swap(Set& other)
{
	if (this != &other)
	{
		int temp_size = other.m_size;
		other.m_size = m_size;
		m_size = temp_size;

		int temp_max_size = other.m_max_size;
		other.m_max_size = m_max_size;
		m_max_size = temp_max_size;

		ItemType* temp = other.m_set;
		other.m_set = m_set;
		m_set = temp;
	}

}

void Set::dump() const
{
	// ONLY WRITE TO CERR

	if (m_size == 0)
		std::cerr << "No item in list" << std::endl;
	else
	{
		std::cerr << "All items in the set" << std::endl;
		for (int i = 0; i < m_size; i++)
			std::cerr << "Item " << i << " :" << m_set[i] << std::endl;

	}
	std::cerr << "Size: " << size() << std::endl;
	std::cerr << std::endl;
}