#include <iostream>
#include <string>

using namespace std;

int main() {

    string curOp;
    int ans = 0;

    while(cin >> curOp){
        ans += stoi(curOp);
    }
    cout << ans << endl;
}