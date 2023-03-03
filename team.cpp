using namespace std;
#include
#include <string>

class team
{
private:
    int group;
    int rank_in_group;
    string name;
    float average

        public : team(/* args */);
    ~team();
};

class Team
{
private:
    string name;
    vector<Player> players;
    int score;

public:
    Team(string name)
    {
        this->name = name;
        this->score = 0;
    }

    void addPlayer(Player player)
    {
        this->players.push_back(player);
    }

    int getTeamRating()
    {
        // Code for calculating the team's overall rating goes here
    }
};
