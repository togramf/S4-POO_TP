#pragma once

#include <iostream>
#include "random.hpp"
#include "get_input_from_user.h"

const char* pick_a_word_to_guess();
char get_char_from_user();
bool player_is_alive(int number_of_lives);
bool player_has_won(const std::vector<bool> &letters_guessed);
void show_number_of_lives(int number_of_lives);
void show_word_with_missing_letters(const std::string word, const std::vector<bool>& letters_guessed);
bool word_contains(std::string word, char guess);
void mark_as_guessed(std::string word, const std::vector<bool>& letters_guessed, char guess);
void remove_one_life(int &number_of_lives);
void show_congrats_message(std::string word);
void show_defeat_message(std::string word);

void play_hangman(); 