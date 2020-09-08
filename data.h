#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include "player.h"
#include "game.h"

#include <stdio.h>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_set>
#include <set>
#include <fstream>

class DataLayer
{
public:
    DataLayer();
    virtual ~DataLayer();

    void initialize_words();
    void initialize_players();
    void initialize_games();

    std::string get_word();
    void add_word(std::string newWord);
    std::vector<std::string> get_all_words();

    void add_player(std::string name);
    void update_player(Player p);

    std::vector<Player> get_players();

    void print_test();


private:

    std::unordered_set<std::string> bank;
    std::set<Player> players;
    std::set<Game> games;
};

#endif // DATA_H_INCLUDED
