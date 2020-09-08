#ifndef HANGMAN_H_INCLUDED
#define HANGMAN_H_INCLUDED

#include <string>
#include <cstdlib>
#include <stdio.h>
#include <algorithm>
#include <set>
#include <vector>

#include "player.h"
#include "game.h"
#include "scoreboard.h"
#include "scoreboard_game.h"
#include "data.h"

class Hangman
{
    public:
        Hangman();
        virtual ~Hangman();
        void run();


    private:

        bool is_game_over();
        bool is_won();
        bool check_if_letters_exist(char input);
        bool check_if_already_guessed(char input);

        void choose_player();
        void print_rules();
        void new_player();
        void set_word();
        void add_word();
        void replace_letters(char input);
        void clear_screen();
        void menu();
        void display_victory();
        void display_defeat();
        void display_alreadyTried();
        void view_scoreboard_players();
        void turn();
        void game_loop();
        void new_game();
        void set_default();
        void difficulty_select();
        void upper_case(std::string& value);
        void word_list();
        void score();

        int word_length();

        std::string _guess;
        std::string _solution;
        std::string _alreadyTried;
        std::string _difficulty;
        int _triesLeft;

        DataLayer _data;

        ScoreboardGames _sbGames;
        ScoreboardPlayers _sbPlayers;
        Player _currentPlayer;
        Game _currentGame;
};

#endif // HANGMAN_H_INCLUDED
