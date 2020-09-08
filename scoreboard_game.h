//TO BE IMPLEMENTED. SEE COMMENT IN LINE 104 IN HANGMAN.CPP

#ifndef SCOREBOARD_GAME_H_INCLUDED
#define SCOREBOARD_GAME_H_INCLUDED

#include <vector>
#include "game.h"

class ScoreboardGames
{
public:
    ScoreboardGames();
    virtual ~ScoreboardGames();

    void push_back(Game g);
    int size();

    friend std::ostream& operator<<(std::ostream& out, ScoreboardGames board);

private:

    std::vector<Game> _games;

};

#endif // SCOREBOARD_GAME_H_INCLUDED
