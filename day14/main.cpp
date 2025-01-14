#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string>
#include <cmath>
#include "../common/pair.h"
#include <regex>
#include<unistd.h>


using namespace std; 

#define WIDTH 101
#define HEIGHT 103

void printGrid(vector<vector<int>>& grid) {
    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid[0].size(); j++) {
            cout << grid[i][j];
        }
        cout << "\n";
    }
}

// Initialize direction vectors
int dRow[] = { 0, 1, 0, -1 };
int dCol[] = { -1, 0, 1, 0 };

bool isValid(vector<vector<int>>& grid, Pair p) {

    if (p.y < 0 || p.x < 0 || p.y >= HEIGHT || p.x >= WIDTH) {
        return false;
    }
 
    if (grid[p.y][p.x] == 0) {
        return false;
    }
 
    return true;
}

void dfs(vector<vector<int>>& grid, Pair p, int& count) {

    grid[p.y][p.x] = 0;

    for (int i=0; i<4; i++) {
        int row = p.y + dRow[i];
        int col = p.x + dCol[i];

        Pair p(row,col);
        if(!isValid(grid, p)) {
            continue;
        }

        count++;
        dfs(grid, p, count);
    }
}

int findSize(vector<vector<int>> grid) {

    Pair start(0,0);

    // find starting point
    bool found = false;
    int largest = 0;
    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid[0].size(); j++) {
            if (grid[i][j] == 1) {
                start.y = i;
                start.x = j;
                int count = 1;
                dfs(grid, start, count);
                if (count > largest) {
                    largest = count;
                }
            }
        }
    }


    return largest;
}

void updateGrid(vector<vector<int>>& grid, vector<vector<int>>& guards) {
    
    // subtract from grid
    for (int i=0; i<guards.size(); i++) {
        int c = guards[i][0];
        int r = guards[i][1];
        grid[r][c]--;
    }

    // update guards
    for (int i=0; i<guards.size(); i++) {
        // update the position of the guards
        guards[i][0] = (((guards[i][0] + (guards[i][2])) % WIDTH) + WIDTH)%WIDTH;
        guards[i][1] = (((guards[i][1] + (guards[i][3])) % HEIGHT) + HEIGHT)%HEIGHT;
    }
    
    // add to grid
    for (int i=0; i<guards.size(); i++) {
        int c = guards[i][0];
        int r = guards[i][1];
        grid[r][c]++;
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

    regex pattern("-?\\d+");
    vector<vector<int>> guards;

    while (getline(f, line)){

        sregex_iterator it(line.begin(), line.end(), pattern);
        sregex_iterator end;
        vector<int> guard;

        while (it != end) {
            smatch match = *it;
            ++it;
            guard.push_back(stoi(match.str()));
        }
        guards.push_back(guard);
    }

    for(int i=0; i<guards.size(); i++) {
        for(int j=0; j<guards[0].size(); j++) {
        //    cout << guards[i][j] << " ";
        }
        //cout << "\n";
    }



    // part 1
    /*
    vector<int> quadrants(4, 0); 

    for (int i=0; i<guards.size(); i++) {
        // update the position of the guards
        guards[i][0] = (((guards[i][0] + (100 * guards[i][2])) % width) + width)%width;
        guards[i][1] = (((guards[i][1] + (100 * guards[i][3])) % height) + height)%height;

        cout << guards[i][0] << " " << guards[i][1] << "\n";

        // update quadrants count
        if (guards[i][0] < width/2) {
            if (guards[i][1] < height/2) {
                quadrants[0]++;
            } else if (guards[i][1] > height/2) {
                quadrants[1]++;
            }
        } else if (guards[i][0] > width/2) {
            if (guards[i][1] < height/2) {
                quadrants[2]++;
            } else if (guards[i][1] > height/2) {
                quadrants[3]++;
            }
        }
    }

    int sum = 1;
    for(int i=0; i<quadrants.size(); i++) {
        sum *= quadrants[i];
        cout << quadrants[i] << " ";
    }

    cout << sum << "\n";
    */

    // create grid
    vector<vector<int>> grid(
        HEIGHT,
        vector<int>(WIDTH, 0)
    );

    // init grid
    for (int i=0; i<guards.size(); i++) {
        int c = guards[i][0];
        int r = guards[i][1];
        grid[r][c]++;
    }

    unsigned int microsecond = 250000;

    vector<vector<int>> originalGuards = guards;

    int seconds = 1;
    int largest = 0;
    vector<int> quadrants(4, 0); 
    while(true) {

        //printGrid(grid);
        updateGrid(grid, guards);

        if (guards == originalGuards) {
            cout << seconds << "\n";
            break;
        }

        int size = findSize(grid);
        if(size > largest) {
            largest = size;
        }
        //cout << "size: " <<  size << "\n";
        if (size == guards.size()) {
            cout << seconds << "\n";
            cout << size << "\n";
        }

        if (size == 229) {
            printGrid(grid);
            cout << seconds << "\n";
        }
    
       //printGrid(grid);
        seconds++;

        //usleep(1 * microsecond);//sleeps for 3 second
        //system("clear"); // Clears the terminal

        if(seconds == 101) {
            // update quadrants count
            for (int i=0; i<guards.size(); i++) {
                if (guards[i][0] < WIDTH/2) {
                    if (guards[i][1] < HEIGHT/2) {
                        quadrants[0]++;
                    } else if (guards[i][1] > HEIGHT/2) {
                        quadrants[1]++;
                    }
                } else if (guards[i][0] > WIDTH/2) {
                    if (guards[i][1] < HEIGHT/2) {
                        quadrants[2]++;
                    } else if (guards[i][1] > HEIGHT/2) {
                        quadrants[3]++;
                    }
                }
            }

            int sum = 1;
            for(int i=0; i<quadrants.size(); i++) {
                sum *= quadrants[i];
                cout << quadrants[i] << " ";
            }

            cout << "PART1 SUM:" << sum << "\n";
        }
    }

    return(0);
}

