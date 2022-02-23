#include "menu.h"

void show_list_of_commands()
{
    std::cout << "What do you want to do?\n";
    std::cout << "  1: Play 'Guess the Number'\n";
    std::cout << "  2: Play 'Hangman'\n";
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
            switch (command) {
            case '1':
                play_guess_the_number();
                break;
            case '2':
                play_hangman();
                break;
            }
        }
    }
}