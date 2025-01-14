#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string>
#include <cmath>
#include "../common/pair.h"

// Help was used from https://youtu.be/-5J-DAsWuJc.

using namespace std; 

int main() {

    // input
    ifstream f("input.txt");

    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return 1;
    }

    string line;
    vector<Pair> buttonA;
    vector<Pair> buttonB;
    vector<Pair> prize;
    
    // Grab 3rd and 4th word from each line
    // Remove non number characters
    // line 0 is button A, line 1 is button B, line 2 is prize, line 3 is blank.
    int count=0;
    while (getline(f, line)){

        if (count % 4 == 3) {
            count++;
            continue;
        }

        stringstream s(line);
        string word;
        string wordX;
        string wordY;
        s >> word;
        if (count %4 != 2)
        s >> word;
        s >> wordX;
        s >> wordY;

        wordX.erase(remove_if(wordX.begin(),
                              wordX.end(),
                              [](unsigned char c) { return !isdigit(c); }),
                              wordX.end());

        wordY.erase(remove_if(wordY.begin(),
                            wordY.end(),
                            [](unsigned char c) { return !isdigit(c); }),
                            wordY.end());

        int x = stoi(wordX);
        int y = stoi(wordY);
        Pair p = {y, x};

        // Button A
        if (count % 4 == 0) {
            buttonA.push_back(p);
        }

        // Button B
        if (count % 4 == 1) {
            buttonB.push_back(p);
        }

        // Prize
        if (count % 4 == 2) {
            prize.push_back(p);
        }

        count++;
    }

    unsigned long int sum = 0;
    
    for(int i=0; i<prize.size(); i++) {
        long int s,t;
        long int px = prize[i].x;
        long int py = prize[i].y;
        long int ax = buttonA[i].x;
        long int ay = buttonA[i].y;
        long int bx = buttonB[i].x;
        long int by = buttonB[i].y;

        px += 10000000000000;
        py += 10000000000000;

        // Check for non integer values of s and t.
        long int mod = (px*by - py*bx)%(ax*by-ay*bx);
        if(mod != 0) {
            continue;
        }

        s = (px*by - py*bx)/(ax*by-ay*bx);

        long int mod_t = (px-ax*s)%bx;
        if(mod_t != 0) {
            continue;
        }
        t = (px-ax*s)/bx;
        
        
        cout << i << "\n";
        cout << px << " " << py << "\n";
        cout << ax << " " << ay << " " << bx << " " << by << "\n";
        cout << s << " " << t << "\n";
        cout << s*ax + t*bx << " " << s*ay + t*by << "\n";
        cout << mod << "\n\n";
        
        sum += (s*3) + t;
    }

    cout << sum << "\n";
    return(0);
}