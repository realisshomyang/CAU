#include <string.h>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Player
{
private:
    string name;
    string birth_year;
    string club;
    // most commonly played
    int run_time;

public:
    Player(string name, int number, string position)
    {
        this->name = name;
        this->number = number;
        this->position = position;
    }

    virtual int getOverallRating() = 0;
};

class Forward : public Player
{
public:
    Forward(string name, int number) : Player(name, number, "Forward") {}

    int getOverallRating()
    {
        // Code for calculating the forward's overall rating goes here
    }
};

class Midfielder : public Player
{
public:
    Midfielder(string name, int number) : Player(name, number, "Midfielder") {}

    int getOverallRating()
    {
        // Code for calculating the midfielder's overall rating goes here
    }
};

class Defender : public Player
{
public:
    Defender(string name, int number) : Player(name, number, "Defender") {}

    int getOverallRating()
    {
        // Code for calculating the defender's overall rating goes here
    }
};

class Goalkeeper : public Player
{
public:
    Goalkeeper(string name, int number) : Player(name, number, "Defender") {}

    int getOverallRating()
    {
        // Code for calculating the defender's overall rating goes here
    }
};

class WorldCup
{
private:
    int year;
    int numTeams;
    string hostCountry;
    map<string, Team> teams;

public:
    WorldCup(int year, int numTeams, string hostCountry)
    {
        this->year = year;
        this->numTeams = numTeams;
        this->hostCountry = hostCountry;
    }

    void addTeam(string name, Team team)
    {
        this->teams[name] = team;
    }

    void determineWinner(string team1, string team2, int score1, int score2)
    {
        // Code for determining the winner of a match goes here
    }

    void updateScores(string team, int score)
    {
        // Code for updating a team's score goes here
    }
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

class Match
{
};