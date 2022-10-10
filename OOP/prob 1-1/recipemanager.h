class recipemanager
{
private:
    <vector> recipe recipes;

public:
    // bring data from DB
    recipemanager();

    // manage recipes from db and update db
    // search by name
    void searchrecipe(string recipename);
    // add recipe in recipe vector
    void addrecipe();
    // delete recipe that user want
    void deleterecipe(string recipename);
    // find recipe by name and edit
    void editrecipe(sring recipename);

    // print recipes by this func
    void printrecipes();

    // save recipes inDB
    void saverecipse();
};