#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility> 
#include <boost/algorithm/string.hpp>
#include <deque>

using namespace std;

bool isOpposite(char a, char b){
    return abs(int(a-b)) == 32;
}

int fully_react(string polymer){
    deque<char> pol;
    for (int i = 0; i < polymer.length(); i++){
        if (pol.size() == 0){
            pol.push_back(polymer[i]);
        } else if (isOpposite(pol.back(), polymer[i])){
            pol.pop_back();
        } else {
            pol.push_back(polymer[i]);
        }
    }
    return pol.size();
}

int main() {
    string polymer;
    getline(cin, polymer);

    cout << fully_react(polymer) << endl;

    int shortest = polymer.length();

    for (int i = 65; i < 91; i++){
        string testPol = polymer;
        testPol.erase(remove(testPol.begin(), testPol.end(), char(i)), testPol.end());
        testPol.erase(remove(testPol.begin(), testPol.end(), char(i+32)), testPol.end());
        
        shortest = min(shortest, fully_react(testPol));
    }
    cout << shortest << endl;;
}