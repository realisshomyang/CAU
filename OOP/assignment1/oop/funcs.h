#pragma once
#ifndef FUNCS_H
#define FUNCS_H
#include "student.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>


class vecmanager {
private:
    vector<student> v;
    int isopen;
public:
    vecmanager() {
        ifstream fin;
        fin.open("file1.txt");
        if (fin.is_open() == false)
        {
            fin.close();

            ofstream writeFile;
            writeFile.open("file1.txt");
            writeFile.close();
            this->isopen = 0;
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
                this->v.push_back(st);
            }

            fin.close();
            this->isopen = 1;

        }
    }
    int getisopen() {
        return this->isopen;
    }
    vector<student> getv() {
        return this->v;
    };
    void add(student a) {
        this->v.push_back(a);
    };
    void setisopen(int a) {
        this->isopen = a;
    };
};




int searchmodenum();
int sortmodenum();
int mainmodenum();
bool isnum(const string& str);
string inputid();
string inputname();
string inputbirth();
string inputdepart();
string inputtel();
string inputadm();
bool comparen(student a, student b);
bool comparei(student a, student b);
bool compareadm(student a, student b);
bool compared(student a, student b);


#endif
