#include "hangman.hpp"

#include <array>
#include <algorithm>

const char* pick_a_word_to_guess()
{
    static constexpr std::array words = {
        "code", 
        "crous", 
        "imac", 
        "opengl",
        "velo",
        "chocolate",
        "jeudimac",
    };

    return words[rand<int>(0,words.size()-1)];
}

char get_char_from_user()
{
    char guess = get_input_from_user<char>('a','z');
    return guess;
}

bool player_is_alive(int number_of_lives)
{
    return number_of_lives > 0;
}

bool player_has_won(const std::vector<bool> &letters_guessed)
{
    return std::all_of(letters_guessed.begin(), letters_guessed.end(), [](bool letters_guessed) {
        return letters_guessed;
    });
}

void show_number_of_lives(int number_of_lives)
{
    std::cout << "You have " << number_of_lives << " lives\n";
}

void show_word_with_missing_letters(const std::string word, const std::vector<bool>& letters_guessed)
{
    for (size_t i=0; i < word.length(); i++){
        if (letters_guessed[i])
            std::cout << word[i];
        else 
            std::cout << "_";
        std::cout<< " ";
    }
    std::cout << std::endl;
}

bool word_contains(std::string word, char guess)
{
    return (word.find(guess) != std::string::npos);
}

void mark_as_guessed(const std::string word, std::vector<bool>& letters_guessed, char guess)
{
    for (size_t i = 0; i < word.length(); i++){
        if (word[i]==guess)
            letters_guessed[i] = true;
    }
}

void remove_one_life(int &number_of_lives)
{
    number_of_lives--;
}

void show_congrats_message(const std::string word)
{
    std::cout << "You found the word '"<< word <<"'! Congratulations!\n";
}

void show_defeat_message(const std::string word)
{
    std::cout << "Sorry, you lost! The word was '"<<word<<"'.\n";
}

void play_hangman() {

    int number_of_lives = 8;

    std::cout << "Hello U! Let's play 'Hangman'!\n";
    std::string word = pick_a_word_to_guess();
    std::vector<bool> letters_guessed; 
    for (size_t i=0; i < word.size(); i++){
        letters_guessed.push_back(false);
    }
    std::cout << "I picked a random word, " << word.size() << " letters, let's try to guess it !\n";
    
    while (player_is_alive(number_of_lives) && !player_has_won(letters_guessed)) {
        show_number_of_lives(number_of_lives);
        show_word_with_missing_letters(word, letters_guessed);
        const auto guess = get_char_from_user();

        if (word_contains(word, guess))
            mark_as_guessed(word, letters_guessed, guess);
        else 
            remove_one_life(number_of_lives);
    }
    if (player_has_won(letters_guessed)) {
        show_congrats_message(word);
    } else {
        show_defeat_message(word);
    }
}