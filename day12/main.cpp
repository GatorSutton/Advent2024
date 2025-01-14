#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string>
#include <cmath>
#include "../common/pair.h"


using namespace std;

// Return a vector<Pair> of horizontal fences
// Return a vector<Pair> of vertical fences
// Sort horizontal fences by y first x second
// Sort vertical fences by x first y second
// Loop through both vectors.
// For horizontal, each time the y axis changes or the x changes by more than 1, increment number of sides.
// For vertical, each time the x axis changes or the y changes by more than 1, increment number of sides.

unsigned long int countVertical(vector<Pair>& verticalSides) {
    // sort by x then y 
    unsigned long int numberOfSides = 1;
    sort(verticalSides.begin(), verticalSides.end(), [](const Pair& a, const Pair& b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });

    Pair prevPair = verticalSides[0];
    for(int i=1; i<verticalSides.size(); i++) {
        if(verticalSides[i].x == prevPair.x &&
           verticalSides[i].y == prevPair.y + 2) {
            prevPair.x = verticalSides[i].x;
            prevPair.y = verticalSides[i].y;
            continue;
        } else {
            numberOfSides++;
        }
        prevPair.x = verticalSides[i].x;
        prevPair.y = verticalSides[i].y;
    }

    return numberOfSides;
}

unsigned long int countHorizontal(vector<Pair>& horizontalSides) {
    // sort by y then x
    unsigned long int numberOfSides = 1;
    sort(horizontalSides.begin(), horizontalSides.end(), [](const Pair& a, const Pair& b) {
        return a.y < b.y || (a.y == b.y && a.x < b.x);
    });

    Pair prevPair = horizontalSides[0];
    for(int i=1; i<horizontalSides.size(); i++) {
        if(horizontalSides[i].y == prevPair.y &&
           horizontalSides[i].x == prevPair.x + 2) {
            prevPair.x = horizontalSides[i].x;
            prevPair.y = horizontalSides[i].y;
            continue;
        } else {
            numberOfSides++;
        }
        prevPair.x = horizontalSides[i].x;
        prevPair.y = horizontalSides[i].y;
    }

    return numberOfSides;
    
}

// Rethink how to calculate the vertical and horizontal sides. 
// Do not use the the bottom of a square needing the fence be the same as
// a square below needing the top of a fence. Double the density of horizontal
// sides and vertical sides to accurately represent the fencing. 0,0 horizontal would
// be above the top left plot, 1,0 would be below the top left plot.

void dfs(vector<vector<char>>& farm,
         vector<vector<bool>>& visited,
         int r, 
         int c,
         unsigned long int& area,
         unsigned long int& perimeter,
         char plant,
         vector<Pair>& horizontalSides,
         vector<Pair>& verticalSides) {

    if(visited[r][c] == true) {
        return;
    }
    visited[r][c] = true;
    area++;

    // check up
    if (r != 0) {
        if (farm[r-1][c] == plant) {
            dfs(farm, visited, r-1, c, area, perimeter, plant, horizontalSides, verticalSides);
        } else {
            perimeter++;
            Pair p = {r*2, c*2};
            horizontalSides.push_back(p);
        }
    } else {
        perimeter++;
        Pair p = {r*2, c*2};
        horizontalSides.push_back(p);
    }

    // check down
    if (r != farm.size()-1) {
        if (farm[r+1][c] == plant) {
            dfs(farm, visited, r+1, c, area, perimeter, plant, horizontalSides, verticalSides);
        } else {
            perimeter++;
            Pair p = {r*2+1, c*2};
            horizontalSides.push_back(p);
        }
    } else {
        perimeter++;
        Pair p = {r*2+1, c*2};
        horizontalSides.push_back(p);
    }

    // check right
    if (c != farm[0].size()-1) {
        if (farm[r][c+1] == plant) {
            dfs(farm, visited, r, c+1, area, perimeter, plant, horizontalSides, verticalSides);
        } else {
            perimeter++;
            Pair p = {r*2, c*2+1};
            verticalSides.push_back(p);
        }
    } else {
        perimeter++;
        Pair p = {r*2, c*2+1};
        verticalSides.push_back(p);
    }

    // check left
    if (c != 0) {
        if (farm[r][c-1] == plant) {
            dfs(farm, visited, r, c-1, area, perimeter, plant, horizontalSides, verticalSides);
        } else {
            perimeter++;
            Pair p = {r*2, c*2};
            verticalSides.push_back(p);
        }
    } else {
        perimeter++;
        Pair p = {r*2, c*2};
        verticalSides.push_back(p);
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
    vector<vector<char>> farm;
    

    while (getline(f, line)){
        stringstream s(line);
        vector<char> row;
        for (auto c : line) {
            row.push_back(c);
        }
        farm.push_back(row);
    }

    vector<vector<bool>> visited(farm.size(), std::vector<bool>(farm[0].size(),false)  );

    for (auto row : farm) {
        for (auto c : row) {
            cout << c;
        }
        cout << "\n";
    }

        for (auto row : visited) {
        for (auto c : row) {
            cout << c;
        }
        cout << "\n";
    }

    // A plot consists of a group of letters that are all touching.
    // The cost of fence is a plot's area x perimeter.
    
    // Loop through every plant.
    // Start a BFS at every plan that is not already a part of a plot.
    // During the BFS pass a perimeter and area variable. Perimeter should check for edges and different plants.
    // Area should just increment.
    // Use the visited 2d vector 

    // vector<Pair> of all starting Positions
    // From the starting position head EAST while always trying to go left (NORTH)
    // When going NORTH fight to go WEST
    // When going WEST fight to go SOUTH
    // When going SOUTH fight to EAST

    vector<Pair> startingPositions;
    vector<unsigned long int> area;
    unsigned long int sum = 0;
    unsigned long int sum2 = 0;
    unsigned long int numberOfSides = 0;



    for (int r=0; r<farm.size(); r++) {
        for (int c=0; c<farm[0].size(); c++) {
            unsigned long int area = 0;
            unsigned long int perimeter = 0;
            if(visited[r][c] == true) {
                continue;
            }

            Pair p = {r,c};
            startingPositions.push_back(p);

            unsigned long int numberOfVerticals = 0;
            unsigned long int numberOfHorizontals = 0;
            vector<Pair> horizontalSides;
            vector<Pair> verticalSides;
            dfs(farm, visited, r, c, area, perimeter, farm[r][c], horizontalSides, verticalSides);
            numberOfHorizontals += countHorizontal(horizontalSides);
            numberOfVerticals += countVertical(verticalSides);
            sum += area * perimeter;
            sum2 += area * (numberOfHorizontals+numberOfVerticals);
            cout << "plant: " << farm[r][c];
            cout << " area: " << area << " perimeter: " << perimeter << "\n";

            cout << "horizontal sides: " << numberOfHorizontals << "\n";
            cout << "vertical sides: " << numberOfVerticals << "\n";

            cout << "vertical sides: \n";
            for(int i=0; i<verticalSides.size(); i++) {
                cout << verticalSides[i].y << " " << verticalSides[i].x << "\n";
            }
            cout << "horizontal sides: \n";
            for(int i=0; i<horizontalSides.size(); i++) {
                cout << horizontalSides[i].y << " " << horizontalSides[i].x << "\n";
            }

            cout << "\n";
            cout << numberOfHorizontals << " " << numberOfVerticals << "\n";
        }
    }

    cout << sum << "\n";
    cout << sum2 << "\n";

    return(0);
}





/*
unsigned long int countSides(vector<vector<char>>& farm, int startingRow, int startingCol) {
    char plant = farm[startingRow][startingCol];
    Direction d = EAST;
    int r = startingRow;
    int c = startingCol;

    do {
        if (checkDirection(static_cast<Direction>((d+1)%4), farm, plant, r, c)) {
            d = static_cast<Direction>((d+1)%4);
        }
        else if (checkDirection(static_cast<Direction>(d), farm, plant, r, c)) {
        }
        else if (checkDirection(static_cast<Direction>((d+3)%4), farm, plant, r, c)) {
            d = static_cast<Direction>((d+3)%4);
        }
        else if (checkDirection(static_cast<Direction>((d+2)%4), farm, plant, r, c)) {
            d = static_cast<Direction>((d+2)%4);
        }

        switch (d) {
            case EAST:
                c++;
                break;
            case NORTH:
                r--;
                break;
            case WEST:
                c--;
                break;
            case SOUTH:
                r++;
                break;
        }

    } while ((r != startingRow) || (c != startingCol));

    return 0;

    enum Direction {
    EAST,
    NORTH,
    WEST,
    SOUTH
};

bool checkDirection(Direction d, vector<vector<char>> farm, char plant, int r, int c) {
    
    switch (d) {
        case EAST:
            if (c == farm[0].size()-1) {
                return false;
            }
            if (farm[r][c+1] == plant) {
                return true;
            }
            break;
        case NORTH:
            if (r == 0) {
                return false;
            }
            if (farm[r-1][c] == plant) {
                return true;
            }
            break;
        case WEST:
            if (c == 0) {
                return false;
            }
            if (farm[r][c-1] == plant) {
                return true;
            }
            break;
        case SOUTH:
            if (r == farm.size()-1) {
                return false;
            }
            if (farm[r+1][c] == plant) {
                return true;
            }
            break;
    }

    return false;
}
}*/