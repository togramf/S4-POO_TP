#include "menu.h"
#include <functional>
#include <map>
#include "guess_the_number.h"
#include "hangman.hpp"
#include "noughts_and_crosses.hpp"

struct Game {
    std::string           name;
    std::function<void()> play;
};

static const std::map<char, Game> games{
    {'1', {"Guess the Number", play_guess_the_number}},
    {'2', {"Hangman", play_hangman}},
    {'3', {"Noughts & Crosses", play_noughts_and_crosses}}};

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
        // draw_menu();
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

void draw_menu()
{
    auto ctx = p6::Context{{1000, 800, "Jeux d'IMAC"}};
    ctx.start();
}