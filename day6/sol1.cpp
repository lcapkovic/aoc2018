#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility> 
#include <boost/algorithm/string.hpp>
#include <set> 

using namespace std;

int findClosest(vector<pair<int,int>> *coordList, int x, int y) {
    int minDist = 1000;
    int minDistOwner = -1;
    bool contested = false;

    for (int i = 0; i < coordList->size(); i++) {
        int dist = abs(coordList->at(i).first-x) + abs(coordList->at(i).second-y);
        if (dist < minDist){
            minDist = dist;
            minDistOwner = i;
            contested = false;
        } else if (dist == minDist) contested = true;
    }

    return contested ? -1 : minDistOwner;
}

vector<vector<int>> fillMap(vector<pair<int,int>> coordList, int minx, int miny, int maxx, int maxy) {
    int width = maxx-minx+1;
    int height = maxy-miny+1;

    vector<vector<int>> map(width, vector<int>(height, -1));

    for (int i = minx; i <=minx+width-1; i++){
        for (int j = miny; j<=miny+height-1; j++){
            map[i-minx][j-miny] = findClosest(&coordList, i,j);
        }
    }

    return map;
}

int main() {
    string coords;
    vector<pair<int,int>> coordList;

    int minx = 1000;
    int miny = 1000;
    int maxx = 0;
    int maxy = 0;

    for (string coords; getline(cin, coords);) {
        int x, y;
        sscanf(coords.c_str(), "%d,%d", &x, &y);
        minx = min(x,minx);
        miny = min(y,miny);
        maxx = max(x,maxx);
        maxy = max(y,maxy);
        coordList.push_back(make_pair(x,y));
    }

    vector<vector<int>> map = fillMap(coordList, minx, miny, maxx, maxy);
    set<int> infinites;
    
    for (int i = 0; i < map.size(); i++){
        infinites.insert(map[i][0]);
        infinites.insert(map[i][map[0].size()-1]);
    }
    for (int i = 0; i < map[0].size(); i++){
        infinites.insert(map[0][i]);
        infinites.insert(map[map.size()-1][i]);
    }
    
    int maxArea = 0;

    for (int i = 0; i < coordList.size(); i++){
        if (!infinites.count(i)){
            int count = 0;
            for (int j = 0; j < map.size(); j++){
                for (int k = 0; k < map[0].size(); k++){
                    if (map[j][k] == i) count++;
                }
            }
            maxArea = max(count, maxArea);
        }
    }
    cout << maxArea << endl;
}