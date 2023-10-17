#include <iostream>
#include <string>
#include <limits>
#include <random>
#include "print_messages.h"
#include "application.h"
#include "string_handling.h"

//Pauses execution until user input
void application::pause()
{
    std::cin.clear();
    std::cin.sync();
    std::cin.get();
}

//Clears console screen
void application::clear()
{
    std::cout << "\x1B[2J\x1B[H";
}

//checks for valid character
std::string application::valid_char(const std::string& input_valid_character)
{
    std::string input{};
    std::cin >> input;
    while (input.size() != 1 || input_valid_character.find(input) == std::string::npos)
    {
        std::cin.clear();
        std::cout << "\nInput invalid, please enter a valid character : ";
        std::cin >> input;
    }
    return input;
}

//checks for valid number
int application::valid_num(const int input_max_number)
{
    int input{};
    std::cin >> input;
    while (std::cin.fail() || input > input_max_number)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nInput invalid, please enter a valid number below or equal to " << input_max_number << " : ";
        std::cin >> input;
    }
    return input;
}

//Processes all user inputs until valid quit key is detected
void application::process_user_inputs()
{
    application application;
    std::string user_selection{};
    bool running{ true };
    while (running)
    {
        string_handling::init_active_chars();
        string_handling::random_key();
        std::cout << "char list " << char_list << std::endl;
        std::cout << "active chars " << active_chars << std::endl;
    	print_messages::print_menu();
        user_selection = application.valid_char("kKsSeEdDcCqQ");
        clear();
        while (running)
        {
            if (user_selection == "k" || user_selection == "K")
            {
                string_handling::encryption_key();
                break;
            }
            if (user_selection == "s" || user_selection == "S")
            {
                string_handling::store_user_phrase();
                break;
            }
            if (!user_phrase.empty() && user_selection == "e" || !user_phrase.empty() && user_selection == "E")
            {
                string_handling::encrypt_phrase();
                break;
            }
            if (user_phrase.empty() && user_selection == "e" || user_phrase.empty() && user_selection == "E")
            {
                print_messages::print_no_phrase();
                break;
            }
            if (!user_phrase.empty() && user_selection == "d" || !user_phrase.empty() && user_selection == "D")
            {
                string_handling::decrypt_phrase();
                break;
            }
            if (user_phrase.empty() && user_selection == "d" || user_phrase.empty() && user_selection == "D")
            {
                print_messages::print_no_phrase();
                break;
            }
            if (user_selection == "c" || user_selection == "C")
            {
                string_handling::clear_phrase();
                break;
            }
            if (user_selection == "q" || user_selection == "Q")
            {
                running = false;
            }
        }
    }
}