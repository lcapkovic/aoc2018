#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility> 
#include <boost/algorithm/string.hpp>
#include <set> 

using namespace std;

int power(int x, int y, int sn) {
    int id = x + 10;
    int out = id;
    out *= y;
    out += sn;
    out *= id;

    if (out < 100) 
        out = 0;
    else
        out = (out / 100) % 10;
    return out - 5;
}

void sol1(int sn) {
    vector<vector<int>> grid(300, vector<int>(300,0));

    for (int x = 0; x < 300; x++) {
        for (int y = 0; y < 300; y++) {
            grid[x][y] = power(x,y,sn);
        }
    }

    vector<vector<int>> gridSums(300, vector<int>(300,0));

    int max = 0;
    int maxx;
    int maxy;
    int maxSize;

    for (int size = 1; size <= 300; size++) {
        cout << size << endl;
        for (int ox = 0; ox < 300-size+1; ox++) {
            for (int oy = 0; oy < 300-size+1; oy++) {
                int sum = 0;
                for (int y = 0; y < size; y++) {
                    gridSums[ox][oy] += grid[ox+size-1][oy+y];
                }
                for (int x = 0; x < size-1; x++) {
                    gridSums[ox][oy] += grid[ox+x][oy+size-1];
                }
                if (gridSums[ox][oy] > max) {
                    max = gridSums[ox][oy];
                    maxx = ox;
                    maxy = oy;
                    maxSize = size;
                }
            }
        }
    }
    cout << maxx << " " << maxy << " " << maxSize << endl;
}

int main() {
    sol1(5235);
}