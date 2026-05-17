#ifndef MOVEPIECE_H
#define MOVEPIECE_H

#include "Defs.h"
#include "MoveGen.h"

inline void MoveWhitePiece(Move& mv, checkers &b){
    Bitboard to = (1ULL << ((mv >> 6) & 63));
    Bitboard f = (1ULL << (mv & 63));
    Bitboard cap = (1ULL << ((ctz(f) + ctz(to)) / 2));

    // Capture
    switch((mv >> 13) & 3){
        case 1:
            b.bp &= ~cap;
            break;
        case 2:
            b.bk &= ~cap;
            break;
    }

    // Move piece
    switch((mv >> 12) & 1){
        case 0:
            b.wp |= to;
            b.wp &= ~f;
            break;
        case 1:
            b.wk |= to;
            b.wk &= ~f;
            break;
    }

    // Promotion
    if (to & mask_8){
        b.wp &= ~to;
        b.wk |= to;
        mv |= (1 << 15);
    }
}

inline void MoveBlackPiece(Move& mv, checkers &b){
    Bitboard to = (1ULL << ((mv >> 6) & 63));
    Bitboard f = (1ULL << (mv & 63));
    Bitboard cap = (1ULL << ((ctz(f) + ctz(to)) / 2));

    // Capture
    switch((mv >> 13) & 3){
        case 1:
            b.wp &= ~cap;
            break;
        case 2:
            b.wk &= ~cap;
            break;
    }

    // Move piece
    switch((mv >> 12) & 1){
        case 0:
            b.bp |= to;
            b.bp &= ~f;
            break;
        case 1:
            b.bk |= to;
            b.bk &= ~f;
            break;
    }

    // Promotion
    if (to & mask_1){
        b.bp &= ~to;
        b.bk |= to;
        mv |= (1 << 15);
    }
}

inline void MovePiece(Move& mv, checkers &b){
    if(b.turn) MoveWhitePiece(mv,b);
    else       MoveBlackPiece(mv,b);
    
    b.bpcs = b.bp|b.bk;
    b.wpcs = b.wp|b.wk;
    b.pieces = b.bpcs|b.wpcs;

    mv |= ((int) b.turn) << 16;
    mv |= (b.chain + 1) << 17;

    // Chain
    b.chain = -1;
    if ((mv >> 13) & 3){
        MoveList chains;
        int to = ((mv >> 6) & 63);
        if (b.turn){
            if ((mv >> 12) & 1)
                chains = WKchain(b, to);
            else
                chains = WPchain(b, to);
        }
        else{
            if ((mv >> 12) & 1)
                chains = BKchain(b, to);
            else
                chains = BPchain(b, to);
        }

        if (chains.size() > 0){
            b.chain = to;   
            b.turn = !b.turn;
        }
    }
    b.turn = !b.turn;
}

inline void UnMoveWhite(const Move mv, checkers &b){
    Bitboard f = (1ULL << (mv & 63));
    Bitboard to = (1ULL << ((mv>>6) & 63));
    Bitboard cap = (1ULL << ((ctz(f) + ctz(to)) / 2));

    // Move back piece
    switch((mv >> 12) & 1){
        case 0:
            b.wp |= f;
            b.wp &= ~to;
            break;
        case 1:
            b.wk |= f;
            b.wk &= ~to;
            break;
    }
     
    // Undo promotion
    if ((mv >> 15) & 1){
        b.wk &= ~to;
    }

    // Undo capture
    switch((mv >> 13) & 3){
        case 1:
            b.bp |= cap;
            break;
        case 2:
            b.bk |= cap;
            break;
    }
}

inline void UnMoveBlack(const Move mv, checkers &b){
    Bitboard f = (1ULL << (mv & 63));
    Bitboard to = (1ULL << ((mv>>6) & 63));
    Bitboard cap = (1ULL << ((ctz(f) + ctz(to)) / 2));

    // Move back piece
    switch((mv >> 12) & 1){
        case 0:
            b.bp |= f;
            b.bp &= ~to;
            break;
        case 1:
            b.bk |= f;
            b.bk &= ~to;
            break;
    }
     
    // Undo promotion
    if ((mv >> 15) & 1){
        b.bk &= ~to;
    }

    // Undo capture
    switch((mv >> 13) & 3){
        case 1:
            b.wp |= cap;
            break;
        case 2:
            b.wk |= cap;
            break;
    }
}

inline void UnmovePiece(const Move mv, checkers &b){
    if ((mv >> 16) & 1) UnMoveWhite(mv, b);
    else UnMoveBlack(mv, b);

    b.bpcs = b.bp|b.bk;
    b.wpcs = b.wp|b.wk;
    b.pieces = b.bpcs|b.wpcs;

    b.turn = (mv >> 16) & 1;
    b.chain = ((mv >> 17) & 127) - 1;
}

#endif