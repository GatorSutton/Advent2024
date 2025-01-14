#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string>
#include <cmath>
#include "../common/pair.h"
#include "../common/grid.h"

using namespace std; 

struct Node {
    int distanceToStart;
    int distanceToEnd;
    char c;

    Node(int distanceToStart, int distanceToEnd, char c)
        :distanceToStart(distanceToStart), distanceToEnd(distanceToEnd), c(c) {}
};

bool checkForValid(vector<vector<Node>>& grid, char c, Pair p) {
    if (p.y < 0 || p.y >= grid.size()) {
        return false;
    }

    if (p.x < 0 || p.x >= grid[0].size()) {
        return false;
    }

    if (grid[p.y][p.x].c == '#') {
        return false;
    }

    if (c == 'S') {
        if (grid[p.y][p.x].distanceToStart != INT_MAX) {
            return false;
        }
    }

    if (c == 'E') {
        if (grid[p.y][p.x].distanceToEnd != INT_MAX) {
            return false;
        }
    }

    return true;
}

void labelAllNodes(vector<vector<Node>>& grid, char c, Pair p, int distance)  {

    // Check for out of bounds || wall || already visited
    if(!checkForValid(grid, c, p)) {
        return;
    }

    if (c == 'S') {
        grid[p.y][p.x].distanceToStart = distance;
    }

    if (c == 'E') {
        grid[p.y][p.x].distanceToEnd = distance;
    }

    // Go North.
    labelAllNodes(grid, c, Pair(p.y-1, p.x), distance + 1);

    // Go South.
    labelAllNodes(grid, c, Pair(p.y+1, p.x), distance + 1);

    // Go East.
    labelAllNodes(grid, c, Pair(p.y, p.x+1), distance + 1);

    // Go West.
    labelAllNodes(grid, c, Pair(p.y, p.x-1), distance + 1);

}

bool checkForShortcut(vector<vector<Node>>& grid, int fairDistance, int minTimeSaved, Pair a, Direction d) {
    
    Pair jump = directionToPair(d);
    // b is the wall we are jumping over.
    Pair b(a.y+jump.y, a.x+jump.x);
    // c is the valid tile we are jumping to.
    Pair c(a.y+jump.y*2, a.x+jump.x*2);

    // Check for out of bounds of c. 
    // If this is in bounds, so is b.
    if (c.y < 0 || c.y >= grid.size()) {
        return false;
    }

    if (c.x < 0 || c.x >= grid[0].size()) {
        return false;
    }

    // Check that we are jumping to a valid tile.
    if (grid[c.y][c.x].c == '#') {
        return false;
    }

    // Check that we are jumping over a wall
    if (grid[b.y][b.x].c != '#') {
        return false;
    }

    // Check if the time saved is under minTimeSaved
    Node start = grid[a.y][a.x];
    Node finish = grid[c.y][c.x];
    if (fairDistance - (start.distanceToStart + finish.distanceToEnd + 2) >= minTimeSaved) {
        cout << '\n';
        cout << start.distanceToStart << ' ';
        cout << finish.distanceToEnd << ' ';
        int timeSaved = fairDistance - (start.distanceToStart + finish.distanceToEnd + 2);
        cout << timeSaved << "\n";
        return true;
    }

    return false;
}

int numberOfShortcuts(vector<vector<Node>>& grid, int fairDistance, int minTimeSaved) {

    int count = 0;

    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid[i].size(); j++) {

            Node n = grid[i][j];

            // Check for valid tile.
            if (n.c == 'E' || n.c == '#') {
                continue;
            }

            // Check North.
            if(checkForShortcut(grid, fairDistance, minTimeSaved, Pair(i,j), UP)) {
                count++;
            }

            // Check South.
            if(checkForShortcut(grid, fairDistance, minTimeSaved, Pair(i,j), DOWN)) {
                count++;
            }

            // Check East.
            if(checkForShortcut(grid, fairDistance, minTimeSaved, Pair(i,j), RIGHT)) {
                count++;
            }

            // Check West.
            if(checkForShortcut(grid, fairDistance, minTimeSaved, Pair(i,j), LEFT)) {
                count++;
            }
        }
    }
    return count;
}

int main() {

    // input
    ifstream f("input.txt");

    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return 1;
    }

    string line;
    vector<vector<Node>> grid;
    Pair start(0,0);
    Pair end(0,0);

    while (getline(f, line)){
        vector<Node> v;
        for (int i=0; i<line.size(); i++) {
            Node n(INT_MAX, INT_MAX, line[i]);
            v.push_back(n);
        }
        grid.push_back(v);
    }

    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid[i].size(); j++) {
            cout << grid[i][j].c;
            if (grid[i][j].c == 'S') {
                start.y = i;
                start.x = j;
            }
            if (grid[i][j].c == 'E') {
                end.y = i;
                end.x = j;
            }
        }
        cout << '\n';
    }

    cout << start.y << " " << start.x << "\n";
    cout << end.y << " " << end.x << "\n";

    labelAllNodes(grid, 'S', start, 0);
    labelAllNodes(grid, 'E', end, 0);

    cout << grid[end.y][end.x].distanceToStart << "\n";
    cout << grid[start.y][start.x].distanceToEnd << "\n";

    int fairDistance = grid[end.y][end.x].distanceToStart;

    int n = numberOfShortcuts(grid, fairDistance, 100);
    cout << n << "\n";

    return(0);
}