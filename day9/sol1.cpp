#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility> 
#include <boost/algorithm/string.hpp>
#include <set> 

using namespace std;

struct Node {
    int n;
    Node *prev;
    Node *next;
};

long sol(int n, int l) {
    Node first;
    first.n = 0;
    first.prev = &first;
    first.next = &first;

    Node *cur = &first;
    int player;
    int curMarble = 1;
    vector<long>scores(n,0);

    while(curMarble <= l) {

        if (curMarble % 23 != 0)
        {
            Node *newNode = new Node;
            newNode->n = curMarble;
            newNode->next = cur->next->next;
            newNode->prev = cur->next;

            newNode->next->prev = newNode;
            cur->next->next = newNode;
            cur = newNode;
        } else {
            Node *toDelete = cur;
            for(int i = 0; i < 7; i++) toDelete = toDelete->prev;
            scores[player] += curMarble;
            scores[player] += toDelete->n;

            toDelete->prev->next = toDelete->next;
            toDelete->next->prev = toDelete->prev;
            cur = toDelete->next;
        }
        
        player = (player + 1) % n;
        curMarble++;
    }
    return *max_element(scores.begin(), scores.end());
}

int main() {
    string line;
    getline(cin, line);

    int n, l;
    sscanf(line.c_str(), "%d players; last marble is worth %d points", &n, &l);

    cout << sol(n,l) << endl;
}