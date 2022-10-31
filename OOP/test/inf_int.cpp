#include "inf_int.h"

inf_int ::inf_int(const inf_int &x)
{
    length = x.length;
    thesign = x.thesign;
    digits = new char[length + 1];
    strcpy(digits, x.digits);
}
inf_int ::~inf_int()
{
    free(digits);
};