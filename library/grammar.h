/*
File created by Steven Zinn.
Contains the grammar used in the program
*/

#ifndef GRAMMAR_H
#define GRAMMAR_H

#define C 3
#define N 5

#include <vector>
#include <string>

// Commands
#define SHOW "show"
#define DEL "del"
#define SQL "sql"

// Nouns
#define ROW "row"
#define COL "col"
#define DUPS "duplicates"
#define TABLE "table"
#define UNIQUE "unique"


// Adjectives
#define ADJ "adjective"

class Grammar
{
private:
    std::string COMMANDS[C] = {SHOW, DEL, SQL};
    std::string NOUNS[N] = {ROW, COL, DUPS, TABLE, UNIQUE};

    bool contains(std::string str, std::string arr[], int sz) 
    {
        for(int i = 0; i < sz; i++)
            if(arr[i] == str) return true;
        return false;
    }

public:
    Grammar()
    {
    }

    std::string which(std::string str)
    {
        if(contains(str, COMMANDS, C)) return "COMMAND";
        if(contains(str, NOUNS, N)) return "NOUN";
        return "ADJ";
    }
};
#endif