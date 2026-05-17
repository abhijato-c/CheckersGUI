#include "Defs.h"
#include "MovePiece.h"
#include "MoveGen.h"
#include "Misc.h"
#include "MakeMove.h"
#include <thread>
#include <atomic>

std::atomic<bool> StopSignal(false);
std::thread SearchThread;

bool isConvertibleToInt(const string& str, int& value) {
    stringstream ss(str);
    ss >> value; 
    return ss && ss.eof(); 
}

void RunSearch(checkers brd, int TimeLimit, int DepthLimit){
    StopSignal = false;

    Move best = 0;

    if (TimeLimit == 0 && DepthLimit == 0) best = IterativeDeepening(brd, 3000, INT_MAX);
    else if (DepthLimit == 0) best = IterativeDeepening(brd, TimeLimit, INT_MAX);
    else if (TimeLimit == 0) best = IterativeDeepening(brd, INT64_MAX, DepthLimit);
    else  best = IterativeDeepening(brd, TimeLimit, DepthLimit);

    cout << "bestmove " << MoveToStr(best) << endl;
}

void StopSearch(){
    StopSignal = true;
    if (SearchThread.joinable()) SearchThread.join();
}

int main(){
    string line;
    checkers brd;

    while (getline(cin, line)) {
        StopSearch();

        // Split the command
        vector<string> command = {};
        istringstream stream(line);
        string token;
        while (getline(stream, token, ' ')) {command.push_back(token);}
        string cmd = command[0];

        if (cmd == "isready") {cout << "readyok" << endl;} 
        else if (cmd == "position") {
            brd.wp = stoll(command[1]);
            brd.wk = stoll(command[2]);
            brd.bp = stoll(command[3]);
            brd.bk = stoll(command[4]);
            brd.chain = stoi(command[5]);
            brd.turn = command[6] == "w";
        } 
        else if (cmd == "go") {
            string sub;
            int arg;
            bool Success = true;

            int TimeLimit = 0;
            int DepthLimit = 0;

            for(int i = 1; i < (int)command.size(); i += 2){
                sub = command[i]; 
                if (sub != "movetime" && sub != "depth"){
                    cout << "Illegal/unsupported subcommand " << sub << "!" << endl;
                    Success = false;
                    break;
                }
                if ((int)command.size() == i+1) {
                    cout << "Incomplete go command!" << endl;
                    Success = false;
                    break;
                }
                if (!isConvertibleToInt(command[i+1], arg)){
                    cout << "Invalid argument to " << sub << ": " << command[i+1] << endl;
                    Success = false;
                    break;
                }

                if (sub == "movetime"){
                    TimeLimit = arg;
                }
                else if (sub == "depth") {
                    DepthLimit = arg;
                }
            }

            if (!Success) continue;
            SearchThread = thread(RunSearch, brd, TimeLimit, DepthLimit);
        }
        else if (cmd == "stop") {
            // search already stopped when input arrived, ignore.
        }
        else if (cmd == "quit") { break; }
        else { cout << "Illegal command " << cmd << "!" << endl;}
    }
    return 0;
}