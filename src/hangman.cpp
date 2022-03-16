#include "hangman.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include "get_input_from_user.h"
#include "random.hpp"

class WordWithMissingLetters {
public:
    WordWithMissingLetters(const std::string word)
        : _word(word), _letters_revealed(_word.size(), false) {}

    void mark_as_guessed(char guess)
    {
        for (size_t i = 0; i < _word.length(); i++) {
            if (_word[i] == guess)
                _letters_revealed[i] = true;
        }
    }

    const std::string&       word() const { return _word; }
    const std::vector<bool>& letters_revealed() const { return _letters_revealed; }

private:
    std::string       _word;
    std::vector<bool> _letters_revealed;
};

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

    return words[rand<int>(0, words.size() - 1)];
}

const char* pick_a_word_from_a_list(std::vector<const char*> list)
{
    return list[rand<int>(0, list.size() - 1)];
}

char get_char_from_user()
{
    return get_input_from_user<char>('a', 'z');
}

bool player_is_alive(int number_of_lives)
{
    return number_of_lives > 0;
}

bool player_has_won(const std::vector<bool>& letters_guessed)
{
    return std::all_of(letters_guessed.begin(), letters_guessed.end(), [](bool letters_guessed) {
        return letters_guessed;
    });
}

void show_number_of_lives(int number_of_lives)
{
    if (number_of_lives >= 2)
        std::cout << "You have " << number_of_lives << " lives\n";
    else
        std::cout << "Be carefull, you only have " << number_of_lives << " life\n";
}

void show_word_with_missing_letters(const WordWithMissingLetters& word)
{
    for (size_t i = 0; i < word.word().size(); i++) {
        if (word.letters_revealed()[i])
            std::cout << word.word()[i];
        else
            std::cout << "_";
        std::cout << " ";
    }
    std::cout << std::endl;
}

bool word_contains(const std::string word, char guess)
{
    return (word.find(guess) != std::string::npos);
}

void remove_one_life(int& number_of_lives)
{
    number_of_lives--;
    show_number_of_lives(number_of_lives);
}

void show_congrats_message(const std::string word)
{
    std::cout << "You found the word '" << word << "'! Congratulations!\n";
}

void show_defeat_message(const std::string word)
{
    std::cout << "Sorry, you lost! The word was '" << word << "'.\n";
}

void play_hangman()
{
    int number_of_lives = 8;

    std::cout << "Hello U! Let's play 'Hangman'!\n";
    WordWithMissingLetters         word          = WordWithMissingLetters(pick_a_word_to_guess());
    std::string                    letters_tried = "";
    const std::vector<const char*> congrats_list = {"Great !", "Amazing !", "U're so good", "Yes, :)", "Congrats !", "You rule !", "Hooray !", "I'm proud of you"};
    const std::vector<const char*> reproach_list = {"No no no !", "Nope !", "U're so bad.", "Sorry...", "Of course not !", "You suck !"};

    std::cout << "I picked a random word, " << word.word().size() << " letters, let's try to guess it !\n";
    show_number_of_lives(number_of_lives);

    while (player_is_alive(number_of_lives) && !player_has_won(word.letters_revealed())) {
        show_word_with_missing_letters(word);
        const auto guess = get_char_from_user();

        if (word_contains(letters_tried, guess))
            std::cout << "You tried this already !\n";
        else {
            letters_tried.push_back(guess);
            if (word_contains(word.word(), guess)) {
                std::cout << pick_a_word_from_a_list(congrats_list) << "\n";
                word.mark_as_guessed(guess);
            }
            else {
                std::cout << pick_a_word_from_a_list(reproach_list) << " ";
                remove_one_life(number_of_lives);
            }
        }
    }
    if (player_has_won(word.letters_revealed()))
        show_congrats_message(word.word());
    else
        show_defeat_message(word.word());
}