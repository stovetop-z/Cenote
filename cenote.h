#ifndef CENOTE_H
#define CENOTE_H

#include "line.h"
#include <fstream>
#include <tuple>
#include "library/hash_map.h"

class Cenote
{
private:
    std::vector<Line> matrix;
    HashMap hash_map;
    int rows, cols;

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
        while(getline(csv, l))
        {
            Line line;
            line = l;

            // Set the header as default to the first one
            if(num == 0) line.setHeader(true);

            matrix.push_back(line);
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
    std::string data(int row = -1, int col = -1, const char* flag = "lambda") // Update this to search column by name and rows by values that are equal to, less than, or greater than
    {

        std::string str = "";
        if(flag == "duplicates")
        {
            if(hash_map.duplicateScale() < 1) // No duplicates
                return "No duplicates found...\n";
            for(auto& dups : hash_map.duplicates()) // Print duplicates
                str += std::to_string(::get<1>(dups)) + " - " + ::get<0>(dups);
        }
        if(row == -1 && col == -1)
        {
            for(Line line : matrix)
                str += line.toString();
        }
        if(row == -1 && col > -1) // Looking up specific column
        {
            for(Line line : matrix)
                str += line.toString(col);
        }
        if(row > -1 && col == -1) // Looking up specific row
            str += matrix[row].toString();
        if(row > -1 && col > -1) // Looking up row-col pair
            str += matrix[row].toString(col);
        
        return str;
    }

    // I really want to try making my own SQL type database incase people want an integrate way of handling the data
    int saveDB()
    {
        
    }

    // This would convert the self made database to sqllite so that people can export the database to another program easily
    int convertToSQLLite();
};
#endif