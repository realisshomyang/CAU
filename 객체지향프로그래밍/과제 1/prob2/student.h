#pragma once
#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;


class student {
private:
	string name;
	string id;
	string birthyear;
	string department;
	string tel;

public:
	student();
	//���Ͽ��� �Է¹޾��� �� Student ��ü�� ������ִ� ������ 
	student(string a, string b, string c, string d, string e);

	//getter
	string getname();
	string getid();
	string getbirthyear();
	string getdepartment();
	string gettel();

	//setter
	void setname(string name);
	void setid(string id);
	void setbirthyear(string birthyear);
	void setdepartment(string dept);
	void settel(string tel);
	void printstudent();

};
#endif
