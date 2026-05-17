#ifndef DEFS_H
#define DEFS_H

#include <iostream>
#include <vector>
#include <chrono>
#include <immintrin.h>
#include <bit>
#include <atomic>

using namespace std;

typedef std::chrono::high_resolution_clock::time_point timept;
typedef unsigned long long int Bitboard;
typedef uint32_t Move;

/* 
Move encoding

0-5   : from square    (0-63)
6-11  : to square      (0-63)
12    : from piece     (0=P 1=K)
13-14 : captured piece (0=N 1=P 2=K)
15    : promotion      (0=N 1=Y)
16    : prev turn      (0=B 1=W)
17-23 : prev chain + 1
*/

extern atomic<bool> StopSignal;
constexpr int inf = 300000;

constexpr Bitboard clear_a=9187201950435737471ULL;
constexpr Bitboard clear_b=13816973012072644543ULL;
constexpr Bitboard clear_c=16131858542891098079ULL;
constexpr Bitboard clear_d=17289301308300324847ULL;
constexpr Bitboard clear_e=17868022691004938231ULL;
constexpr Bitboard clear_f=18157383382357244923ULL;
constexpr Bitboard clear_g=18302063728033398269ULL;
constexpr Bitboard clear_h=18374403900871474942ULL;

constexpr Bitboard mask_a=9259542123273814144ULL;
constexpr Bitboard mask_b=4629771061636907072ULL;
constexpr Bitboard mask_c=2314885530818453536ULL;
constexpr Bitboard mask_d=1157442765409226768ULL;
constexpr Bitboard mask_e=578721382704613384ULL;
constexpr Bitboard mask_f=289360691352306692ULL;
constexpr Bitboard mask_g=144680345676153346ULL;
constexpr Bitboard mask_h=72340172838076673ULL;

constexpr Bitboard clear_8=72057594037927935ULL;
constexpr Bitboard clear_7=18374967954648334335ULL;
constexpr Bitboard clear_6=18446463698244468735ULL;
constexpr Bitboard clear_5=18446742978492891135ULL;
constexpr Bitboard clear_4=18446744069431361535ULL;
constexpr Bitboard clear_3=18446744073692839935ULL;
constexpr Bitboard clear_2=18446744073709486335ULL;
constexpr Bitboard clear_1=18446744073709551360ULL;

constexpr Bitboard mask_8=18374686479671623680ULL;
constexpr Bitboard mask_7=71776119061217280ULL;
constexpr Bitboard mask_6=280375465082880ULL;
constexpr Bitboard mask_5=1095216660480ULL;
constexpr Bitboard mask_4=4278190080ULL;
constexpr Bitboard mask_3=16711680ULL;
constexpr Bitboard mask_2=65280ULL;
constexpr Bitboard mask_1=255ULL;

struct checkers {
    Bitboard wp=0ULL; Bitboard wk=0ULL;
    Bitboard bp=0ULL; Bitboard bk=0ULL;
    Bitboard bpcs=0; Bitboard wpcs=0; Bitboard pieces=0;
	int chain = -1;
    bool turn = true;
};

struct MoveList {
    Move moves[256];
    int count = 0;
    
    inline void Add(Move m) { moves[count++] = m; }
    
    // Functions required for foreach loop
    Move* begin() { return moves; }
    Move* end() { return moves + count; }
    const Move* begin() const { return moves; }
    const Move* end() const { return moves + count; }

    int size() const { return count; }
    Move operator[](int index) const { return moves[index]; }
    Move& operator[](int index) { return moves[index]; }
};

inline int64_t TimeElapsed(timept t){
	return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - t).count();
}

inline int ctz(const Bitboard b) { return countr_zero(b); }
inline int popcnt(const Bitboard b) { return popcount(b); }
inline Bitboard blsr(Bitboard val) { return val & (val - 1); }

#endif