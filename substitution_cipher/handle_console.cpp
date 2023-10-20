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
    while (std::cin.fail() || input > input_max_number || input < 1)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (input > input_max_number)
        {
            std::cout << "\n*Input invalid, the number below or equal to " << input_max_number << "*" <<  std::endl;
            std::cout << "\nPlease enter a number: ";
            std::cin >> input;
        }
		if(input < 1)
		{
            std::cout << "\n*Input invalid, minimum number is 1*" << std::endl;
            std::cout << "\nPlease enter a number: ";
            std::cin >> input;
		}
    }
    return input;
}
