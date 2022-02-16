#include <iostream>
#include <random>

#include "play_guess_the_number.h"
#include "hangman.hpp"

void show_list_of_commands() 
{
    std::cout << "What do you want to do?\n";
    std::cout << "  1: Play 'Guess the Number'\n";
    std::cout << "  2: Play 'Hangman'\n";
    std::cout << "  q: Quit\n";
}

int main()
{
    bool quit = false;
    while (!quit) {
        show_list_of_commands();
        const auto command = get_input_from_user<char>();
        switch (command) {
            case '1':
                play_guess_the_number();
                break;
            case '2':
                play_hangman();
                break;
            case 'q':
                std::cout << "Bye bye !\n";
                return 0;
            default:
                std::cout << "Invalid command\n";
        }
    }

    
}