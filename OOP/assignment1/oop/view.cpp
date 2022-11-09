#include "view.h"
bool isexist(string str,manage a)
{
	for (int i = 0; i < a.getv().size(); i++)
	{
		if (a.getv()[i].getid() == str)
		{
			return true;
		}
	}
	return false;
}
vector<student> asort(int a, manage b)
{
	vector<student> tmpv;
	tmpv = b.getv();
	if (a == 1)
	{
		cout << "sort by name\n";
		sort(tmpv.begin(), tmpv.end(), comparen);
		return tmpv;
	}
	else if (a == 2)
	{
		cout << "sort by studentID\n";
		sort(tmpv.begin(), tmpv.end(), comparei);
		return tmpv;
	}
	else if (a == 3)
	{
		cout << "sort by admin\n";
		sort(tmpv.begin(), tmpv.end(), compareadm);
		return tmpv;
	}
	else if (a == 4)
	{
		cout << "sort by department name\n";
		sort(tmpv.begin(), tmpv.end(), compared);
		return tmpv;
	}
}

void view() {
	manage vec = manage();
	vector<student> sortresult = asort(1, vec);
	vec.setv(sortresult);
	while (true) {
		int num = mainmodenum();
		if (num == 1) {
			student a = student();
			a.setname(inputname());
			string tmpid = inputid();
			while (isexist(tmpid,vec)) {
				cout << "Error : Already inserted input again\n";
				tmpid = inputid();
			}
			a.setid(tmpid);
			a.setbirthyear(inputbirth());
			a.setdepartment(inputdepart());
			a.settel(inputtel());
			ofstream writeToFile;
			writeToFile.open("file1.txt", ios::out | ios::app);
			if (vec.getisopen() == 0)
			{
				string strtemp = a.getname() + "/" + a.getid() + "/" + a.getbirthyear() + "/" + a.getdepartment() + "/" + a.gettel();
				writeToFile.write(strtemp.c_str(), strtemp.size());
			}
			else
			{
				string strtemp = "\n" + a.getname() + "/" + a.getid() + "/" + a.getbirthyear() + "/" + a.getdepartment() + "/" + a.gettel();
				writeToFile.write(strtemp.c_str(), strtemp.size());
			}
			vec.add(a);
			vec.setisopen(1);
		}
		else if ((num == 2) && (vec.getisopen() == 1))
		{
			int searchmode = searchmodenum();
			if (searchmode == 1)
			{
				cout << "input name that you will find.\n";
				string tmp_name = inputname();
				search(searchmode, tmp_name,vec);
			}
			else if (searchmode == 2)
			{
				cout << "input id that you will find\n";
				string tmp_id = inputid();
				search(searchmode, tmp_id,vec);
			}
			else if (searchmode == 3)
			{
				cout << "input addmission year that you will find\n";
				string tmp_ad = inputadm();
				search(searchmode, tmp_ad,vec);
			}
			else if (searchmode == 4)
			{
				cout << "input department that you will find\n";
				string tmp_dept = inputdepart();
				search(searchmode, tmp_dept,vec);
			}
			else if (searchmode == 5)
			{
				cout << setw(14) << left << "Name";
				cout << setw(12) << left << "Student ID";
				cout << setw(12) << left << "Birth Year";
				cout << setw(11) << left << "Dept";
				cout << setw(12) << left << "Tel" << endl;
				vector<student>::iterator iter;
				for (int i = 0; i < vec.getv().size(); i++)
				{
					vec.getv()[i].printstudent();
				}
				cout << "\n";
			}
		}
		else if ((num == 3) && (vec.getisopen() == 1))
		{
			int sortmode = sortmodenum();
			vector<student> sortresult = asort(sortmode,vec);
			vec.setv(sortresult);
		}
		else if ((num == 4) && (vec.getisopen() == 1))
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

void search(int a, string str,manage b)
{
	int flag = 0;
	vector<student> tmpvec;
	if (a == 1)
	{
		for (int i = 0; i < b.getv().size(); i++)
		{
			if (b.getv()[i].getname() == str)
			{

				flag = 1;
				tmpvec.push_back(b.getv()[i]);
			}
		}
		if (flag == 0)
		{
			cout << "no data in file\n";
		}
		else if (flag == 1) {
			cout << setw(14) << left << "Name";
			cout << setw(12) << left << "Student ID";
			cout << setw(12) << left << "Birth Year";
			cout << setw(11) << left << "Dept";
			cout << setw(12) << left << "Tel" << endl;

			for (int i = 0; i < tmpvec.size(); i++) {
				tmpvec[i].printstudent();
			}
		}
	}
	else if (a == 2)
	{
		for (int i = 0; i < b.getv().size(); i++)
		{
			if (b.getv()[i].getid() == str)
			{
				flag = 1;
				tmpvec.push_back(b.getv()[i]);
			}
		}

		if (flag == 0)
		{
			cout << "no data in file\n";
		}
		else if (flag == 1) {
			cout << setw(14) << left << "Name";
			cout << setw(12) << left << "Student ID";
			cout << setw(12) << left << "Birth Year";
			cout << setw(11) << left << "Dept";
			cout << setw(12) << left << "Tel" << endl;

			for (int i = 0; i < tmpvec.size(); i++) {
				tmpvec[i].printstudent();
			}
		}
	}
	else if (a == 3)
	{
		for (int i = 0; i < b.getv().size(); i++)
		{
			if (b.getv()[i].getid().substr(0, 4) == str)
			{
				flag = 1;
				tmpvec.push_back(b.getv()[i]);
			}
		}
		if (flag == 0)
		{
			cout << "no data in file\n";
		}
		else if (flag == 1) {
			cout << setw(14) << left << "Name";
			cout << setw(12) << left << "Student ID";
			cout << setw(12) << left << "Birth Year";
			cout << setw(11) << left << "Dept";
			cout << setw(12) << left << "Tel" << endl;

			for (int i = 0; i < tmpvec.size(); i++) {
				tmpvec[i].printstudent();
			}
		}
	}
	else if (a == 4)
	{
		for (int i = 0; i < b.getv().size(); i++)
		{
			if (b.getv()[i].getdepartment() == str) {
				flag = 1;
				tmpvec.push_back(b.getv()[i]);
			}
		}
		if (flag == 0)
		{
			cout << "no data in file\n";
		}
		else if (flag == 1) {
			cout << setw(14) << left << "Name";
			cout << setw(12) << left << "Student ID";
			cout << setw(12) << left << "Birth Year";
			cout << setw(11) << left << "Dept";
			cout << setw(12) << left << "Tel" << endl;

			for (int i = 0; i < tmpvec.size(); i++) {
				tmpvec[i].printstudent();
			}
		}
	}
}
