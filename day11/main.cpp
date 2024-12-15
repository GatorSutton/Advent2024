#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string>
#include <cmath>
#include <boost/multiprecision/integer.hpp>

using namespace std;
using namespace boost::multiprecision;

void printRocks(list<unsigned long int> rocks) {
    cout << "\n";
    list<unsigned long int>::iterator it;
    for (it = rocks.begin(); it != rocks.end(); it++) {
        cout << *it << " ";
    }
    cout << "\n";
}

void splitDigit(vector<int> v, unsigned long int& a, unsigned long int& b) {
    for (int i=0; i<v.size()/2; i++) {
        b += v[i] * pow(10, i);
    }

    for (int i=v.size()/2; i<v.size(); i++) {
        a += v[i] * pow(10, i-v.size()/2);
    }
}

int countDigits(unsigned long int n, vector<int>& v) {
    // this will never happen
    if (n == 0) {
        return 1;
    }

    int numOfDigits = 0;

    while (n != 0) {
        v.push_back(n%10);
        n = n/10;
        numOfDigits++;
    }

    return numOfDigits;
}

vector<unsigned long int> solveRock(unsigned long int rock) {
     vector<unsigned long int> v;

    // Check for value 0
    if (rock == 0) {
        rock = 1;
        v.push_back(rock);
        return v;
    }

    // Check for even number of digits
    unsigned long int number = rock;
    vector<int> splitVector;
    int numOfDigits = countDigits(number, splitVector);
    if (numOfDigits % 2 == 0) {
        unsigned long int a = 0;
        unsigned long int b = 0;
        splitDigit(splitVector, a, b);
        v.push_back(a);
        v.push_back(b);
        return v;
    }

    // Multiply by 2024
    v.push_back(rock*2024);
    return v;
}

unordered_map<unsigned long int, 
    unordered_map<unsigned long int, unsigned long int>>  um;

unsigned long int calculateFutureRock(unsigned long int rock, 
                                      int distanceIntoFuture,
                                      unordered_map<unsigned long int,
                                      unordered_map<unsigned long int, unsigned long int>>& um) {

    unsigned long int count = 0;

    if(distanceIntoFuture == 0) {
        return 1;
    }

    if(um[rock].find(distanceIntoFuture) != um[rock].end()) {
        //cout << "found" << "\n";
        return um[rock][distanceIntoFuture];
    } else {
        vector<unsigned long int> v = solveRock(rock);
        count += calculateFutureRock(v[0], --distanceIntoFuture, um);
        if(v.size() == 2) {
            count += calculateFutureRock(v[1], distanceIntoFuture, um);
        }
    }

    um[rock][++distanceIntoFuture] = count;

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
    list<unsigned long int> rocks;

    while (getline(f, line)){
        stringstream s(line);
        string word;
        while(s >> word) {
            rocks.push_back(stoi(word));
        }
    }


    unsigned long int sum = 0;
    while(rocks.size() != 0) {
        sum += calculateFutureRock(rocks.front(), 75, um);
        rocks.pop_front();
    }

/*
    for (auto i = um.begin(); i!= um.end(); i++) {
        auto distanceMap = i->second;
        cout << i->first << ": ";
        int count = 0;
        for (auto j = distanceMap.begin(); j != distanceMap.end(); j++) {
            cout << j->first << "," << j->second << " ";
            count ++;
            if(count % 10 == 0) {
                cout << "\n";
            }
        }
        cout << "\n";
    }
*/

    cout << sum << "\n";

    return(0);
}















/*
    list<unsigned long int>::iterator it;
    unordered_map<unsigned long int, vector<unsigned long int>> um;
    int count = 0;
    int numberOfBlinks = 6;
for (int i=0; i<numberOfBlinks; i++) {
    for (it = rocks.begin(); it != rocks.end(); it++) {
        if (um.find(*it) != um.end()) {
            //cout << "insert" << "\n";
            rocks.insert(it, um[*it].begin(), um[*it].end());
            vector<unsigned long int> v= um[*it];
            it = rocks.erase(it);
            it--;
        } else {
            solveRockUpdateRocks(rocks, it, um);
        }
    }
}


void solveRockUpdateRocks(list<unsigned long int>& rocks, 
               list<unsigned long int>::iterator& it, 
               unordered_map<unsigned long int, vector<unsigned long int>>& um) {

    vector<unsigned long int> v;

    // Check for value 0
    if (*it == 0) {
        *it = 1;
        v.push_back(*it);
        um[0] = v;
        return;
    }

    // Check for even number of digits
    unsigned long int number = *it;
    vector<int> splitVector;
    int numOfDigits = countDigits(number, splitVector);
    if (numOfDigits % 2 == 0) {
        unsigned long int a = 0;
        unsigned long int b = 0;
        splitDigit(splitVector, a, b);
        v.push_back(a);
        v.push_back(b);
        um[*it] = v;
        it = rocks.erase(it);
        rocks.insert(it, a);
        rocks.insert(it, b);
        it--;
        return;
    }

    // Multiply by 2024
    int prev = *it;
    *it *= 2024;
    v.push_back(*it);
    um[prev] = v;
 
}
*/

