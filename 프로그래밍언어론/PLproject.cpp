#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

// parsing을 위한 split함수
vector<string> split(const string &str)
{
    vector<string> tokens;
    string token;
    istringstream token_stream(str);
    while (getline(token_stream, token, ','))
    {
        tokens.push_back(token);
    }
    return tokens;
}
// Player class -> 포지션 별 class의 base class 포지션별로 상속될 예정
class Player
{
private:
    string name;
    int birthyear;
    string team;
    string club;
    string position;

public:
    Player() {}
    Player(string name, int birthyear, string team, string club, string position)
    {
        this->name = name;
        this->birthyear = birthyear;
        this->team = team;
        this->club = club;
        this->position = position;
    }
    // pure virtual function이므로
    virtual int setOverallRating() = 0;
    virtual void print()
    {
        cout << this->name << " " << this->team << " " << this->birthyear << " " << this->club << " " << this->position << endl;
    }
    string getName()
    {
        return this->name;
    }
    int getBirthyear()
    {
        return this->birthyear;
    }
    string getTeam()
    {
        return this->team;
    }
    string getClub()
    {
        return this->club;
    }
    string getPosition() { return this->position; }
};
// Player를 상속한 Forward
class Forward : public Player
{
private:
    int goals;
    float shoots_per90;
    float shoots_on_traget_per90;
    float pass_received;
    float dribbles_completed_pct;

public:
    Forward(string name, int birthyear, string team, string club) : Player(name, birthyear, team, club, "FW")
    {
        int a = setOverallRating();
    }
    Forward() {}

    int setOverallRating()
    {
        ifstream file("player_shooting.csv");
        if (!file.is_open())
        {
            cerr << "Error opening file" << endl;
            return 1;
        }

        // Read the file line by line
        string line;
        while (getline(file, line))
        {
            // Split the line into values
            stringstream ss(line);
            string value;
            while (getline(ss, value))
            {
                vector<string> b = split(value);
                if (b[0].compare(this->getName()) == 0)
                {
                    this->goals = stoi(b[6]);
                    this->shoots_per90 = strtof(b[10].c_str(), nullptr);
                    this->shoots_on_traget_per90 = strtof(b[11].c_str(), nullptr);
                }
            }
        }

        ifstream file2("player_possession.csv");
        if (!file2.is_open())
        {
            cerr << "Error opening file" << endl;
            return 1;
        }

        // Read the file line by line
        string line2;
        while (getline(file2, line2))
        {
            // Split the line into values
            stringstream ss2(line2);
            string value2;
            while (getline(ss2, value2))
            {
                vector<string> b2 = split(value2);
                if (b2[0].compare(this->getName()) == 0)
                {
                    this->dribbles_completed_pct = strtof(b2[15].c_str(), nullptr);
                    this->pass_received = strtof(b2[18].c_str(), nullptr) + strtof(b2[19].c_str(), nullptr);
                }
            }
        }
        file.close();
        file2.close();
        return 0;
    }
    void print()
    {
        cout << this->getName() << " " << this->getTeam() << " " << this->getBirthyear() << " " << this->getClub() << " ";
        cout << "FW";
        cout << "\nStats in worldcup\n";
        cout << "shoots_per90 : " << this->shoots_per90 << " Goals : " << this->goals << " shoots_on_traget_per90 : " << this->shoots_on_traget_per90 << endl;
    }
    int getGoals() { return this->goals; }
    float getShoots_per90() { return this->shoots_per90; }
    float getShoots_on_target_per90() { return this->shoots_on_traget_per90; }
    float getPass_received() { return this->pass_received; }
    float getDribbles_completed_pct() { return this->dribbles_completed_pct; }
};

class Midfielder : public Player
{
private:
    float passes_pct;
    float passes_total_distance;
    float passes_about_attack;
    float dribbles_completed_pct;
    float touches;
    float pass_received;

public:
    Midfielder(string name, int birthyear, string team, string club) : Player(name, birthyear, team, club, "MF")
    {
        int a = setOverallRating();
    }
    Midfielder(){};

    int setOverallRating()
    {
        ifstream file("player_passing.csv");
        if (!file.is_open())
        {
            cerr << "Error opening file" << endl;
            return 1;
        }

        // Read the file line by line
        string line;
        while (getline(file, line))
        {
            // Split the line into values
            stringstream ss(line);
            string value;
            while (getline(ss, value))
            {
                vector<string> b = split(value);
                if (b[0].compare(this->getName()) == 0)
                {
                    this->passes_pct = strtof(b[8].c_str(), nullptr);
                    this->passes_total_distance = strtof(b[9].c_str(), nullptr);
                    this->passes_about_attack = strtof(b[28].c_str(), nullptr) + strtof(b[27].c_str(), nullptr) + strtof(b[26].c_str(), nullptr) + stoi(b[25].c_str(), nullptr);
                }
            }
        }

        ifstream file2("player_possession.csv");
        if (!file2.is_open())
        {
            cerr << "Error opening file" << endl;
            return 1;
        }

        // Read the file line by line
        string line2;
        while (getline(file2, line2))
        {
            // Split the line into values
            stringstream ss2(line2);
            string value2;
            while (getline(ss2, value2))
            {
                vector<string> b2 = split(value2);
                if (b2[0].compare(this->getName()) == 0)
                {
                    this->touches = strtof(b2[6].c_str(), nullptr);
                    this->dribbles_completed_pct = strtof(b2[15].c_str(), nullptr);
                    this->pass_received = strtof(b2[18].c_str(), nullptr) + strtof(b2[19].c_str(), nullptr);
                }
            }
        }
        file.close();
        file2.close();
        return 0;
    }
    void print()
    {
        cout << this->getName() << " " << this->getTeam() << " " << this->getBirthyear() << " " << this->getClub() << " ";
        cout << "MF";
        cout << "\nStats in worldcup\n";
        cout << "passes_pct : " << this->passes_pct << " passes_total_distacnde : " << this->passes_total_distance << " passes_about_attack : " << this->passes_about_attack << " ";
        cout << " dribbles_completed_pct : " << this->dribbles_completed_pct << " touches : " << this->touches << " pass_received :  " << this->pass_received << endl;
    }
    float getPasses_pct()
    {
        return this->passes_pct;
    }

    float getPasses_total_distance()
    {
        return this->passes_total_distance;
    }

    float getPasses_about_attack()
    {
        return this->passes_about_attack;
    }

    float getDribbles_completed_pct()
    {
        return this->dribbles_completed_pct;
    }

    float getTouches()
    {
        return this->touches;
    }
    float getPass_received()
    {
        return this->pass_received;
    }
};
class Defender : public Player
{
private:
    int blocks;
    int tackles_won;
    int interceptions;
    int clearances;
    float aerials_won_pct;
    int ball_recovories;

public:
    Defender(string name, int birthyear, string team, string club) : Player(name, birthyear, team, club, "DF")
    {
        int a = setOverallRating();
    }
    Defender() {}

    int setOverallRating()
    {
        ifstream file("player_defense.csv");
        if (!file.is_open())
        {
            cerr << "Error opening file" << endl;
            return 1;
        }

        // Read the file line by line
        string line;
        while (getline(file, line))
        {
            // Split the line into values
            stringstream ss(line);
            string value;
            while (getline(ss, value))
            {
                vector<string> b = split(value);
                if (b[0].compare(this->getName()) == 0)
                {
                    this->blocks = strtof(b[14].c_str(), nullptr);
                    this->tackles_won = stoi(b[15]);
                    this->interceptions = stoi(b[19]) + stoi(b[18]);
                    this->clearances = stoi(b[20]);
                }
            }
        }

        ifstream file2("player_misc.csv");
        if (!file.is_open())
        {
            cerr << "Error opening file" << endl;
            return 1;
        }

        // Read the file line by line
        string line2;
        while (getline(file2, line2))
        {
            // Split the line into values
            stringstream ss2(line2);
            string value2;
            while (getline(ss2, value2))
            {
                vector<string> b2 = split(value2);
                if (b2[0].compare(this->getName()) == 0)
                {
                    this->ball_recovories = stoi(b2[18]);
                    this->aerials_won_pct = strtof(b2[21].c_str(), nullptr);
                }
            }
        }
        file.close();
        file2.close();
        return 0;
    }
    void print()
    {
        cout << this->getName() << " " << this->getTeam() << " " << this->getBirthyear() << " " << this->getClub() << " ";
        cout << "DF";
        cout << "\nStats in worldcup\n";
        cout << "aerials_won_pct : " << this->aerials_won_pct << " ball_recoveries : " << this->ball_recovories << " blocks : " << this->blocks << " clearances : ";
        cout << this->clearances << " interceptions : " << this->interceptions << " tackle_won : " << this->tackles_won << endl;
    }
    int getBlocks()
    {
        return this->blocks;
    }

    int getTackles_won()
    {
        return this->tackles_won;
    }

    int getInterceptions()
    {
        return this->interceptions;
    }

    int getClearances()
    {
        return this->clearances;
    }

    float getAerials_won_pct()
    {
        return this->aerials_won_pct;
    }

    int getBall_recovories()
    {
        return this->ball_recovories;
    }
};
class Goalkeeper : public Player
{
private:
    float save_pct;
    float clean_sheet_pct;
    float gk_pass_pct;

public:
    Goalkeeper(string name, int birthyear, string team, string club) : Player(name, birthyear, team, club, "GK")
    {
        int a = setOverallRating();
    }
    Goalkeeper() {}

    int setOverallRating()
    {
        ifstream file("player_keepers.csv");
        if (!file.is_open())
        {
            cerr << "Error opening file" << endl;
            return 1;
        }

        // Read the file line by line
        string line;
        while (getline(file, line))
        {
            // Split the line into values
            stringstream ss(line);
            string value;
            while (getline(ss, value))
            {
                vector<string> b = split(value);
                if (b[0].compare(this->getName()) == 0)
                {
                    this->save_pct = strtof(b[14].c_str(), nullptr);
                    this->clean_sheet_pct = strtof(b[19].c_str(), nullptr);
                }
            }
        }

        ifstream file2("player_keepersadv.csv");
        if (!file2.is_open())
        {
            cerr << "Error opening file" << endl;
            return 1;
        }

        // Read the file line by line
        string line2;
        while (getline(file2, line2))
        {
            // Split the line into values
            stringstream ss2(line2);
            string value2;
            while (getline(ss2, value2))
            {
                vector<string> b2 = split(value2);
                if (b2[0].compare(this->getName()) == 0)
                {
                    this->gk_pass_pct = strtof(b2[17].c_str(), nullptr);
                }
            }
        }
        file.close();
        file2.close();
        return 0;
        // Code for calculating the defender's overall rating goes here
    }
    void print()
    {
        cout << this->getName() << " " << this->getTeam() << " " << this->getBirthyear() << " " << this->getClub() << " ";
        cout << "GK";
        cout << "\nStats in worldcup\n";
        cout << "clean_sheet_pct : " << this->clean_sheet_pct << " save_pct : " << this->save_pct << " gk_pass_pct : " << this->gk_pass_pct << endl;
    }
    float getSave_pct()
    {
        return this->save_pct;
    }

    float getClean_sheet_pct()
    {
        return this->clean_sheet_pct;
    }

    float getGk_pass_pct()
    {
        return this->gk_pass_pct;
    }
};
class Team
{
public:
    Forward *fwarr;
    Midfielder *mfarr;
    Defender *dfarr;
    Goalkeeper *gkarr;
    string name;
    int fwcount;
    int mfcount;
    int dfcount;
    int gkcount;
    Team(string name, vector<Forward> &fw, vector<Midfielder> &mf, vector<Defender> &df, vector<Goalkeeper> &gk)
    {
        this->name = name;
        fwcount = 0;
        mfcount = 0;
        dfcount = 0;
        gkcount = 0;
        for (int i = 0; i < fw.size(); i++)
        {
            if (fw[i].getTeam().compare(this->getName()) == 0)
            {
                fwcount++;
            }
        }
        for (int i = 0; i < mf.size(); i++)
        {
            if (mf[i].getTeam().compare(this->getName()) == 0)
            {
                mfcount++;
            }
        }
        for (int i = 0; i < df.size(); i++)
        {
            if (df[i].getTeam().compare(this->getName()) == 0)
            {
                dfcount++;
            }
        }
        for (int i = 0; i < gk.size(); i++)
        {
            if (gk[i].getTeam().compare(this->getName()) == 0)
            {
                gkcount++;
            }
        }
        fwarr = new Forward[fwcount];
        int fwarrcount = 0;
        mfarr = new Midfielder[mfcount];
        int mfarrcount = 0;
        dfarr = new Defender[dfcount];
        int dfarrcount = 0;
        gkarr = new Goalkeeper[gkcount];
        int gkarrcount = 0;

        for (int i = 0; i < mf.size(); i++)
        {
            if (mf[i].getTeam().compare(this->getName()) == 0)
            {
                mfarr[mfarrcount] = mf[i];
                mfarrcount++;
            }
        }
        for (int i = 0; i < fw.size(); i++)
        {
            if (fw[i].getTeam().compare(this->getName()) == 0)
            {
                fwarr[fwarrcount] = fw[i];
                fwarrcount++;
            }
        }
        for (int i = 0; i < gk.size(); i++)
        {
            if (gk[i].getTeam().compare(this->getName()) == 0)
            {
                gkarr[gkarrcount] = gk[i];
                gkarrcount++;
            }
        }
        for (int i = 0; i < df.size(); i++)
        {
            if (df[i].getTeam().compare(this->getName()) == 0)
            {
                dfarr[dfarrcount] = df[i];
                dfarrcount++;
            }
        }
    }
    Team()
    {
    }
    // 소멸자
    ~Team()
    {
        cout << this->name << "team destructor called \n";
        delete[] fwarr;
        delete[] mfarr;
        delete[] dfarr;
        delete[] gkarr;
    }
    void print()
    {
        printFW();
        printMF();
        printDF();
        printGK();
    }

    string getName()
    {
        return this->name;
    }

    int getFwcount() { return this->fwcount; }
    int getMfcount() { return this->mfcount; }
    int getDfcount() { return this->dfcount; }
    int getGkcount() { return this->gkcount; }
    void printFW()
    {
        for (int i = 0; i < fwcount; i++)
        {
            fwarr[i].print();
        }
    }
    Forward *getFwarr()
    {
        return this->fwarr;
    }
    Midfielder *getMfarr()
    {
        return this->mfarr;
    }
    Defender *getDfarr()
    {
        return this->dfarr;
    }
    Goalkeeper *getGkarr()
    {
        return this->gkarr;
    }
    void printMF()
    {
        for (int i = 0; i < mfcount; i++)
        {
            mfarr[i].print();
        }
    }
    void printDF()
    {
        for (int i = 0; i < dfcount; i++)
        {
            dfarr[i].print();
        }
    }
    void printGK()
    {
        for (int i = 0; i < gkcount; i++)
        {
            gkarr[i].print();
        }
    }
};

int main()
{
    // Open the file
    ifstream file("player_stats.csv");
    if (!file.is_open())
    {
        cerr << "Error opening file" << endl;
        return 1;
    }
    vector<Forward> fw;
    vector<Midfielder> mf;
    vector<Defender> df;
    vector<Goalkeeper> gk;

    /*파일을 읽은 후 선수의 포지션 정보, 생년월일 , 국가, 소속팀 정보를 포지션별 선수 class로 생성한 후
    main의 각각 포지션별 벡터에 선수 정보 적재*/
    string line;
    int num = 0;
    while (getline(file, line))
    {
        // Split the line into values
        stringstream ss(line);
        string value;
        while (getline(ss, value))
        {
            vector<string> b = split(value);
            if (b[1].compare("FW") == 0)
            {
                Forward a(b[0], stoi(b[5]), b[2], b[4]);
                fw.push_back(a);
            }
            if (b[1].compare("MF") == 0)
            {
                Midfielder a(b[0], stoi(b[5]), b[2], b[4]);
                mf.push_back(a);
            }
            if (b[1].compare("DF") == 0)
            {
                Defender a(b[0], stoi(b[5]), b[2], b[4]);
                df.push_back(a);
            }
            if (b[1].compare("GK") == 0)
            {
                Goalkeeper a(b[0], stoi(b[5]), b[2], b[4]);
                gk.push_back(a);
            }
            num++;
        }
    }
    file.close();

    // 적재 이후 test (team class)
    string kd = "Korea Republic";
    Team teamkr(kd, fw, mf, df, gk);
    // 모든 선수 출력
    cout << endl;
    teamkr.print();
    cout << endl;

    // 우승팀 아르헨티나 정보 적재
    cout << "print argentina" << endl;

    string arge = "Argentina";
    Team teamarg(arge, fw, mf, df, gk);
    cout << endl;
    // 아르헨티나 대표팀 내 모든 선수 출력
    teamarg.print();
    cout << endl;
    cout << "print fw in argentina";
    teamarg.printFW();

    cout << "ended" << endl;

    cout << "test player object";
    // 메서드 작동 여부 check team 객체의 공격수 0번째 값
    Forward test = teamkr.getFwarr()[0];
    test.print();

    Midfielder test1 = teamkr.getMfarr()[1];
    test1.print();

    Goalkeeper test2 = teamarg.getGkarr()[0];
    test2.print();

    return 0;
}
