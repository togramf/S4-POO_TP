#pragma once

#include <iostream>

/// Blocks until the user inputs something of type T in the console, and then returns it
template<typename T>
T get_input_from_user()
{
    T input;
    while (!(std::cin >> input)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // std::cin.sync();
        std::cout << "Invalid input, try again! \n";
    }
    return input;
}

template<typename T>
T get_input_from_user(const T min, const T max)
{
    T input;
    while (!(std::cin >> input) || !(input >= min && input <= max)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input, try again! \n";
    }
    return input;
}
