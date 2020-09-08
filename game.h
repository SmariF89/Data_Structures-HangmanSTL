//TO BE IMPLEMENTED. SEE COMMENT IN LINE 104 IN HANGMAN.CPP

#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <string>
#include <iostream>
#include <ctime>

class Game
{
public:
    Game();
    virtual ~Game();

    void set_status(int b);
    void set_guesses(int value);
    void set_scoreEarned(double value);
    void set_player(std::string player);
    void set_time(std::string time);
    void set_word(std::string word);
    void set_difficulty(std::string difficulty);

    std::string get_status();
    int get_guesses();
    double get_scoreEarned();
    std::string get_player();
    std::string get_time();
    std::string get_word();
    std::string get_difficulty();

    friend std::ostream& operator <<(std::ostream& out, Game game);
    bool operator <(const Game &game) const;

private:

    bool _wasWon;

    int _guesses;

    double _scoreEarned;

    std::string _player;
    std::string _time;
    std::string _word;
    std::string _difficulty;
};

#endif // GAME_H_INCLUDED
