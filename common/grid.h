#ifndef GRID_H
#define GRID_H

#include <bits/stdc++.h>
#include "pair.h"

using namespace std;


enum Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN
};

Pair charToDirection(char c) {
    static const std::unordered_map<char, Pair> charToDirMap = {
        {'<', Pair(0,-1)},
        {'>', Pair(0,1)},
        {'^', Pair(-1,0)},
        {'v', Pair(1,0)}
    };

    auto it = charToDirMap.find(c);
    if (it != charToDirMap.end()) {
        return it->second;
    } else {
        throw invalid_argument("Invalid direction character");
    }
}

Pair directionToPair(Direction d) {
    static const std::unordered_map<Direction, Pair> directionToPairMap = {
        {LEFT, Pair(0,-1)},
        {RIGHT, Pair(0,1)},
        {UP, Pair(-1,0)},
        {DOWN, Pair(1,0)}
    };

    auto it = directionToPairMap.find(d);
    if (it != directionToPairMap.end()) {
        return it->second;
    } else {
        throw invalid_argument("Invalid direction");
    }
}

Direction rotateCW(Direction current) {
    static const std::unordered_map<Direction, Direction> clockwiseMap = {
        {UP, RIGHT},
        {RIGHT, DOWN},
        {DOWN, LEFT},
        {LEFT, UP}
    };

    auto it = clockwiseMap.find(current);
    if (it != clockwiseMap.end()) {
        return it->second;
    } else {
        throw std::invalid_argument("Invalid current direction");
    }
}

Direction rotateCCW(Direction current) {
    static const std::unordered_map<Direction, Direction> counterclockwiseMap = {
        {UP, LEFT},
        {LEFT, DOWN},
        {DOWN, RIGHT},
        {RIGHT, UP}
    };

    auto it = counterclockwiseMap.find(current);
    if (it != counterclockwiseMap.end()) {
        return it->second;
    } else {
        throw std::invalid_argument("Invalid current direction");
    }
}

#endif // GRID_H