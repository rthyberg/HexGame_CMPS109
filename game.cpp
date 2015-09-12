#include <iostream>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <thread>
#include <functional>
#include "game.h"
#include "graph.h"
//using namespace std;
using std::cout;
using std::thread;
using std::vector;
using std::cin;

//a constructor
Game::Game(int threading) {
  // cout << "constrotor test";
   board = new Graph(11);
   threads = threading;
   print_board();
}

// calls the << overload from graph
void Game::print_board() {
  std::cout << *board;
}

// has the player make a move
void Game::player_move() {
   int x,y;

   while(true) {
      cout << "Player turn: " << "\n";
      cout << "Enter x: ";
      cin >> x;
      cout << "\n";
      cout << "Enter y: ";
      cin >> y;
      cout << "\n";
      if(board->moveValid(x,y)) {
         board->graph_insert(x,y,1);
         break;
      }
   }
}


 // back when threading didnt make sense  we used this to thread print statements
void Game::printshit()
{
cout << "threading test \n";
}

 // basic vector add overload
template <typename T>
std::vector<T> operator+(const std::vector<T>& a, const std::vector<T>& b)
{
    //assert(a.size() == b.size());

    std::vector<T> result;
    result.reserve(a.size());

    std::transform(a.begin(), a.end(), b.begin(),
                   std::back_inserter(result), std::plus<T>());
    return result;
}

void Game::threading_ai(int threading, vector<int> &final_vector) {
   thread core = thread(std::bind (&Game::get_ai, this, 500, final_vector)); 
   vector<int> main_thread_weight(121,0);
   get_ai(500, main_thread_weight);
   core.join();

   final_vector = final_vector + main_thread_weight;


}



void Game::get_ai(int iterations, vector<int> &winning_nodes) {

 for(int i = 0; i <121; i++){                        // loops throught nodes to find possiable moves
     Graph* rboard = new Graph(*board);
    // std::cout << rboard->occupied[i] <<"\n";
     if(rboard->occupied[i] == 0){                   // if there isnt a move we will monte carlo
        winning_nodes[i] = rboard->monte_carlo_ai(iterations, i); // keep a vector of # of wins
       // std::cout << i <<": " << winning_nodes[i] << "\n";
     }
     delete rboard;
  }
}

void Game::computer_move(int do_we_thread) {
   int x, y;
   vector<int> winning_nodes(121,0);
   //winning_nodes.resize(121,0);
   std::cout << "Calculating optimal move" << "\n";
  if(do_we_thread > 1) {
  std::cout << " Threading... " << "\n";
  threading_ai(do_we_thread, winning_nodes);
  } else {
   get_ai(1000, winning_nodes);
}
   int current_index = 0;
   int winning_index = -1;
   int most_wins = -1;
   int current_wins = 0;
   for(int i = 0; i <121; i++) { // cycle through nodes to find biggest
      current_wins = winning_nodes[i];
      if(current_wins > most_wins) {
         winning_index = i;
         most_wins = current_wins;
      }
   }


   x = winning_index%11;
   y = winning_index/11;
   std:: cout << "x: " << x << "\t y: " << y << "\t index: " << winning_index << "\n";
   if(board->moveValid(x,y)) {
      board->graph_insert(x,y,2); // move to teh most likely spot to win
   }

}

void Game::game_loop() {

for(int i = 122; i>1; i--) { // basic loop... ull figure it out

         if(board->who_Wins(board->top_check, board->bottom_check, 2)){
           std::cout << "Computer Wins" << "\n";
           break;
         }
         if(board->who_Wins(board->left_check, board->right_check, 1)){
           std::cout << "Player Wins" << "\n";
           break;
         }


      if( i%2 == 0)
         player_move();
      else computer_move(threads);
      print_board();
   }

}

