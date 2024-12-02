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
    vector<int> v1;
    vector<int> v2;

    while (getline(f, line)){
        istringstream ss(line);
        string word;
        ss >> word;
        v1.push_back(stoi(word));
        ss >> word;
        v2.push_back(stoi(word));  
    }

    for(int i = 0; i<v1.size(); i++) {
        cout << v1[i] << " " << v2[i] << "\n";
    }

    f.close();

    // sort each list
    sort(v1.begin(), v1.end(), compare);
    sort(v2.begin(), v2.end(), compare);

    cout << "\n\n";
    int sum = 0;
    map<int, int> m;
    map<int, int>::iterator it;
    for (int i = 0; i<v1.size(); i++) {
        cout << v1[i] << " " << v2[i] << "\n";
        sum += abs(v1[i] - v2[i]);
        
        it = m.find(v2[i]);
        if (it != m.end()){
           m[v2[i]]++;
        } else {
           m[v2[i]]=1;
        }
    }

    for (auto it = m.begin(); it!=m.end(); it++){
        cout << it->first
             << ":"
             << it->second
             << "\n";
    }

    int sum2 = 0;
    for (int i=0; i<v1.size(); i++){
        it = m.find(v1[i]);
        if( it != m.end()){
            sum2 += v1[i] * m[v1[i]];
        }
    }

    cout << sum << "\n";
    cout << sum2 << "\n";

    return(0);
}