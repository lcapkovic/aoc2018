#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility> 
#include <boost/algorithm/string.hpp>
#include <set> 

using namespace std;

int findIdle(vector<int> nums) {
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] <= 0) return i;
    }
    return -1;
}

bool allIdle(vector<int> counters) {
    for(auto x : counters) {
        if (x > 0) return false;
    }
    return true;
}

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

    int durOffset = 61;
    vector<int> counters = vector<int>(5,0);
    vector<char> jobs = vector<char>(5, '.');
    
    vector<char> completed;
    int seconds = -1;
    while(!allIdle(counters) || available.size() > 0) {
        seconds++;
        // Finish jobs
        for (int i = 0; i < counters.size(); i++){
            counters[i]--;
            if (counters[i] <= 0 && jobs[i] != '.') {
                completed.push_back(jobs[i]);
                
                // Update available jobs
                vector<char> to_erase;
                for (auto &kp : prereqs) {
                    auto found = find(kp.second.begin(), kp.second.end(), jobs[i]);
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
                jobs[i] = '.';
            }
        }

        // Assign new jobs
        while (available.size() > 0 && findIdle(counters) >= 0) {
            int ix = findIdle(counters);
            jobs[ix] = available.back();
            counters[ix] = int(jobs[ix]-'A') +  durOffset;
            available.pop_back();
        }
    }
    for (auto x:completed) cout << x;
    cout << endl;
    cout << seconds << endl;
}