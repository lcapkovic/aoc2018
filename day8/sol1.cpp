#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility> 
#include <boost/algorithm/string.hpp>
#include <set> 

using namespace std;

int addMeta(vector<int> *data, int *ix) {
    if (*ix >= data->size()-1) return 0;

    int num_children = data->at(*ix);
    int num_meta = data->at(*ix+1);

    int metaSum = 0;
    *ix += 2;
    for (int i = 0; i < num_children; i++){

        metaSum += addMeta(data, ix);
    }

    for (int i = 0; i < num_meta; i++){
        metaSum += data->at(*ix);
        (*ix)++;
    }
    return metaSum;
}

int value(vector<int> *data, int *ix) { 
    if (*ix >= data->size()-1) return 0;

    int num_children = data->at(*ix);
    int num_meta = data->at(*ix+1);

    *ix += 2;
    vector<int> childVals;
    for (int i = 0; i < num_children; i++){
        childVals.push_back(value(data, ix));
    }

    int valSum = 0;

    if (num_children == 0) {
        // sum up metadata vals
        for (int i = 0; i < num_meta; i++){
            valSum += data->at(*ix);
            (*ix)++;
        }
    } else {
        // sum up children vals at metadata indices - 1
        for (int i = 0; i < num_meta; i++){
            if (data->at(*ix) > 0 && data->at(*ix) <= num_children)
                valSum += childVals[data->at(*ix)-1];
            (*ix)++;
        }
    }
    return valSum;
}

int main() {
    vector<int> data;
    int curNum;
    while(cin >> curNum) {
        data.push_back(curNum);
    }

    int startIx = 0;
    cout << addMeta(&data, &startIx) << endl;

    startIx = 0;    
    cout << value(&data, &startIx) << endl;
}