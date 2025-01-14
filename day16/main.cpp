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
    Pair p;
    int distance;
    Direction direction;
    Node* prevNode;

    Node(Pair p, int distance, Direction direction, Node* prevNode = nullptr)
        : p(p), distance(distance), direction(direction), prevNode(prevNode) {}

    Node(const Node* other)
        : p(other->p), 
          distance(other->distance), 
          direction(other->direction), 
          prevNode(other->prevNode) {}

    bool operator<(const Node& other) const {
        if (p < other.p) {
            return true;
        } else if (other.p < p) {
            return false;
        }
        return direction < other.direction;
    }
};

struct CompareNode {
    bool operator()(const Node& n1, const Node& n2) {
        return n1.distance > n2.distance;
    }
};

void dijkstra(vector<vector<char>>& grid, 
         Pair start, 
         Pair end, 
         int& shortest,
         Node* prevNode,
         vector<Node>& endNodes) {

    priority_queue<Node, vector<Node>, CompareNode> pq;
    map<Node, int> addedNodes;

    // init the priority queue
    Node* initialNode = new Node(start, 0, RIGHT, NULL);
    pq.push(*initialNode);

    while(!pq.empty()) {
        Node* node = new Node(pq.top());
        pq.pop();

        //cout << "Pair: (" << node.p.x << ", " << node.p.y << "), Distance: " << node.distance << " Direction: " << node.direction << '\n';

        auto itr = addedNodes.find(node);
        if(itr == addedNodes.end()) {
            addedNodes[node] = node->distance;
        } else if (itr->second == node->distance) {
            // don't "continue"/skip this iteration.
            // This could be another shortest path.
        }
        else {
            continue;
        }

        // end this search if there is no way to be the shortest
        if(node->distance > shortest) {
            break;
        }

        // check if on a wall
        if(grid[node->p.y][node->p.x] == '#') {
            continue;
        }

        // check if reached the end
        if(grid[node->p.y][node->p.x] == 'E') {
            if(node->distance == shortest) {
                endNodes.push_back(node);
            }
            if(node->distance < shortest) {
                endNodes.clear();
                endNodes.push_back(node);
                shortest = node->distance;
            }

            continue;
        }

        // attempt to move forward
        Pair d = directionToPair(node->direction);
        Pair forward(node->p.y + d.y, node->p.x + d.x);
        Node* forwardNode = new Node(forward, node->distance + 1, node->direction, node);
        pq.push(*forwardNode);

        // rotate CW
        Direction cw = rotateCW(node->direction);
        Node* CWNode = new Node(node->p, node->distance + 1000, cw, node);
        pq.push(*CWNode);

        // rotate CCW
        Direction ccw = rotateCCW(node->direction);
        Node* CCWNode = new Node(node->p, node->distance + 1000, ccw, node);
        pq.push(*CCWNode);
    }

    for (int i=0; i<endNodes.size(); i++) {
        Node n = endNodes[i];
        cout << "Pair: (" << n.p.x << ", " << n.p.y << "), Distance: " << n.distance << " Direction: " << n.direction << '\n';
    }

}

int main() {

    // input
    ifstream f("test_input.txt");

    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return 1;
    }

    string line;
    vector<vector<char>> grid;
    Pair start(0,0);
    Pair end(0,0);

    while (getline(f, line)){
        vector<char> v;
        for (int i=0; i<line.size(); i++) {
            v.push_back(line[i]);
            if (line[i] == 'S') {
                start.y = grid.size();
                start.x = i;
            }
            if (line[i] == 'E') {
                end.y = grid.size();
                end.x = i;
            }
        }
        grid.push_back(v);
    }

    int shortest = INT_MAX;
    vector<Node> endNodes;
    dijkstra(grid, start, end, shortest, NULL, endNodes);

    cout << shortest << "\n";

    set<Pair> pSet;

    for (int i=0; i<endNodes.size(); i++) {
        Node* n = &endNodes[i];
        
        while(n != NULL) {
            Pair p(n->p.y, n->p.x);
            cout << p.y << " " << p.x << "\n";
            auto itr = pSet.find(p);
            if(itr == pSet.end()) {
                pSet.insert(p);
            }
            n = n->prevNode;
        }
        cout << "\n";
    }

    cout << pSet.size() << "\n";

    return(0);
}