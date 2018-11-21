/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <iostream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */
    ifstream wordsFile(word_list_fname);
    string word;
    if(wordsFile.is_open()){
      while(getline(wordsFile,word)){
        if(word.size()>3){
        std::string word_two = word.substr(1,word.length()-1);
        std::string word_three = word[0]+ word.substr(2,word.length()-1);
        if(d.homophones(word,word_two)&&d.homophones(word,word_three)&&d.homophones(word_two,word_three))
        {
          ret.push_back(make_tuple(word,word_two,word_three));
        }
      }
      }
    }
    return ret;
    
}
