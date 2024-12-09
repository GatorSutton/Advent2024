#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string>

using namespace std;

enum class Direction { NORTH, SOUTH, EAST, WEST };

unordered_map<Direction, char> directionMap = {
    {Direction::NORTH, '^'},
    {Direction::SOUTH, 'v'},
    {Direction::EAST, '>'},
    {Direction::WEST, '<'}
};

void printChart(vector<vector<char>>& chart) {
    cout << "\n";
        for (vector<char> &row : chart) {
        for (char &c : row) {
            cout << c;
        }
        cout << "\n";
    }
}

bool updatePosition(vector<vector<char>> &chart, Direction &d, int &r, int &c) {
    //chart[r][c] = 'X';

    switch(d) {
        case Direction::NORTH:
            if (r == 0) {
                return false;
            }
            if (chart[r-1][c] == '#') {
                d = Direction::EAST;
                break;
            }
            r--;

            break;
        case Direction::SOUTH:
            if (r == chart.size()-1) {
                return false;
            }
            if (chart[r+1][c] == '#') {
                d = Direction::WEST;
                break;
            }
            r++;

            break;  
        case Direction::EAST:
            if (c == chart[0].size()-1) {
                return false;
            }
            if (chart[r][c+1] == '#') {
                d = Direction::SOUTH;
                break;
            }
            c++;

            break; 
        case Direction::WEST:
            if (c == 0) {
                return false;
            }
            if (chart[r][c-1] == '#') {
                d = Direction::NORTH;
                break;
            }
            c--;

            break; 
        default:
            break;
    }

    return true;
}

class GuardState {

public: 

    Direction dir;
    int row;
    int col;

    GuardState(Direction d, int r, int c) : dir(d), row(r), col(c) {}

    bool operator==(const GuardState& other) const {
        return dir == other.dir &&
               row == other.row &&
               col == other.col;
    }

    struct Hash {
        size_t operator()(const GuardState& obj) const {
            size_t h1 = hash<int>()(static_cast<int>(obj.dir));
            size_t h2 = hash<int>()(obj.row);
            size_t h3 = hash<int>()(obj.col);

            return h1 ^ (h2 << 1) ^ (h3 << 2);
        }
    };

    friend struct Hash;
};

bool loopCalculate(vector<vector<char>> chart, Direction d, int r, int c) {

    // Returning to this state indicates a loop!
    unordered_set<GuardState, GuardState::Hash> us;

    // Update position until the guard leaves the chart or the starting position/direction is found again.
    // You moron. Any repeat position/direction is a loop not just the starting position/direction.
    // printChart(chart);
    // Moron again. You cannot spawn the obstacle during the run it has to exist at the start of the run.
    // Start by brute forcing every spot with an obstacle.


    while (updatePosition(chart, d, r, c)) {
        GuardState gs(d, r, c);
        if (us.find(gs) == us.end()) {
            us.insert(gs);
        } else {
            return true;
        }

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
    vector<vector<char>> chart;

    while (getline(f, line)){
        vector<char> row;
        for (char &c : line) {
            row.push_back(c);
        }
        chart.push_back(row);
    }

    for (vector<char> &row : chart) {
        for (char &c : row) {
            cout << c;
        }
        cout << "\n";
    }

    
    int guard_pos_r;
    int guard_pos_c;
    Direction guard_direction;

    // find the guard position
    for (int i=0; i<chart.size(); i++) {
        for (int j=0; j<chart[0].size(); j++) {
            if (chart[i][j] == directionMap[Direction::NORTH]){
                guard_pos_r = i;
                guard_pos_c = j;
                guard_direction = Direction::NORTH;
            } else if (chart[i][j] == directionMap[Direction::SOUTH]){
                guard_pos_r = i;
                guard_pos_c = j;
                guard_direction = Direction::SOUTH;
            } else if (chart[i][j] == directionMap[Direction::EAST]){
                guard_pos_r = i;
                guard_pos_c = j;
                guard_direction = Direction::EAST;
            } else if (chart[i][j] == directionMap[Direction::WEST]){
                guard_pos_r = i;
                guard_pos_c = j;
                guard_direction = Direction::WEST;
            }
        }
    }

    int sum2=0;
    // while guard is on the screen update his position


    for (int i=0; i<chart.size(); i++) {
        for (int j=0; j<chart[0].size(); j++) {
            cout << i << " " << j << "\n";
            if(chart[i][j] == '.') {
                chart[i][j] = '#';
                if(loopCalculate(chart, guard_direction, guard_pos_r, guard_pos_c)) {
                    sum2++;
                }
                chart[i][j] = '.';
            }
        }
    }

    while (updatePosition(chart, guard_direction, guard_pos_r, guard_pos_c)) {
        //cout << directionMap[guard_direction] << " " << guard_pos_r << " " << guard_pos_c << "\n";
        // generate a new map that calculates loop/no loop if a box were to spawn in front of the guard
    }

    int sum = 0;
    for (vector<char> &row : chart) {
        for (char &c : row) {
            if( c == 'X') {
                sum++;
            }
        }
    }

    cout << sum << "\n";
    cout << sum2 << "\n";

    return(0);
}

