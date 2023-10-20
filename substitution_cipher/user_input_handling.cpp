#include <iostream>
#include <string>
#include <limits>
#include <random>

#include "string_handling.h"
#include "user_input_handling.h"
#include "print_messages.h"

//Create class instance
user_input_handling* user_input_handling_main = new user_input_handling();

//Pauses execution until user input
void user_input_handling::pause()
{
    std::cin.clear();
    std::cin.sync();
    std::cin.get();
}

//checks for valid character
std::string user_input_handling::valid_char(const std::string& input_valid_character)
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
int user_input_handling::valid_num(const int input_max_number)
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
void user_input_handling::process_user_inputs()
{
    user_input_handling user_input_handling;
    std::string user_selection{};
    bool running{ true };
    while (running)
    {
        print_messages_main->print_menu();
        user_selection = user_input_handling.valid_char("kKsSeEdDcCqQ");
        print_messages_main->clear();
        while (running)
        {
            if (user_selection == "k" || user_selection == "K")
            {
                string_handling_main->encryption_key();
                break;
            }
            if (user_selection == "s" || user_selection == "S")
            {
                string_handling_main->store_user_phrase();
                break;
            }
            if (!string_handling_main->user_phrase_string.empty() && user_selection == "e" 
                || !string_handling_main->user_phrase_string.empty() && user_selection == "E")
            {
                string_handling_main->encrypt_phrase();
                break;
            }
            if (string_handling_main->user_phrase_string.empty() && user_selection == "e" 
                || string_handling_main->user_phrase_string.empty() && user_selection == "E")
            {
                print_messages_main->print_no_phrase();
                break;
            }
            if (!string_handling_main->user_phrase_string.empty() && user_selection == "d" 
                || !string_handling_main->user_phrase_string.empty() && user_selection == "D")
            {
                string_handling_main->decrypt_phrase();
                break;
            }
            if (string_handling_main->user_phrase_string.empty() && user_selection == "d" 
                || string_handling_main->user_phrase_string.empty() && user_selection == "D")
            {
                print_messages_main->print_no_phrase();
                break;
            }
            if (user_selection == "c" || user_selection == "C")
            {
                string_handling_main->clear_phrase();
                break;
            }
            if (user_selection == "q" || user_selection == "Q")
            {
                running = false;
            }
        }
    }
}