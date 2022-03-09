
#include "guess_the_number.h"

int get_int_from_user(const int min, const int max)
{
    int int_user = get_input_from_user<int>(min, max);
    return int_user;
}

void compare(const int hypothese, const int to_find)
{
    if (hypothese > to_find)
        std::cout << "Smaller\n";
    else if (hypothese < to_find)
        std::cout << "Greater\n";
    else
        std::cout << "Congrats, you won ";
}

void play_guess_the_number()
{
    srand(time(0));

    int number_to_find = rand(0, 100);
    int number_guess;
    int score = 0;

    std::cout << "Hello U! Let's play 'Guess the number'!\n";
    std::cout << "I picked a number between 0 and 100, try to guess it\n";

    while (number_guess != number_to_find) {
        number_guess = get_int_from_user(0, 100);
        compare(number_guess, number_to_find);
        score++;
    }
    std::cout << "in " << score << " tries !\n";
}