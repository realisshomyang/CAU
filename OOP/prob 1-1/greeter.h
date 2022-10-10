#include "recipemanager.h"
#include "planmanager.h"

class gretter
{
private:
    recipemanager recipemanage();
    planmanager planmanager();

public:
    gretter(){};
    // basic IIKH intoduction print
    void printUI();
    // input mode
    void inputMode(){};
    void searchRecipe(recipemanager recipes);
    void addRecipe(recipemanager recipes);
    void deleteRecipe(recipemanager recipes);
};