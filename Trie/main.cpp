//
//  main.cpp
//  Trie
//
//  Created by Ben Goebel on 5/16/15.
//  Copyright (c) 2015 Ben Goebel. All rights reserved.
//
// This file runs the Trie program.
//

#include "Trie.h"

void run_insert(Trie *t);
void run_isPrefix(Trie *t);
void run_isWord(Trie *t);
void run_remove(Trie *t);
void run_print(Trie *t);
void run_remove_all(Trie *t);
void run_num_words(Trie *t);

int main()
{
    Trie t;
    string input = "";
    cout << "Please type a command: 'insert', 'isPrefix', 'isWord', " << endl;
    cout << "'remove', 'print', 'remove_all', 'num_words' " << endl;
    cout << "or 'end' to end the program. " << "Input is case sensitive.";
    cout << endl;
    while(input != "end")
    {
        cout << "Command: ";
        cin >>input;
        if( input == "insert" )
            run_insert(&t);
        else if( input == "isPrefix" )
            run_isPrefix(&t);
        else if( input == "isWord" )
            run_isWord(&t);                 // Pass the trie by reference.
        else if( input == "remove" )
            run_remove(&t);
        else if( input == "print" )
            run_print(&t);
        else if( input == "remove_all" )
            run_remove_all(&t);
        else if( input == "num_words" )
            run_num_words(&t);
    }
    return 0;
}

// Purpose: Runs the insert function.
// Arguments: A pointer to a Trie: the list we are inserting words into.
// Returns: Nothing
void run_insert(Trie *t)
{
    string input = "";
    cout << "Please enter words to input into the list. ";
    cout << "End input by inputing '.' " << endl;
    cout << "Input: ";
    cin >> input;
    cout << endl;
    while( input != "." )
    {
        if( t->insert(input) )
            cout << "The word entered has been inserted into the list." << endl;
        else
            cout << "The word entered is already in the list." << endl;
        cout << "Input: ";
        cin >> input;
        cout << endl;
    }
}

// Purpose: Runs the isPrefix function.
// Arguments: A pointer to a Trie: the list being examined.
// Returns: Nothing
void run_isPrefix(Trie *t)
{
    string input = "";
    cout << "Please enter a prefix to check in the list. ";
    cout << "End input by inputing '.' " << endl;
    cout << "Input: ";
    cin >> input;
    cout << endl;
    while( input != "." )
    {
        if( t->isPrefix(input) )
            cout << "The word entered is a prefix in the list." << endl;
        else
            cout << "The word entered is not a prefix in the list." << endl;
        cout << "Input: ";
        cin >> input;
        cout << endl;
    }
}

// Purpose: Runs the isWord function.
// Arguments: A pointer to a Trie: the list being examined.
// Returns: Nothing
void run_isWord(Trie *t)
{
    string input = "";
    cout << "Please enter a word to check in the list. ";
    cout << "End input by inputing '.' " << endl;
    cout << "Input: ";
    cin >> input;
    cout << endl;
    while( input != "." )
    {
        if( t->isWord(input) )
            cout << "The word entered is in the list." << endl;
        else
            cout << "The word entered is not in the list." << endl;
        cout << "Input: ";
        cin >> input;
        cout << endl;
    }
}

// Purpose: Runs the remove function.
// Arguments: A pointer to a Trie: the list we are removing words from.
// Returns: Nothing
void run_remove(Trie *t)
{
    string input = "";
    cout << "Please enter a word to remove from the list. ";
    cout << "End input by inputing '.' " << endl;
    cout << "Input: ";
    cin >> input;
    cout << endl;
    while( input != "." )
    {
        if( t->remove(input) )
        {
            cout << "The word entered has been removed from the list.";
            cout << endl;
        }
        else
            cout << "The word entered is not in the list." << endl;
        cout << "Input: ";
        cin >> input;
        cout << endl;
    }
}

// Purpose: Runs the print function.
// Arguments: A pointer to a Trie: the list being printed.
// Returns: Nothing
void run_print(Trie *t)
{
    t->print();
}

// Purpose: Runs the remove_all function.
// Arguments: A pointer to a Trie: the list that is being erased.
// Returns: Nothing
void run_remove_all(Trie *t)
{
    t->remove_all();
    cout << "All words have been removed from the list." << endl;
}

// Purpose: Runs the num_words function.
// Arguments: A pointer to a Trie: the list being examined.
// Returns: Nothing
void run_num_words(Trie *t)
{
    cout << "They're are " << t->num_words() << " word(s) in the list." << endl;
}




