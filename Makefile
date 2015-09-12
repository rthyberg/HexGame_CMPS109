all: graph.cpp game.cpp main.cpp
	g++ -std=c++11 -lpthread -o graph graph.cpp game.cpp main.cpp

thread: graph.cpp game.cpp main.cpp
	g++ -std=c++0x -pthread -o graph graph.cpp game.cpp main.cpp

graph: graph.cpp 
	g++ -std=c++11 -o graph graph.cpp
clean:
	rm graph
