//
//  Trie.h
//  Trie
//
//  Created by Ben Goebel on 5/11/15.
//  Copyright (c) 2015 Ben Goebel. All rights reserved.
//
//  This is the header file for the Trie class.
//

#ifndef __Trie__Trie__
#define __Trie__Trie__

#include <iostream>
#include <string>
#include <stack>

using namespace std;

const int ALPHA = 26;   // Length of the alphabet
const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

struct trie_node
{
    char lett;
    trie_node *children[ALPHA];
    bool isWord;
};

class Trie
{
public:
    Trie(); // The constructor
    ~Trie();    // The destructor
    bool insert(string word);   // Inserts a word into the list if it is not
                                // already in the list
    bool isPrefix(string input); // Checks to see if the user's input is a
                                 // prefix in the list
    bool isWord(string word);   // Checks to see if the user's input is a word
                                // in the list
    bool remove(string word);   // Removes the word from the list
    void print();               // Prints out all the words in the list
    void remove_all(); // Deletes every word in the list
    int num_words();    // Gets the number of words in the list
private:
    trie_node *root;
    int numWords;   // Number of words in the list
    bool isPrefix(trie_node *temp, string word); // Checks to see if the user's
                                            // input is a prefix in the list
    bool isWord(trie_node *temp, string word); // Checks to see if the user's
                                               // input is a word in the list
    bool remove(trie_node *node, string word, int orig_size); // Removes the
                                                        // word from the list
    void delete_all(trie_node *temp);   // Deletes all the words from the list
    void print(stack<char> s, trie_node *temp, bool isRoot); // Prints all the
                                                        // words in the list
    int get_alpha_num(char c);  // Gets the characters place in the alphabet
    bool is_leaf(trie_node *node); // Determines if the node is a leaf
    void print_stack(stack<char> s); // Prints all the elements in the stack
    string make_uppercase(string word);   // Converts the word to all uppercase
                                          // letters
};


#endif /* defined(__Trie__Trie__) */
