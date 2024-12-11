#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string>
#include <cmath>

using namespace std;

struct Data {
    int id;
    int startPos;
    int length;
};

int main() {

    // input
    ifstream f("input.txt");

    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return 1;
    }

    string line;
    vector<int> files;
    vector<Data> free;
    vector<Data> data;

    while (getline(f, line)){
        stringstream s(line);
        cout << line << "\n";
        int pos = 0;
        int id = 0;
        for (int i=0; i<line.size(); i++){
            // Add files if i is even.
            // Add free space if i is odd.
            int length = line[i] - 48;
            if (i%2 == 0) {
                Data d{id, pos, length};
                data.push_back(d);
                for (int j=0; j<length; j++) {
                    files.push_back(id);
                    pos++;
                }
                id++;
            } else {
                Data d{-1, pos, length};
                free.push_back(d);
                for (int j=0; j<length; j++) {
                    files.push_back(-1);
                    pos++;
                }
            }
        }
    }

    vector<int> files2 = files;

    cout << "\n";
    for (int i=0; i<files.size(); i++) {
        if(files[i] >= 0)
            cout << files[i];
        else {
            cout << '.';
        }
    }
    cout << "\n";

    // Create a pointer to the start of the filesystem and one to the end of the files system. 
    // Move the beginning pointer forward if its not on empty space.
    // Move the end pointer backwards if its not on data.
    // When both are at a correct location, move the data to the empty space.
    // When they point to the same spot, terminate.

    int a = 0;
    int b = files.size()-1;

    while(a != b) {

        // find empty space
        if (files[a] != -1) {
            a++;
            continue;
        }

        // find files
        if (files[b] == -1) {
            b--;
            continue;
        }

        files[a] = files[b];
        files[b] = -1;
    }

    cout << "\n";
    unsigned long int sum = 0;
    for (int i=0; i<files.size(); i++) {
        if(files[i] >= 0) {
            cout << files[i];
            sum += i * files[i];
        }
        else {
            cout << '.';
        }
    }
    cout << "\n";
    cout << sum << "\n";

    for (int i=0; i<data.size(); i++) {
        cout << data[i].id << " "
             << data[i].length << " "
             << data[i].startPos << "\n";
    }

    for (int i=0; i<free.size(); i++) {
        cout << free[i].id << " "
             << free[i].length << " "
             << free[i].startPos << "\n";
    }

    // Loop backwards through the data vector 
    // For each piece of data search for the earliest spot in the free vector 
    // Move the data vector into free2 and erase the spot in free vector

    for (int i=data.size()-1; i>=0; i--) {
        for (int j=0; j<free.size(); j++) {
            // check if the data fits and its at an earlier positions
            if(data[i].length <= free[j].length &&
                free[j].startPos < data[i].startPos) {
                // write the data
                int freeStart = free[j].startPos;
                cout << freeStart << "\n";
                for (int k=freeStart; k<data[i].length + freeStart; k++) {
                    files2[k] = data[i].id;
                }

                // clear the old data
                int dataStart = data[i].startPos;
                for (int k=dataStart; k<data[i].length + dataStart; k++) {
                    files2[k] = -1;
                }

                // update the free vector
                free[j].length -= data[i].length;
                free[j].startPos += data[i].length;

                // move onto the next file in data
                break;
            }
        }
    }

    unsigned long int sum2 = 0;
    for (int i=0; i<files2.size(); i++) {
        if(files2[i] >= 0) {
            cout << files2[i];
            sum2 += files2[i] * i;
        }
        else {
            cout << '.';
        }
    }
    cout << "\n";
    cout << sum2 << "\n";

    return(0);
}

