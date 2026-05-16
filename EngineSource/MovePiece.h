#ifndef MOVEPIECE_H
#define MOVEPIECE_H

#include "Defs.h"

inline void MoveWhitePiece(Move& mv, checkers &b){
    Bitboard to = (1ULL << ((mv >> 6) & 63));
    Bitboard f = (1ULL << (mv & 63));
    Bitboard cap = (1ULL << ((ctz(f) + ctz(to)) / 2));

    // Capture
    switch((mv >> 13) & 2){
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
    switch((mv >> 13) & 2){
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

    // Chain
    if ((mv >> 13) & 2){
        
    }
}

inline void UnMoveWhite(const Move mv, chess &b){
    Bitboard f = (1ULL << (mv & 63));
    Bitboard to = (1ULL << ((mv>>6) & 63));

    // Move back piece
    switch ((mv >> 15) & 7){
        case 0: b.wp = (b.wp & ~to) | f; break;
        case 1: b.wn = (b.wn & ~to) | f; break;
        case 2: b.wb = (b.wb & ~to) | f; break;
        case 3: b.wr = (b.wr & ~to) | f; break;
        case 4: b.wq = (b.wq & ~to) | f; break;
        case 5:
            b.wk = (b.wk & ~to) | f;

            // Castle
            if (ctz(f) == 3){
                // Kingside
                if (ctz(to) == 1 || ctz(to) == 0) b.wr = (b.wr & ~(1ULL << 2)) | (1ULL << 0);
                //Queen
                else if (ctz(to) == 5 || ctz(to) == 7) b.wr = (b.wr & ~(1ULL << 4)) | (1ULL << 7);
            }
            break;
    }
     
    // Undo promotion
    switch (((mv >> 12) & 7)){
        case 1: b.wn &= ~to; break;
        case 2: b.wb &= ~to; break;
        case 3: b.wr &= ~to; break;
        case 4: b.wq &= ~to; break;
    }

    // Undo capture
    switch (((mv >> 18) & 7)){
        case 1: b.bp |= to; break;
        case 2: b.bn |= to; break;
        case 3: b.bb |= to; break;
        case 4: b.br |= to; break;
        case 5: b.bq |= to; break;
        case 6: b.bk |= to; break;
        case 7: b.bp |= (to >> 8); break;
    }
}

inline void UnMoveBlack(const Move mv, chess &b){
    Bitboard f = (1ULL << (mv & 63));
    Bitboard to = (1ULL << ((mv>>6) & 63));

    // Move back piece
    switch ((mv >> 15) & 7){
        case 0: b.bp = (b.bp & ~to) | f; break;
        case 1: b.bn = (b.bn & ~to) | f; break;
        case 2: b.bb = (b.bb & ~to) | f; break;
        case 3: b.br = (b.br & ~to) | f; break;
        case 4: b.bq = (b.bq & ~to) | f; break;
        case 5:
            b.bk = (b.bk & ~to) | f;

            // Castle
            if (ctz(f) == 59){
                // Kingside
                if (ctz(to) == 57 || ctz(to) == 56) b.br = (b.br & ~(1ULL << 58)) | (1ULL << 56);
                //Queen
                else if (ctz(to) == 61 || ctz(to) == 63) b.br = (b.br & ~(1ULL << 60)) | (1ULL << 63);
            }
            break;
    }
     
    // Undo promotion
    switch (((mv >> 12) & 7)){
        case 1: b.bn &= ~to; break;
        case 2: b.bb &= ~to; break;
        case 3: b.br &= ~to; break;
        case 4: b.bq &= ~to; break;
    }

    // Undo capture
    switch (((mv >> 18) & 7)){
        case 1: b.wp |= to; break;
        case 2: b.wn |= to; break;
        case 3: b.wb |= to; break;
        case 4: b.wr |= to; break;
        case 5: b.wq |= to; break;
        case 6: b.wk |= to; break;
        case 7: b.wp |= (to << 8); break;
    }
}

inline void UnmovePiece(const Move mv, chess &b){
    b.WCastleKing = (mv >> 24) & 1;
    b.WCastleQueen = (mv >> 23) & 1;
    b.BCastleKing = (mv >> 22) & 1;
    b.BCastleQueen = (mv >> 21) & 1;
    b.ep = (int)((mv >> 25) & 127) - 1;

    if (b.turn) UnMoveBlack(mv, b);
    else UnMoveWhite(mv, b);

    b.turn = !b.turn;
    b.bpcs = b.bp|b.br|b.bn|b.bb|b.bq|b.bk;
    b.wpcs = b.wp|b.wr|b.wn|b.wb|b.wq|b.wk;
    b.pieces = b.bpcs|b.wpcs;
}

#endif