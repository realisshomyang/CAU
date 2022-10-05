#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

void filetostuvec();

class student
{
private:
    string name;
    string id;
    string birthyear;
    string department;
    string tel;

public:
    student()
    {
    }
    student(string a, string b, string c, string d, string e)
    {
        this->id = b;
        this->name = a;
        this->birthyear = c;
        this->department = d;
        this->tel = e;
    }
    void printstudent()
    {
        cout << this->name << this->id << this->birthyear << this->department << this->tel << endl;
    }
};

vector<student> v;

int main()
{
    filetostuvec();
    /*
    filetostuvec();
    ifstream fin;
    fin.open("file1.txt");
    string line;
    string str[5];
    int i = 0;
    while (!fin.eof())
    {
        i = 0;
        getline(fin, line);
        stringstream ss(line);
        string word;
        while (!ss.eof())
        {
            getline(ss, word, '/');
            str[i] = word;
            i++;
        }
        student st = student(str[0], str[1], str[2], str[3], str[4]);
        v.push_back(st);
    }
    vector<student>::iterator iter;
    for (int i = 0; i < v.size(); i++)
    {
        v[i].printstudent();
    }

    fin.close();*/
}

/*
string adv_tokenizer(string s, char del)
{
    stringstream ss(s);
    string word;
    while (!ss.eof())
    {
        getline(ss, word, del);
        cout << word << endl;
    }
}

int main()
{
    ifstream fin;
    fin.open("file1.txt");
    string line;
    string str[5] = 0;

    while (!fin.eof())
    {
        getline(fin, line);
        adv_tokenizer(line, '/');
        cout << line << endl;
    }

    fin.close();
}
*/

void filetostuvec()
{
    ifstream fin;
    fin.open("file1.txt");
    string line;
    string str[5];
    int i = 0;
    while (!fin.eof())
    {
        i = 0;
        getline(fin, line);
        stringstream ss(line);
        string word;
        while (!ss.eof())
        {
            getline(ss, word, '/');
            str[i] = word;
            i++;
        }
        student st = student(str[0], str[1], str[2], str[3], str[4]);
        v.push_back(st);
    }
    vector<student>::iterator iter;
    for (int i = 0; i < v.size(); i++)
    {
        v[i].printstudent();
    }

    fin.close();
}