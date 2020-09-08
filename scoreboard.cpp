#include "scoreboard.h"

ScoreboardPlayers::ScoreboardPlayers(){}

ScoreboardPlayers::~ScoreboardPlayers(){}

void ScoreboardPlayers::push_back(Player p)
{
    for(std::vector<Player>::iterator it = _players.begin(); it != _players.end(); it++)
    {
        //Overwriting, avoiding duplicates.
        if(it->get_name() == p.get_name())
        {
            *it = p;
            return;
        }
    }

    _players.push_back(p);
}

int ScoreboardPlayers::size()
{
    return _players.size();
}

//Ascii credits: http://scoreboard.ascii.uk/
std::ostream& operator<<(std::ostream& out, ScoreboardPlayers board)
{
    std::cout <<    "                        _                         _ " << std::endl;
    std::cout <<    "                       | |                       | |" << std::endl;
    std::cout <<    " ___  ___ ___  _ __ ___| |__   ___   __ _ _ __ __| |" << std::endl;
    std::cout <<    "/ __|/ __/ _ \\| '__/ _ \\ '_ \\ / _ \\ / _` | '__/ _` |" << std::endl;
    std::cout <<    "\\__ \\ (_| (_) | | |  __/ |_) | (_) | (_| | | | (_| |" << std::endl;
    std::cout <<    "|___/\\___\\___/|_|  \\___|_.__/ \\___/ \\__,_|_|  \\__,_|" << std::endl << std::endl;

    std::cout << "Name	          Games won	Games lost	Total score" << std::endl;

    for(std::vector<Player>::iterator it = board._players.begin(); it != board._players.end(); it++)
    {
        out << *it << std::endl;
    }

    return out;
}



