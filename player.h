#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <vector>
#include <string>
#include "game.h"

class Player
{
public:
    Player();
    Player(std::string name, int gamesLost, int gamesWon, double totalScore);
    virtual ~Player();

    std::string get_name() const;
    int get_gamesLost() const;
    int get_gamesWon() const;
    double get_currentScore() const;
    double get_totalScore() const;

    void set_name(std::string name);
    void inc_gamesLost();
    void inc_gamesWon();
    void set_currentScore(double value);
    void set_totalScore(double value);

    friend std::ostream& operator <<(std::ostream& out, Player player);
    bool operator <(const Player &player) const;

private:

    std::string _name;

    //std::vector<Game> _games;

    int _gamesLost;
    int _gamesWon;

    double _currentScore;
    double _totalScore;
};

#endif // PLAYER_H_INCLUDED
