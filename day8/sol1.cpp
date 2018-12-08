#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility> 
#include <boost/algorithm/string.hpp>
#include <set> 

using namespace std;

int addMeta(vector<int> *data, int *startIx) {
    if (*startIx >= data->size()-1) return 0;

    int num_children = data->at(*startIx);
    int num_meta = data->at(*startIx+1);

    int metaSum = 0;
    int tempIx = *startIx+2;
    for (int i = 0; i < num_children; i++){
        metaSum += addMeta(data, &tempIx);
    }

    for (int i = 0; i < num_meta; i++){
        metaSum += data->at(tempIx);
        tempIx++;
    }
    *startIx = tempIx;
    return metaSum;
}

int value(vector<int> *data, int *startIx) { 
    if (*startIx >= data->size()-1) return 0;

    int num_children = data->at(*startIx);
    int num_meta = data->at(*startIx+1);

    int tempIx = *startIx+2;

    vector<int> childVals;
    for (int i = 0; i < num_children; i++){
        childVals.push_back(value(data, &tempIx));
    }

    int valSum = 0;

    if (num_children == 0) {
        // sum up metadata vals
        for (int i = 0; i < num_meta; i++){
            valSum += data->at(tempIx);
            tempIx++;
        }
    } else {
        // sum up children vals at metadata indices - 1
        for (int i = 0; i < num_meta; i++){
            if (data->at(tempIx) > 0 && data->at(tempIx) <= num_children)
                valSum += childVals[data->at(tempIx)-1];
            tempIx++;
        }
    }

    *startIx = tempIx;
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