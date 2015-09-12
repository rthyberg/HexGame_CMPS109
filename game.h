#include <vector>
#include <cstdlib>
#include <utility>
#include "graph.h"


#ifndef GAME_H
#define GAME_H

class Game{
    public:
    Game(int);
    void print_board();
    void player_move();
    void computer_move(int);
    void game_loop();
    void get_ai(int, std::vector<int>&);
    void threading_ai(int, std::vector<int>&);
    void printshit();
    private:
    int threads;
    Graph* board;
};
#endif
