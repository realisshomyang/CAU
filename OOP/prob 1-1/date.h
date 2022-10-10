#include <string.h>

class date
{
private:
    int year;
    int month;
    int day;
    string time;

public:
    date();
    date(int year, int month, int day, int time){};
    // Setter
    void setYear(int year);
    void setMonth(int month);
    void setDay(int day);
    void setTime(int time);
    // Getter
    int getYear();
    int getMonth();
    int getDay();
    string time;
}