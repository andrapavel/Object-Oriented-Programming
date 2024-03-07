#pragma once
#include<unordered_map>
#include<string>
#include<vector>

//replace a letter at the position 'index' in a word with '*'
std::string replaceLetter(std::string pattern, int index);

//create a dictionary with patterns as keys and a set of words as values
void createDictionary(std::string path, std::unordered_map<std::string, std::vector<std::string>>& patternMap);