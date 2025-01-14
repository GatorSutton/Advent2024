#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string>
#include <cmath>
#include "../common/pair.h"

using namespace std; 

#define LENGTH 71

struct Node {
    Pair p;
    int distance;

    Node(Pair p, int distance)
        : p(p), distance(distance) {}
};

struct CompareNode {
    bool operator()(const Node& n1, const Node& n2) {
        return n1.distance > n2.distance;
    }
};

bool checkForCorruption(vector<vector<int>>& grid, Pair p) {
    // check bounds
    if(p.y < 0 || p.y >= LENGTH) {
        return true;
    }
    if(p.x < 0 || p.x >= LENGTH) {
        return true;
    }

    // check corruption or already visited
    if(grid[p.y][p.x] != 0) {
        return true;
    }

    return false;
}

bool dijkstra(vector<vector<int>> grid, Pair start, Pair end) {
    priority_queue<Node, vector<Node>, CompareNode> pq;

    Node s(start, 0);
    pq.push(s);

    while(!pq.empty()) {
        Node n = pq.top();
        pq.pop();

        // check for end
        if(n.p.x == end.x && n.p.y == end.y) {
            cout << "Distance: " << n.distance << "\n";
            return true;
        }

        // Check for corruption and bounds
        if(checkForCorruption(grid, n.p)) {
            continue;
        }

        // set square as visited
        grid[n.p.y][n.p.x] = 1;

        // up
        Pair p_up(n.p.y-1, n.p.x);
        Node up(p_up, n.distance+1);
        pq.push(up);

        // down
        Pair p_down(n.p.y+1, n.p.x);
        Node down(p_down, n.distance+1);
        pq.push(down);

        // left
        Pair p_left(n.p.y, n.p.x-1);
        Node left(p_left, n.distance+1);
        pq.push(left);

        // right
        Pair p_right(n.p.y, n.p.x+1);
        Node right(p_right, n.distance+1);
        pq.push(right);
    }

    return false;
}

int main() {

    // input
    ifstream f("input.txt");

    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return 1;
    }

    string line;
    regex pattern("-?\\d+");
    vector<Pair> points;

    while (getline(f, line)){

        sregex_iterator it(line.begin(), line.end(), pattern);
        sregex_iterator end;
        Pair point(0,0);

        while (it != end) {
            smatch match = *it;
            ++it;


            if(it == end) {
                point.y = stoi(match.str());
            } else {
                point.x = stoi(match.str());
            }
 
        }
        points.push_back(point);
    }

    vector<vector<int>> grid(
        LENGTH,
        vector<int>(LENGTH));
    for(int i=0; i<1024; i++) {
        cout << points[i].x << " " << points[i].y << "\n";
        grid[points[i].y][points[i].x] = 2;
    }

    for(int i=0; i<grid.size(); i++) {
        for(int j=0; j<grid[0].size(); j++) {
            cout << grid[i][j];
        }
        cout << "\n";
    }


    Pair start(0,0);
    Pair end(grid.size()-1, grid[0].size()-1);


    int i = 1023;
    while( dijkstra(grid, start, end) ) {
        i++;
        grid[points[i].y][points[i].x] = 2;
    }

    cout << points[i].y << " " << points[i].x << "\n";

    return(0);
}