#include "Set.h"

#include <iostream>

Set::Set()
	:m_size(0)
{}

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
	if (m_size == DEFAULT_MAX_ITEMS || contains(value))
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
	for (int i = 0; i < m_size; i++)
	{
		if (m_set[i] == value)
			return true;
	}
	return false;
}

bool Set::get(int i, ItemType& value) const
{
	if (0 <= i && i < m_size)
	{
		value = m_set[i];
		return true;
	}
	return false;
}

void Set::swap(Set& other)
{

	int min_length = other.m_size;
	if (min_length > m_size)
	{
		// size of other set is greater than this set.
		min_length = m_size;
		for (int i = 0; i < min_length; i++)
		{
			ItemType temp = other.m_set[i];
			other.m_set[i] = m_set[i];
			m_set[i] = temp;
		}

		m_size = other.m_size;
		other.m_size = min_length;

		// size of this set is greater than the other set now.
		for (int i = min_length; i < m_size; i++)
		{
			m_set[i] = other.m_set[i];
		}
	}
	else if (min_length == m_size)
	{
		if (this != &other)
		{
			for (int i = 0; i < min_length; i++)
			{
				ItemType temp = other.m_set[i];
				other.m_set[i] = m_set[i];
				m_set[i] = temp;
			}
		}
	}
	else
	{
		// size of this set is greater than other set.

		for (int i = 0; i < min_length; i++)
		{
			ItemType temp = other.m_set[i];
			other.m_set[i] = m_set[i];
			m_set[i] = temp;
		}

		other.m_size = m_size;
		m_size = min_length;


		// size of other set is greater than this set now.
		for (int i = min_length; i < other.m_size; i++)
		{
			other.m_set[i] = m_set[i];
		}
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
