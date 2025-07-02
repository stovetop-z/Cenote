#ifndef CENOTE_H
#define CENOTE_H

#include "line.h"
#include <fstream>
#include <tuple>
#include <algorithm>
#include "library/hash_map.h"
#include "library/translator.h"

class Cenote
{
private:
    std::vector<Line> matrix;
    HashMap hash_map;
    int rows, cols;
    void lower(std::string& str) {for(char& c : str) std::tolower(c);}
    bool isNumeric(const std::string& str) {return (str[0] == '0' || str[0] == '1' || str[0] == '2' || str[0] == '3' || str[0] == '4' || str[0] == '5' || str[0] == '6' || str[0] == '7' || str[0] == '8' || str[0] == '9') ? true : false;}

    bool isValid(std::string line, std::string ind)
    {
        int index = -1;
        if(line == "row")
        {
            if(isNumeric(ind))
            {
                index = std::stoi(ind);
                if(index > matrix.size() || index < 0) return false;
            }
        }
        if(line == "col")
        {
            if(isNumeric(ind))
            {
                index = std::stoi(ind);
                if(index > matrix[0].getLine().size() || index < 0) return false;
            }
        }
        
        return true;
    }

    std::string show(std::vector<std::string> command)
    {
        int r = -1;
        int c = -1;
        for(size_t i = 0; i < command.size(); i++)
        {
            auto word = command[i];
            if(word == "duplicates")
            {
                std::string str = "";
                for(auto& dups : hash_map.duplicates()) // Print duplicates
                    str += std::to_string(get<1>(dups)) + " - " + get<0>(dups);
                return str;
            }
            if(word == "row")
            {
                i++;
                std::string row = command[i];
                if(isNumeric(row)) // Looking up specific row
                    r = std::stoi(row);
            }
            if(word == "col")
            {
                i++;
                std::string col = command[i];
                if(isNumeric(col)) // Looking up specific row
                  c = std::stoi(col);
            }
        }

        std::string str = "";
        if(r == -1 && c == -1)
        {
            for(Line line : matrix)
                str += line.toString();
        }
        if(r == -1 && c > -1) // Looking up specific column
        {
            for(Line line : matrix)
                str += line.toString(c);
        }
        if(r > -1 && c == -1) // Looking up specific r
            str += matrix[r].toString();
        if(r > -1 && c > -1) // Looking up r-col pair
            str += matrix[r].toString(c);
        
            return str;
    }

public:
    Cenote() 
    {    }

    std::tuple<bool, std::string> processFile(const std::string& f)
    {
        std::ifstream csv;

        csv.open(f, std::ifstream::in);
        if(!csv.is_open())
            return std::make_tuple(false, "Error: open or read file error...\n");
        
        std::string l;
        int num = 0;
        auto count = std::count_if(std::istreambuf_iterator<char>{csv}, {}, [](char c) { return c == '\n'; });
        csv.close();
        hash_map.rescale(count);
        csv.open(f, std::ifstream::in);
        while(getline(csv, l))
        {
            Line line;
            line = l;

            // Set the header as default to the first one
            if(num == 0) line.setHeader(true);

            matrix.push_back(line);
            if(num > 0)
                hash_map.stow(line.toString(), num);
            num++;
        }

        csv.close();
        return std::make_tuple(true, "File has been processed...\n");
    }

    std::tuple<bool, std::string> operator=(const std::string& f) { return processFile(f); }

    /*
    *   Flags:
    *   - duplicates -> prints all the duplicates with their corresponding line numbers
    *   - 
    */
    std::string processCommand(std::string cmd) // command processor
    {
        lower(cmd);
        Translator t;
        std::pair<std::vector<std::string>, std::string> interpreter = t.interpret(cmd);
        std::vector<std::string> command;
        if(interpreter.second == "Valid") command = interpreter.first;
        else return interpreter.second;

        if(command[0] == "show")
        {
            // Pop front
            command.erase(command.begin());
            return show(command);
        }
        if(command[0] == "del")
        {
            
        }
        
        
        return "Try again...";
    }

    
    // I really want to try making my own SQL type database incase people want an integrate way of handling the data
    int saveDB()
    {
        return 1;
    }

    // This would convert the self made database to sqllite so that people can export the database to another program easily
    int convertToSQLLite();

    // Test to see if hash map is reading properly
    std::string hashString()
    {
        return hash_map.toString();
    }
};
#endif