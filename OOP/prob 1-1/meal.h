#include "recipe.h"

class meal
{
private:
    <vector> recipe recipes;
    int personamount;
    string mealname;

public:
    meal();
    meal(<vector> recipe recipes, int personamount, string meal_name);
    // setter
    void setrecipes(<vector> recipe recipes);
    void setpersonamount(int personamount);
    void setmealname(string mealname);

    // edit meal
    void editmeal();
    // meal info print -> ingredients, recipe, direction by recipe class
    void printmeal();
};