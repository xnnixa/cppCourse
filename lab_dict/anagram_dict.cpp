/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>
#include <iterator>
#include <map>
#include <iostream>

using std::ifstream;
using std::string;
using std::vector;

string AnagramDict::sorted_word(const string &word) const
{
    string temp = word;
    std::sort(temp.begin(), temp.end());
    return temp;
}

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */

AnagramDict::AnagramDict(const string &filename)
{
    ifstream words(filename);
    string word;
    if (words.is_open())
    {
        while (std::getline(words, word))
        {
            string key = sorted_word(word);
            auto it = std::find(dict[key].begin(), dict[key].end(), word);
            if (it == dict[key].end())
            {
                dict[key].push_back(word);
            }
        }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string> &words)
{
    for (const auto &word : words)
    {
        string key = sorted_word(word);
        auto it = std::find(dict[key].begin(), dict[key].end(), word);
        if (it == dict[key].end())
        {
            dict[key].push_back(word);
        }
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string &word) const
{
    string key = sorted_word(word);
    auto it = dict.find(key);
    if (it != dict.end())
    {
        return it->second;
    }
    return {}; // Return empty vector if no anagrams found
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    vector<vector<string>> out;
    for (auto word : dict)
    {
        if (word.second.size() > 1)
        {
            out.push_back(word.second);
        }
    }
    return out;
}
