#ifndef LINE_H
#define LINE_H

#include <string>
#include <vector>

class Line
{
private:
    std::vector<std::string> z_line;
    size_t z_size;
    char z_row_or_col; // row = r, col = c, undefined = u
    bool z_is_header;

public:
    Line(std::vector<std::string> line = std::vector<std::string>(), char row_or_col = 'u', bool is_header = false) : z_line(line), z_size(line.size()), z_row_or_col(row_or_col), z_is_header(is_header) {}

    bool isHeader() {return z_is_header;}
    void setHeader(bool header) {z_is_header = header;}
    bool setLine(std::vector<std::string> line = std::vector<std::string>(), char row_or_col = 'u', bool is_header = false)
    {
        z_line = line;
        z_size = line.size();
        z_row_or_col = row_or_col;
        z_is_header = is_header;

        return true;
    }

    void processLine(const std::string& line)
    {
        std::vector<std::string> processed_line;
        std::string word = "";
        for(char c : line)
        {
            if(c == '\n' || c == ',') 
            {
                processed_line.push_back(word);
                word = "";
                continue;
            }

            word += c;
        }

        setLine(processed_line);
    }

    std::vector<std::string> getLine() {return z_line;}

    void operator=(const std::string& line)
    {
        processLine(line);
    }

    std::string toString(int col = -1)
    {
        std::string str = "";
        if(col != -1) // Only print specific column
            return z_line[col];
            
        for(std::string word : z_line)
            str += word + ", ";
        str.pop_back();
        str.pop_back();
        str += "\n";
        
        return str;
    }
};
#endif