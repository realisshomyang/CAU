#include <iostream>
#include <string>
using namespace std;
int searchmodenum();
int sortmodenum();
int mainmodenum();
int getdigit(int a);
bool isnum(const string &str);

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
        this->name = temp;
    }
    void setid()
    {
        string temp;
        cout << "Student ID (10 digits)?";
        cin >> temp;
        while (true)
        {
            if (isnum(temp))
            {
                if (stoi(temp) > 0)
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
                if (stoi(temp) > 0)
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
        cout << "department";
        cin >> temp;
        this->department = temp;
    }
    void settel()
    {
        string temp;
        cout << "tel (up to 12 digits)?";
        cin >> temp;
        while (true)
        {
            if (isnum(temp))
            {
                if (stoi(temp) > 0)
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
        this->tel = temp;
    }
    void printstudent()
    {
        cout << this->name << this->id << this->birthyear << this->department << this->tel << endl;
    }
};

int main(void)
{
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
            a.printstudent();
        }
        else if (num == 2)
        {
            int searchmode = searchmodenum();
            /*student 배열 sort 후 프린트
            모드 1
            모드 2
            모드 3
            모드 4
            */
        }
        else if (num == 3)
        {
            int sortmmode = sortmodenum();
        }
        else if (num == 4)
        {
            cout << "Exit";
            /*파일에 write*/
            break;
        }
        else
        {
            cout << "input valid num 1,2,3,4";
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