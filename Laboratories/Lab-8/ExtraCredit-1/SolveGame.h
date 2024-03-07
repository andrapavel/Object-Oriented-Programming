#pragma once
#include "Graph.h"
#include "WildCard.h"


//crete the graph with words as vertices and edges between words that differ by one letter
void createGraph(Graph<std::string>& graph, int nrLetters);

//returns the shortest path between two words using BFS
//std::vector<std::string> shortestPath(Graph<std::string>& graph, std::string start, std::string target);
std::vector<std::string> shortestPath(Graph<std::string>& graph, const std::string& start, const std::string& target);
