#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

int filetostuvec();
void vectofile();
void search(int a, string str);
void asort(int a);
// compare함수

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
bool comparen(student a, student b);
bool comparei(student a, student b);
bool compareadm(student a, student b);
vector<student> v;
int main()
{
    filetostuvec();
    asort(1);
    for (int i = 0; i < v.size(); i++)
    {
        v[i].printstudent();
    }

    /*vector<student> tmp;
    search(1,"")
    string a = "2019380210";
    string b = a.substr(0, 4);
    cout << b;*/

    // vectofile();
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

bool comparen(student a, student b)
{
    if (a.getname() < b.getname())
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool comparei(student a, student b)
{
    if (atoll(a.getid().c_str()) < atoll(b.getid().c_str()))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool compareadm(student a, student b)
{
    if (atoll(a.getid().substr(0, 4).c_str()) < atoll(b.getid().substr(0, 4).c_str()))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool compared(student a, student b)
{
    if (a.getdepartment() < b.getdepartment())
    {
        return true;
    }
    else
    {
        return false;
    }
}
void search(int a, string str)
{
    if (a == 1)
    {
        for (int i = 0; i < v.size(); i++)
        {
            if (v[i].getname() == str)
            {
                string temp = v[i].getname() + "/" + v[i].getid() + "/" + v[i].getbirthyear() + "/" + v[i].getdepartment() + "/" + v[i].gettel() + "\n";
                cout << temp;
            }
            else
            {
                cout << "no data in file";
            }
        }
    }
    else if (a == 2)
    {
        for (int i = 0; i < v.size(); i++)
        {
            if (v[i].getid() == str)
            {
                string temp = v[i].getname() + "/" + v[i].getid() + "/" + v[i].getbirthyear() + "/" + v[i].getdepartment() + "/" + v[i].gettel() + "\n";
                cout << temp;
            }
            else
            {
                cout << "no data in file";
            }
        }
    }
    else if (a == 3)
    {
        for (int i = 0; i < v.size(); i++)
        {
            if (v[i].getid().substr(0, 3) == str)
            {
                string temp = v[i].getname() + "/" + v[i].getid() + "/" + v[i].getbirthyear() + "/" + v[i].getdepartment() + "/" + v[i].gettel() + "\n";
                cout << temp;
            }
            else
            {
                cout << "no data in file";
            }
        }
    }
    else if (a == 4)
    {
        for (int i = 0; i < v.size(); i++)
        {
            if (v[i].getdepartment() == str)
            {
                string temp = v[i].getname() + "/" + v[i].getid() + "/" + v[i].getbirthyear() + "/" + v[i].getdepartment() + "/" + v[i].gettel() + "\n";
                cout << temp;
            }
            else
            {
                cout << "no data in file";
            }
        }
    }
}
void asort(int a)
{
    if (a == 1)
    {
        cout << "sort by name\n";
        sort(v.begin(), v.end(), comparen);
    }
    else if (a == 2)
    {
        cout << "sort by studentID\n";
        sort(v.begin(), v.end(), comparei);
    }
    else if (a == 3)
    {
        cout << "sort by "
    }
}
