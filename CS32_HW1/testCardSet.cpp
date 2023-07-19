#include "CardSet.h"
#include <iostream>
#include <cassert>
using namespace std;
int main()
{
	CardSet cs;
	cs.print();
	assert(cs.add(1));
	assert(cs.add(2));
	assert(cs.add(3));
	assert(cs.add(4));
	assert(!cs.add(4));
	assert(cs.add(5));
	assert(!cs.add(5));
	assert(cs.add(6));
	assert(!cs.add(1));
	cs.print();
}