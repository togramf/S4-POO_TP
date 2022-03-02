#pragma once

#include <random>

/**
 * @brief return a random T between min and max (both included)
 * 
 * @param min 
 * @param max 
 * @return T 
 */
template<typename T>
T rand(T min, T max)
{
    static std::default_random_engine generator{std::random_device{}()};
    std::uniform_int_distribution<T>  distribution{min, max};
    return distribution(generator);
}
