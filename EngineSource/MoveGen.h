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
    Bitboard iter = b.bp;
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
    Bitboard iter = b.bp;
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

inline MoveList WhiteMoves(const checkers &b){
    MoveList moves;
    WKmoves(b,moves);
    WPmoves(b,moves);
}

inline MoveList BlackMoves(const checkers &b){
    MoveList moves;
    BKmoves(b,moves);
    BPmoves(b,moves);
}

inline MoveList LegalMoves(const checkers &b){
    switch (b.turn){
        case true:
            return WhiteMoves(b);
        case false:
            return BlackMoves(b);
    }
}

inline MoveList Chains(const checkers &b, const Bitboard bb){
    MoveList Moves;
    
    if(b.turn){
        
    }
}

#endif