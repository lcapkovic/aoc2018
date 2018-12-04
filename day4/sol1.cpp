#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility> 
#include <boost/algorithm/string.hpp>

using namespace std;

struct entry {
    string time;
    string content;
};

void sol1(vector<entry> entries){
    std::map<int, vector<int>> m;

    int curGuard = -1;
    int start = 0;

    for (auto e : entries){
        if (e.content[0] == 'G') {
            sscanf(e.content.c_str(), "Guard #%d begins shift", &curGuard);
            if (m.find(curGuard) == m.end())
                m[curGuard] = vector<int>(60, 0);
        } else if (e.content[0] == 'f') {
            start = stoi(e.time.substr(9,2));
        } else {
            int end = stoi(e.time.substr(9,2));
            for (int i = start; i < end; i++) m[curGuard][i]++;
        }
    }

    int maxGuard = -1;
    int maxGuardMinutes = -1;
    int maxMinute = -1;
    for (auto kp : m){
        int asleepMins = 0;
        for (auto x : kp.second) asleepMins += x;
        if (asleepMins > maxGuardMinutes){
            maxGuard = kp.first;
            maxGuardMinutes = asleepMins;
            maxMinute = std::distance(kp.second.begin(), std::max_element(kp.second.begin(), kp.second.end()));
        }
    }

    cout << "Strategy 1: " << endl;
    cout << "MaxGuard: " << maxGuard << " Max minute: " << maxMinute << endl;
    cout << maxGuard*maxMinute << endl;

    int maxMinuteVal = -1;
    maxMinute = -1;
    maxGuard = -1;

    for (auto kp : m) {
        for (int i = 0; i < 60; i++) {
            if (kp.second[i] > maxMinuteVal) {
                maxMinute = i;
                maxMinuteVal = kp.second[i];
                maxGuard = kp.first;
            }
        }
    }

    cout << "Strategy 2: " << endl;
    cout << "MaxGuard: " << maxGuard << " Max minute: " << maxMinute << endl;
    cout << maxGuard*maxMinute << endl;
}

int main() {

    vector<entry> entries; 

    // read in the entries and sort
    for (string curLine; getline(cin, curLine);){
        entry newEntry = {};
        newEntry.content = curLine.substr(19, curLine.length()-19);
        newEntry.time = curLine.substr(6,11);
        entries.push_back(newEntry);
    }        

    sort(entries.begin(), entries.end(),
    [](const entry & a, const entry & b) -> bool
    { 
        return a.time < b.time; 
    });
    sol1(entries);
}