#include "menu.h"
#include <functional>
#include <map>
#include "hangman.hpp"
#include "play_guess_the_number.h"

struct Game {
    std::string           name;
    std::function<void()> play;
};

static const std::map<char, Game> games{
    {'1', {"Guess the Number", play_guess_the_number}},
    {'2', {"Hangman", play_hangman}}};

void show_list_of_commands()
{
    std::cout << "What do you want to do?\n";
    for (auto& [command, game] : games) {
        std::cout << "  " << command << ": Play '" << game.name << "'\n";
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
            if (it != games.end()) {
                it->second.play();
            }
            else {
                std::cout << "Invalid command\n";
            }
        }
    }
}