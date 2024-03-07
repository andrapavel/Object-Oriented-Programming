#pragma once

#include <iostream>
#include <unordered_map>
#include <list>

template <typename T>
class Graph
{
private:
    std::unordered_map<T, std::vector<T>> adjacencyList;

public:
    // add a vertex to the graph
    void addVertex(T vertex)
    {
        adjacencyList[vertex];
    }

    // add an edge between two vertices of the graph
    void addEdge(T vertex1, T vertex2)
    {
        adjacencyList[vertex1].push_back(vertex2);
        adjacencyList[vertex2].push_back(vertex1);
    }

    // remove an edge between two vertices of the graph
    void removeEdge(T vertex1, T vertex2)
    {
        adjacencyList[vertex1].remove(vertex2);
        adjacencyList[vertex2].remove(vertex1);
    }

    // remove a vertex and all its edges from the graph
    void removeVertex(T vertex)
    {
        adjacencyList.erase(vertex);
        // remove vertex 
        for (auto& pair : adjacencyList)
        {
            // remove edge
            pair.second.remove(vertex);
        }
    }

    std::unordered_map<T, std::vector<T>> getGraph()
    {
        return adjacencyList;
    }

    // print adjecency List
    void print() const
    {
        for (auto const& pair : adjacencyList)
        {
            std::cout << pair.first << ": ";

            for (auto const& vertex : pair.second)
            {
                std::cout << vertex << " ";
            }
            std::cout << std::endl;
        }
    }
};

