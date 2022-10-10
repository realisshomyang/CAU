#include "recipemanager.h"
#include "planmanager.h"

class gretter
{
private:
    recipemanager recipemanage();
    planmanager planmanager();

public:
    // load datas from db -> control datas by recipemanager, planmanager class.
    gretter(){};
    // basic IIKH intoduction print
    void printUI();
    // choose mode
    int inputMode(){};

    // edit, add, search ,delete recipes information in this func
    // edit ,add, search, delete palns information in this func
    void runprogramfunc(int inputmodenum);
};