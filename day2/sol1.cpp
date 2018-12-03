#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

    string curID;

    int doubles = 0;
    int triples = 0;

    while (cin >> curID){
        int counts[26] = {};

        for (int i = 0; i < curID.length(); i++){
            counts[int(curID[i]-'a')]++;
        }

        bool tDone = false;
        bool dDone = false;

        

        for (int i = 0; i < 26; i++){
            if (counts[i]==2 && !dDone){
                doubles++;

                dDone = true;
            } else if (counts[i]==3 && !tDone){
                triples++;
                tDone = true;
            }

            if (dDone && tDone) break;
        }
    }

    cout << "Checksum: " << endl;
    cout << doubles * triples << endl;
    cout << endl;
}