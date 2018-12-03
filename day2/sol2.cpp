#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

    string curID;
    vector<string> IDs; 

    // read in the ids
    while (cin >> curID){
        IDs.push_back(curID);
    }

    for (int i = 0; i < IDs.size(); i++){
        for (int j = 0; j < IDs.size(); j++){
            if (i == j) break;

            int diffIx = -1;
            bool invalid = false;

            for (int k = 0; k < IDs[i].length(); k++){
                if (IDs[i][k] != IDs[j][k]){
                    if (diffIx > -1){
                        invalid = true;
                        break;
                    }
                    diffIx = k;
                }
            }

            if (diffIx > -1 && !invalid){
                for (int k = 0; k < IDs[i].length(); k++){
                    if (k != diffIx) cout << IDs[i][k];
                }
                cout << endl;
                return 1;

            }
        }
    }
}