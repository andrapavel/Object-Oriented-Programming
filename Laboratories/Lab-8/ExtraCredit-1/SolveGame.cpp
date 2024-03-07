#include "SolveGame.h"
#include<unordered_set>
#include<queue>


//runs for 21 seconds

// It traverses the patternMap, which is a map containing words grouped by their patterns. 
// The traversal process involves iterating over the key-value pairs in the patternMap and performing operations on them.
// The function creates a graph with a specific number of vertices and edges based on the value of nrLetters
void createGraph(Graph<std::string>& graph, int nrLetters)
{
    // Create a map to store words grouped by their patterns
    std::unordered_map<std::string, std::vector<std::string>> patternMap;

    // Populate the patternMap by reading words from a dictionary file
    createDictionary("dictionary.txt", patternMap);

    // Add vertices to the graph
    for (const auto& pair : patternMap)
    {
        // Skip words that don't have the desired number of letters
        if (pair.first.size() != nrLetters)
            continue;

        const std::vector<std::string>& words = pair.second;
        const int numWords = words.size();

        // Add each word as a vertex to the graph
        for (int i = 0; i < numWords; i++)
        {
            graph.addVertex(words[i]);
        }

        // Add edges between words that differ by one letter
        for (int i = 0; i < numWords - 1; i++)
        {
            const std::string& word1 = words[i];

            for (int j = i + 1; j < numWords; j++)
            {
                const std::string& word2 = words[j];
                graph.addEdge(word1, word2);
            }
        }
    }
}

//It implements a breadth-first search (BFS) algorithm to find the shortest path between two nodes in a graph
std::vector<std::string> shortestPath(Graph<std::string>& graph, const std::string& start, const std::string& target)
{
    // Create a visited set to keep track of visited nodes
    std::unordered_set<std::string> visited;

    // Create a queue for BFS
    std::queue<std::vector<std::string>> q;

    // Mark the starting node as visited and enqueue it with an empty path
    visited.insert(start);
    q.push({ start });

    // Loop until the queue is empty
    while (!q.empty())
    {
        // Dequeue a path from the queue
        std::vector<std::string> path = q.front();
        q.pop();
        std::string curr = path.back();

        // If the last node in the path is the target, return the path
        if (curr == target)
        {
            return path;
        }

        // Get all adjacent vertices of the current node
        std::vector<std::string> neighbors = graph.getGraph()[curr];

        // Traverse through all adjacent vertices
        for (const auto& neighbor : neighbors)
        {
            // If a neighbor is not visited, mark it visited and enqueue a new path to it
            if (visited.find(neighbor) == visited.end())
            {
                visited.insert(neighbor);
                std::vector<std::string> newPath = path;
                newPath.push_back(neighbor);
                q.push(newPath);
            }
        }
    }

    // If the target is not reachable from the starting node, return an empty path
    return {};
}
