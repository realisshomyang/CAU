#include "meal.h"
#include "date.h"
class plan
{
private:
    meal mealinfo;
    date dateinfo;

public:
    plan();
    plan(meal mealinfo, date dateinfo);

    // setter
    void setmealinfo(meal mealinfo);
    void setdateinfo(date dateinfo);
    // getter
    meal getmealnfo();
    s
        date
        getdateinfo();

    // print mealinfo, dateinfo
    void printplan();
}