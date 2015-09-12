#include<iostream>
#include<cstdlib>
#include<cmath>
#include<vector>
#include<queue>
#include<thread>
#include "graph.h"
#include "game.h"
int main(int argc, char** argv)
{
int threading = std::thread::hardware_concurrency();
std::cout << "There are " << threading <<" cores" << "\n";
  srand(time(0));
  std::cout << "Lets play hex\n";
  
 Game* test = new Game(threading);
 test->game_loop();
  // test.print_board();
 //  test.board->simulate();

 // Graph test2(11); //constructs hexboard 11x11 
 //test2.simulate(); 
 // std::cout << test2;
  std::cout << "\n" << "END OF GAME \n\n";

 return 0;
}
