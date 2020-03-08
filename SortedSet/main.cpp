#include <iostream>
#include "SortedSet.h"
using namespace std;

int main()
{
    SortedSet ss;
    ss.add(-97);
    ss.add(70);
    ss.add(99);
    ss.add(114);

    SortedSet ss1;
    ss1.add(-97);
    ss1.add(70);
    ss1.add(99);
    ss1.add(114);

    SortedSet ss2 = ss | ss1;
    ss1 |= ss2;
    cout << ss1 << endl;
    return 0;
}
