#include "cenote.h"
#include <iostream>

using namespace std;

int main()
{
    std::string f = "/Users/stevenzinn/Desktop/Projects/CVS Reader/student_habits_performance.csv";

    Cenote cenote;
    cenote = f;

    cout << cenote.data();

    return 0;
}