//TO BE IMPLEMENTED. SEE COMMENT IN LINE 104 IN HANGMAN.CPP

#include "scoreboard_game.h"

ScoreboardGames::ScoreboardGames(){}

ScoreboardGames::~ScoreboardGames(){}


void ScoreboardGames::push_back(Game g)
{
    for(std::vector<Game>::iterator it = _games.begin(); it != _games.end(); it++)
    {
        if(it->get_player() == g.get_player())
        {
            *it = g;
            return;
        }
    }

    _games.push_back(g);
}

int ScoreboardGames::size()
{
    return _games.size();
}

//Ascii credits: http://scoreboard.ascii.uk/
std::ostream& operator<<(std::ostream& out, ScoreboardGames board)
{
    std::cout <<    "                        _                         _ " << std::endl;
    std::cout <<    "                       | |                       | |" << std::endl;
    std::cout <<    " ___  ___ ___  _ __ ___| |__   ___   __ _ _ __ __| |" << std::endl;
    std::cout <<    "/ __|/ __/ _ \\| '__/ _ \\ '_ \\ / _ \\ / _` | '__/ _` |" << std::endl;
    std::cout <<    "\\__ \\ (_| (_) | | |  __/ |_) | (_) | (_| | | | (_| |" << std::endl;
    std::cout <<    "|___/\\___\\___/|_|  \\___|_.__/ \\___/ \\__,_|_|  \\__,_|" << std::endl;

    std:: cout << "Player		Time			Word		Difficulty		Won/Lost	#Guesses		Score earned";

    for(std::vector<Game>::iterator it = board._games.begin(); it != board._games.end(); it++)
    {
        out << *it << std::endl;
    }

    return out;
}



