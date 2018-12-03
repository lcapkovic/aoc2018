#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

    string curOp;
    vector<string> ops; 

    // read in the ops
    while (cin >> curOp){
        ops.push_back(curOp);
    }

    vector<int> seenFreqs;    
    seenFreqs.push_back(0);

    int ix = 0;
    int ans = 0;
    while(true){
        curOp = ops[ix];
        ans += stoi(curOp);

        if(find(seenFreqs.begin(), seenFreqs.end(), ans) != seenFreqs.end()) {
            cout << ans << endl;
            break;
        } else {
            seenFreqs.push_back(ans);
            cout << seenFreqs.size() << endl;
        }

        ix = (ix + 1) % ops.size();
    }
}