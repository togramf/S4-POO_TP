
#include "play_guess_the_number.h"

/**
 * @brief return a random int between min and max (both included)
 * 
 * @param min 
 * @param max 
 * @return int 
 */
int rand (int min, int max) 
{
    static std::default_random_engine generator{std::random_device{}()};
    std::uniform_int_distribution<int> distribution{min, max};
    return distribution(generator);
}

int get_int_from_user() 
{
    int int_user = -1;
    while (!(std::cin >> int_user) || !(int_user<=100 && int_user>=0)){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input, please enter a number between 0 and 100. \n";
    }
    return int_user;
}

void compare(const int hypothese, const int to_find)
{
    if (hypothese > to_find)
        std::cout << "Smaller\n";
    else if (hypothese < to_find)
        std::cout << "Greater\n";
    else 
        std::cout << "Congrats, you won!\n";
}

void play_guess_the_number()
{
    srand(time(0));

    int number_to_find = rand(0,100); 
    int number_guess;

    std::cout << "Hello U! Let's play 'Guess the number'!\n";
    std::cout << "I picked a number between 0 and 100, try to guess it\n";

    while (number_guess != number_to_find) {
        number_guess = get_int_from_user();
        compare(number_guess, number_to_find);
    }
}