#include "Set.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main()
{
    Set s;
    assert(s.empty());
    ItemType x = "arepa";
    assert(!s.get(42, x) && x == "arepa"); // x unchanged by get failure
    s.insert("chapati");
    assert(s.size() == 1);
    assert(s.get(0, x) && x == "chapati");
    


    Set e;
    e.dump();

    Set ss;
    ss.insert("f1");
    ss.dump();
    ss.insert("b1");
    ss.dump();
    ss.insert("g1");
    ss.dump();
    ss.insert("d1");
    ss.dump();
    ss.insert("e1");
    ss.dump();
    ss.insert("c1");
    ss.dump();
    ss.insert("a1");
    ss.dump();


    ss.erase("f1");
    ss.dump();
    ss.erase("b1");
    ss.dump();
    ss.erase("g1");
    ss.dump();
    ss.erase("d1");
    ss.dump();
    ss.erase("e1");
    ss.dump();
    ss.erase("c1");
    ss.dump();
    ss.erase("a1");
    ss.dump();

    ss.insert("lavash");
    ss.insert("roti");
    ss.insert("chapati");
    ss.insert("injera");
    ss.insert("roti");
    ss.insert("matzo");
    ss.insert("injera");

    assert(ss.size() == 5);  // duplicate "roti" and "injera" were not added
    ss.get(0, x);
    assert(x == "chapati");  // "chapati" is greater than exactly 0 items in ss
    ss.get(4, x);
    assert(x == "roti");  // "roti" is greater than exactly 4 items in ss
    ss.get(2, x);
    assert(x == "lavash");  // "lavash" is greater than exactly 2 items in ss

    Set ss1;
    ss1.insert("laobing");
    Set ss2;
    ss2.insert("matzo");
    ss2.insert("pita");
    ss1.dump();
    ss2.dump();
    ss1.swap(ss2);
    ss1.dump();
    ss2.dump();

    assert(ss1.size() == 2 && ss1.contains("matzo") && ss1.contains("pita") &&
        ss2.size() == 1 && ss2.contains("laobing"));

    Set ss3;
    ss3.insert("dosa");
    assert(!ss.contains(""));
    ss3.insert("tortilla");
    ss3.insert("");
    ss3.insert("focaccia");
    assert(ss3.contains(""));
    ss3.erase("dosa");
    assert(ss3.size() == 3 && ss3.contains("focaccia") && ss3.contains("tortilla") &&
        ss3.contains(""));
    string v;
    assert(ss3.get(1, v) && v == "focaccia");
    assert(ss3.get(0, v) && v == "");

    Set s4;
	Set s1;
	s4.dump();
	assert(!s4.erase("1"));
	s4.dump();
	string a = "5";
    assert(!s4.get(0, a));
    assert(!s4.contains(a));
	s4.swap(s1);
	s4.dump();
	s1.dump();
}