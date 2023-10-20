#include "handle_console.h"
#include <iostream>

handle_console::handle_console()
= default;

//Clears console screen
void handle_console::clear()
{
    std::cout << "\x1B[2J\x1B[H";
}

//Pauses execution until user input
void handle_console::pause()
{
    std::cin.clear();
    std::cin.sync();
    std::cin.get();
}

std::string handle_console::valid_char(const std::string& input_valid_character)
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
int handle_console::valid_num(const int input_max_number)
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
