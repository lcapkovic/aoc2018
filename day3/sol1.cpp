#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility> 
#include <boost/algorithm/string.hpp>

using namespace std;

struct entry {
    int id;
    pair<int,int> loc;
    pair<int,int> size;

};

int sol1(vector<entry> entries){
    vector<vector<int> > map(1200, vector<int>(1200, -1));
    vector<int> candidates;
    int doubles = 0;

    for (int i = 0; i<entries.size(); i++){
        bool broken = false;
        for (int x=0; x<entries[i].size.second; x++){
            for (int y=0; y<entries[i].size.first; y++){
                int ix = x+entries[i].loc.second;
                int iy = y+entries[i].loc.first;
                if (map[ix][iy] > -1){
                    doubles++;
                    candidates.erase(remove(candidates.begin(), candidates.end(), map[ix][iy]), candidates.end());
                    map[ix][iy] = -2;

                    broken = true;
                } else if (map[ix][iy] == -1){
                    map[ix][iy] = entries[i].id;
                } else {
                    broken = true;
                }
            }
        }
        if (!broken) candidates.push_back(entries[i].id);
    }
    
    cout << candidates[0] << endl;
    return doubles;
}

int main() {

    string curLine;
    vector<entry> entries; 

    // read in the ids
    int counter = 0;
    while (getline(cin, curLine)){
        vector<string> tokens;
        boost::split(tokens, curLine, boost::is_any_of(" "));

        entry singleEntry = {};
        singleEntry.id = stoi(tokens[0].substr(1,tokens[0].length()-1));
        singleEntry.loc = pair<int,int>();
        singleEntry.size = pair<int,int>();

        vector<string> locTokens;

        boost::split(locTokens, tokens[2], boost::is_any_of(",:"));
        singleEntry.loc.first = stoi(locTokens[0]);
        singleEntry.loc.second = stoi(locTokens[1]);

        boost::split(locTokens, tokens[3], boost::is_any_of("x"));
        singleEntry.size.first = stoi(locTokens[0]);
        singleEntry.size.second = stoi(locTokens[1]);

        entries.push_back(singleEntry);
    }

    cout << sol1(entries) << endl;
}