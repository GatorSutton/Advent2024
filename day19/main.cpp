#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string>
#include <cmath>
#include "../common/pair.h"

using namespace std; 

// Create a set of all of the towels.
// Create a vector<string> of all of the designs.
// Loop through all remaining substrings and see if it exists in the towels set.
// If it does recurse the search.
// If the end is reached, end the search.

void findTowels(set<string>& towels, string pattern, bool& found) {

    /*
    for(int i=0; i<pattern.size(); i++) {
        string substring = pattern.substr(0, pattern.size() - i);
        auto it = towels.find(substring);

        if(it != towels.end()) {
            if(i == 0) {
                found = true;
                break;
            } else {
                string restOfString = pattern.substr(pattern.size()-i, i);
                findTowels(towels, restOfString, found);
            }
        }
    }
    */
   if(found == true) {
        return;
   }

    for(int i=1; i<=pattern.size(); i++) {

        if(found == true) {
            return;
        }

        string substring = pattern.substr(0, i);
        auto it = towels.find(substring);

        if(it != towels.end()) {
            if(i == pattern.size()) {
                found = true;
                break;
            } else {
                string restOfString = pattern.substr(i, pattern.size()-i);
                findTowels(towels, restOfString, found);
            }
        }
    }
}

// Find how many permutations are possible to get to each character.
// At each character, starting at 0, look back at most maxLength or beginning of the pattern whichever comes first,
unsigned long int findAllTowels(const set<string>& towels, const string& pattern, int maxLength) {
    vector<unsigned long int> combinations(pattern.size(), 0);

    for (int i = 0; i < pattern.size(); ++i) {
        int substr_max_length = min(maxLength, i + 1);
        
        for (int len = 1; len <= substr_max_length; ++len) {
            int start_index = i - len + 1;
            string substr = pattern.substr(start_index, len);

            if (towels.find(substr) != towels.end()) {
                // If this substr reaches the beginning of the pattern add 1.
                // If this substr doesn't reach the beginning, add the combinations that it starts at.
                combinations[i] += (start_index == 0) ? 1 : combinations[start_index - 1];
            }
        }
    }
    return combinations.back();
}

set<string> separatedWords(string line, char separator) {
    regex lowerCaseWordRegex(R"([a-z]+)"); 
    auto wordsBegin = sregex_iterator(line.begin(), line.end(), lowerCaseWordRegex);
    auto wordsEnd = sregex_iterator();
    set<string> set;

    for (sregex_iterator it = wordsBegin; it != wordsEnd; ++it) {
        set.insert(it->str());
    }

    return set;
}

int main() {

    // input
    ifstream f("input.txt");

    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return 1;
    }

    string line;

    int count = -1;
    set<string> towels;
    vector<string> patterns;
    while (getline(f, line)){
        count++;
        if(count == 0) {
            towels = separatedWords(line, ',');
            continue;
        }
        if(line == "") {
            continue;
        }
        patterns.push_back(line);

    }

    int maxLength = 0;
    for(auto it=towels.begin(); it!=towels.end(); it++) {
        //cout << *it << "\n";
        if((*it).size() > maxLength) {
            maxLength = (*it).size();
        }
    }
    //cout << "\n";



    int sum = 0;
    unsigned long int sum2 =0;
    for (int i=0; i<patterns.size(); i++) {
        bool found = false;
        //findTowels(towels, patterns[i], found);
        unsigned long int total = findAllTowels(towels, patterns[i], maxLength);
        cout << total << "\n";
        sum2 += total;
        if(found) {
            sum++;
        }
    }

    cout << sum << "\n";
    cout << sum2 << "\n";

    return(0);
}