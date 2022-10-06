#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

int filetostuvec();
void vectofile();
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
    string getname()
    {
        return name;
    }
    string getid()
    {
        return id;
    }
    string getbirthyear()
    {
        return birthyear;
    }
    string getdepartment()
    {
        return department;
    }
    string gettel()
    {
        return tel;
    }
};

vector<student> v;

int main()
{
    filetostuvec();
    vector<student>::iterator iter;
    /*for (int i = 0; i < v.size(); i++)
    {
        v[i].printstudent();
    }*/
    vectofile();
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

int filetostuvec()
{

    ifstream fin;
    fin.open("file1.txt");
    if (fin.is_open() == false)
    {
        cout << "no file";
        fin.close();

        ofstream writeFile;
        writeFile.open("file1.txt");
        writeFile.close();
        return 0;
    }
    else
    {
        cout << "file\n";
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

        fin.close();
        return 1;
    }
}
void vectofile()
{
    vector<student>::iterator iter;
    for (int i = 0; i < v.size(); i++)
    {
        string temp = v[i].getname() + "/" + v[i].getid() + "/" + v[i].getbirthyear() + "/" + v[i].getdepartment() + "/" + v[i].gettel() + "\n";
        cout << temp;
    }
}