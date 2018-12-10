#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility> 
#include <boost/algorithm/string.hpp>
#include <set> 

using namespace std;

struct Entry {
    int x;
    int y;
    int vx;
    int vy;
};

void oneStep(vector<Entry*> *entries, int *minx, int *miny, int *maxx, int *maxy, bool rev) {
    *minx = INT_MAX;
    *miny = INT_MAX;
    *maxx = INT_MIN;
    *maxy = INT_MIN;
    for (auto e : *entries) {
        if (!rev) {
            e->x += e->vx;
            e->y += e->vy;
        } else {
            e->x -= e->vx;
            e->y -= e->vy;
        }
        *minx = min(*minx, e->x);
        *miny = min(*miny, e->y);
        *maxx = max(*maxx, e->x);
        *maxy = max(*maxy, e->y);
    }
}

void simulate(vector<Entry*> entries, int steps) {
    int minx,miny,maxx,maxy;
    int lastbbSize = INT_MAX;
    
    for (int i = 0; i < steps; i++) {
        oneStep(&entries, &minx, &miny, &maxx, &maxy, false);
        
        if (maxx-minx + maxy-miny > lastbbSize) {
            cout << "Terminated after " << i << " steps." << endl;
            cout << "Bounds : " << minx << " " << miny << " " << maxx << " " << maxy << endl;
            break;
        }     
        lastbbSize = maxx-minx + maxy-miny;   
    }
        
    oneStep(&entries, &minx, &miny, &maxx, &maxy, true);
    int shiftx = -minx;
    int shifty = -miny;

    vector<vector<char>> board(maxx+shiftx+1, vector<char>(maxy+shifty+1, '.'));
    for (auto e: entries) {
        board[e->x+shiftx][e->y+shifty] = '*';
    }

    for(int y = 0; y < board[0].size(); y++) {
        for(int x = 0; x < board.size(); x++){
            cout << board[x][y];
        }
        cout << endl;
    }
}

int main() {
    vector<Entry*> entries;
    for(string line; getline(cin, line);) {
        int x,y,vx,vy;
        sscanf(line.c_str(), "position=<%d,  %d> velocity=<%d,%d>", &x, &y, &vx, &vy);
        Entry *e = new Entry;
        e->x = x;
        e->y = y;
        e->vx = vx;
        e->vy = vy;
        entries.push_back(e);
    }
    simulate(entries, 20000);
}