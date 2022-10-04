#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

using namespace std;

class student
{
    string stu_name;
    string stu_id;
    string stu_birthyear;
    string stu_department;
    string stu_tel;

public:
    student();
    student(string name, string student_id, string birthyear, string department, string tel);
    void inputInfo(string name, string student_id, string birthyear, string department, string tel);
    void printStu();
};

#endif
