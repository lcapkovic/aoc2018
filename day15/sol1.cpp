#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility> 

using namespace std;

struct character {
    int r;
    int c;
    int health;
};

vector<vector<int>> getDistanceMap2(int sr, int sc, char target, vector<vector<char>> &map) {
    int n = map.size();
    vector<vector<int>> distMap(map.size(), vector<int>(map[0].size(), -1));

    for (int r = 0; r < map.size(); r++) {
        for (int c = 0; c < map[0].size(); c++) {
            if (map[r][c] == target) {
                    if (map[r+1][c] == '.') distMap[r+1][c] = 0;
                    if (map[r-1][c] == '.') distMap[r-1][c] = 0;
                    if (map[r][c+1] == '.') distMap[r][c+1] = 0;
                    if (map[r][c-1] == '.') distMap[r][c-1] = 0;
            }
        }
    }

    int curDist = 1;
    bool startReached = false;
    bool prevDistFound = false;
    while(!startReached) {
        for (int r = 0; r < map.size(); r++) {
            for (int c = 0; c < map[0].size(); c++) {
                if (distMap[r][c] == curDist-1) {
                    prevDistFound = true;
                    if (abs(r-sr) + abs(c-sc) == 1) {
                        startReached = true;
                    }
                    if (map[r+1][c] == '.' && distMap[r+1][c] == -1) distMap[r+1][c] = curDist;
                    if (map[r-1][c] == '.' && distMap[r-1][c] == -1) distMap[r-1][c] = curDist;
                    if (map[r][c+1] == '.' && distMap[r][c+1] == -1) distMap[r][c+1] = curDist;
                    if (map[r][c-1] == '.' && distMap[r][c-1] == -1) distMap[r][c-1] = curDist;
                }
            }
        }
        if (!prevDistFound) break;
        prevDistFound = false;
        curDist++;
    }
    return distMap;
}

character* getCharByPos(int r, int c, vector<character*> characters) {
    for (auto ch : characters) {
        if (ch->r == r && ch->c == c && ch->health > 0) return ch;
    }
    return nullptr;
}

bool hasMoved(int r, int c, vector<character*> moved) {
    for (auto ch : moved) if (ch->r == r && ch->c == c) return true;
    return false;
}

void step(vector<vector<char>> &map, vector<character*> &goblins, vector<character*> &elves, int ap) {
    vector<character*> moved;
    for (int r = 0; r < map.size(); r++) {
        for (int c = 0; c < map.size(); c++) {
            if ((map[r][c] == 'G' || map[r][c] == 'E') && !hasMoved(r,c,moved)) {
                character* ch;
                char target;
                bool attack = false;
                int curr, curc;
                if (map[r][c] == 'G'){
                    ch = getCharByPos(r, c, goblins);
                    target = 'E';
                }
                else{
                    ch = getCharByPos(r, c, elves);
                    target = 'G';
                }
                if (map[r+1][c] == target || map[r-1][c] == target || map[r][c+1] == target || map[r][c-1] == target) {
                    attack = true;
                    curr = r;
                    curc = c;
                } else {
                    vector<vector<int>> distmap = getDistanceMap2(r,c,target,map);
                    int nextr,nextc;
                    int mindist = 10000;
                    if (distmap[r-1][c] > -1 && distmap[r-1][c] < mindist) {
                        nextr = r-1;
                        nextc = c;
                        mindist = distmap[r-1][c];
                    }
                    if (distmap[r][c-1] > -1 && distmap[r][c-1] < mindist) {
                        nextr = r;
                        nextc = c-1;
                        mindist = distmap[r][c-1];
                    }
                    if (distmap[r][c+1] > -1 && distmap[r][c+1] < mindist) {
                        nextr = r;
                        nextc = c+1;
                        mindist = distmap[r][c+1];
                    }
                    if (distmap[r+1][c] > -1 && distmap[r+1][c] < mindist) {
                        nextr = r+1;
                        nextc = c;
                        mindist = distmap[r+1][c];
                    }
                    if (mindist == 10000) {
                        continue;
                    }
                    map[nextr][nextc] = target == 'G' ? 'E' : 'G';
                    map[r][c] = '.';
                    ch->r = nextr;
                    ch->c = nextc;
                    moved.push_back(ch);
                    cout << "MOVING " << r << " " << c << " to " << nextr << " " << nextc << endl;
                    
                    if (mindist == 0) attack = true;
                    curr = nextr;
                    curc = nextc;
                }

                if (attack) {
                    character* toAttack;
                    int minhp = 10000;
                    vector<character*> *targets = target == 'E' ? &elves : &goblins;
                    if (map[curr-1][curc] == target && getCharByPos(curr-1,curc, *targets)->health < minhp) {
                        toAttack = getCharByPos(curr-1,curc, *targets);
                        minhp = toAttack->health;
                    }
                    if (map[curr][curc-1] == target && getCharByPos(curr,curc-1, *targets)->health < minhp) {
                        toAttack = getCharByPos(curr,curc-1, *targets);
                        minhp = toAttack->health;
                    }
                    if (map[curr][curc+1] == target && getCharByPos(curr,curc+1, *targets)->health < minhp) {
                        toAttack = getCharByPos(curr,curc+1, *targets);
                        minhp = toAttack->health;
                    }
                    if (map[curr+1][curc] == target && getCharByPos(curr+1,curc, *targets)->health < minhp) {
                        toAttack = getCharByPos(curr+1,curc, *targets);
                        minhp = toAttack->health;
                    }
                    cout << "ATTACKING " << toAttack->r << " " << toAttack->c << endl;
                    if (target == 'G') {
                        toAttack->health -= ap;
                    } else {
                        toAttack->health -= 3;
                    }
                    
                    if (toAttack->health <= 0) {
                        map[toAttack->r][toAttack->c] = '.';
                        cout << "DIED" << endl;
                    }
                    cout << ch->health << " HP left." << endl;
                }
            }
        }
    }
}

bool isDone(vector<character*> &goblins, vector<character*> &elves, char &winner) {
    bool hasAlive = false;
    for (auto ch : goblins) {
        if (ch->health > 0) {
            hasAlive = true;
            break;
        }
    }
    if (!hasAlive) {
        winner = 'E';
        return true;
    }

    hasAlive = false;
    for (auto ch : elves) {
        if (ch->health > 0) {
            hasAlive = true;
            break;
        }
    }
    if (!hasAlive) {
        winner = 'G';
        return true;
    }
    return false;
}

int healthSum(vector<character*> &goblins, vector<character*> &elves) {
    int sum = 0;
    for (auto c : goblins) {
        if (c->health > 0) sum += c->health;
    }
    for (auto c : elves) {
        if (c->health > 0) sum += c->health;
    }
    return sum;
}

void sol1(vector<vector<char>> map) {
    vector<character*> goblins;
    vector<character*> elves;
    int ap = 15;

    for (int r = 0; r < map.size(); r++) {
        for(int c = 0; c < map.size(); c++) {
            if (map[r][c] == 'G' || map[r][c] == 'E') {
                character *p = new character();
                p->r = r;
                p->c = c;
                p->health = 200; 
                if (map[r][c] == 'G') goblins.push_back(p);
                else elves.push_back(p);
            }
        }
    }
    char winner;
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            cout << map[i][j];
        }
        cout << endl;
    }
    for (int i = 0; i < 200; i++) {
        cout << "ROUND " << i+1 << endl;
        step(map, goblins, elves, ap);
        if (isDone(goblins, elves, winner)) {
            int totalHP = healthSum(goblins, elves);
            cout << "Winner is " << winner << " after " << i << " rounds with " << totalHP << " HP." <<  endl;
            break;
        }
        for (int i = 0; i < map.size(); i++) {
            for (int j = 0; j < map[0].size(); j++) {
                cout << map[i][j];
            }
            cout << endl;
        }
        cout << "----------------" << endl;
    }
    bool allAlive = true;
    for (auto e : elves) {
        if (e->health <= 0) {
            allAlive = false;
            break;
        }
    }
    cout << "All elves alive: " << allAlive << endl;
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            cout << map[i][j];
        }
        cout << endl;
    }
}

int main() {
    vector<vector<char>> map;

    for(string line; getline(cin, line);) {
        vector<char> newVec;
        for (auto c: line) {
            newVec.push_back(c);
        }
        map.push_back(newVec);
    }
    int n = map.size();
    cout << n << endl;
    sol1(map);
}