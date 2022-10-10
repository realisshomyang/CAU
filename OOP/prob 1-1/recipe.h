class recipe
{
private:
    <vector> string ingredients;
    string directions;

public:
    recipe();
    recipe(<vector> string ingredients, string directions);
    void editrecipe();
    // setter
    void setingredients(<vector> ingredient ingredients);
    void setdirections(string direction);
    // getter
    <vector> ingredient getingredients();
    string getdirections();
    // print
    void printrecipe();
};