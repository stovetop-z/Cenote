#include "cenote.h"
#include <iostream>

using namespace std;

int main()
{
    std::string f = "/Users/stevenzinn/Desktop/Projects/CSV Reader/student_habits_performance.csv";

    Cenote cenote;
    cenote = f;

    int row = -1;
    int col = -1;
    while(true)
    {

        cout << "Enter row: ";
        cin >> row;
        cout << "Enter col: ";
        cin >> col;
        cout << cenote.data(row, col) << endl;
    }

    return 0;
}