#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string>
#include <cmath>

using namespace std;

void decToTernary(int decimal, vector<int> &v) {

   if ( decimal < 3 )
   {
      v.push_back(decimal);
      return;
   }

   int rem = decimal % 3;
   decToTernary(decimal/3, v);

   v.push_back(rem);
}

int main() {

    // input
    ifstream f("input.txt");

    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return 1;
    }

    string line;
    vector<unsigned long int> answers;
    vector<vector<unsigned long int>> equations;

    while (getline(f, line)){

        int pos = line.find(":");
        line.erase(pos, 1);
        stringstream s(line);

        string word;
        s >> word;
        answers.push_back(stoul(word));
        vector<unsigned long int> v;
        while (s >> word) {
            v.push_back(stoi(word));
        }
        equations.push_back(v);
    }

    /*
    for(auto &i : answers) {
        cout << i << "\n";
    }

    for(auto &v : equations) {
        for(auto &i : v) {
            cout << i << " ";
        }
        cout << "\n";
    }
    */

   /*
    int sum = 0;
    // Try each combination of (+/*) on the equations. Check each combination for equality to its corresponding value in answers.
    for (int i=0; i<equations.size(); i++) {

        int numberOfCombinations = pow(2, equations[i].size()-1);
        for (int j=0; j<numberOfCombinations; j++) {
            long int total = equations[i][0];
            for( int k=1; k<equations[i].size(); k++) {
                    int mask =  1 << (k-1);
                    int masked_n = j & mask;
                    bool bit = masked_n >> (k-1);

                    if(bit) {
                        total += equations[i][k];
                    } else {
                        total *= equations[i][k];
                    }
            }
            if(total == answers[i]) {
                //cout << "found: " << i << "\n";
                sum += answers[i];
                break;
            }
        }
    }

    long int sum2 = 0;
        // Try each combination of (+/*) on the equations. Check each combination for equality to its corresponding value in answers.
    for (int i=0; i<equations.size(); i++) {
        int numberOfCombinations = pow(2, equations[i].size()-1);
        for (int j=0; j<numberOfCombinations; j++) {
            long int total = answers[i];
            for( int k=equations[i].size()-1; k>0; k--) {
                    int mask =  1 << (k-1);
                    int masked_n = j & mask;
                    bool bit = masked_n >> (k-1);

                    if (bit) {
                        total -= equations[i][k];
                    } else {
                        if(total % equations[i][k] != 0) {
                            break;
                        }
                        total /= equations[i][k];
                    }
            }
            if(total == equations[i][0]) {
                cout << "found: " << answers[i] << "\n";
                sum2 += answers[i];
                break;
            }
        }
    }
    */


    long int sum3 = 0;
    int count = 0;
    // Try each combination of (+/*/||) on the equations. Check each combination for equality to its corresponding value in answers.
    for (int i=0; i<equations.size(); i++) {
        int numberOfCombinations = pow(3, equations[i].size()-1);
        for (int j=0; j<numberOfCombinations; j++) {
            vector<unsigned long int> v = equations[i];
            for( int k=0; k<equations[i].size()-1; k++) {

                    vector<int> ternary;
                    decToTernary(j, ternary);
                    reverse(ternary.begin(), ternary.end());
                    int ternary_bit;
                    if(k > ternary.size()-1) {
                        ternary_bit = 0;
                    } else {
                        ternary_bit = ternary[k];
                    }

                    if (ternary_bit == 0) {
                        v[k+1] += v[k];
                    } else if(ternary_bit == 1) {
                        // edge case for init and multiplication
                        v[k+1] *= v[k];
                    } else if(ternary_bit == 2) {
                        
                        string a = to_string(v[k]);
                        string b = to_string(v[k+1]);
                        string c =  a + b;

                        v[k+1] = stoul(c);
                    }
            }
            //cout << v[v.size()-1];
            //cout << "\n";
            if(v[v.size()-1] == answers[i]) {
                //cout << "found: " << answers[i] << "\n";
                sum3 += answers[i];
                break;
            }
        }
        cout << count++ << "\n";
    }

    //cout << sum << "\n";
    //cout << sum2 << "\n";
    cout << sum3 << "\n";
    return(0);
}

