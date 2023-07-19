#include "CardSet.h"
#include <iostream>
CardSet::CardSet()
    :m_s()
{
}

bool CardSet::add(unsigned long cardNumber)
{
    if (m_s.insert(cardNumber))
        return true;
    return false;
}

int CardSet::size() const
{
    return m_s.size();
}

void CardSet::print() const
{
    unsigned long temp = 0;
    for (int i = 0; i < m_s.size(); i++)
    {
        if(m_s.get(i, temp))
            std::cout << temp << std::endl;
    }
}
