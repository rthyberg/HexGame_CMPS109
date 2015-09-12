#ifndef GRAPH_H
#define GRAPH_H

using std::vector; 
using std::ostream;                                         
//graph class
class Graph {   
vector<vector<int>> matrix; //our graph that will be constructed as 2d vector
public:
   int size; 
   vector<int> occupied;
   Graph(int); // our constructor for hexboard where [int] is the dimensions
   Graph(Graph &Graph);//copy constructor
   void print_graph(); // declare the print function
   bool simulate(int);
   bool who_Wins(int, int, int);
   void graph_insert(int,int,int);
   bool moveValid(int, int);
   int monte_carlo_ai(int, int);                                   
   friend ostream& operator<<(std::ostream& stream, const Graph& other); 
   int top_check;
   int bottom_check;
   int left_check;
   int right_check;
 
 };

         
#endif
