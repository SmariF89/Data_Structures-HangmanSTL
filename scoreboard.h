#ifndef SCOREBOARD_H_INCLUDED
#define SCOREBOARD_H_INCLUDED

#include <vector>
#include "player.h"

class ScoreboardPlayers
{
public:
    ScoreboardPlayers();
    virtual ~ScoreboardPlayers();

    void push_back(Player p);
    int size();

    friend std::ostream& operator<<(std::ostream& out, ScoreboardPlayers board);

private:

    std::vector<Player> _players;

};

#endif // SCOREBOARD_H_INCLUDED
