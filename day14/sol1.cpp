#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility> 

using namespace std;

struct node {
    int content;
    node* next;
};

int main() {
    // Part 1
    int n = 540561;

    // For part 2
    // int n = 100000000;
    int recipesMade = 2;

    node* head = new node();
    node* tail = new node();
    head->content = 3;
    tail->content = 7;
    head->next = tail;
    tail->next = head;

    vector<node*> elves = {head, tail};

    while(true) {
        int recSum = 0;
        for (auto elf : elves) {
            recSum += elf->content;
        }

        // Add new recipes
        string str = to_string(recSum);
        for (auto charRec : str) {
            node* newRec = new node();
            newRec->content = charRec - '0';
            newRec->next = head;
            tail->next = newRec;
            tail = newRec;
            recipesMade++;
        }

        // Assign recipes
        for(int i = 0; i < elves.size(); i++) {
            int steps = elves[i]->content + 1;
            for (int j = 0; j < steps; j++) {
                elves[i] = elves[i]->next;
            }
            // cout << "New recipe for elf " << i << " :" << elves[i]->content << endl;
        }
        if (recipesMade > n+10) break;
    }
    node* trav = head;

    // For part 1
    for(int i = 0; i < n; i++) {
        trav = trav->next;
    }
    string res = "";
    for (int i = 0; i < 10; i++){
        res = res + to_string(trav->content);
        trav = trav->next;
    }
    cout << res << endl;

    // For part 2 print all of these out to a file and get the number manually
    // for (int i = 0; i < recipesMade; i++) {
    //     cout << trav->content;
    //     trav = trav->next;
    // }
    // cout << endl;

}