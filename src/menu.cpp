#include "menu.h"
#include <functional>
#include <map>
#include "connect_4.hpp"
#include "get_input_from_user.h"
#include "guess_the_number.h"
#include "hangman.hpp"
#include "noughts_and_crosses.hpp"

struct Game {
    std::string           _name;
    std::function<void()> _play;
};

static const std::map<char, Game> games{
    {'1', {"Guess the Number", play_guess_the_number}},
    {'2', {"Hangman", play_hangman}},
    {'3', {"Noughts & Crosses", play_noughts_and_crosses}},
    {'4', {"Connect 4", play_connect_4}}};

void show_list_of_commands()
{
    std::cout << "What do you want to do?\n";
    for (auto& [command, game] : games) {
        std::cout << "  " << command << ": Play '" << game._name << "'\n";
    }
    std::cout << "  q: Quit\n";
}

void show_menu()
{
    bool quit = false;
    while (!quit) {
        show_list_of_commands();
        const auto command = get_input_from_user<char>();
        if (command == 'q') {
            std::cout << "Bye bye \n";
            quit = true;
        }
        else {
            const auto it = games.find(command);
            if (it != games.end())
                it->second._play();
            else
                std::cout << "Invalid command\n";
        }
    }
}