#include <iostream>
#include <string>
int searchmodenum();
int sortstunum();

/*
class student
{
private:
    std :: string stu_name;
    ststring stu_id;
    string stu_birthyear;
    string stu_department;
    string stu_tel;

public:
    student()
    {
    }
};*/

using namespace std;
int getdigit(int a);

int main(void)
{
    while (true)
    {
        int num;
        cout << "1. Insertion\n2. Search\n3. Sorting Option\n4. Exit\n";
        cin >> num;
        if (num == 1)
        {
            string name;
            int student_id;
            int birth_year;
            string department;
            int tel;
            cout << "Name ?";
            cin >> name;
            while (true)
            {
                if (name.length() > 15)
                {
                    cout << "Name input is up to 15 input again";
                    cin >> name;
                }
                else
                {
                    break;
                }
            }
            cout << "Student ID (10 digits)?";
            cin >> student_id;
            while (true)
            {
                if (student_id > 0)
                {
                    int len = getdigit(student_id);
                    if (len == 10)
                    {
                        break;
                    }
                    else
                    {
                        cout << "Student ID should be 10 digits input again";
                        cin >> student_id;
                    }
                }
                else
                {
                    cout << "Student ID should 양수";
                }
            }
            cout << "Birth Year (4 digits)?";
            cin >> birth_year;
            while (true)
            {
                if (birth_year > 0)
                {
                    int len = getdigit(birth_year);
                    if (len == 4)
                    {
                        break;
                    }
                    else
                    {
                        cout << "bitrh year should be 4 digits input again";
                        cin >> birth_year;
                    }
                }
                else
                {
                    cout << "birth year should 양수";
                }
            }
            cout << "Department ?";
            cin >> department;

            cout << "tel (up to 12 digits)?";
            cin >> tel;
            while (true)
            {
                if (birth_year > 0)
                {
                    int len = getdigit(birth_year);
                    if (len >= 12)
                    {
                        break;
                    }
                    else
                    {
                        cout << "tel should be up to 12 digits input again";
                        cin >> tel;
                    }
                }
                else
                {
                    cout << "tel should 양수";
                }
            }
        }
        else if (num == 2)
        {
            int searchmode = searchmodenum();
        }
        else if (num == 3)
        {
            cout << "1. Sort by Name\n2. Sort by Student ID\n3. Sort by Admission Year\n4. Sort by Department name\n";
        }
        else if (num == 4)
        {
            cout << "Exit";
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