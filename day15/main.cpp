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

void printGrid(vector<vector<char>>& grid) {
    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid[0].size(); j++) {
            cout << grid[i][j];
        }
        cout << "\n";
    }
}

void dfs(vector<vector<char>>& grid, 
         char d, 
         Pair p, 
         bool& wiggleRoom, 
         unordered_set<Pair, Pair::Hash>& boxes) {
    
    Pair direction = charToDirection(d);

    if(!wiggleRoom) {
        return;
    }

    if(grid[p.y][p.x] == '#') {
        wiggleRoom = false;
        return;
    }

    if(grid[p.y][p.x] == '.') {
        return;
    }

    int yOffset = 0;
    if (d == 'v') {
        yOffset = 1;
    }
    if (d == '^') {
        yOffset = -1;
    }

    // Check above/below
    Pair direct(p.y+yOffset, p.x);
    dfs(grid, d, direct, wiggleRoom, boxes);

    // Only check directly above/below on the player
    if(grid[p.y][p.x] == '@') {
        return;
    }

    if(grid[p.y][p.x] == ']') {
        Pair other(p.y,p.x-1);
        auto got = boxes.find(other);
        if (got == boxes.end()) {
            Pair left(p.y+yOffset, p.x-1);
            dfs(grid, d, left, wiggleRoom, boxes);
            boxes.insert(other);
        }
    }

    if(grid[p.y][p.x] == '[') {

        auto got = boxes.find(p);
        if (got == boxes.end()) {
            Pair right(p.y+yOffset, p.x+1);
            dfs(grid, d, right, wiggleRoom, boxes);
            boxes.insert(p);
        }
    }
}

// Used for vertical movement on part 2.
void updateWideGrid(vector<vector<char>>& grid, char d, Pair& player) {
    Pair direction = charToDirection(d);

    // depth first search all affected boxes
    // return true if all tails have room to move
    bool wiggleRoom = true;
    unordered_set<Pair,Pair::Hash> boxes;
    // only dfs the boxes remove the player
    dfs(grid, d, player, wiggleRoom, boxes);

    // move the player and the boxes
    if (wiggleRoom) {

        // move the boxes
        for(auto itr = boxes.begin(); itr != boxes.end(); itr++) {
            Pair box = *itr;
            grid[box.y][box.x] = '.';
            grid[box.y][box.x+1] = '.';

        }
        for(auto itr = boxes.begin(); itr != boxes.end(); itr++) {
            Pair box = *itr;
            grid[box.y + direction.y][box.x + direction.x] = '[';
            grid[box.y + direction.y][box.x + direction.x+1] = ']';
        }

        // move the player
        grid[player.y][player.x] = '.';
        player.y += direction.y;
        player.x += direction.x;
        grid[player.y][player.x] = '@';
    }
}

void updateGrid(vector<vector<char>>& grid, char d, Pair& player) {
    Pair direction = charToDirection(d);

    // check for length of boxes in front of the player
    int length = 0;
    Pair nextPair(player.y + direction.y, player.x + direction.x);
    char nextObject = grid[nextPair.y][nextPair.x];

    while(nextObject == ']' || nextObject == '[') {
        length++;
        nextPair.y += direction.y;
        nextPair.x += direction.x;
        nextObject = grid[nextPair.y][nextPair.x];
    }

    // part 1
    // No wall detected. Move all boxes in front of player.
    /*
    if(nextObject == '.') {
        grid[player.y][player.x] = '.';
        nextPair.y = player.y + direction.y;
        nextPair.x = player.x + direction.x;
        grid[nextPair.y][nextPair.x] = '@';
        player.y = nextPair.y;
        player.x = nextPair.x;

        for (int i=0; i<length; i++) {
            nextPair.y += direction.y;
            nextPair.x += direction.x;
            grid[nextPair.y][nextPair.x] = 'O';
        }
    }
    */
    if(nextObject == '.') {
        for (int i=0; i<=length; i++) {
            grid[nextPair.y][nextPair.x] = grid[nextPair.y - direction.y][nextPair.x - direction.x];
            nextPair.y -= direction.y;
            nextPair.x -= direction.x;
        }

        grid[player.y][player.x] = '.';
        player.y += direction.y;
        player.x += direction.x;
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
    vector<vector<char>> grid;
    vector<char> directions;
    Pair player(0,0);

    bool gridFinish = false;
    while (getline(f, line)){
        if(line == "") {
            gridFinish = true;
        }

        if (!gridFinish) {
            vector<char> v;
            for (int i=0; i<line.size(); i++) {
                // change for part 2
                //v.push_back(line[i]);

                if(line[i] == '@') {
                    player.x = i*2;
                    player.y = grid.size();
                    v.push_back('@');
                    v.push_back('.');
                }
                if(line[i] == 'O') {
                    v.push_back('[');
                    v.push_back(']');
                }
                if(line[i] == '.') {
                    v.push_back('.');
                    v.push_back('.');
                }
                if(line[i] == '#') {
                    v.push_back('#');
                    v.push_back('#');
                }
            }
            grid.push_back(v);
        } else {
            for (auto &ch : line) {
                directions.push_back(ch);
            }
        }
    }

    system("clear");
    printGrid(grid);


    unsigned int second = 100000;
    // part 1
    /*
    for (int i=0; i<directions.size(); i++) {
        usleep(1 * second);
        system("clear");
        updateGrid(grid, directions[i], player);
        printGrid(grid);
    }
    */

   // part 2

   for (int i=0; i<directions.size(); i++) {

        if (directions[i] == '<' || directions[i] == '>') {
            updateGrid(grid, directions[i], player);
        } else {
            updateWideGrid(grid, directions[i], player);
        }
        //usleep(1 * second);
        //system("clear");
        //printGrid(grid);
   }

    unsigned long int sum = 0;
    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid[0].size(); j++) {
            if(grid[i][j] == '[') {
                sum += 100 * i + j;
            }
        }
    }

    cout << sum << "\n";

    return(0);
}