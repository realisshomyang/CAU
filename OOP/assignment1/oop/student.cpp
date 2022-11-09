#include "student.h"

using namespace std;

student::student() {}

student::student(string a, string b, string c, string d, string e) {
	student :: setname(a);
	student::setid(b);
	student::setbirthyear(c);
	student::setdepartment(d);
	student::settel(e);
}

//getter
string student::getname(){
	return this->name;
}
string student::getid() {
	return this->id;
}
string student::getbirthyear() {
	return this->birthyear;
}
string student::getdepartment() {
	return this->department;
}
string student::gettel() {
	return this->tel;
}
//setter

void student::setname(string name) {
	this->name = name;
}
void student::setid(string id) {
	this->id = id;
}
void student::setbirthyear(string birthyear) {
	this->birthyear = birthyear;
}
void student::setdepartment(string dept) {
	this->department = dept;
}
void student::settel(string tel) {
	this->tel = tel;
}
void student::printstudent() {
	cout << setw(12) << right << this->name;
	cout << setw(12) << right << this->id;
	cout << setw(12) << right << this->birthyear;
	cout << setw(12) << right << this->department;
	cout << setw(12) << right << this->tel << endl;
}
