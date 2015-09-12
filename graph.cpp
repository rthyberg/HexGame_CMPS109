#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<vector>
#include<limits>
#include<set>
#include<stack>
#include<queue>
#include<algorithm>
#include<thread>
#include "graph.h"
#include "game.h"
using std::vector;
using std::set;
using std::pair;
using std::cout;

//constructor for hex graph
Graph::Graph (int hexsize) {
   size = (hexsize * hexsize);  //hexsize *hexsize will be our n by n board aka total # of nodes
   matrix.resize(size+4,vector<int>(size+4, 0));
   occupied.resize(size+4, 0);
   //occupied.resize(size+3,0);
   for(int i = 0; i < size; ++i) { //for loop to intiallize the matrix
      if(i == 0) {                 // top corner check
      matrix[i][i] = 0;
      matrix[i][i+1] = 1;
      matrix[i][i+hexsize] = 1;
      matrix[size+3][i] = 1; //top_check
      matrix[i][size+3] = 1;
      matrix[size][i] = 1;//left check
      matrix[i][size] = 1;
      }
      else if(i == (size-1)) {    // bottom corner check
              matrix[i][i] = 0;
              matrix[i][i-1] = 1;
              matrix[i][(size-1)-hexsize] = 1;
              matrix[size+2][i] = 1; //bottom_check
              matrix[i][size+2] = 1;
              matrix[size+1][i] = 1; //right check
              matrix[i][size+1] = 1;
           }
      else if(i%hexsize == 0) {  // left side check
              matrix[i][i] = 0;
              matrix[i][i-hexsize] = 1;
              matrix[i][(i-hexsize)+1] = 1;
              if(i != (size-1)-hexsize)
                 matrix[i][i+hexsize] = 1;
              matrix[i][i+1] = 1;
              matrix[size][i] = 1; //left_check
              matrix[i][size] = 1;
              if(i == (size)-hexsize) {
                 matrix[size+2][i] = 1;
                 matrix[i][size+2] = 1;
              }
           }

      else if((i+1)%hexsize == 0) { //right side check
              matrix[i][i] = 0;
              if(i != hexsize-1) {
                 matrix[i][i-hexsize] = 1;
              }
              if(i == hexsize-1) {
                 matrix[size+3][i] = 1;
                 matrix[i][size+3] = 1;
              }
              matrix[i][i+hexsize] = 1;
              matrix[i][(i+hexsize)-1] = 1;
              matrix[i][i-1] = 1;
              matrix[size+1][i] = 1; //right_check
              matrix[i][size+1] = 1;
       }
                         //middle check and top and bottom check
       else if(i<(size-1)-hexsize && i > hexsize) {
                 matrix[i][i] = 0;
                 matrix[i][i-1] = 1;
                 matrix[i][i+1] = 1;

                 matrix[i][i+hexsize] = 1;
                 matrix[i][(i+hexsize)-1] = 1;

                 matrix[i][i-hexsize] = 1;
                 matrix[i][(i-hexsize)+1] = 1;

              }
       else if(i<hexsize){
                 matrix[i][i] = 0;
                 matrix[i][i-1] = 1;
                 matrix[i][i+1] = 1;

                 matrix[i][i+hexsize] = 1;
                 matrix[i][(i+hexsize)-1] = 1;

                 matrix[size+3][i] = 1;//top_check
                 matrix[i][size+3] = 1;
           }
       else if(i>(size-1)-hexsize) {

                 matrix[i][i] = 0;
                 matrix[i][i-1] = 1;
                 matrix[i][i+1] = 1;

                 matrix[i][i-hexsize] = 1;
                 matrix[i][(i-hexsize)+1] = 1;

                 matrix[size+2][i] = 1; //bot_check
                 matrix[i][size+2] = 1;
            }
     }
   occupied[size] = 1;
   left_check = size;

   occupied[size+1] = 1;
   right_check = size+1;

   occupied[size+3] = 2;
   top_check = size+3;

   occupied[size+2] = 2;
   bottom_check = size+2;

   //print_graph();
}
Graph::Graph(Graph &oldGraph) { 
   top_check = oldGraph.top_check;
   bottom_check = oldGraph.bottom_check;
   left_check = oldGraph.left_check;
   right_check = oldGraph.right_check;
   occupied = oldGraph.occupied;
   matrix = oldGraph.matrix;
   size = oldGraph.size;
}
ostream& operator<<(std::ostream& stream, const Graph& other) {
   int whitespace = 0;
   int size = other.size;
   for(int i = 0; i < other.size; i++) {
      int count = 0;
      if(i%(static_cast<int>(sqrt(size)))==0){
         whitespace++;
         std::cout << "\n";
         while(count < whitespace){
            std::cout << " ";
            count++;
         }
         std::cout << "\\";
      }
      if(other.occupied[i] == 0)
         std::cout << "-"<< "\\";
      if(other.occupied[i] == 1)
         std::cout << "p" << "\\";
      if(other.occupied[i] == 2)
         std::cout << "c" << "\\";
       //  std::cout << other.occupied[i] << "\\";
      }
              std::cout << "\n";
}

//left over debug function from asg3/2
void Graph::print_graph () {
   std::cout << "Graph size " << size << "\n   "; //prints size
   for( int i = 0; i <size+4; ++i) {
      std::cout << "|" << i << "|\t";
   }
   for(int i = size ; i < size+4; ++i) {             //iterates through the rows and prints a new line at end of each row
      std::cout <<"\n" << i << ": ";
      for(int j = 0; j < size+ 4; ++j) {          // goes across the columns and prints the value of matrix with tab spacin
         std::cout << matrix[i][j] << "\t";
      }
   }
   std::cout << "\n";
   std::cout << "\n";
 }

// search using a vector
bool Graph::who_Wins(int source, int target, int player) {
   vector<int> queue; //who is in line
   vector<bool> set; //who has been seen
   set.resize(size+3,0); //no one so far
   queue.push_back(source); //source is in queue
   set[source] = true; //source has been seen
   while(!queue.empty()) {
      int node = queue.back(); //set node as back
      queue.pop_back();
      if(node == target) return true; //we win!!
      for(int i = 0; i<size+3; i++) { //else check its neigbors and if its occupeied by player and it its been visited
         if(matrix[node][i] == 1
            && occupied[i] == player
            && set[i] == false)
         {
               set[i] = true;
               queue.push_back(i);
         }
      }
   }
   return false;
}

// makes sure the move isnt occupied
//
bool Graph::moveValid(int x, int y) {
   if(y*11 + x > 121) return false;
   if(occupied[y*11 + x] == 0) return true;
   std::cout << " Invalid move" << "\n";
   return false;
}

// insert move into graph
void Graph::graph_insert(int x, int y, int player) {
   if (occupied[y*11 + x] == 0)
       occupied[y*11 + x] = player;
}

int Graph::monte_carlo_ai(int iterations, int move) {
  if(occupied[move] != 0) return 0; // if there is already a move here... we cant go there can we...
  occupied[move] = 2; // make ur move

  //find empty moves
  int empty_spaces_count = 0;
  vector<int> empty_spaces; // count the spots left
  for(int i = 0; i < size; i++) {
     if(occupied[i] == 0) {
        empty_spaces_count++;
        empty_spaces.push_back(i); // add there index to a vector

     }
  }

 //fill vector
 vector<int> random_moves(empty_spaces_count-1); // assign 1 and 2 to ever other vector[i]
 for(int i = 0; i<empty_spaces_count-1; i++) {
    if(i%2 == 0) random_moves[i] = 1;
    else random_moves[i] = 2;
 }

 //monte carlo
 int wins = 0;
 for(int i = 0; i < iterations; i++) {
    random_shuffle(random_moves.begin(), random_moves.end()); // do teh shuffle
    for(int j = 0; j<empty_spaces_count; j++) {
       occupied[empty_spaces[j]] = random_moves[j]; // populate occupied with the shuffle
    }
    if(who_Wins(top_check, bottom_check, 2)){ // check winner
         wins++;
   //      std::cout << " ZODFASDFAWEFRASDFAWER" << "\n";
      }
    }
  return wins;
 }






