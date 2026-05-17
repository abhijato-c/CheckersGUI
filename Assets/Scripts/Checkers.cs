using System.Collections.Generic;
using Unity.Mathematics;

using Bitboard = System.UInt64;
using Move = System.Int32;
public class Checkers {
    Bitboard clear_a=9187201950435737471UL;
    Bitboard clear_b=13816973012072644543UL;
    //Bitboard clear_c=16131858542891098079UL;
    //Bitboard clear_d=17289301308300324847UL;
    //Bitboard clear_e=17868022691004938231UL;
    //Bitboard clear_f=18157383382357244923UL;
    Bitboard clear_g=18302063728033398269UL;
    Bitboard clear_h=18374403900871474942UL;

    //Bitboard mask_a=9259542123273814144UL;
    //Bitboard mask_b=4629771061636907072UL;
    //Bitboard mask_c=2314885530818453536UL;
    //Bitboard mask_d=1157442765409226768UL;
    //Bitboard mask_e=578721382704613384UL;
    //Bitboard mask_f=289360691352306692UL;
    //Bitboard mask_g=144680345676153346UL;
    //Bitboard mask_h=72340172838076673UL;

    Bitboard clear_8=72057594037927935UL;
    Bitboard clear_7=18374967954648334335UL;
    //Bitboard clear_6=18446463698244468735UL;
    //Bitboard clear_5=18446742978492891135UL;
    //Bitboard clear_4=18446744069431361535UL;
    //Bitboard clear_3=18446744073692839935UL;
    Bitboard clear_2=18446744073709486335UL;
    Bitboard clear_1=18446744073709551360UL;

    Bitboard mask_8=18374686479671623680UL;
    //Bitboard mask_7=71776119061217280UL;
    //Bitboard mask_6=280375465082880UL;
    //Bitboard mask_5=1095216660480UL;
    //Bitboard mask_4=4278190080UL;
    //Bitboard mask_3=16711680UL;
    //Bitboard mask_2=65280UL;
    Bitboard mask_1=255UL;

    public Bitboard wp = 0; public Bitboard bp = 0; public Bitboard wk = 0; public Bitboard bk = 0;
    public Bitboard wpcs = 0; public Bitboard bpcs = 0; public Bitboard pieces = 0; public int chain = -1;
    public bool turn=true;
    public int ctz(Bitboard brd) {return math.tzcnt(brd);}
    public int popcnt(Bitboard brd) {return math.countbits(brd);}

    public void ResetBoard(){
        wp = 11163050UL; bp = 6172839697753047040UL; wk = 0; bk = 0;
        wpcs = wp | wk; bpcs = bp | bk; pieces = wpcs | bpcs; turn = true; chain = -1;
    }

    public void WPmoves(int i, ref List<Move> Moves){
        Bitboard bb = 1UL << i;
        if (((bb & clear_h & clear_8) != 0) && ((bb << 7) & pieces) == 0) 
            Moves.Add(ctz(bb << 7) << 6 | i);
        if (((bb & clear_a & clear_8) != 0) && ((bb << 9) & pieces) == 0)
            Moves.Add(ctz(bb << 9) << 6 | i);
        if (((bb & clear_h & clear_g & clear_8 & clear_7) != 0) && ((bb << 14) & pieces) == 0 && ((bb << 7) & bpcs) != 0)
            Moves.Add((1 << 12) | ctz(bb << 14) << 6 | i);
        if (((bb & clear_a & clear_b & clear_8 & clear_7) != 0) && ((bb << 18) & pieces) == 0 && ((bb << 9) & bpcs) != 0)
            Moves.Add((1 << 12) | ctz(bb << 18) << 6 | i);
    }

    public void BPmoves(int i, ref List<Move> Moves){
        Bitboard bb = 1UL << i;
        if (((bb & clear_a & clear_1) != 0) && ((bb >> 7) & pieces) == 0) 
            Moves.Add(ctz(bb >> 7) << 6 | i);
        if (((bb & clear_h & clear_1) != 0) && ((bb >> 9) & pieces) == 0)
            Moves.Add(ctz(bb >> 9) << 6 | i);
        if (((bb & clear_a & clear_b & clear_1 & clear_2) != 0) && ((bb >> 14) & pieces) == 0 && ((bb >> 7) & wpcs) != 0)
            Moves.Add((1 << 12) | ctz(bb >> 14) << 6 | i);
        if (((bb & clear_h & clear_g & clear_1 & clear_2) != 0) && ((bb >> 18) & pieces) == 0 && ((bb >> 9) & wpcs) != 0)
            Moves.Add((1 << 12) | ctz(bb >> 18) << 6 | i);
    }

    public void WKmoves(int i, ref List<Move> Moves){
        Bitboard bb = 1UL << i;
        if (((bb & clear_h & clear_8) != 0) && ((bb << 7) & pieces) == 0) 
            Moves.Add(ctz(bb << 7) << 6 | i);
        if (((bb & clear_a & clear_8) != 0) && ((bb << 9) & pieces) == 0)
            Moves.Add(ctz(bb << 9) << 6 | i);
        if (((bb & clear_a & clear_1) != 0) && ((bb >> 7) & pieces) == 0) 
            Moves.Add(ctz(bb >> 7) << 6 | i);
        if (((bb & clear_h & clear_1) != 0) && ((bb >> 9) & pieces) == 0)
            Moves.Add(ctz(bb >> 9) << 6 | i);
        if (((bb & clear_h & clear_g & clear_8 & clear_7) != 0) && ((bb << 14) & pieces) == 0 && ((bb << 7) & bpcs) != 0)
            Moves.Add((1 << 12) | ctz(bb << 14) << 6 | i);
        if (((bb & clear_a & clear_b & clear_8 & clear_7) != 0) && ((bb << 18) & pieces) == 0 && ((bb << 9) & bpcs) != 0)
            Moves.Add((1 << 12) | ctz(bb << 18) << 6 | i);
        if (((bb & clear_a & clear_b & clear_1 & clear_2) != 0) && ((bb >> 14) & pieces) == 0 && ((bb >> 7) & bpcs) != 0)
            Moves.Add((1 << 12) | ctz(bb >> 14) << 6 | i);
        if (((bb & clear_h & clear_g & clear_1 & clear_2) != 0) && ((bb >> 18) & pieces) == 0 && ((bb >> 9) & bpcs) != 0)
            Moves.Add((1 << 12) | ctz(bb >> 18) << 6 | i);
    }

    public void BKmoves(int i, ref List<Move> Moves){
        Bitboard bb = 1UL << i;
        if (((bb & clear_h & clear_8) != 0) && ((bb << 7) & pieces) == 0) 
            Moves.Add(ctz(bb << 7) << 6 | i);
        if (((bb & clear_a & clear_8) != 0) && ((bb << 9) & pieces) == 0)
            Moves.Add(ctz(bb << 9) << 6 | i);
        if (((bb & clear_a & clear_1) != 0) && ((bb >> 7) & pieces) == 0) 
            Moves.Add(ctz(bb >> 7) << 6 | i);
        if (((bb & clear_h & clear_1) != 0) && ((bb >> 9) & pieces) == 0)
            Moves.Add(ctz(bb >> 9) << 6 | i);
        if (((bb & clear_h & clear_g & clear_8 & clear_7) != 0) && ((bb << 14) & pieces) == 0 && ((bb << 7) & wpcs) != 0)
            Moves.Add((1 << 12) | ctz(bb << 14) << 6 | i);
        if (((bb & clear_a & clear_b & clear_8 & clear_7) != 0) && ((bb << 18) & pieces) == 0 && ((bb << 9) & wpcs) != 0)
            Moves.Add((1 << 12) | ctz(bb << 18) << 6 | i);
        if (((bb & clear_a & clear_b & clear_1 & clear_2) != 0) && ((bb >> 14) & pieces) == 0 && ((bb >> 7) & wpcs) != 0)
            Moves.Add((1 << 12) | ctz(bb >> 14) << 6 | i);
        if (((bb & clear_h & clear_g & clear_1 & clear_2) != 0) && ((bb >> 18) & pieces) == 0 && ((bb >> 9) & wpcs) != 0)
            Moves.Add((1 << 12) | ctz(bb >> 18) << 6 | i);
    }

    public List<Move> GenerateMoves(){
        List<Move> Moves = new List<Move>();
        if (chain != -1){
            Bitboard bb = 1UL << chain;
            if (turn){
                if ((bb & wp) != 0)
                    WPmoves(chain, ref Moves);
                else
                    WKmoves(chain, ref Moves);
            }
            else {
                if ((bb & bp) != 0)
                    BPmoves(chain, ref Moves);
                else
                    BKmoves(chain, ref Moves);
            }

            List<Move> caps = new List<Move>();
            foreach (Move move in Moves){
                if ((move >> 12) != 0)
                    caps.Add(move);
            }
            return caps;
        }

        Bitboard temp;
        int i;

        if (turn){
            temp = wp;
            while (temp != 0){
                i = ctz(temp);
                temp &= temp - 1;
                WPmoves(i, ref Moves);
            }
            temp = wk;
            while (temp != 0){
                i = ctz(temp);
                temp &= temp - 1;
                WKmoves(i, ref Moves);
            }
        } 
        else {
            temp = bp;
            while (temp != 0){
                i = ctz(temp);
                temp &= temp - 1;
                BPmoves(i, ref Moves);
            }
            temp = bk;
            while (temp != 0){
                i = ctz(temp);
                temp &= temp - 1;
                BKmoves(i, ref Moves);
            }
        }

        List<Move> CaptureMoves = new List<Move>();
        foreach (Move move in Moves){
            if ((move >> 12) != 0)
                CaptureMoves.Add(move);
        }
        if (CaptureMoves.Count > 0)
            return CaptureMoves;
        return Moves;
    }

    public void MakeMove(Move move){
        Bitboard from = 1UL << (move & 63);
        Bitboard to = 1UL << ((move >> 6) & 63);

        if (turn){
            if ((from & wp) != 0){
                wp &= ~from;
                wp |= to;
                if ((to & mask_8) != 0) {
                    wp &= ~to;
                    wk |= to;
                }
            } 
            else {
                wk &= ~from;
                wk |= to;
            }
            
            if (move >> 12 != 0) {
                Bitboard cap = 1UL << ((ctz(from) + ctz(to)) / 2);
                bp &= ~cap;
                bk &= ~cap;
            }
        } 
        else {
            if ((from & bp) != 0){
                bp &= ~from;
                bp |= to;
                if ((to & mask_1) != 0) {
                    bp &= ~to;
                    bk |= to;
                }
            } 
            else {
                bk &= ~from;
                bk |= to;
            }
            
            if (move >> 12 != 0) {
                Bitboard cap = 1UL << ((ctz(from) + ctz(to)) / 2);
                wp &= ~cap;
                wk &= ~cap;
            }
        }

        pieces = wp | bp | wk | bk;
        wpcs = wp | wk;
        bpcs = bp | bk;
        chain = -1;

        if (move >> 12 != 0) {
            List<Move> PLmoves = GenerateMoves();
            foreach (Move m in PLmoves) {
                if ((m >> 12) == 0) break;
                if ((m & 63) == ((move >> 6) & 63)){
                    chain = m & 63;
                    return;
                }
            }
        }
        turn = !turn;
    }

    public bool IsGameOver() {
        if (wpcs == 0 || bpcs == 0) return true;
        List<Move> Moves = GenerateMoves();
        if (Moves.Count == 0) return true;
        return false;
    }

    public bool GetWinner() {
        if (wpcs == 0) return false;
        if (bpcs == 0) return true;
        List<Move> Moves = GenerateMoves();
        if (Moves.Count == 0) return !turn;
        return false;
    }
}