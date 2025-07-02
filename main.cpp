#include "cenote.h"
#include <iostream>

using namespace std;

int main()
{
    std::string f = "/Users/stevenzinn/Desktop/Projects/CSV Reader/student_habits_performance.csv";
    cout << "Enter file name: ";
    getline(cin, f, '\n');

    cout << "Reading " << f << "...\n";
    Cenote cenote;
    tuple<bool, string> read = cenote.processFile(f);

    if(get<0>(read))
        cout << "Dataframe created!\n";
    else
        cout << get<1>(read) << endl;

    cout << "Available commands:\n";
    cout << "show\n";
    cout << "row *row number*\n";
    cout << "col *column number*\n";
    cout << "duplicates\n";
    cout << "-------------------\n\n";
    cout << "You can combine commands with a space.\nE.g. show row 2 col 4\n\n";
    
    while(true)
    {
        string str;
        cout << "User: ";
        getline(cin, str, '\n');
        cout << cenote.processCommand(str) << endl;
    }

    return 0;
}