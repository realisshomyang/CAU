#pragma once
#ifndef MANAGE_H
#define MANAGE_H
#include "funcs.h"


class manage {
private:
    vector<student> v;
    int isopen;
public:
    manage();
    int getisopen();
    vector<student> getv();
    void setv(vector<student> a);
    void add(student a);
    void setisopen(int a);
};





#endif