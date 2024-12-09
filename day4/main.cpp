#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <regex>

using namespace std;

void dfs(vector<vector<char>> &chart, int depth, int direction, int r, int c, int &count);
bool checkForX(vector<vector<char>> chart, int r, int c);

int main() {

    // input
    ifstream f("input.txt");

    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return 1;
    }

    string line;
    vector<vector<char>> chart;


    while (getline(f, line)){
        vector<char> row;
        
        for (char &c : line) {
            row.push_back(c);
        }

        chart.push_back(row);
    }

    // On each letter start a string and depth first search if the letter is correct.
    int count = 0;
    for (int i=0; i<chart.size(); i++) {
        for (int j=0; j<chart[0].size(); j++) {
            if(chart[i][j] == 'X') {
                dfs(chart, 0, 0, i, j, count);
            }
        }
    }

    cout << count << "\n";
    int count2 = 0;
    // on each A look for an M/A pair on the diagonals
    for (int i=0; i<chart.size(); i++) {
        for (int j=0; j<chart[0].size(); j++) {
            if(chart[i][j] == 'A') {
                if(checkForX(chart, i, j)) {
                    count2++;
                    cout << i << " " << j << "\n";
                }
            }
        }
    }

    cout << count2 << "\n";
    return(0);
}

bool checkForX(vector<vector<char>> chart, int r, int c) {
    
    unordered_set<char> us;
    us.insert('M');
    us.insert('S');
    unordered_set<char>::iterator got;
    // check up-right
    if (r != 0 && c != chart[0].size()-1) {
        got = us.find(chart[r-1][c+1]);
        if(got == us.end()) {
            return false;
        } else {
            us.erase(chart[r-1][c+1]);
        }
    } else {
        return false;
    }

    // check down-left
    if (r != chart.size()-1 && c != 0) {
        got = us.find(chart[r+1][c-1]);
        if(got == us.end()) {
            return false;
        } else {
            us.erase(chart[r+1][c-1]);
        }
    } else {
        return false;
    }

    // reset the unordered set for the other cross
    us.insert('M');
    us.insert('S');
    // check down-right
    if (r != chart.size()-1 && c != chart[0].size()-1) {
        got = us.find(chart[r+1][c+1]);
        if(got == us.end()) {
            return false;
        } else {
            us.erase(chart[r+1][c+1]);
        }
    } else {
        return false;
    }

    // check up-left
    if (r != 0 && c != 0) {
        got = us.find(chart[r-1][c-1]);
        if(got == us.end()) {
            return false;
        } else {
            us.erase(chart[r-1][c-1]);
        }
    } else {
        return false;
    }

    return true;
}

void dfs(vector<vector<char>> &chart, int depth, int direction, int r, int c, int& count) {
    string xmas = "XMAS";
    if(depth == 3){
        cout << r << " " << c << "\n";
        count++;
    }

    cout << chart[r][c] << " " <<  depth << " " << direction << " " << xmas[depth+1] << "\n";

    // check left
    if (c != 0 && (depth == 0 || direction == 1)) {
        if(chart[r][c-1] == xmas[depth+1]) {
            dfs(chart, depth+1, 1, r, c-1, count);
        }
    }
    // check right
    if (c != chart[0].size()-1 && (direction == 0 || direction == 2)) {
        if(chart[r][c+1] == xmas[depth+1]) {
            dfs(chart, depth+1, 2, r, c+1, count);
        }
    }

    // check up
    if (r != 0 && (direction == 0 || direction == 3)) {
        if(chart[r-1][c] == xmas[depth+1]) {
            dfs(chart, depth+1, 3, r-1, c, count);
        }
    }

    // check down
    if (r != chart.size()-1 && (direction == 0 || direction == 4)) {
        if(chart[r+1][c] == xmas[depth+1]) {
            dfs(chart, depth+1, 4, r+1, c, count);
        }
    }

    // check up-right
    if (r != 0 && c != chart[0].size()-1 && (direction == 0 || direction == 5)) {
        if(chart[r-1][c+1] == xmas[depth+1]) {
            dfs(chart, depth+1, 5, r-1, c+1, count);
        }
    }
    // check down-right
    if (r != chart.size()-1 && c != chart[0].size()-1 && (direction == 0 || direction == 6)) {
        if(chart[r+1][c+1] == xmas[depth+1]) {
            dfs(chart, depth+1, 6, r+1, c+1, count);
        }
    }

    // check down-left
    if (r != chart.size()-1 && c != 0 && (direction == 0 || direction == 7)) {
        if(chart[r+1][c-1] == xmas[depth+1]) {
            dfs(chart, depth+1, 7, r+1, c-1, count);
        }
    }

    // check up-left
    if (r != 0 && c != 0 && (direction == 0 || direction == 8)) {
        if(chart[r-1][c-1] == xmas[depth+1]) {
            dfs(chart, depth+1, 8, r-1, c-1, count);
        }
    }
}