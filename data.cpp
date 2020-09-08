#include <fstream>
#include <iostream>             //To be deleted - For debug purposes
#include <cstdlib>
#include <time.h>

#include "data.h"

//The constructor calls separate initialization functions which fill
//the data structures with data from file.
DataLayer::DataLayer()
{
    initialize_words();
    initialize_players();
    initialize_games();         //To be implemented.
}

DataLayer::~DataLayer(){}

//Gets word from file and puts them into an unordered_set. I chose to use that data structure because it does not
//allow duplicates plus it is faster because it is unordered and no time is spent on sorting algorithms which are
//not needed for this game.
void DataLayer::initialize_words()
{
    std::string word;
    std::string url = "word_bank.txt";

    std::ifstream file;

    file.open(url.c_str());

    do
    {
        getline(file, word, ' ');
        if (word == "")
        {
            break;
        }

        std::transform(word.begin(), word.end(),word.begin(), ::toupper);
        bank.insert(word);

    }while (!file.eof());

    file.close();
}

//Gets player data from file and puts it into a set. I chose set because I don't want duplicates but I do want
//sorting. The players are displayed by high score. Highest first.
void DataLayer::initialize_players()
{
    std::string name;
    std::string gamesLost;
    std::string gamesWon;
    std::string totalScore;

    std::string url = "players.txt";

    std::ifstream file;

    file.open(url.c_str());

    do
    {
        getline(file, name, ' ');
        if (name == "")
        {
            break;
        }

        getline(file, gamesLost, ' ');
        getline(file, gamesWon, ' ');
        getline(file, totalScore, ' ');

        int intGamesLost = atoi(gamesLost.c_str());
        int intGamesWon = atoi(gamesWon.c_str());
        double doubleTotalScore = atof(totalScore.c_str());

        Player player(name, intGamesLost, intGamesWon, doubleTotalScore);

        players.insert(player);

    }while (!file.eof());

    file.close();
}

//To be implemented.
void DataLayer::initialize_games()
{

}

//Gets a random word from the bank, based on time. Returns it.
std::string DataLayer::get_word()
{
    //Generate random seed.
    srand(time(NULL));

    //Random seed modulo the set's size gives a random number between 0 and size.
    int randomIndex = rand() % bank.size();

    //Iterator starts at beginning.
    std::unordered_set<std::string>::iterator it = bank.begin();

    //We iterate forward until the random element is reached.
    for(int i = 0; i < randomIndex; i++)
    {
        it++;
    }

    return *it;
}

//Adds a new word to the database. A space is used to separate words in the file.
void DataLayer::add_word(std::string newWord)
{
    std::ofstream out_stream;
    std::string url = "word_bank.txt";

    out_stream.open(url, std::ios::app);
    out_stream << " " << newWord << " ";
    bank.insert(newWord);

     out_stream.close();
}

//Moves all the words from the unordered set to a vector which is in turn returned.
std::vector<std::string> DataLayer::get_all_words()
{
    std::vector<std::string> all_words;

    for(std::unordered_set<std::string>::iterator it = bank.begin(); it != bank.end(); it++)
    {
        all_words.push_back(*it);
    }

    return all_words;
}

//Adds a new player to the databases. The numerical values are set to 0 by default.
void DataLayer::add_player(std::string name)
{
    Player newPlayer(name, 0, 0, 0.0);

    std::ofstream out_stream;
    std::string url = "players.txt";

    out_stream.open(url, std::ios::app);
    out_stream << newPlayer.get_name() << " " << newPlayer.get_gamesLost() << " " << newPlayer.get_gamesWon() << " " << newPlayer.get_totalScore() << " ";
    players.insert(newPlayer);

     out_stream.close();
}

//Damn, this was a complex one!
//It iterates from the beginning of the unordered_set of words until the iterator gets to the desired word.
//This is done in order to erase the correct value, the erase function takes an iterator as parameter.
//Next the entire text file is cleared as well as the desired word is removed from the unordered set.
//Afterwards the text file is rewritten without the recently erased value. Finally, the updated value (Player p)
//is written to the file without any duplication as well as being inserted into the unordered set.
void DataLayer::update_player(Player p)
{
    std::set<Player>::iterator it = players.begin();

    while(it != players.end())
    {
        if(it->get_name() == p.get_name())
        {
            break;
        }
        it++;
    }

    std::ofstream out_stream;
    std::string url = "players.txt";
    out_stream.open(url);
    out_stream.clear();
    players.erase(it);
    for(std::set<Player>::iterator it = players.begin(); it != players.end(); it++)
    {
        out_stream << it->get_name() << " " << it->get_gamesLost() << " " << it->get_gamesWon() << " " << it->get_totalScore() << " ";
    }

    out_stream << p.get_name() << " " << p.get_gamesLost() << " " << p.get_gamesWon() << " " << p.get_totalScore() << " ";
    players.insert(p);

    out_stream.close();
}

//Moves all the player data from the set to a vector which is in turn returned.
std::vector<Player> DataLayer::get_players()
{
    std::vector<Player> all_players;

    for(std::set<Player>::iterator it = players.begin(); it != players.end(); it++)
    {
        all_players.push_back(*it);
    }

    return all_players;
}
