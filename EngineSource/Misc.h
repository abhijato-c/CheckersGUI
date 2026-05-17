#ifndef MISC_H
#define MISC_H

#include "Defs.h"
#include <sstream>

inline int StaticEval(const checkers &b){
    if (b.turn)
        return ((popcnt(b.wp)*1) + (popcnt(b.wk)*2) - (popcnt(b.bp)*1) - (popcnt(b.bk)*2));
    return ((popcnt(b.bp)*1) + (popcnt(b.bk)*2) - (popcnt(b.wp)*1) - (popcnt(b.wk)*2));
}

inline string MoveToStr(const Move move){
    int from = (move & 63);
    int to = ((move>>6) & 63);
    string MoveStr = "";

    MoveStr += to_string(7 - from%8); // From file
    MoveStr += to_string(from / 8);   // From rank
    MoveStr += to_string(7 - to % 8); // To file
    MoveStr += to_string(to / 8);     // To rank

    return MoveStr;
}

#endif