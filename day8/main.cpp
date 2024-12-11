#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string>
#include <cmath>

using namespace std;

struct Pair {
    int y;
    int x;
};

void createAntiNodes(vector<vector<bool>> &chart, vector<Pair> nodes) {
    // for each node
    for (int i=0; i<nodes.size();  i++) {
        // pair with remaining nodes
        for (int j=i+1; j<nodes.size(); j++) {

            // added for part 2
            chart[nodes[i].y][nodes[i].x] = '#';
            chart[nodes[j].y][nodes[j].x] = '#';

            Pair diff = {nodes[i].y - nodes[j].y, nodes[i].x - nodes[j].x};
            Pair aAnti = {nodes[i].y + diff.y, nodes[i].x + diff.x};
            Pair bAnti = {nodes[j].y - diff.y, nodes[j].x - diff.x,};

            cout << nodes[i].y << " " << nodes[i].x << "\n";
            cout << nodes[j].y << " " << nodes[j].x << "\n";

            cout << aAnti.y << " " << aAnti.x << "\n";
            cout << bAnti.y << " " << bAnti.x << "\n";

            // check if A antinode is on the chart
            // change from if to while for part 2
            while(aAnti.x >= 0 &&
               aAnti.x < chart[0].size() &&
               aAnti.y >= 0 &&
               aAnti.y < chart.size()) {
                chart[aAnti.y][aAnti.x] = '#';
                // added for part 2 (continuous anti nodes instead of a single one per pair)
                aAnti.y += diff.y;
                aAnti.x += diff.x;
            }

            // check if B antinode is on the chart
            while(bAnti.x >= 0 &&
               bAnti.x < chart[0].size() &&
               bAnti.y >= 0 &&
               bAnti.y < chart.size()) {
                chart[bAnti.y][bAnti.x] = '#';
                bAnti.y -= diff.y;
                bAnti.x -= diff.x;
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
    vector<vector<char>> chart;

    while (getline(f, line)){
        stringstream s(line);
        vector<char> v;
        for (char &c : line) {
            v.push_back(c);
        }
        chart.push_back(v);
    }



    unordered_map<char, vector<Pair>> um;
    for(int i=0; i<chart.size(); i++) {
        for(int j=0; j<chart[0].size(); j++) {
            cout << chart[i][j];
            if( chart[i][j] != '.') {
                Pair pair = {i, j};
                um[chart[i][j]].emplace_back(pair);
            }
        }
        cout << "\n";
    }


    vector<vector<bool>> boolChart(chart.size(), vector<bool> (chart[0].size(), false));
    cout << um.size() << "\n";
    for (const auto& kv: um) {
        char c = kv.first;
        vector<Pair> nodes = kv.second;
        cout << nodes.size() << '\n';

        createAntiNodes(boolChart, nodes);
    }

    int sum = 0;
    for (const auto &row : boolChart) {
        for (const auto &b : row) {
            if(b) {
                cout << '#';
                sum++;
            } else {
                cout << '.';
            }
        }
        cout << "\n";
    }

    cout << sum << "\n";
    return(0);
}

