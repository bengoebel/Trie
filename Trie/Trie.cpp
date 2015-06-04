//
//  Trie.cpp
//  Trie
//
//  Created by Ben Goebel on 5/11/15.
//  Copyright (c) 2015 Ben Goebel. All rights reserved.
//
//  This is the implementation for the Trie class.
//

#include "Trie.h"


// The constructor
Trie::Trie()
{
    root = new trie_node();
    root->lett = ' ';
    root->isWord = false;
    numWords = 0;
}

// The destructor
Trie::~Trie()
{
    delete_all(root);
}

// Purpose: Inserts a word into the list if it is not already in the list.
// Arguments: A string: the word to be inserted into the list.
// Returns: A bool: true if the word is inserted into the list, and false
//          if the word is already in the list.
bool Trie::insert(string word)
{
    word = make_uppercase(word);
    trie_node *temp = root;
    bool already_there = true;  // The word is already in the list.
    int pos;
    for(int i = 0; i < (int)word.length(); i++)
    {
        pos = get_alpha_num( word[i] );
        if( pos == -1 )     // Invalid character check
            return false;
        if( temp->children[pos] == NULL )  // If the letter is not in the list,
        {                                  // add it to the list.
            already_there = false;
            temp->children[pos] = new trie_node();
            temp = temp->children[pos];
            temp->lett = word[i];
            if( i == (int)word.length() - 1 )   // If it's the last letter,
                temp->isWord = true;       // mark it.
            else
                temp->isWord = false;
        }
        else
        {                                   // Otherwise, continue traversing
            temp = temp->children[pos];     // the list.
            if( i == (int)word.length() - 1 && !temp->isWord )
            {                                 // If you're at the last letter
                temp->isWord = true;          // make it a word.
                already_there = false;
            }
        }
    }
    if( !already_there )
        numWords++;
    return !already_there;
}

// Purpose: Checks to see if the user's input is a prefix in the list.
// Arguments: A string: the prefix to check.
// Returns: A bool: true if the user's input is a prefix in the list and
//          false if otherwise.
bool Trie::isPrefix(string input)
{
    input = make_uppercase(input);
    return isPrefix(root, input);
}

// Purpose: Checks to see if the user's input is a word in the list.
// Arguments: A string: the word to check.
// Returns: A bool: true if the word is in the list, and false if otherwise.
bool Trie::isWord(string word)
{
    word = make_uppercase(word);
    return isWord(root, word);
}

// Purpose: Removes the word from the list.
// Arguments: A string: the word to be removed from the list.
// Returns: A bool: true if the word is removed from the list, and false
//          if the word is not in the list.
bool Trie::remove(string word)
{
    word = make_uppercase(word);
    bool is_removed = remove(root, word, (int)word.length());
    if( is_removed )
        numWords--;
    return is_removed;
}

// Purpose: Prints out all the words in the list.
// Arguments: None
// Returns: Nothing
void Trie::print()
{
    stack<char> s;
    cout << "Words in the list: " << endl;
    print(s, root, true);
}

// Purpose: Removes all the words in the list.
// Arguments: None
// Returns: Nothing
void Trie::remove_all()
{
    delete_all(root);
    root = new trie_node();
    root->lett = ' ';
    root->isWord = false;
    numWords = 0;
}

// Purpose: Gets the number of words in the list.
// Arguments: None
// Returns: An int: the number of words in the list.
int Trie::num_words()
{
    return numWords;
}

// Purpose: Checks to see if the user's input is a prefix in the list.
// Arguments: A trie_node: the list we are looking through
//            for the prefix. A string: the prefix to check
// Returns: A bool: true if the user's input is a prefix in the list and
//          false if otherwise.
bool Trie::isPrefix(trie_node *temp, string input)
{                                       // Check if the node's child's lett
    if( input.length() == 0 )           // is equal to the first letter in the
        return false;                   // word, and do this for the rest of
    int pos = get_alpha_num(input[0]);  // the input until the end of the input.
    if( pos == -1 )     // Invalid character check
        return false;
    if( temp->children[pos] == NULL )
        return false;
    if( temp->children[pos]->lett == input[0] && input.length() == 1 )
        return true;
    else if( temp->children[pos]->lett == input[0] )
        return isPrefix( temp->children[pos],input.substr(1) );
    else
        return false;
}

// Purpose: Checks to see if the user's input is a word in the list.
// Arguments: A trie_node: the list we are looking through
//            for the word. A string: the word we are looking for in the list.
// Returns: A bool: true if the word is in the list, and false if otherwise.
bool Trie::isWord(trie_node *temp, string word)
{                                       // Check if the node's child's lett
    if( word.length() == 0 )            // is equal to the first letter in the
        return false;                   // word, and do this for the rest of
    int pos = get_alpha_num(word[0]);   // the word until the end of the word.
    if( pos == -1 )     // Invalid character check
        return false;
    if( temp->children[pos] == NULL )
        return false;
    if( temp->children[pos]->lett == word[0]                   // Check if the
       && temp->children[pos]->isWord && word.length() == 1 )  // node
        return true;  // containing the last letter in the word is a word.
    else if( temp->children[pos]->lett == word[0] )
        return isWord( temp->children[pos], word.substr(1) );
    else
        return false;
}

// Purpose: Removes the word from the list.
// Arguments: A trie_node: the part of the list we are looking through
//            for the word. A string: the word to be removed from the list.
//            An int: the original size of the word.
// Returns: A bool: true if the word is removed from the list, and false
//          if the word is not in the list.
bool Trie::remove(trie_node *node, string word, int orig_size)
{
    if( word.length() == 0 && orig_size > 0 )   // Prevents empty inputs from
        return true;                            // returning true
    trie_node *temp_prev = NULL;
    trie_node *temp = node;
    int pos = 0;
    for(int i = 0; i < (int)word.length(); i++)     // Traverse through all
    {                                               // the nodes to get to
        pos = get_alpha_num(word[i]);               // the node that contains
        if( pos == -1 ) // Invalid character check  // the last letter in the
            return false;                           // word.
        temp_prev = temp;
        temp = temp->children[pos];
        if( temp == NULL )
            return false;
    }
    if( word.length() == orig_size && !temp->isWord ) // Word validation check
        return false;
    if( !is_leaf(temp) )                     // If the node is not a leaf,
    {                                        // return true. Before returning,
        if( word.length() == orig_size )     // if this is the last letter in
            temp->isWord = false;            // the original word, change it
        return true;                         // to not a word.
    }
    if( temp->isWord && word.length() != orig_size )
        return true;
    temp_prev->children[pos] = NULL;  // If the node is a leaf, delete it and
    delete temp;                      // call remove on its preceding nodes.
    return remove(node, word.substr(0, word.length() - 1 ), orig_size);
}

// Purpose: Deletes all the words in the list
// Arguments: A trie_node: the list we are deleting
// Returns: Nothing
void Trie::delete_all(trie_node *temp)
{
    if( temp != NULL )
    {
        for(int i = 0; i < ALPHA; i++)          // If the node is not NULL,
        {                                       // delete its children and then
            delete_all(temp->children[i]);      // delete the node.
        }
        delete temp;
    }
}

// Purpose: Prints all the words in the list.
// Arguments: A stack: the data structure that will be used to print all the
//            the words in the list. A trie_node: the list we are
//            looking through. A bool: whether or not the node
//            we are examining is the root.
// Returns: Nothing.
void Trie::print(stack<char> s, trie_node *temp, bool isRoot)
{
    if( temp != NULL )
    {
        if( !isRoot )           // Don't add root because no meaningful
        {                       // character is stored in it.
            s.push(temp->lett); // Add letter to stack if the node is not
            if( temp->isWord )  // the root and print the stack if the node
                print_stack(s); // is the last letter in the word.
        }
        for(int i = 0; i < ALPHA; i++)
        {
            print(s, temp->children[i], false);    // Prints next letter
        }
        if( !s.empty() )    // Remove the letter from the stack after
            s.pop();        // after adding and printing the rest of the letters
    }                       // in the words.
}


// Purpose: Gets the character's place in the alphabet.
// Arguments: A char: the character needed to find its numerical alphabetical
//            position.
// Returns: An int: the character's numerical alphabetical position. If the
//          character is not in the alphabet, return -1.
int Trie::get_alpha_num(char c)
{
    for(int i = 0; i < ALPHA; i++ )
    {                             // Find the character's place in the alphabet
        if( ALPHABET[i] == c )    // and return it. If the character is not
            return i;             // in the alphabet, return -1.
    }
    return -1;
}

// Purpose: Determines if the node being examined is a leaf.
// Arguments: A trie_node: the node being examined.
// Returns: A bool: true if the node is a leaf and false if otherwise.
bool Trie::is_leaf(trie_node *node)
{
    for(int i = 0; i < ALPHA; i++)      // Look through all the node's children.
    {                                   // If they're all NULL, return true.
        if( node->children[i] != NULL ) // Otherwise, return false.
            return false;
    }
    return true;
}

// Purpose: Prints all the elements in the stack. The first element inserted
//          will be printed first and the last element inserted will be
//          printed last.
// Arguments: A stack: the stack that will be printed out.
// Returns: Nothing
void Trie::print_stack(stack<char> s)
{
    stack<char> reverse;    // The stack in reversed order.
    while( !s.empty() )
    {
        reverse.push(s.top());  // Take the elements from the original stack
        s.pop();                // and put them in the new stack in reversed
    }                           // order.
    while( !reverse.empty() )
    {                           // Until the new stack is empty, print the
        cout << reverse.top();  // first element and then removed it.
        reverse.pop();
    }
    cout << endl;
}

// Purpose: Converts the word to all uppercase letters.
// Arguments: A string: the word.
// Returns: A string: the word in all uppercase letters.
string Trie::make_uppercase(string word)
{
    for(int i = 0; i < (int)word.length(); i++) // Traverse each letter in
    {                                           // the word and convert it
        word[i] = toupper(word[i]);             // to uppercase.
    }
    return word;
}


