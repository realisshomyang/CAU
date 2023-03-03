#include <string>
using namespace std;

// 경기 정보를 담을 class

class Match
{
private:
    string hometeam;
    string awayteam;
    string score;
    string venue;
    string match_time;

public:
    Match(string t1, string t2);
    void setTeam1(string t1);
    void setTeam2(string t2);
    string getTeam1();
    string getTeam2();
    void setScore1(int s1);
    void setScore2(int s2);
    int getScore1();
    int getScore2();
    void simulate();
};