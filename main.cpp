#include "cenote.h"
#include <iostream>

using namespace std;

int main()
{
    std::string f = "/Users/stevenzinn/Desktop/Projects/CSV Reader/student_habits_performance.csv";

    Cenote cenote;
    cenote = f;

    // cout << cenote.hashString();

    int row = -1;
    int col = -1;
    while(true)
    {
        string flag;
        cout << "Enter row: ";
        cin >> row;
        cout << "Enter col: ";
        cin >> col;
        cin.get();
        cout << "Enter flag: ";
        getline(cin, flag, '\n');
        cout << cenote.data(row, col, flag) << endl;
    }

    return 0;
}