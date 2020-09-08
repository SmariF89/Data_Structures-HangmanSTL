#include "player.h"

Player::Player()
{
    _currentScore = 0;
}

Player::Player(std::string name, int gamesLost, int gamesWon, double totalScore)
{
    _name = name;
    _gamesLost = gamesLost;
    _gamesWon = gamesWon;
    _totalScore = totalScore;
    _currentScore = 0;
}

Player::~Player(){};


std::string Player::get_name() const
{
    return _name;
}

int Player::get_gamesLost() const
{
    return _gamesLost;
}

int Player::get_gamesWon() const
{
    return _gamesWon;
}

double Player::get_totalScore() const
{
    return _totalScore;
}

void Player::set_name(std::string name)
{
    _name = name;
}

void Player::inc_gamesLost()
{
    _gamesLost++;
}

void Player::inc_gamesWon()
{
    _gamesWon++;
}

void Player::set_totalScore(double value)
{
    _totalScore += value;
}

void Player::set_currentScore(double value)
{
    _currentScore+= value;
}

double Player::get_currentScore() const
{
    return _currentScore;
}

std::ostream& operator <<(std::ostream& out, Player player)
{
    out << player._name << "            " << player._gamesWon << "             " << player._gamesLost << "               " << player._totalScore;

    return out;
}

//Overloaded in order to get highest scores at top.
bool Player::operator <(const Player &player) const
{
    if(_name == player._name)
    {
        if(_totalScore == player._totalScore)
        {
            return (_name > player._name);
        }
        return (_totalScore > player._totalScore);
    }
    return (_totalScore > player._totalScore);
}
