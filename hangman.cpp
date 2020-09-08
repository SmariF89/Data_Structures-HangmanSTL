#include <iostream>

#include "hangman.h"

Hangman::Hangman()
{
    std::vector<Player> availablePlayers = _data.get_players();

    for(size_t i = 0; i < availablePlayers.size(); i++)
    {
        _sbPlayers.push_back(availablePlayers[i]);
    }

    _solution = "";
    _triesLeft = 10;
}

Hangman::~Hangman(){}

///Functions beneath this point and up until next point contain graphics and instructions mostly but also some minor logic.

//Prints the rules of the game.
void Hangman::print_rules()
{
    clear_screen();

    std::cout << "                <--RULES-->                    " << std::endl << std::endl;
    std::cout << " -------------------------------------------" << std::endl;
    std::cout << "| Player plays against the computer.       |" << std::endl;
    std::cout << "| The computer always picks the word.      |" << std:: endl;
    std::cout << "| You can guess a single letter at a time. |" << std:: endl;
    std::cout << "| If you think you have found the correct  |" << std:: endl;
    std::cout << "| answer, you can input the whole word.    |" << std:: endl;
    std::cout << "| Easy difficulty grants you 5 points for  |" << std:: endl;
    std::cout << "| each correct guess.                      |" << std:: endl;
    std::cout << "| Medium difficulty grants you 10 points   |" << std:: endl;
    std::cout << "| for each correct guess.                  |" << std:: endl;
    std::cout << "| Hard difficulty grants you 15 points for |" << std:: endl;
    std::cout << "| each correct guess.                      |" << std:: endl;
    std::cout << " -------------------------------------------" << std::endl;

    char tmp;

    do
    {
        std::cout << std::endl << "Press 'b' and hit <ENTER> to return to menu." << std::endl;
        std::cout << std::endl << "<COMMAND:> ";
        std::cin >> tmp;
    }while(tmp != 'b' && tmp != 'B');

    clear_screen();
    menu();
}

//The first thing the player sees when entering the game. Lets him choose player.
//This offers competition as friends can make new players and compare to each other
//on the scoreboard.
void Hangman::choose_player()
{
    clear_screen();

    int index;
    size_t playerNO;

    std::vector<Player> availablePlayers = _data.get_players();

    std::cout << "       <--PLAYERS-->       " << std::endl << std::endl;

    do
    {
        index = 1;
        playerNO = 0;

        std::cout << "Please choose a player: " << std::endl;
        for(std::vector<Player>::iterator it = availablePlayers.begin(); it != availablePlayers.end(); it++)
        {
            std::cout << index << ". " << it->get_name() << std::endl;
            index++;
        }
        std::cout << "No.: ";
        std::cin >> playerNO;
        clear_screen();
    }while(playerNO > availablePlayers.size());

    _currentPlayer = availablePlayers[playerNO - 1];
    clear_screen();
    menu();
}

//Lets player create a new player. Only a name is needed
//as the other values will be set to 0 by default.
void Hangman::new_player()
{
    clear_screen();

    std::string name;
    std::cout << "       <--NEW PLAYER-->       " << std::endl << std::endl;
    std::cout << "Enter a name: ";
    std::cin >> name;
    _data.add_player(name);

    choose_player();
}

//Displays the scoreboard I already implemented. I planned on having two types of scoreboard
//but I ran out of time. The unused code is still within the project though, if you'd like to see.
//The class is named ScoreboardGames and it contains a vector of Game (which is the class).
void Hangman::view_scoreboard_players()
{
    char tmp;

    std::cout << _sbPlayers << std::endl << std::endl;

    do
    {
        std::cout << std::endl << "Press 'b' and hit <ENTER> to return to menu." << std::endl;
        std::cout << std::endl << "<COMMAND:> ";
        std::cin >> tmp;
    }while(tmp != 'b' && tmp != 'B');

    clear_screen();
    menu();
}

//The main menu. Displays the actions available for the player and shows
//which key to press perform them.
void Hangman::menu()
{
    char input;

    std::cout << "       <--MAIN MENU-->       " << std::endl << std::endl;
    std::cout << "PLAYER: " << _currentPlayer.get_name() << std::endl;
    std::cout << " ----------------------------" << std::endl;
    std::cout << "|'n'......Starts a new game. |" << std::endl;
    std::cout << "|'p'......Change player.     |" << std:: endl;
    std::cout << "|'l'......New player.        |" << std:: endl;
    std::cout << "|'s'......View scoreboards.  |" << std:: endl;
    std::cout << "|'a'......Adds word to bank. |" << std::endl;
    std::cout << "|'w'......View words in bank.|" << std:: endl;
    std::cout << "|'?'......View game rules.   |" << std:: endl;
    std::cout << "|'q'......Quits to desktop.  |" << std::endl;
    std::cout << " ----------------------------" << std::endl;
    std::cout << std::endl << "<COMMAND:> ";
    do
    {
        std::cin >> input;

        if(input == 'N' || input == 'n')
        {
            new_game();
        }
        else if(input == 'P' || input == 'p')
        {
            choose_player();
        }
        else if(input == 'L' || input == 'l')
        {
            new_player();
        }
        else if(input == 'S' || input == 's')
        {
            view_scoreboard_players();
        }
        else if(input == 'A' || input == 'a')
        {
            add_word();
        }
        else if(input == 'W' || input == 'w')
        {
            word_list();
        }
        else if(input == '?')
        {
            print_rules();
        }
        else if(input == 'Q' || input == 'q')
        {
            exit(1);
        }
    }while(true);
}

//The main game function. It displays current game status as well as letting the player guess.
void Hangman::game_loop()
{
    do
    {
        std::cout << std::endl;
        std::cout << "Player: " << _currentPlayer.get_name() << std::endl;
        std::cout << "Difficulty: " << _difficulty << std::endl;
        std::cout << "Score: " << _currentPlayer.get_currentScore() << std::endl << std::endl;
        std::cout << "Progress: " << _guess << std::endl;
        std::cout << "Already guessed: ";
        display_alreadyTried();
        std::cout << std::endl;
        std::cout << "Tries left: " << _triesLeft << std::endl;
        turn();

        //If game is lost the earned score of that round will not be added to the total score of the player (which is stored in a file).
        if(is_game_over())
        {
            _currentPlayer.inc_gamesLost();
            _data.update_player(_currentPlayer);
            _sbPlayers.push_back(_currentPlayer);           //Re-inserts the player to the scoreboard after updating.
            display_defeat();
            return;
        }
        //If game is won the earned score of that round will be added to the total score of the player (which is stored in a file).
        else if(is_won())
        {
            _currentPlayer.inc_gamesWon();
            _currentPlayer.set_totalScore(_currentPlayer.get_currentScore());
            _data.update_player(_currentPlayer);
            _sbPlayers.push_back(_currentPlayer);           //Re-inserts the player to the scoreboard after updating.
            display_victory();
            return;
        }
    }while(true);
}

//The guess function. It handles taking player guess input and calls other functions to replace letters etc.
void Hangman::turn()
{
    std::string input;

    std::cout << "Input a letter: ";
    std::cin >> input;
    upper_case(input);

    if(input == _solution)                         //Check whole word
    {
        _guess = input;
        return;
    }
    else if(check_if_letters_exist(input[0]))
    {
        clear_screen();
        std::cout << std::endl << "Correct guess!" << std::endl;
        replace_letters(input[0]);
        score();
    }
    else
    {
        clear_screen();
        std::cout << std::endl << "Incorrect guess!" << std::endl;

        if(check_if_already_guessed(input[0]))
        {
            return;
        }
        //Incorrectly guessed letters are stored and shown to the player.
        //Incorrect guess results in tries left been decremented by 1.
        else
        {
            _alreadyTried.push_back(input[0]);
            _triesLeft--;
        }
    }
}

//The splash screen.
///ASCII credits: http://ascii.co.uk/art/hangman
void Hangman::run()
{
    std::cout << "| |                                            " << std::endl;
    std::cout << "| |__   __ _ _ __   __ _ _ __ ___   __ _ _ __  " << std::endl;
    std::cout << "| '_ \\ / _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\ " << std::endl;
    std::cout << "| | | | (_| | | | | (_| | | | | | | (_| | | | |" << std::endl;
    std::cout << "|_| |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_|" << std::endl;
    std::cout << "                    __/ |                      " << std::endl;
    std::cout << "                   |___/                       " << std::endl;

    std::cout << std::endl << "           Press <ENTER> to continue...        " << std::endl;

    std::cin.get();
    clear_screen();
    choose_player();
}

//Victory display. Displays rewarding words along with the answer.
void Hangman::display_victory()
{
    std::cout << std::endl << std::endl;
    std::cout << "You won!" << std::endl;
    std::cout << "Answer: " << _guess << std::endl;
    std::cout << std::endl << std::endl;
}

//Defeat display. Displays humiliating words along with the correct answer.
void Hangman::display_defeat()
{
    std::cout << std::endl << std::endl;
    std::cout << "You lost!" << std::endl;
    std::cout << "The correct answer was: " << _solution << std::endl;
    std::cout << std::endl << std::endl;
}

//Displays already tried letters.
void Hangman::display_alreadyTried()
{
    for(size_t i = 0; i < _alreadyTried.size(); i++)
    {
        std::cout << _alreadyTried[i] << " ";
    }
}

//Displays difficulty options along with letting player pick one.
void Hangman::difficulty_select()
{
    char input;

    std::cout << "Please select a difficulty level:" << std::endl << std::endl;

    std::cout << "<--MAIN MENU-->" << std::endl << std::endl;
    std::cout << " ------------------------------" << std::endl;
    std::cout << "|'e'......Easy   - 10 guesses. |" << std::endl;
    std::cout << "|'m'......Medium - 5 guesses.  |" << std::endl;
    std::cout << "|'h'......Hard   - 3 guesses.  |" << std::endl;
    std::cout << "|                              |" << std::endl;
    std::cout << "|'b'......Back to menu         |" << std::endl;
    std::cout << " ------------------------------" << std::endl;
    std::cout << std::endl << "<COMMAND:> ";

    do
    {
        std::cin >> input;

        if(input == 'b' || input == 'B')
        {
            clear_screen();
            menu();
        }
        else if(input == 'e' || input == 'E')
        {
            _triesLeft = 10;
            _difficulty = "Easy";
            return;
        }
        else if(input == 'm' || input == 'M')
        {
            _triesLeft = 5;
            _difficulty = "Medium";
            return;
        }
        else if(input == 'h' || input == 'H')
        {
            _triesLeft = 3;
            _difficulty = "Hard";
            return;
        }
    }while(input != 'e' || input != 'E' || input != 'm' || input != 'M' || input != 'h' || input != 'H');
}

//Gets a vector of all possible words from database and displays them.
void Hangman::word_list()
{
    std::vector<std::string> theList = _data.get_all_words();
    char tmp;

    clear_screen();
    std::cout << "<--WORD LIST-->" << std::endl << std::endl;
    for(std::vector<std::string>::iterator it = theList.begin(); it != theList.end(); it++)
    {
        std::cout << *it << std::endl;
    }

    do
    {
        std::cout << std::endl << "Press 'b' and hit <ENTER> to return to menu." << std::endl;
        std::cout << std::endl << "<COMMAND:> ";
        std::cin >> tmp;
    }while(tmp != 'b' && tmp != 'B');

    clear_screen();
    menu();

}

///Functions beneath this point contain logic only.

//Starts a new game progress. From difficulty selection until you get back to menu.
void Hangman::new_game()
{
    difficulty_select();    //Select difficulty.
    clear_screen();         //Makes a screen transition.
    set_word();             //Gets a random word.
    game_loop();            //Starts the game sequence.
    set_default();          //Sets variables back to default.
    menu();                 //Goes back to main menu.
}

//Grants player score depending on difficulty level.
void Hangman::score()
{
    if(_difficulty == "Easy")
    {
        _currentPlayer.set_currentScore(5);
    }
    else if(_difficulty == "Medium")
    {
        _currentPlayer.set_currentScore(10);
    }
    else if(_difficulty == "Hard")
    {
        _currentPlayer.set_currentScore(15);
    }
}

//The game is won if the guess is the same as the solution.
bool Hangman::is_won()
{
    return _guess == _solution;
}

//The game is over if the tries left have reached 0.
bool Hangman::is_game_over()
{
    return _triesLeft == 0;
}

//Clears the screen. Is called multiple times in the program in order to
//simulate smooth transitions between screens.
void Hangman::clear_screen()
{
    for(int i = 0; i < 100; i++)
    {
        std::cout << std::endl;
    }
}

//Sets game values to their default settings before starting a new game.
void Hangman::set_default()
{
    _triesLeft = 10;
    _guess = "";
    _alreadyTried = "";
    _currentPlayer.set_currentScore(0);
}

//Checks if the input letter is in the solution.
bool Hangman::check_if_letters_exist(char input)
{
    for(int i = 0; i < word_length(); i++)
    {
        if(_solution[i] == input)
        {
            return true;
        }
    }
    return false;
}

//Checks if the input letter has already been guessed.
bool Hangman::check_if_already_guessed(char input)
{
    for(size_t i = 0; i < _alreadyTried.size(); i++)
    {
        if(_alreadyTried[i] == input)
        {
            return true;
        }
    }
    return false;
}

//Replaces the dashes in _guess with correct letters in correct places.
void Hangman::replace_letters(char input)
{
    for(int i = 0; i < word_length(); i++)
    {
        if(_solution[i] == input)
        {
            _guess[i] = input;
        }
    }
}

//Gets a random word from database. _guess becomes a string of
//dashes which is the same length as the random word.
void Hangman::set_word()
{
    _solution = _data.get_word();
    upper_case(_solution);

    for(int i = 0; i < word_length(); i++)
    {
        _guess.push_back('-');
    }
}

//Adds a word to the database.
void Hangman::add_word()
{
    clear_screen();

    std::string newWord;

    std::cout << "<--ADD WORD-->" << std::endl << std::endl;
    std::cout << "Input a new word to the word bank: ";

    std::cin >> newWord;
    upper_case(newWord);
    _data.add_word(newWord);

    clear_screen();
    word_list();
}

//Puts value to upper-case.
void Hangman::upper_case(std::string& value)
{
    std::transform(value.begin(), value.end(),value.begin(), ::toupper);
}

//Returns the length of _solution.
int Hangman::word_length()
{
    return _solution.size();
}
