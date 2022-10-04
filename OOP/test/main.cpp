#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "student.h"

using namespace std;

student linetostu(string input, char delimiter)
{
    string a[5];
    student b;
    int i = 0;
    stringstream ss(input);
    string temp;
    while (getline(ss, temp, delimiter))
    {
        a[i] = temp;
        i++;
    }
    b.Input(a[0], a[1], a[2], a[3], a[4]);

    return b;
}

vector<student> filetostuvec()
{
    string filename("file1.txt");
    vector<student> lines;
    string line;

    ifstream input_file(filename);
    if (!input_file.is_open())
    {
        cerr << "Could not open the file - '" << filename << "'" << endl;
    }

    while (getline(input_file, line))
    {
        student b = linetostu(line, '/');
        lines.push_back(b);
    }

    input_file.close();
    return lines;
}

int main()
{
    vector<student> test = filetostuvec();
}