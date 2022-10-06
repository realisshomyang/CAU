#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
int searchmodenum();
int sortmodenum();
int mainmodenum();
int getdigit(int a);
bool isnum(const string &str);
int filetostuvec();
void search(int a, string str);
string inputid();
string inputname();
string inputbirth();
string inputdepart();
string inputtel();
string inputadm();
class student
{
private:
    string name;
    string id;
    string birthyear;
    string department;
    string tel;

public:
    // constructor
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
    // getter
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
    // setter
    void setname()
    {
        string temp;
        temp = inputname();
        this->name = temp;
    }
    void setid()
    {
        string temp;
        temp = inputid();
        this->id = temp;
    }
    void setbirthyear()
    {
        string temp;
        cout << "Birth year (4 digits)?";
        cin >> temp;
        while (true)
        {
            if (isnum(temp))
            {
                if (stoll(temp) > 0)
                {
                    if (temp.size() == 4)
                    {
                        break;
                    }
                    else
                    {
                        cout << "birthyear must be 4 digits";
                        cin >> temp;
                    }
                }
                else
                {
                    cout << "birthyear must be positive";
                    cin >> temp;
                }
            }
            else
            {
                cout << "birth year input must be digit";
                cin >> temp;
            }
        }
        this->birthyear = temp;
    }
    void setdepartment()
    {
        string temp;
        temp = inputdepart();
        this->department = temp;
    }
    void settel()
    {
        string temp;
        temp = inputtel();
        this->tel = temp;
    }
    void printstudent()
    {
        cout << this->name << this->id << this->birthyear << this->department << this->tel << endl;
    }
};

vector<student> v;

class manage
{
};

int main(void)
{
    /*파일 입력 -> student list*/
    int isopennum = filetostuvec();
    while (true)
    {
        int num = mainmodenum();
        if (num == 1)
        {
            student a = student();
            a.setname();
            a.setid();
            a.setbirthyear();
            a.setdepartment();
            a.settel();
            ofstream writeToFile;
            writeToFile.open("file1.txt", ios::out | ios::app);
            if (isopennum == 0)
            {
                string strtemp = a.getname() + "/" + a.getid() + "/" + a.getbirthyear() + "/" + a.getdepartment() + "/" + a.gettel();
                writeToFile.write(strtemp.c_str(), strtemp.size());
            }
            else
            {
                string strtemp = "\n" + a.getname() + "/" + a.getid() + "/" + a.getbirthyear() + "/" + a.getdepartment() + "/" + a.gettel();
                writeToFile.write(strtemp.c_str(), strtemp.size());
            }
            v.push_back(a);
            isopennum = 1;
        }
        else if ((num == 2) && (isopennum == 1))
        {
            int searchmode = searchmodenum();
            if (searchmode == 1)
            {
                cout << "input name that you will find.\n";
                string tmp_name = inputname();
                search(searchmode, tmp_name);
            }
            else if (searchmode == 2)
            {
                cout << "input id that you will find\n";
                string tmp_id = inputid();
                search(searchmode, tmp_id);
            }
            else if (searchmode == 3)
            {
                cout << "input addmission year that you will find\n";
                string tmp_ad = inputadm();
                search(searchmode, tmp_ad);
            }
            else if (searchmode == 4)
            {
                cout << "input department that you will find\n";
                string tmp_dept = inputdepart();
                search(searchmode, tmp_dept);
            }
            else if (searchmode == 5)
            {
                vector<student>::iterator iter;
                for (int i = 0; i < v.size(); i++)
                {
                    v[i].printstudent();
                }
            }
        }
        else if ((num == 3) && (isopennum == 1))
        {
            int sortmmode = sortmodenum();
            /*student 배열 sort 후 프린트
            모드 1
            모드 2
            모드 3
            모드 4
            */
        }
        else if ((num == 4) && (isopennum == 1))
        {
            cout << "Exit";
            break;
        }
        else
        {
            cout << "if there is no file, you can only choose insert mode\n";
        }
    }
}

int getdigit(int a)
{
    string tmp;
    tmp = to_string(a);
    return tmp.size();
}

int mainmodenum()
{
    int srnum;
    cout << "1. Insertion\n2. Search\n3. Sorting Option\n4. Exit\n";
    cin >> srnum;
    if ((srnum > 0) && (srnum <= 4))
    {
        return srnum;
    }
    else
    {
        return mainmodenum();
    }
}

int searchmodenum()
{
    int srnum;
    cout << "1. Search by name\n2. Search by student ID(10 numbers)\n3. Search by admission year(4numbers) Option\n4. Search by department name\n5. List ALL\n";
    cin >> srnum;
    if ((srnum > 0) && (srnum <= 5))
    {
        return srnum;
    }
    else
    {
        return searchmodenum();
    }
}
int sortmodenum()
{
    int srnum;
    cout << "1. Sort by Name\n2. Sort by Student ID\n3. Sort by Admission Year\n4. Sort by Department name\n";
    cin >> srnum;
    if ((srnum > 0) && (srnum <= 4))
    {
        return srnum;
    }
    else
    {
        return sortmodenum();
    }
}

bool isnum(string const &str)
{
    auto it = str.begin();
    while (it != str.end() && std::isdigit(*it))
    {
        it++;
    }
    return !str.empty() && it == str.end();
}
int filetostuvec()
{

    ifstream fin;
    fin.open("file1.txt");
    if (fin.is_open() == false)
    {
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

string inputid()
{
    string temp;
    cout << "Student ID (10 digits)?";
    cin >> temp;
    while (true)
    {
        if (isnum(temp))
        {
            if (stoll(temp) > 0)
            {
                if (temp.size() == 10)
                {
                    break;
                }
                else
                {
                    cout << "Student ID must be 10 digits";
                    cin >> temp;
                }
            }
            else
            {
                cout << "Student ID must be positive";
                cin >> temp;
            }
        }
        else
        {
            cout << "Student ID input must be digit";
            cin >> temp;
        }
    }
    return temp;
}
string inputadm()
{
    string temp;
    cout << "adminin year (4 digits)?";
    cin >> temp;
    while (true)
    {
        if (isnum(temp))
        {
            if (stoll(temp) > 0)
            {
                if (temp.size() == 4)
                {
                    break;
                }
                else
                {
                    cout << "adminyear must be 4 digits";
                    cin >> temp;
                }
            }
            else
            {
                cout << "Student ID must be positive";
                cin >> temp;
            }
        }
        else
        {
            cout << "adminyear input must be digit";
            cin >> temp;
        }
    }
    return temp;
}
string inputname()
{
    string temp;
    cout << "Name ?";
    cin >> temp;
    while (true)
    {
        if (temp.length() > 15)
        {
            cout << "Name input is up to 15 input again";
            cin >> temp;
        }
        else
        {
            break;
        }
    }
    return temp;
}
string inputbirth()
{
    string temp;
    cout << "Birth year (4 digits)?";
    cin >> temp;
    while (true)
    {
        if (isnum(temp))
        {
            if (stoll(temp) > 0)
            {
                if (temp.size() == 4)
                {
                    break;
                }
                else
                {
                    cout << "birthyear must be 4 digits";
                    cin >> temp;
                }
            }
            else
            {
                cout << "birthyear must be positive";
                cin >> temp;
            }
        }
        else
        {
            cout << "birth year input must be digit";
            cin >> temp;
        }
    }
    return temp;
}
string inputdepart()
{
    string temp;
    cout << "department";
    cin >> temp;

    return temp;
}
string inputtel()
{
    string temp;
    cout << "tel (up to 12 digits)?";
    cin >> temp;
    while (true)
    {
        if (isnum(temp))
        {
            if (stoll(temp) > 0)
            {
                if (temp.size() <= 12)
                {
                    break;
                }
                else
                {
                    cout << "tel must be up to 12 digits";
                    cin >> temp;
                }
            }
            else
            {
                cout << "tel must be positive";
                cin >> temp;
            }
        }
        else
        {
            cout << "telnum input must be digit";
            cin >> temp;
        }
    }
    return temp;
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

void search(int a, string str)
{
    int flag = 0;
    if (a == 1)
    {
        for (int i = 0; i < v.size(); i++)
        {
            if (v[i].getname() == str)
            {
                flag = 1;
                string temp = v[i].getname() + "/" + v[i].getid() + "/" + v[i].getbirthyear() + "/" + v[i].getdepartment() + "/" + v[i].gettel() + "\n";
                cout << temp;
            }
        }
        if (flag == 0)
        {
            cout << "no data in file";
        }
    }
    else if (a == 2)
    {
        for (int i = 0; i < v.size(); i++)
        {
            if (v[i].getid() == str)
            {
                flag = 1;
                string temp = v[i].getname() + "/" + v[i].getid() + "/" + v[i].getbirthyear() + "/" + v[i].getdepartment() + "/" + v[i].gettel() + "\n";
                cout << temp;
            }
        }
        if (flag == 0)
        {
            cout << "no data in file";
        }
    }
    else if (a == 3)
    {
        for (int i = 0; i < v.size(); i++)
        {
            if (v[i].getid().substr(0, 4) == str)
            {
                flag = 1;
                string temp = v[i].getname() + "/" + v[i].getid() + "/" + v[i].getbirthyear() + "/" + v[i].getdepartment() + "/" + v[i].gettel() + "\n";
                cout << temp;
            }
        }
        if (flag == 0)
        {
            cout << "no data in file";
        }
    }
    else if (a == 4)
    {
        for (int i = 0; i < v.size(); i++)
        {
            if (v[i].getdepartment() == str)
            {
                flag = 1;
                string temp = v[i].getname() + "/" + v[i].getid() + "/" + v[i].getbirthyear() + "/" + v[i].getdepartment() + "/" + v[i].gettel() + "\n";
                cout << temp;
            }
        }
        if (flag == 0)
        {
            cout << "no data in file";
        }
    }
}
