#include "manage.h"


manage::manage() {
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
int manage::getisopen() {
    return this->isopen;
}

vector<student> manage::getv() {
    return this->v;
};

void manage :: add(student a){
    this->v.push_back(a);
};
void manage :: setisopen(int a){
    this->isopen = a;
};
void manage::setv(vector<student> a) {
    this->v = a;
}