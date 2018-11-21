/**
 * @file common_words.cpp
 * Implementation of the CommonWords class.
 *
 * @author Zach Widder
 * @date Fall 2014
 */

#include "common_words.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::feof;


using namespace std;
string remove_punct(const string& str)
{
    string ret;
    std::remove_copy_if(str.begin(), str.end(), std::back_inserter(ret),
                        std::ptr_fun<int, int>(&std::ispunct));
    return ret;
}

CommonWords::CommonWords(const vector<string>& filenames)
{
    // initialize all member variables
    init_file_word_maps(filenames);
    init_common();
}

void CommonWords::init_file_word_maps(const vector<string>& filenames)
{
    // make the length of file_word_maps the same as the length of filenames
    file_word_maps.resize(filenames.size());

    // go through all files
    for (size_t i = 0; i < filenames.size(); i++) {
        // get the corresponding vector of words that represents the current
        // file
        vector<string> words = file_to_vector(filenames[i]);
        /* Your code goes here! */
        map<std::string, unsigned int> memo;
        for (size_t i=0; i<words.size(); i++)
        {
          // map<std::string, unsigned int>::iterator lookup = memo.find(words[i]);
          // if (lookup != memo.end())
              memo[words[i]] += 1;
          // else
          //   memo[words[i]] = 1;
          // cout<<words[i]<<" "<<memo[words[i]]<<endl;
        }
        // std::cout<<memo<<std::endl;
        file_word_maps[i] = memo;
        //Why is find not necessary? Don't you have to initialize the words that haven't been yet declared?
    }
}

void CommonWords::init_common()
{
    /* Your code goes here! */
    for (size_t i=0; i<file_word_maps.size(); i++)
    {
      map<string,unsigned int > m = file_word_maps[i];
      for(std::pair<const std::string,unsigned int> &key_val : m)
      {
        map<std::string, unsigned int>::iterator lookup = common.find(key_val.first);
        if (lookup != common.end())
            common[key_val.first] += 1;
        else
          common[key_val.first] = 1;
      }
    }
}

/**
 * @param n The number of times to word has to appear.
 * @return A vector of strings. The vector contains all words that appear
 * in each file >= n times.
 */
vector<string> CommonWords::get_common_words(unsigned int n) const
{
    vector<string> out;
    /* Your code goes here! */
    // for (std::pair<const string,unsigned int> val:common)
    // {
    //   if(val.second == file_word_maps.size())
    //   {
    //     map<std::string, unsigned int>::iterator lookup;
    //     for(map<string,unsigned int> num: file_word_maps)
    //     {
    //       lookup = num.find(val.first);
    //       if(lookup->second < n){
    //         break;
    //       }
    //     }
    //     if(lookup->second >= n){
    //       // cout<<lookup->second<<endl;
    //       out.push_back(val.first);
    //     }
    //   }
    // }
    // return out;
    // why does it give me const error whenver I try to reference "num" (to &num)????
    for(std::pair<const string,unsigned int> val:common)
    {
      if(val.second == file_word_maps.size()){

        unsigned temp=0;

        for(size_t i =0; i< file_word_maps.size(); i++)
        {
          temp = file_word_maps[i].at(val.first);
          if(temp < n)
            break;
        }

        if(temp >= n)
        {
          out.push_back(val.first);
        }

      }
    }

    return out;


  }

    // return out;

/**
 * Takes a filename and transforms it to a vector of all words in that file.
 * @param filename The name of the file that will fill the vector
 */
vector<string> CommonWords::file_to_vector(const string& filename) const
{
    ifstream words(filename);
    vector<string> out;

    if (words.is_open()) {
        std::istream_iterator<string> word_iter(words);
        while (!words.eof()) {
            out.push_back(remove_punct(*word_iter));
            ++word_iter;
        }
    }
    return out;
}
