#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility> 
#include <boost/algorithm/string.hpp>
#include <set> 

using namespace std;

struct record {
    vector<int> regsBefore;
    vector<int> regsAfter;
    vector<int> instruction;
};

int sol1(vector<record*> records, map<int,string> &mapping) {
    int overThree = 0;
    map<int,set<string>> candidates;
    map<int,string> finalMapping;
    for (int i = 0; i < 16; i++) {
        candidates[i] = set<string>();
    }

    for (auto sample : records) {
        set<string> cands = set<string>();

        int opcode = sample->instruction[0];

        if (candidates[opcode].size() == 1) continue; // no need to check this one again
        int A = sample->instruction[1];
        int B = sample->instruction[2];
        int C = sample->instruction[3];
        vector<int> bf = sample->regsBefore;
        vector<int> af = sample->regsAfter;

        // addr
        if (af[C] == bf[A] + bf[B]) cands.insert("addr");
        // addi
        if (af[C] == bf[A] + B) cands.insert("addi");
        // mulr
        if (af[C] == bf[A] * bf[B]) cands.insert("mulr");
        // muli
        if (af[C] == bf[A] * B) cands.insert("muli");
        // banr
        if (af[C] == (bf[A] & bf[B])) cands.insert("banr");
        // bani
        if (af[C] == (bf[A] & B)) cands.insert("bani");
        // borr
        if (af[C] == (bf[A] | bf[B])) cands.insert("borr");
        // bori
        if (af[C] == (bf[A] | B)) cands.insert("bori");
        // setr
        if (af[C] == bf[A]) cands.insert("setr");
        // seti
        if (af[C] == A) cands.insert("seti");
        // gtir
        if ((af[C] == 1 && (A > bf[B])) || (af[C] == 0 && (A <= bf[B]))) cands.insert("gtir");
        // gtri
        if ((af[C] == 1 && (bf[A] > B)) || (af[C] == 0 && (bf[A] <= B))) cands.insert("gtri");
        // gtrr
        if ((af[C] == 1 && (bf[A] > bf[B])) || (af[C] == 0 && (bf[A] <= bf[B]))) cands.insert("gtrr");
        // eqir
        if ((af[C] == 1 && (A == bf[B])) || (af[C] == 0 && (A != bf[B]))) cands.insert("eqir");
        // eqri
        if ((af[C] == 1 && (bf[A] == B)) || (af[C] == 0 && (bf[A] != B))) cands.insert("eqri");
        // eqrr
        if ((af[C] == 1 && (bf[A] == bf[B])) || (af[C] == 0 && (bf[A] != bf[B]))) cands.insert("eqrr");

        if (cands.size() >= 3) overThree++;
        if (candidates[opcode].size() == 0) candidates[opcode] = cands;
        else  {
            set<string> newSet;
            set_intersection(candidates[opcode].begin(), candidates[opcode].end(),
                             cands.begin(), cands.end(), std::inserter(newSet,newSet.begin()));
            candidates[opcode] = newSet;
        }
        if (candidates[opcode].size() == 1 && finalMapping.find(opcode) == finalMapping.end()) {
                string op = *candidates[opcode].begin();
                finalMapping[opcode] = op;
            }
    }

    // Delete known
    vector<string> toDelete;
    vector<int> toAdd;

    while(true) {
        toAdd = vector<int>();
        for (auto kvp : finalMapping) {
            int opcode = kvp.first;
            string op = kvp.second;

            for (int i = 0; i < 16; i++) {
                if (finalMapping.find(i) != finalMapping.end()) continue;
                auto found = find(candidates[i].begin(), candidates[i].end(), op);
                if (found != candidates[i].end()) {
                    candidates[i].erase(op);
                    if (candidates[i].size() == 1) {
                        toAdd.push_back(i);
                    }
                }
            }
        }

        if (toAdd.size() == 0) break;

        for (auto x : toAdd) {
            finalMapping[x] = *candidates[x].begin();
        }
    }
    mapping = finalMapping;

    return overThree;
}

int sol2(vector<vector<int>> instructions, map<int,string>mapping) {
    vector<int> regs(4,0);

    for (auto instr : instructions) {
        string op = mapping[instr[0]];
        int A = instr[1];
        int B = instr[2];
        int C = instr[3];

        if (op == "addr") regs[C] = regs[A] + regs[B];
        else if (op == "addi") regs[C] = regs[A] + B;
        else if (op == "mulr") regs[C] = regs[A] * regs[B];
        else if (op == "muli") regs[C] = regs[A] * B;
        else if (op == "banr") regs[C] = regs[A] & regs[B];
        else if (op == "bani") regs[C] = regs[A] & B;
        else if (op == "borr") regs[C] = regs[A] | regs[B];
        else if (op == "bori") regs[C] = regs[A] | B;
        else if (op == "setr") regs[C] = regs[A];
        else if (op == "seti") regs[C] = A;
        else if (op == "gtir") regs[C] = A > regs[B];
        else if (op == "gtri") regs[C] = regs[A] > B;
        else if (op == "gtrr") regs[C] = regs[A] > regs[B];
        else if (op == "eqir") regs[C] = A == regs[B];
        else if (op == "eqri") regs[C] = regs[A] == B;
        else if (op == "eqrr") regs[C] = regs[A] == regs[B];
    }
    return regs[0];
}

int main() {
    vector<record*> records;
    for (string line; getline(cin, line);) {
        if (line.length() == 0) break;
        record *r = new record();
        r->regsBefore = vector<int>(4,0);
        r->regsAfter = vector<int>(4,0);
        r->instruction = vector<int>(4,0);

        string before = line;
        sscanf(line.c_str(), "Before: [%d, %d, %d, %d]", &r->regsBefore[0], &r->regsBefore[1], &r->regsBefore[2], &r->regsBefore[3]);
        
        cin >> r->instruction[0] >> r->instruction[1] >> r->instruction[2] >> r->instruction[3];
        
        getline(cin, line);
        
        getline(cin, line);
        sscanf(line.c_str(), "After: [%d, %d, %d, %d]", &r->regsAfter[0], &r->regsAfter[1], &r->regsAfter[2], &r->regsAfter[3]);
        
        records.push_back(r);
        getline(cin, line);
    }
    string line;
    getline(cin, line);
    vector<vector<int>> instructions;
    for (string line; getline(cin, line);) {
        vector<int> instr(4,0);
        sscanf(line.c_str(), "%d %d %d %d", &instr[0], &instr[1], &instr[2], &instr[3]);
        instructions.push_back(instr);
    }

    map<int,string> instrMapping;
    cout << sol1(records, instrMapping) << endl;

    for (auto kvp : instrMapping) {
        cout << kvp.first << ": " << kvp.second << endl;
    }

    cout << sol2(instructions, instrMapping) << endl;

}