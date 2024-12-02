#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

bool compare(int a, int b) {
    return a <= b;
}

int main() {

    // input
    ifstream f("input.txt");

    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return 1;
    }

    string line;
    vector<vector<int>> v1;
    vector<int> v2;

    while (getline(f, line)){
        istringstream ss(line);
        string word;
        while(ss >> word) {
            v2.push_back(stoi(word));
        }
        v1.push_back(v2);
        v2.clear();
    }

    for (const auto &row : v1){
        for (const auto &i : row){
            cout << i << " ";
        }
        cout << endl;
    }

    int safe_count = 0;
    for (auto i=0; i<v1.size(); i++){

        // Test removing each value
        for (auto k=0; k<v1[i].size(); k++){
            bool increasing = true;
            bool decreasing = true;
            int current_value;
            int previous_value;
            vector<int> v = v1[i];
            v.erase(v.begin() + k);

            for (auto j=0; j<v.size(); j++){

                cout << v[j] << " ";

                // Initialize
                if (j == 0) {
                    current_value = v[j];
                    continue;
                }
                // Update values
                previous_value = current_value;
                current_value = v[j];

                // No value change
                if (current_value == previous_value) {
                    cout << "No value change : " << i << "\n";
                    cout << current_value << " " << previous_value << "\n";
                    break;
                }

                // Too high of change
                int change = abs(current_value - previous_value);
                if (change > 3) {
                    cout << "Too high of change : " << i << "\n";
                    break;
                }

                // Check for increasing
                if (current_value > previous_value) {
                    decreasing = false;
                }

                // Check for decreasing
                if (current_value < previous_value) {
                    increasing = false;
                }

                // Check for not all increasing or decreasing
                if (!increasing && !decreasing){
                    cout << "Not all increasing or decreasing : " << i << "\n";
                    break;
                }

                if (j == v.size()-1) {
                    safe_count++;
                    cout << "safe : " << i << "\n";
                    goto Exit;
                }
            }
        }
        Exit:
            cout << "\n";

    }

    cout << safe_count << "\n";

    return(0);
}