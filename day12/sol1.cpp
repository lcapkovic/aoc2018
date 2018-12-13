#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility> 
#include <boost/algorithm/string.hpp>
#include <set> 

using namespace std;

void sol1(string pots, map<string, bool> pats, int gens, int buffer) {
    cout << pots << endl;
    int prevSum = 0;
    for (int gen = 0; gen < gens; gen++) {
        string newPots = pots;
        for (int i = 0; i < pots.length()-4; i++) {
            string pat = pots.substr(i, 5);
            if (pats.find(pat) == pats.end()) {
                newPots[i+2] = '.';
            } else {
                if (pats[pat]) {
                    newPots[i+2] = '#';
                } else {
                    newPots[i+2] = '.';
                }
            }
        }
        pots = newPots;
        // cout << pots << endl;
        int cur = -buffer;
        int sum = 0;

        while(cur < int(pots.length()-buffer)) {
            if (pots[cur + buffer] == '#') sum += cur;
            cur++;
        }
        cout << "After " << gen+1 << " :" << sum-prevSum << " " << sum <<  endl;
        prevSum = sum;
    }
    cout << pots << endl;
}


int main() {
    string pots;
    cin >> pots;
    cin >> pots;
    cin >> pots;
    string buff = string(160, '.');
    pots = buff + pots + buff;

    map<string, bool> pats;
    for(string str; cin >> str;) {
        string left = str;
        string right;

        cin >> right;
        cin >> right;

        pats[left] = right == "#" ? true : false;
    }
    sol1(pots, pats, 100, buff.length());
}