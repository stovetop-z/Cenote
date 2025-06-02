#ifndef CENOTE_H
#define CENOTE_H

#include "line.h"
#include <fstream>
#include <tuple>

class Cenote
{
private:
    std::vector<Line> matrix;
    int rows, cols;

public:
    Cenote() {}

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
            num++;
        }

        csv.close();
        return std::make_tuple(true, "File has been processed...\n");
    }

    std::tuple<bool, std::string> operator=(const std::string& f) { return processFile(f); }

    std::string data(int row = -1, int col = -1)
    {
        std::string str = "";
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

};
#endif