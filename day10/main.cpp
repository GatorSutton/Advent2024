#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string>
#include <cmath>

using namespace std;

class Pair {

public: 

    int y;
    int x;

    Pair(int y, int x) : y(y), x(x) {}

    bool operator==(const Pair& other) const {
        return x == other.x &&
               y == other.y;
    }

    struct Hash {
        size_t operator()(const Pair& obj) const {
            size_t h1 = hash<int>()(obj.x);
            size_t h2 = hash<int>()(obj.y);

            return h1 ^ (h2 << 1);
        }
    };

    friend struct Hash;
};

void exploreAllPaths(vector<vector<int>>& chart, stack<Pair>& stack, Pair p) {
        int height = chart[p.y][p.x];

    // Explore North
    if (p.y != 0) {
        if(chart[p.y-1][p.x] == height + 1) {
            Pair n = {p.y-1, p.x};
            stack.push(n);
        }
    }

    // Explore South
    if (p.y != chart.size()-1) {
        if(chart[p.y+1][p.x] == height + 1) {
            Pair s = {p.y+1, p.x};
            stack.push(s);
        }
    }

    // Explore West
    if (p.x != 0) {
        if(chart[p.y][p.x-1] == height + 1) {
            Pair w = {p.y, p.x-1};
            stack.push(w);
        }
    }

    // Explore East
    if (p.x != chart[0].size()-1) {
        if(chart[p.y][p.x+1] == height + 1) {
            Pair e = {p.y, p.x+1};
            stack.push(e);
        }
    }
}

// Attempt to visit N,S,E,W. 
// It must be on the chart.
// It must be +1 from the square you are on.
// Add newly visited to locations to the set AND the stack.
void explore(vector<vector<int>>& chart, unordered_set<Pair, Pair::Hash>& us, stack<Pair>& stack, Pair p) {
    int height = chart[p.y][p.x];

    // Explore North
    if (p.y != 0) {
        if(chart[p.y-1][p.x] == height + 1) {
            Pair n = {p.y-1, p.x};
            if(us.find(n) == us.end()) {
                us.insert(n);
                stack.push(n);
            }
        }
    }

    // Explore South
    if (p.y != chart.size()-1) {
        if(chart[p.y+1][p.x] == height + 1) {
            Pair s = {p.y+1, p.x};
            if(us.find(s) == us.end()) {
                us.insert(s);
                stack.push(s);
            }
        }
    }

    // Explore West
    if (p.x != 0) {
        if(chart[p.y][p.x-1] == height + 1) {
            Pair w = {p.y, p.x-1};
            if(us.find(w) == us.end()) {
                us.insert(w);
                stack.push(w);
            }
        }
    }

    // Explore East
    if (p.x != chart[0].size()-1) {
        if(chart[p.y][p.x+1] == height + 1) {
            Pair e = {p.y, p.x+1};
            if(us.find(e) == us.end()) {
                us.insert(e);
                stack.push(e);
            }
        }
    }
}     

int main() {

    // input
    ifstream f("input.txt");

    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return 1;
    }

    string line;
    vector<vector<int>> chart;
    vector<Pair> trailHeads;

    while (getline(f, line)){
        stringstream s(line);
        vector<int> v;
        for (int i=0; i<line.size(); i++) {
            v.push_back(line[i]-48);
        }
        chart.push_back(v);
    }

    for(int i=0; i<chart.size(); i++) {
        for(int j=0; j<chart[0].size(); j++) {
            cout << chart[i][j];
            if(chart[i][j] == 0) {
                Pair p = {i,j};
                trailHeads.push_back(p);
            }
        }
        cout << "\n";
    }

    // Test all trailHeads.
    // Create a stack to keep up with next locations and 
    // an unsorted_set to keep up with what has been visited.
    int sum = 0;
    for (int i=0; i<trailHeads.size(); i++) {
        unordered_set<Pair, Pair::Hash> us;
        stack<Pair> stack;
        Pair trailHead = {trailHeads[i].y, trailHeads[i].x};
        stack.push(trailHead);

        while(stack.size() != 0) {
            Pair p = stack.top();
            stack.pop();


            if(chart[p.y][p.x] == 9) {
                sum++;
            } else {
                explore(chart, us, stack, p);
            }            
        }
    }

    int sum2 = 0;
    for (int i=0; i<trailHeads.size(); i++) {
        stack<Pair> stack;
        Pair trailHead = {trailHeads[i].y, trailHeads[i].x};
        stack.push(trailHead);

        while(stack.size() != 0) {
            Pair p = stack.top();
            stack.pop();

            if(chart[p.y][p.x] == 9) {
                sum2++;
            } else {
                exploreAllPaths(chart, stack, p);
            }            
        }
    }

    cout << sum << "\n";
    cout << sum2 << "\n";


    return(0);
}

