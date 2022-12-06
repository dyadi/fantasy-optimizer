#include <iostream>
#include <sstream>
#include <chrono>
#include <map>
#include "date.h"

using namespace std;
using date::operator<<;

int main() {
    map<chrono::sys_days, int> mp;
    istringstream iss {"2022-12-01"};
    chrono::sys_days tp;
    iss >> date::parse("%F", tp);
    mp[tp] = 1;

    for (auto& [k, v] : mp) {
        cout << k << endl;
        cout << v << endl;
    }

    return 0;
}
