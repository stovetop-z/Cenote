#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "grammar.h"
#include <utility>
#include <sstream>

class Translator
{
private:
    std::vector<std::string> lexed;
    std::vector<std::string> cmd;

    std::string command;
    Grammar grammar;

    bool lexer(std::string cmd)
    {
        command = cmd;
        if(command.size() < 1) return false;

        std::stringstream ss(command);
        std::string word;
        while(getline(ss, word, ' '))
        {
            word = grammar.which(word) + " " + word;
            lexed.push_back(word);
        }

        return true;
    }

    std::string parser()
    {
        int ind = 0;

        std::string exp = "";
        for(auto& word : lexed)
        {
            std::stringstream ss(word);
            std::string gram, key;
            ss >> gram >> key;
            if(exp == "")
            {
                if(gram != "COMMAND") return "Must begin with command: SHOW, DEL, SQL";
                else exp = "NOUN";
            }
            else if(gram != exp) return "Expected a " + exp + ", got " + gram;
            else if(gram == "NOUN") exp = "ADJ";
            else if(gram == "ADJ") exp = "NOUN";
            cmd.push_back(key);
        }

        return "Valid";
    }

public:
    Translator() 
    {
    }

    std::pair<std::vector<std::string>, std::string> interpret(std::string com) 
    { 
        if(lexer(com))
        {
            std::string p = parser();
            return std::make_pair(cmd, p); 
        }
        return std::make_pair(cmd, "Invalid command");
    }

    ~Translator(){}

};
#endif