#include "WildCard.h"
#include <fstream>
#include <iostream>
#include <algorithm>

std::string replaceLetter(std::string pattern, int index)
{
    // Create a copy of the input pattern
    std::string word = pattern;

    // Replace the character at the specified index with '*'
    word[index] = '*';

    // Return the modified word
    return word;
}


// The createDictionary function takes a filename and a reference to an unordered_map called patternMap as input.
void createDictionary(std::string filename, std::unordered_map<std::string, std::vector<std::string>>& patternMap)
{
    // Open the file
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Error opening file!" << std::endl;
        return;
    }

    std::string word;
    while (file >> word)
    {
        for (int i = 0; i < word.length(); i++)
        {
            // Create a pattern by replacing the i-th character with '*'
            std::string pattern = word;
            pattern[i] = '*';

            // Add the word to the vector corresponding to the pattern in the patternMap
            patternMap[pattern].push_back(word);
        }
    }

    file.close();
}

