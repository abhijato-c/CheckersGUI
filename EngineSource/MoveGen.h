#ifndef MOVEGEN_H
#define MOVEGEN_H

#include "Defs.h"

inline void WPmoves(const checkers &b, MoveList &Moves){
    Bitboard iter = b.wp;
    int i;
    Bitboard bb;

    while(iter){
        i = ctz(iter);
        iter = blsr(iter);
        bb = 1ULL << i;

        if (((bb & clear_h & clear_8) != 0) && ((bb << 7) & b.pieces) == 0) 
            Moves.Add(ctz(bb << 7) << 6 | i);
        if (((bb & clear_a & clear_8) != 0) && ((bb << 9) & b.pieces) == 0)
            Moves.Add(ctz(bb << 9) << 6 | i);
        if (((bb & clear_h & clear_g & clear_8 & clear_7) != 0) && ((bb << 14) & b.pieces) == 0 && ((bb << 7) & b.bp) != 0)
            Moves.Add((1 << 13) | ctz(bb << 14) << 6 | i);
        if (((bb & clear_h & clear_g & clear_8 & clear_7) != 0) && ((bb << 14) & b.pieces) == 0 && ((bb << 7) & b.bk) != 0)
            Moves.Add((2 << 13) | ctz(bb << 14) << 6 | i);
        if (((bb & clear_a & clear_b & clear_8 & clear_7) != 0) && ((bb << 18) & b.pieces) == 0 && ((bb << 9) & b.bp) != 0)
            Moves.Add((1 << 13) | ctz(bb << 18) << 6 | i);
        if (((bb & clear_a & clear_b & clear_8 & clear_7) != 0) && ((bb << 18) & b.pieces) == 0 && ((bb << 9) & b.bk) != 0)
            Moves.Add((2 << 13) | ctz(bb << 18) << 6 | i);
    }
}

inline void BPmoves(const checkers &b, MoveList &Moves){
    Bitboard iter = b.bp;
    int i;
    Bitboard bb;

    while(iter){
        i = ctz(iter);
        iter = blsr(iter);
        bb = 1ULL << i;

        if (((bb & clear_a & clear_1) != 0) && ((bb >> 7) & b.pieces) == 0) 
            Moves.Add(ctz(bb >> 7) << 6 | i);
        if (((bb & clear_h & clear_1) != 0) && ((bb >> 9) & b.pieces) == 0)
            Moves.Add(ctz(bb >> 9) << 6 | i);
        if (((bb & clear_a & clear_b & clear_1 & clear_2) != 0) && ((bb >> 14) & b.pieces) == 0 && ((bb >> 7) & b.wp) != 0)
            Moves.Add((1 << 13) | ctz(bb >> 14) << 6 | i);
        if (((bb & clear_a & clear_b & clear_1 & clear_2) != 0) && ((bb >> 14) & b.pieces) == 0 && ((bb >> 7) & b.wk) != 0)
            Moves.Add((2 << 13) | ctz(bb >> 14) << 6 | i);
        if (((bb & clear_h & clear_g & clear_1 & clear_2) != 0) && ((bb >> 18) & b.pieces) == 0 && ((bb >> 9) & b.wp) != 0)
            Moves.Add((1 << 13) | ctz(bb >> 18) << 6 | i);
        if (((bb & clear_h & clear_g & clear_1 & clear_2) != 0) && ((bb >> 18) & b.pieces) == 0 && ((bb >> 9) & b.wk) != 0)
            Moves.Add((2 << 13) | ctz(bb >> 18) << 6 | i);
    }
}

inline void WKmoves(const checkers &b, MoveList &Moves){
    Bitboard iter = b.wk;
    int i;
    Bitboard bb;

    while(iter){
        i = ctz(iter);
        iter = blsr(iter);
        bb = 1ULL << i;

        if (((bb & clear_h & clear_8) != 0) && ((bb << 7) & b.pieces) == 0) 
            Moves.Add((1 << 12) | ctz(bb << 7) << 6 | i);
        if (((bb & clear_a & clear_8) != 0) && ((bb << 9) & b.pieces) == 0)
            Moves.Add((1 << 12) | ctz(bb << 9) << 6 | i);
        if (((bb & clear_a & clear_1) != 0) && ((bb >> 7) & b.pieces) == 0) 
            Moves.Add((1 << 12) | ctz(bb >> 7) << 6 | i);
        if (((bb & clear_h & clear_1) != 0) && ((bb >> 9) & b.pieces) == 0)
            Moves.Add((1 << 12) | ctz(bb >> 9) << 6 | i);
        if (((bb & clear_h & clear_g & clear_8 & clear_7) != 0) && ((bb << 14) & b.pieces) == 0 && ((bb << 7) & b.bp) != 0)
            Moves.Add((1 << 13) | (1 << 12) | ctz(bb << 14) << 6 | i);
        if (((bb & clear_h & clear_g & clear_8 & clear_7) != 0) && ((bb << 14) & b.pieces) == 0 && ((bb << 7) & b.bk) != 0)
            Moves.Add((2 << 13) | (1 << 12) | ctz(bb << 14) << 6 | i);
        if (((bb & clear_a & clear_b & clear_8 & clear_7) != 0) && ((bb << 18) & b.pieces) == 0 && ((bb << 9) & b.bp) != 0)
            Moves.Add((1 << 13) | (1 << 12) | ctz(bb << 18) << 6 | i);
        if (((bb & clear_a & clear_b & clear_8 & clear_7) != 0) && ((bb << 18) & b.pieces) == 0 && ((bb << 9) & b.bk) != 0)
            Moves.Add((2 << 13) | (1 << 12) | ctz(bb << 18) << 6 | i);
        if (((bb & clear_a & clear_b & clear_1 & clear_2) != 0) && ((bb >> 14) & b.pieces) == 0 && ((bb >> 7) & b.bp) != 0)
            Moves.Add((1 << 13) | (1 << 12) | ctz(bb >> 14) << 6 | i);
        if (((bb & clear_a & clear_b & clear_1 & clear_2) != 0) && ((bb >> 14) & b.pieces) == 0 && ((bb >> 7) & b.bk) != 0)
            Moves.Add((2 << 13) | (1 << 12) | ctz(bb >> 14) << 6 | i);
        if (((bb & clear_h & clear_g & clear_1 & clear_2) != 0) && ((bb >> 18) & b.pieces) == 0 && ((bb >> 9) & b.bp) != 0)
            Moves.Add((1 << 13) | (1 << 12) | ctz(bb >> 18) << 6 | i);
        if (((bb & clear_h & clear_g & clear_1 & clear_2) != 0) && ((bb >> 18) & b.pieces) == 0 && ((bb >> 9) & b.bk) != 0)
            Moves.Add((2 << 13) | (1 << 12) | ctz(bb >> 18) << 6 | i);
    }
}

inline void BKmoves(const checkers &b, MoveList &Moves){
    Bitboard iter = b.bk;
    int i;
    Bitboard bb;

    while(iter){
        i = ctz(iter);
        iter = blsr(iter);
        bb = 1ULL << i;

        if (((bb & clear_h & clear_8) != 0) && ((bb << 7) & b.pieces) == 0) 
            Moves.Add((1 << 12) | ctz(bb << 7) << 6 | i);
        if (((bb & clear_a & clear_8) != 0) && ((bb << 9) & b.pieces) == 0)
            Moves.Add((1 << 12) | ctz(bb << 9) << 6 | i);
        if (((bb & clear_a & clear_1) != 0) && ((bb >> 7) & b.pieces) == 0) 
            Moves.Add((1 << 12) | ctz(bb >> 7) << 6 | i);
        if (((bb & clear_h & clear_1) != 0) && ((bb >> 9) & b.pieces) == 0)
            Moves.Add((1 << 12) | ctz(bb >> 9) << 6 | i);
        if (((bb & clear_h & clear_g & clear_8 & clear_7) != 0) && ((bb << 14) & b.pieces) == 0 && ((bb << 7) & b.wp) != 0)
            Moves.Add((1 << 13) | (1 << 12) | ctz(bb << 14) << 6 | i);
        if (((bb & clear_h & clear_g & clear_8 & clear_7) != 0) && ((bb << 14) & b.pieces) == 0 && ((bb << 7) & b.wk) != 0)
            Moves.Add((2 << 13) | (1 << 12) | ctz(bb << 14) << 6 | i);
        if (((bb & clear_a & clear_b & clear_8 & clear_7) != 0) && ((bb << 18) & b.pieces) == 0 && ((bb << 9) & b.wp) != 0)
            Moves.Add((1 << 13) | (1 << 12) | ctz(bb << 18) << 6 | i);
        if (((bb & clear_a & clear_b & clear_8 & clear_7) != 0) && ((bb << 18) & b.pieces) == 0 && ((bb << 9) & b.wk) != 0)
            Moves.Add((2 << 13) | (1 << 12) | ctz(bb << 18) << 6 | i);
        if (((bb & clear_a & clear_b & clear_1 & clear_2) != 0) && ((bb >> 14) & b.pieces) == 0 && ((bb >> 7) & b.wp) != 0)
            Moves.Add((1 << 13) | (1 << 12) | ctz(bb >> 14) << 6 | i);
        if (((bb & clear_a & clear_b & clear_1 & clear_2) != 0) && ((bb >> 14) & b.pieces) == 0 && ((bb >> 7) & b.wk) != 0)
            Moves.Add((2 << 13) | (1 << 12) | ctz(bb >> 14) << 6 | i);
        if (((bb & clear_h & clear_g & clear_1 & clear_2) != 0) && ((bb >> 18) & b.pieces) == 0 && ((bb >> 9) & b.wp) != 0)
            Moves.Add((1 << 13) | (1 << 12) | ctz(bb >> 18) << 6 | i);  
        if (((bb & clear_h & clear_g & clear_1 & clear_2) != 0) && ((bb >> 18) & b.pieces) == 0 && ((bb >> 9) & b.wk) != 0)
            Moves.Add((2 << 13) | (1 << 12) | ctz(bb >> 18) << 6 | i);        
    }
}

inline MoveList WPchain(const checkers &b, const int i){
    Bitboard bb = (1ULL << i);
    MoveList Moves;

    if (((bb & clear_h & clear_g & clear_8 & clear_7) != 0) && ((bb << 14) & b.pieces) == 0 && ((bb << 7) & b.bp) != 0)
        Moves.Add((1 << 13) | ctz(bb << 14) << 6 | i);
    if (((bb & clear_h & clear_g & clear_8 & clear_7) != 0) && ((bb << 14) & b.pieces) == 0 && ((bb << 7) & b.bk) != 0)
        Moves.Add((2 << 13) | ctz(bb << 14) << 6 | i);
    if (((bb & clear_a & clear_b & clear_8 & clear_7) != 0) && ((bb << 18) & b.pieces) == 0 && ((bb << 9) & b.bp) != 0)
        Moves.Add((1 << 13) | ctz(bb << 18) << 6 | i);
    if (((bb & clear_a & clear_b & clear_8 & clear_7) != 0) && ((bb << 18) & b.pieces) == 0 && ((bb << 9) & b.bk) != 0)
        Moves.Add((2 << 13) | ctz(bb << 18) << 6 | i);
    
    return Moves;
}

inline MoveList WKchain(const checkers &b, const int i){
    Bitboard bb = (1ULL << i);
    MoveList Moves;

    if (((bb & clear_h & clear_g & clear_8 & clear_7) != 0) && ((bb << 14) & b.pieces) == 0 && ((bb << 7) & b.bp) != 0)
        Moves.Add((1 << 13) | (1 << 12) | ctz(bb << 14) << 6 | i);
    if (((bb & clear_h & clear_g & clear_8 & clear_7) != 0) && ((bb << 14) & b.pieces) == 0 && ((bb << 7) & b.bk) != 0)
        Moves.Add((2 << 13) | (1 << 12) | ctz(bb << 14) << 6 | i);
    if (((bb & clear_a & clear_b & clear_8 & clear_7) != 0) && ((bb << 18) & b.pieces) == 0 && ((bb << 9) & b.bp) != 0)
        Moves.Add((1 << 13) | (1 << 12) | ctz(bb << 18) << 6 | i);
    if (((bb & clear_a & clear_b & clear_8 & clear_7) != 0) && ((bb << 18) & b.pieces) == 0 && ((bb << 9) & b.bk) != 0)
        Moves.Add((2 << 13) | (1 << 12) | ctz(bb << 18) << 6 | i);
    if (((bb & clear_a & clear_b & clear_1 & clear_2) != 0) && ((bb >> 14) & b.pieces) == 0 && ((bb >> 7) & b.bp) != 0)
        Moves.Add((1 << 13) | (1 << 12) | ctz(bb >> 14) << 6 | i);
    if (((bb & clear_a & clear_b & clear_1 & clear_2) != 0) && ((bb >> 14) & b.pieces) == 0 && ((bb >> 7) & b.bk) != 0)
        Moves.Add((2 << 13) | (1 << 12) | ctz(bb >> 14) << 6 | i);
    if (((bb & clear_h & clear_g & clear_1 & clear_2) != 0) && ((bb >> 18) & b.pieces) == 0 && ((bb >> 9) & b.bp) != 0)
        Moves.Add((1 << 13) | (1 << 12) | ctz(bb >> 18) << 6 | i);
    if (((bb & clear_h & clear_g & clear_1 & clear_2) != 0) && ((bb >> 18) & b.pieces) == 0 && ((bb >> 9) & b.bk) != 0)
        Moves.Add((2 << 13) | (1 << 12) | ctz(bb >> 18) << 6 | i);
    
    return Moves;
}

inline MoveList BPchain(const checkers &b, const int i){
    Bitboard bb = (1ULL << i);
    MoveList Moves;

    if (((bb & clear_a & clear_b & clear_1 & clear_2) != 0) && ((bb >> 14) & b.pieces) == 0 && ((bb >> 7) & b.wp) != 0)
        Moves.Add((1 << 13) | ctz(bb >> 14) << 6 | i);
    if (((bb & clear_a & clear_b & clear_1 & clear_2) != 0) && ((bb >> 14) & b.pieces) == 0 && ((bb >> 7) & b.wk) != 0)
        Moves.Add((2 << 13) | ctz(bb >> 14) << 6 | i);
    if (((bb & clear_h & clear_g & clear_1 & clear_2) != 0) && ((bb >> 18) & b.pieces) == 0 && ((bb >> 9) & b.wp) != 0)
        Moves.Add((1 << 13) | ctz(bb >> 18) << 6 | i);
    if (((bb & clear_h & clear_g & clear_1 & clear_2) != 0) && ((bb >> 18) & b.pieces) == 0 && ((bb >> 9) & b.wk) != 0)
        Moves.Add((2 << 13) | ctz(bb >> 18) << 6 | i);

    return Moves;
}

inline MoveList BKchain(const checkers &b, const int i){
    Bitboard bb = (1ULL << i);
    MoveList Moves;

    if (((bb & clear_h & clear_g & clear_8 & clear_7) != 0) && ((bb << 14) & b.pieces) == 0 && ((bb << 7) & b.wp) != 0)
        Moves.Add((1 << 13) | (1 << 12) | ctz(bb << 14) << 6 | i);
    if (((bb & clear_h & clear_g & clear_8 & clear_7) != 0) && ((bb << 14) & b.pieces) == 0 && ((bb << 7) & b.wk) != 0)
        Moves.Add((2 << 13) | (1 << 12) | ctz(bb << 14) << 6 | i);
    if (((bb & clear_a & clear_b & clear_8 & clear_7) != 0) && ((bb << 18) & b.pieces) == 0 && ((bb << 9) & b.wp) != 0)
        Moves.Add((1 << 13) | (1 << 12) | ctz(bb << 18) << 6 | i);
    if (((bb & clear_a & clear_b & clear_8 & clear_7) != 0) && ((bb << 18) & b.pieces) == 0 && ((bb << 9) & b.wk) != 0)
        Moves.Add((2 << 13) | (1 << 12) | ctz(bb << 18) << 6 | i);
    if (((bb & clear_a & clear_b & clear_1 & clear_2) != 0) && ((bb >> 14) & b.pieces) == 0 && ((bb >> 7) & b.wp) != 0)
        Moves.Add((1 << 13) | (1 << 12) | ctz(bb >> 14) << 6 | i);
    if (((bb & clear_a & clear_b & clear_1 & clear_2) != 0) && ((bb >> 14) & b.pieces) == 0 && ((bb >> 7) & b.wk) != 0)
        Moves.Add((2 << 13) | (1 << 12) | ctz(bb >> 14) << 6 | i);
    if (((bb & clear_h & clear_g & clear_1 & clear_2) != 0) && ((bb >> 18) & b.pieces) == 0 && ((bb >> 9) & b.wp) != 0)
        Moves.Add((1 << 13) | (1 << 12) | ctz(bb >> 18) << 6 | i);  
    if (((bb & clear_h & clear_g & clear_1 & clear_2) != 0) && ((bb >> 18) & b.pieces) == 0 && ((bb >> 9) & b.wk) != 0)
        Moves.Add((2 << 13) | (1 << 12) | ctz(bb >> 18) << 6 | i);

    return Moves;
}

inline MoveList WhiteMoves(const checkers &b){
    if (b.chain == -1){
        MoveList moves;
        WKmoves(b,moves);
        WPmoves(b,moves);

        MoveList caps;
        for (Move m : moves){
            if ((m >> 13) & 3)
                caps.Add(m);
        }

        if (caps.size() > 0)
            return caps;
        return moves;
    }
    else{
        if (b.wp & (1ULL << b.chain))
            return WPchain(b, b.chain);
        else
            return WKchain(b, b.chain);
    }
}

inline MoveList BlackMoves(const checkers &b){
    if (b.chain == -1) {
        MoveList moves;
        BKmoves(b,moves);
        BPmoves(b,moves);

        MoveList caps;
        for (Move m : moves){
            if ((m >> 13) & 3)
                caps.Add(m);
        }

        if (caps.size() > 0)
            return caps;
        return moves;
    }
    else{
        if (b.bp & (1ULL << b.chain))
            return BPchain(b, b.chain);
        else
            return BKchain(b, b.chain);
    }
}

inline MoveList LegalMoves(const checkers &b){
    switch (b.turn){
        case true:
            return WhiteMoves(b);
        case false:
            return BlackMoves(b);
    }
}

#endif