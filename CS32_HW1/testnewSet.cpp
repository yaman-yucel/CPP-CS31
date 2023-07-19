#include "newSet.h"
#include <iostream>
#include <cassert>

using namespace std;
int main()
{ 
    Set z(0);
    Set z2(0);
    Set z3 = z;
    z2 = z;
    z = z;
    z.dump();
    z2.dump();
    z3.dump();
    ItemType z1 = "z1";
    assert(!z.insert(z1));
    z.dump();
    assert(!z.erase(z1));
    z.dump();
    assert(z.size() == 0);
    assert(z.empty());
    Set y(1);
    assert(y.insert(z1));
    y.dump();
    y.swap(z);
    z.dump();
    y.dump();
    z3 = z;
    z = z3;
    z3 = y;
    Set a(1000);   // a can hold at most 1000 distinct items
    Set b(5);      // b can hold at most 5 distinct items
    Set c;         // c can hold at most DEFAULT_MAX_ITEMS distinct items
    ItemType v[6] = { "1","2","3","4","5","6" };

    // No failures inserting 5 distinct items into b
    for (int k = 0; k < 5; k++)
    {
        assert(b.insert(v[k]));
        //b.dump();
    }
    // Failure if we try to insert a sixth distinct item into b
    assert(!b.insert(v[5]));
    b.dump();
    // When two Sets' contents are swapped, their capacities are swapped
    // as well:
    a.swap(b);
    assert(!a.insert(v[5]) && b.insert(v[5]));
    a.dump();
    b.dump();

    Set s;
    assert(s.empty());
    ItemType x = "arepa";
    assert(!s.get(42, x) && x == "arepa"); // x unchanged by get failure
    s.insert("chapati");
    assert(s.size() == 1);
    assert(s.get(0, x) && x == "chapati");

    Set cpy = b;
    
    cerr << "COPY" << endl;
    cpy.dump();
    cerr << "COPY END" << endl;
    b.dump();
    
    a = b;
    cerr << "ASSIGMENT" << endl;
    //a.dump();
    cerr << "COPY END" << endl;

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
}