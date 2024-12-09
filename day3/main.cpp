#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <regex>

using namespace std;

int main() {

    // input
    ifstream f("input.txt");

    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return 1;
    }

    string line;
    string s;

    while (getline(f, line)){
        istringstream ss(line);
        s += line;
    }

    cout << s << endl;

    regex word_regex("[m][u][l][(][\\[0-9]{1,3}[,][\\[0-9]{1,3}[)]|([d][o][n]['][t][(][)])|[d][o][(][)]");
    auto words_begin = 
        sregex_iterator(s.begin(), s.end(), word_regex);
    auto words_end = sregex_iterator();
 
    cout << "Found "
              << distance(words_begin, words_end)
              << " words\n";

    int sum = 0;
    bool enabled = true;
    for (sregex_iterator i = words_begin; i != words_end; ++i) {
            smatch match = *i;
            string match_str = match.str();
            cout << "  " << match_str << '\n';

            if (match_str == "don't()") {
                enabled = false;
            } else if (match_str == "do()") {
                enabled = true;
            } else if (enabled) {
                // extra the 2 numbers out of the match_str
                regex number_regex("[\\[0-9]{1,3}");
                auto numbers_begin = sregex_iterator(match_str.begin(), match_str.end(), number_regex);
                auto numbers_end = sregex_iterator();

                int mul = 1;
                for(sregex_iterator j = numbers_begin; j != numbers_end; ++j) {
                    smatch n_match = *j;
                    string n_match_str = n_match.str();
                    cout << " " << n_match_str << endl;
                    mul *= stoi(n_match_str);

                }
                sum += mul;
            }
    }

    cout << sum << "\n";

    return(0);
}