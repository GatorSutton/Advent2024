// common.h
#ifndef COMMON_H
#define COMMON_H

#include <bits/stdc++.h>

using namespace std;

class Pair {

public: 

    int y;
    int x;

    Pair(int y, int x) : y(y), x(x) {}

    bool operator==(const Pair& other) const {
        return x == other.x &&
               y == other.y;
    }

    struct Hash {
        size_t operator()(const Pair& obj) const {
            size_t h1 = hash<int>()(obj.x);
            size_t h2 = hash<int>()(obj.y);

            return h1 ^ (h2 << 1);
        }
    };

    friend struct Hash;
};

#endif // COMMON_H