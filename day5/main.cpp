#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <regex>
#include <string>

using namespace std;

// Create a hashmap<int, vector<int>> of table 1
// Create a vector<vector<int>> of table 2
// For each number in table 2 look up the key and check if any previous values are in the vector<int> return false if any are found.

void parseTableOne(string line, unordered_map<int, vector<int>>& um) {
    stringstream ss(line);
        string substr;
        getline(ss, substr, '|');
        cout << substr << " ";
        int key = stoi(substr);
        getline(ss, substr);
        cout << substr << "\n";
        int value = stoi(substr);
        um[key].push_back(value);
}

void parseTableTwo(string line, vector<vector<int>>& updates) {
    stringstream ss(line);
    vector<int> v;
    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        v.push_back(stoi(substr));
    }
    updates.push_back(v);
    for(int i=0; i<v.size(); i++){
        cout << v[i] << " ";
    }
    cout << "\n";
}

int main() {

    // input
    ifstream f("input.txt");

    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return 1;
    }

    string line;
    unordered_map<int, vector<int>> um;
    vector<vector<int>> updates;


    while (getline(f, line)){
 
        if (line.find('|') < line.length()) {
        // parse table 1
        parseTableOne(line, um);
        } else if (line.find(',') < line.length()) {
        // parse table 2
        parseTableTwo(line, updates);
        }
    }

    for (const auto & [ key, value ] : um) {
        cout << key << ": ";
        for(int i=0; i<value.size(); i++) {
            cout << value[i] << " ";
        }
        cout << "\n";
    }


    int sum = 0;
    int sum2 = 0;
    for (int i = 0; i<updates.size(); i++) {
        bool valid = true;
        for (int j=0; j<updates[i].size(); j++) {
            cout << updates[i][j] << " ";
            if (um.find(updates[i][j]) !=  um.end()) {
                // check all previous table 2 values against the vector from the map
                for(int x=0; x<j; x++) {
                    vector<int> v = um[updates[i][j]];
                    for(int y=0; y<v.size(); y++) {
                        if(updates[i][x] == v[y]) {
                            valid = false;
                            int temp = updates[i][j];
                            updates[i].erase(updates[i].begin() + j);
                            updates[i].insert(updates[i].begin() + x, temp);
                        }
                    }
                }
            }
        }
        cout << "\n";
        if(valid){
            vector<int> v = updates[i];
            sum += v[v.size()/2];
        } else {
            vector<int> v = updates[i];
            sum2 += v[v.size()/2];
        }
    }

    cout << sum << "\n";
    cout << sum2 << "\n";

    return(0);
}

