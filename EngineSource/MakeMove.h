#ifndef MAKEMOVE_H
#define MAKEMOVE_H

#include "Defs.h"
#include "MoveGen.h"
#include "MovePiece.h"
#include "Misc.h"

inline int MiniMax(checkers &b, int depth, int alpha, int beta, timept start = chrono::high_resolution_clock::now(), int64_t time = INT64_MAX){
    //check for game over, higher eval for delayed checkmate
    if(b.wpcs == 0 || b.bpcs == 0) return (-inf + 30 - depth);
    if(depth == 1) return StaticEval(b);

    MoveList Moves = LegalMoves(b);

    // Compute static evals of each position for move ordering
    int StaticEvals[Moves.size()];
    for (int i=0; i<Moves.size(); ++i){
        Move m = Moves[i];
        int score = 0;
    
        // Capture check
        if ((m << 13) & 2){
            score += 100;
        }
        // Promotions

        StaticEvals[i] = score;
    }

    // Evaluate positions in order of static evals
    for(int i=0; i<Moves.size(); ++i){
        // Find position with highest static eval
        int MaxEval = StaticEvals[0];
        int MaxIndex = 0;
        for(int j=1; j<Moves.size(); ++j){
            if(StaticEvals[j] > MaxEval){ 
                MaxEval = StaticEvals[j]; 
                MaxIndex=j;
            }
        }
        StaticEvals[MaxIndex] = -inf;
        MovePiece(Moves[MaxIndex], b);
        if (b.chain != -1) 
            alpha = max(MiniMax(b, depth, alpha, beta, start, time), alpha);
        else
            alpha = max(-MiniMax(b, depth-1, -beta, -alpha, start, time), alpha);
        UnmovePiece(Moves[MaxIndex], b);

        if(alpha >= beta || TimeElapsed(start) > time || StopSignal.load()) return alpha;
    }
    return alpha;
}

inline Move IterativeDeepening(checkers &b, int64_t time, int Mdepth){
    timept StartTime = chrono::high_resolution_clock::now();
    int CurrentDepth = 3;
    Move OverallBestMove = 0;
    int BestEval = -inf;
    while(TimeElapsed(StartTime) < time && CurrentDepth <= Mdepth && !StopSignal.load()){
        int eval;
        int bestmove = 0;
        int alpha = -inf;
        int beta = inf;
        MoveList Moves = LegalMoves(b);

        // Compute static evals of each position for move ordering
        int StaticEvals[Moves.size()];
        for (int i=0; i<Moves.size(); ++i){
            Move m = Moves[i];
            int score = 0;
        
            // Capture check
            if ((m << 13) & 2){
                score += 100;
            }
            // Promotions

            StaticEvals[i] = score;
        }

        // Evaluate positions in order of static evals
        for (int i=0; i<Moves.size(); ++i){
            // Find position with highest static eval
            int MaxEval = StaticEvals[0];
            int MaxIndex = 0;
            for(int j=1; j<Moves.size(); ++j){
                if(StaticEvals[j] > MaxEval){ 
                    MaxEval = StaticEvals[j]; 
                    MaxIndex=j;
                }
            }
            StaticEvals[MaxIndex] = -inf;
            MovePiece(Moves[MaxIndex], b);
            if (b.chain != -1) 
                eval = MiniMax(b, CurrentDepth, alpha, beta, StartTime, time);
            else
                eval = -MiniMax(b, CurrentDepth-1, -beta, -alpha, StartTime, time);
            UnmovePiece(Moves[MaxIndex], b);
            
            if(TimeElapsed(StartTime) > time || StopSignal.load()){
                if(alpha > BestEval) return bestmove; 
                return OverallBestMove;
            }
            if(eval>alpha){
                alpha=eval;
                bestmove=Moves[MaxIndex];
            }
            if(alpha>=beta) break;
        }
        BestEval = alpha;
        OverallBestMove = bestmove;
        cout << "info Depth: " << CurrentDepth << ", Move: " << MoveToStr(OverallBestMove) << endl;
        ++CurrentDepth;
    }
    return OverallBestMove;
}

#endif