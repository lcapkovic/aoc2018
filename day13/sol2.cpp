#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility> 

using namespace std;

struct cart {
    int x,y,vx,vy,option;
};

bool step(vector<vector<char>> &map, vector<cart*> &carts) {
    vector<cart*> toErase;
    for (auto c : carts) {
        if(std::find(toErase.begin(), toErase.end(), c) != toErase.end()) {
            // Skip, this cart is getting erased
            continue;
        }
        // Move
        c->x += c->vx;
        c->y += c->vy;

        // Check crash
        bool crash = false;
        for (auto c2 : carts) {
            if (c != c2 && c->x == c2->x && c->y == c2->y) {
                // CRASH
                toErase.push_back(c);
                toErase.push_back(c2);
            }
        }
        if (crash) continue;
        
        // New Orientation
        if (map[c->x][c->y] == '+') {
            if (c->option == 0) {
                // Left
                int tmpX = c->vx;
                c->vx = c->vy;
                c->vy = -tmpX;
            } else if (c->option == 2) {
                // Right
                int tmpX = c->vx;
                c->vx = -c->vy;
                c->vy = tmpX;
            }
            c->option = (c->option+1)%3;
        } else if (map[c->x][c->y] == '\\') {
            if (c->vx != 0) {
                // Right turn
                int tmpX = c->vx;
                c->vx = -c->vy;
                c->vy = tmpX;
            } else {
                // Left turn
                int tmpX = c->vx;
                c->vx = c->vy;
                c->vy = -tmpX;
            }
        } else if (map[c->x][c->y] == '/') {
            if (c->vx != 0) {
                // Left turn
                int tmpX = c->vx;
                c->vx = c->vy;
                c->vy = -tmpX;
            } else {
                // Right turn
                int tmpX = c->vx;
                c->vx = -c->vy;
                c->vy = tmpX;
            }
        }
        // cout << c->x << " " << c->y << "  " << c->vx << " " << c->vy << "  " << c->option << endl; 
    }
    for (auto c : toErase) {
        carts.erase(std::remove(carts.begin(), carts.end(), c), carts.end());
    }
    return false;
}

void sol2(vector<vector<char>> &map, vector<cart*> &carts) {
    int crashX = 0, crashY = 0;
    int counter = 0;
    
    while (carts.size() > 1) {
        step(map, carts);
        counter++;
    }
    
    cout << "After " << counter+1 << " steps." << endl;
    cout << carts[0]->x << " " << carts[0]->y << endl;
}


int main() {
    int n = 150;
    vector<vector<char>> map(n, vector<char>(n, ' '));
    vector<cart*> carts;

    int y=0;
    for(string line; getline(cin, line);) {
        for (int x=0; x < line.length(); x++) {
            char cur = line[x];
            if (cur != '>' && cur != '<' && cur != '^' && cur != 'v') {
                map[x][y] = cur;
            } else {
                cart *newCart = new cart();
                newCart->x = x;
                newCart->y = y;
                newCart->option = 0;
                if (cur == '>') {
                    map[x][y] = '-';
                    newCart->vx = 1;
                    newCart->vy = 0;
                } else if (cur == '<') {
                    map[x][y] = '-';
                    newCart->vx = -1;
                    newCart->vy = 0;
                } else if (cur == '^') {
                    map[x][y] = '|';
                    newCart->vx = 0;
                    newCart->vy = -1;
                } else if (cur == 'v') {
                    map[x][y] = '|';
                    newCart->vx = 0;
                    newCart->vy = 1;
                }
                carts.push_back(newCart);
            }
        }
        y++;
    }

    for (auto c : carts) {
        cout << c->x << " " << c->y << " " << c->vx << " " << c->vy << " " << c->option << endl; 
    }
    cout << endl;
    sol2(map, carts);
}