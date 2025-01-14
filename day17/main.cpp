#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string>
#include <cmath>
#include "../common/pair.h"

using namespace std; 

int calculateCombo(int operand, int A, int B, int C) {
    if(operand < 4) {
        return operand;
    }
    if(operand == 4) {
        return A;
    }
    if(operand == 5) {
        return B;
    }
    if(operand == 6) {
        return C;
    }
    cout << "invalid operand" << "\n";
    return -1;
}

void dfs(unsigned long int a, vector<int> instructions, int count) {
    
    for(int j=0; j<8; j++) {
        a += j;
        unsigned long int b = a % 8;
        b = b ^ 5;
        unsigned long int c = a / (pow(2,b));
        b = b ^ 6;
        b = b ^ c;
        if(b % 8 == instructions[count]) {
            if(count == 0) {
                cout << "A:" << a << "\n";
            } else {
            dfs(a*8, instructions, count-1);
            }
        }
        a -= j;
    }
    

   /*
    for(int j=0; j<8; j++) {
        if((a+j) % 8 == instructions[count]) {
            dfs((a+j)*8, instructions, count-1);
            break;
        }
    }
    */
}   

int main() {

    // input
    ifstream f("input.txt");

    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return 1;
    }

    string line;
    stringstream ss;

    unsigned long int A,B,C;
    vector<int> instructions;
    regex r(R"(\b\d+\b)");
    smatch match;

    int count = 0;
    while (getline(f, line)){

        if(count == 0) {
            regex_search(line, match, r);
            cout << match.str() << "\n";
            //A = stoi(match.str());
            A = 107416870457097;
        }
        if(count == 1) {
            regex_search(line, match, r);
            B = stoi(match.str());
        }
        if(count == 2) {
            regex_search(line, match, r);
            C = stoi(match.str());
        }

        if( count == 4) {
            sregex_iterator currentMatch(line.begin(), line.end(), r);
            sregex_iterator end; 

            while (currentMatch != end) {
                match = *currentMatch;
                instructions.push_back(stoi(match.str()));
                currentMatch++;
            }
        }
       count++;
    }


    string out;

        int pc = 0;

        while(pc < instructions.size()) {
            int instruction = instructions[pc];
            int operand = instructions[pc+1];
            int combo = calculateCombo(operand, A, B, C);

            switch(instruction) {
                case 0:
                    A = A / (pow(2,combo));
                    break;
                case 1:
                    B = B ^ operand;
                    break;
                case 2:
                    B = combo%8;
                    break;
                case 3:
                    if(A != 0) {
                        pc = operand;
                        pc -= 2;
                    }
                    break;
                case 4:
                    B = B ^ C;
                    break;
                case 5: {
                    string s = to_string((combo%8));
                    out += s;
                    out.push_back(',');
                    break;
                }
                case 6:
                    B = A / (pow(2,combo));
                    break;
                case 7:
                    C = A / (pow(2,combo));
                    break;             
            }
            pc+=2;
        }

    cout << out << "\n";

/*
    unsigned long int sum = 0;


    unsigned long int a = 0;
    for(int i=instructions.size()-1; i>=0; i--) {
        for(int j=0; j<8; j++) {
            a += j;
            int b = a % 8;
            b = b ^ 5;
            unsigned long int c = a / (pow(2,b));
            b = b ^ 6;
            b = b ^ c;
            if(b % 8 == instructions[i]) {
                a *= 8;
                break;
            }
            a -= j;
        }
        for(int j=0; j<8; j++) {
            if((a+j) % 8 == instructions[i]) {
                a += j;
                a *= 8;
                break;
            }
        }
    }
    */

   unsigned long int a = 0;
   dfs(a, instructions, instructions.size()-1);


    return(0);
}
