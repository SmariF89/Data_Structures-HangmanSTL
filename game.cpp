//TO BE IMPLEMENTED. SEE COMMENT IN LINE 104 IN HANGMAN.CPP

#include "game.h"

Game::Game(){}

Game::~Game(){}

std::ostream& operator <<(std::ostream& out, Game game)
{
    out << game._player << "          " << game._time << "     " << game._word << "     " << game._difficulty << "     " << game.get_status() << "     " << game._guesses << "     " << game._scoreEarned;

    return out;
}

bool Game::operator <(const Game &game) const
{
    return (_player < game._player);
}



std::string Game::get_status()
{
    if(_wasWon)
    {
        return "Won";
    }
    else
    {
        return "Lost";
    }
}

int Game::get_guesses()
{
    return _guesses;
}

double Game::get_scoreEarned()
{
    return _scoreEarned;
}

std::string Game::get_player()
{
    return _player;
}

std::string Game::get_time()
{
    return _time;
}

std::string Game::get_word()
{
    return _word;
}

std::string Game::get_difficulty()
{
    return _difficulty;
}


void Game::set_status(int b)
{
    if(b != 0)
    {
        _wasWon = true;
    }
    else
    {
        _wasWon = false;
    }
}

void Game::set_guesses(int value)
{
    _guesses = value;
}

void Game::set_scoreEarned(double value)
{
    _scoreEarned = value;
}

void Game::set_player(std::string player)
{
    _player = player;
}

void Game::set_time(std::string time)
{
    _time = time;
}

void Game::set_word(std::string word)
{
    _word = word;
}

void Game::set_difficulty(std::string difficulty)
{
    _difficulty = difficulty;
}



