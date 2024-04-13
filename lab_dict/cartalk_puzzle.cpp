/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <vector>
#include <fstream>
#include <string>
#include <cctype>
#include <iostream>
#include <algorithm>
#include <tuple>

#include "cartalk_puzzle.h"

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of "StringTriples" (a typedef'd std::tuple, see top of
 * cartalk_puzzle.h). Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
std::vector<StringTriple> cartalk_puzzle(PronounceDict d, const std::string &word_list_fname)
{
    std::vector<StringTriple> results;
    std::ifstream words(word_list_fname);
    std::string word;

    if (words.is_open())
    {
        while (std::getline(words, word))
        {
            if (word.size() >= 5)
            {
                std::transform(word.begin(), word.end(), word.begin(),
                               [](unsigned char c)
                               { return std::toupper(c); });

                std::string firstCharR = word.substr(1);
                std::string secondCharR = std::string(1, word.at(0)) + word.substr(2);

                if (d.homophones(word, firstCharR) && d.homophones(word, secondCharR))
                {
                    results.push_back(StringTriple(word, firstCharR, secondCharR));
                }
            }
        }
    }

    return results;
}
