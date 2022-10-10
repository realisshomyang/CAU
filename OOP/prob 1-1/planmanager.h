#include "plan.h"
class planmanager
{
private:
    <vector> plan plans;

public:
    // make plan vector by loading data in Database
    planmanager();
    void printplans();

    // manage plans
    void editplan(string planname);
    void addplan();
    void deleteplan(string planname);
    void printplan();
    void searchplan(string planname);

    // save data in db
    void saveplansindb();

    // getter
    <vector> plan getplans();
    // setter
    void setplans(<vector> plan);
};