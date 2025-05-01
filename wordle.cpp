#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <vector>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void allCombos( const string& in,
    const string& floating,
    const set<string>& dict, 
    set<string>& possibleWords,
    vector<char>& wordBuilder,
    size_t idx);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> possibleWords;
    vector<char> wordBuilder;
    allCombos(in, floating, dict, possibleWords, wordBuilder, 0);
    return possibleWords;
}

// Define any helper functions here
void allCombos( const string& in,
    const string& floating,
    const set<string>& dict, 
    set<string>& possibleWords,
    vector<char>& wordBuilder,
    size_t idx)
{   //base case
    if (idx == in.size()){
        string word = string(wordBuilder.begin(), wordBuilder.end());
        if (dict.find(word) == dict.end()){
            return;
        }
        //count letters in empty spots
        map<char, int> emptySpots;
        map<char, int> floaters;
        for (int i = 0; i < word.size(); i++){
            if (in[i] == '-'){
                emptySpots[word[i]]++;
            }
        }
        //set boundary for next loop
        int l = 0;
        if (in.length() > floating.length()){
            l = in.length(); 
        }
        else{
            l = floating.length();
        }
        //store floating letter counts 
        for (int i = 0; i < l; i++){
            if (i < floating.length()){
                floaters[floating[i]]++;
            }
            if (i < in.length() && in[i] != '-'){
                if (floaters.count(in[i])){
                    floaters[in[i]]--;
                    if (floaters[in[i]] == 0){
                        floaters.erase(in[i]);
                    }
                }
            }
        }
        //check if floating letters were used
        bool flag = true;
        for (map<char, int>::iterator it = floaters.begin(); it!= floaters.end(); it++){
          if (emptySpots[it->first] < it->second){
            flag = false;
            break;
          }
        }
        if (flag == true){
          possibleWords.insert(word);
        }
        return;
    }
    //recursive cases
    if (in[idx] == '-'){
      for (char current = 'a'; current <= 'z'; current++){
        wordBuilder.push_back(current);
        allCombos(in, floating, dict, possibleWords, wordBuilder, idx + 1);
        wordBuilder.pop_back();
      }
    } 
    else{
        wordBuilder.push_back(in[idx]);
        allCombos(in, floating, dict, possibleWords, wordBuilder, idx + 1);
        wordBuilder.pop_back();
    }
}
