#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility> 
#include <boost/algorithm/string.hpp>
#include <set> 

using namespace std;

int main() {
    map<char, vector<char>> prereqs;
    set<char> steps;

    for(string line;  getline(cin, line);) {
        char from, to;
        sscanf(line.c_str(), "Step %c must be finished before step %c can begin.", &from, &to);
        steps.insert(from);
        steps.insert(to);

        if (prereqs[to].size() == 0) {
            prereqs[to] = vector<char>{from};
        } else {
            prereqs[to].push_back(from);
        }
    }
    
    vector<char> available;
    for (auto x : steps) {
        if (prereqs[x].size() == 0){
            available.push_back(x);
            prereqs.erase(x);
        }
    }
    sort(available.rbegin(), available.rend());
    
    vector<char> completed;
    while(available.size() > 0) {
        char cur = available.back();
        available.pop_back();
        completed.push_back(cur);

        vector<char> to_erase;
        for (auto &kp : prereqs) {
            auto found = find(kp.second.begin(), kp.second.end(), cur);
            if (found != kp.second.end()) {
                kp.second.erase(found);
                if (kp.second.size() == 0) {
                    available.push_back(kp.first);
                    to_erase.push_back(kp.first);
                }
            }
        }
        for(auto x : to_erase) prereqs.erase(x);
        sort(available.rbegin(), available.rend());
    }
    for (auto x:completed) cout << x;
    cout << endl;
}