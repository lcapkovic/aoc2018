#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility> 
#include <boost/algorithm/string.hpp>
#include <deque>

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

bool isSafe(vector<pair<int,int>> *coordList, int x, int y) {
    int total = 0;
    for (int i = 0; i < coordList->size(); i++) {
        total += abs(coordList->at(i).first-x) + abs(coordList->at(i).second-y);
    }

    return total < 10000;
}

vector<vector<int>> fillMap(vector<pair<int,int>> coordList, int minx, int miny, int maxx, int maxy) {
    int width = 1000;
    int height = 1000;

    vector<vector<int>> map(width, vector<int>(height, -1));

    for (int i = minx; i <=minx+width-1; i++){
        for (int j = miny; j<=miny+height-1; j++){
            if (isSafe(&coordList, i, j)) {
                map[i-minx][j-miny] = 1;
            } else {
                map[i-minx][j-miny] = 0;
            }
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

    int area = 0;
    for (int j = 0; j < map[0].size(); j++){
        for (int i = 0; i < map.size(); i++){
            area += map[i][j];
        }
    }
    cout << area << endl;
}