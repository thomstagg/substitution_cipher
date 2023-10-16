#include <iostream>
#include <string>
#include <limits>
#include <random>
#include <algorithm>
#include "print_messages.h"
#include "application.h"


std::string char_list{ "!@#$%^&*()_+-={}[]:;',.<>/?|`~abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890" };
std::string active_chars{};
std::string active_key{};
std::string user_phrase{};
char invalid_char;

//Generates random key using characters in active_chars
std::string random_key(std::string input_string)
{
    std::string chars{};
    chars = std::move(input_string);
    std::random_device random;
    std::mt19937 twist(random());
    std::shuffle(chars.begin(), chars.end(), twist);
    return chars;
}

//Encrypts or decrypts string
std::string encrypt_decrypt(std::string string_to_encrypt, const std::string& string_to_compare_to,
    const std::string& string_get_position_of_char_from, const std::string& encrypt_key)
{
    for (size_t i{ 0 }; i < string_to_encrypt.length(); ++i)
    {
        const size_t position = string_to_compare_to.find(string_get_position_of_char_from.at(i));
        if (i != std::string::npos)
        {
            string_to_encrypt.at(i) = encrypt_key.at(position);
        }
    }
    return string_to_encrypt;
}

//Pauses execution until user input
void pause()
{
    std::cin.clear();
    std::cin.sync();
    std::cin.get();
}

//Clears console screen
void clear()
{
    std::cout << "\x1B[2J\x1B[H";
}

//checks for valid character
std::string valid_char(const std::string& input_valid_character)
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
int valid_num(const int input_max_number)
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

//Gets words from user to be stored in the user_phrase string
void store_user_phrase()
{
    if (user_phrase.length() > 0)
    {
        std::cout << "\n--------------------------------------------" << std::endl;
        std::cout << "||             A word or phrase           ||" << std::endl;
        std::cout << "||            is already stored!          ||" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
    }
    if (user_phrase.length() == 0)
    {
        bool running{ true };
        while (running)
        {
            std::cout << "Enter the word or phrase you would like to be encrypted or decrypted" << std::endl;
            std::cout << "Your Phrase: ";
            pause();
            std::getline(std::cin, user_phrase);
            clear();
            if (user_phrase.length() > 0)
            {
                std::cout << "\n--------------------------------------------" << std::endl;
                std::cout << "||             Words or phrase            ||" << std::endl;
                std::cout << "||           stored successfully!         ||" << std::endl;
                std::cout << "--------------------------------------------" << std::endl;
                running = false;
            }
        }
    }
}

//View or edit encryption key
void encryption_key()
{
    bool running{ true };
    while (running)
    {
        std::string user_selection{};
        print_messages::print_current_key();
        std::cout << "\nWould you like to generate a new key or enter an existing one?" << std::endl;
        std::cout << "\nEnter 'Y' to proceed or 'N' to keep the current key and return to the menu: ";
        user_selection = valid_char("yYnN");
        if (user_selection == "y" || user_selection == "Y")
        {
            clear();
            std::cout << "\nPlease choose from the following options" << std::endl;
            std::cout << "\n--------------------------------------------" << std::endl;
            std::cout << "--------------------------------------------" << std::endl;
            std::cout << "||                                        ||" << std::endl;
            std::cout << "||       1 - Generate New Key             ||" << std::endl;
            std::cout << "||       2 - Enter existing key           ||" << std::endl;
            std::cout << "||                                        ||" << std::endl;
            std::cout << "--------------------------------------------" << std::endl;
            std::cout << "--------------------------------------------" << std::endl;
            std::cout << "Enter your choice: ";
            user_selection = valid_char("12");
            if (user_selection == "1")
            {
                clear();
                active_key = random_key(active_chars);
                std::cout << "New key generated successfully!" << std::endl;
                print_messages::print_current_key();
                std::cout << "\nPress 'Y' to continue: ";
                user_selection = valid_char("yYnN");
                if (user_selection == "y" || user_selection == "Y")
                {
                    clear();
                    break;
                }
            }
            if (user_selection == "2")
            {
                clear();
                std::cout << "Enter your encryption key below" << std::endl;
                std::cout << "\nYour key: ";
                pause();
                std::getline(std::cin, active_key);
                clear();
                std::cout << "Encryption key updated successfully!";
                print_messages::print_current_key();
                std::cout << "\nPress 'Y' to continue: ";
                user_selection = valid_char("yYnN");
                if (user_selection == "y" || user_selection == "Y")
                {
                    clear();
                    break;
                }
            }
        }
        clear();
        running = false;
    }
}

//Encrypts user phrase
void encrypt_phrase()
{
    bool running{ true };
    while (running)
    {
        std::cout << "\n--------------------------------------------" << std::endl;
        std::cout << "||               *IMPORTANT*              ||" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        print_messages::print_current_key();
        std::cout << "\nNote this key down and keep it safe. Without this key future decryption will be impossible!" << std::endl;
        std::cout << "\nWhen ready to proceed press 'Y' or to cancel press 'N': ";
        std::string user_selection = valid_char("yYnN");
        if (user_selection == "n" || user_selection == "N")
        {
            running = false;
        }
        if (user_selection == "y" || user_selection == "Y")
        {
            clear();
            std::cout << "\nEnter the number of encryption passes you would like: ";
            int num_of_passes = valid_num(100);
            clear();
            for (int x{ 0 }; x < num_of_passes; ++x)
            {
                bool success{ false };
                for (size_t i{ 0 }; i < user_phrase.length(); ++i)
                {
                    const size_t position = active_chars.find(user_phrase.at(i));
                    if (position > active_chars.length())
                    {
                        invalid_char = user_phrase.at(i);
                        success = false;
                    }
                    if (i != std::string::npos && position <= active_chars.length())
                    {
                        success = true;
                    }
                }
                if (success)
                {
                    active_chars = encrypt_decrypt(active_chars, char_list, active_key, active_key);
                    user_phrase = encrypt_decrypt(user_phrase, active_chars, user_phrase, active_key);
                    running = false;
                }
                else
                {
                    print_messages::print_char_not_in_key();
                    num_of_passes = 0;
                    break;
                }
            }
            if (num_of_passes == 1)
            {
                std::cout << "*1 encryption pass complete*" << std::endl;
                print_messages::print_encrypt_success();
            }
            if (num_of_passes > 1)
            {
                std::cout << "\n*" << num_of_passes << " encryption passes complete*" << std::endl;
                print_messages::print_encrypt_success();
            }
        }
    }
}

//Decrypts user phrase
void decrypt_phrase()
{
    bool running{ true };
    while (running)
    {
        bool success{ false };
        print_messages::print_current_key();
        std::cout << "\nEnter the number of decryption passes you would like: ";
        int num_of_passes = valid_num(100);
        clear();
        active_chars = encrypt_decrypt(active_chars, char_list, active_key, active_key);
        for (int x{ 0 }; x < num_of_passes; ++x)
        {
            for (size_t i{ 0 }; i < user_phrase.length(); ++i)
            {
                const size_t position = active_key.find(user_phrase.at(i));
                const char letter = user_phrase.at(i);
                if (position > active_key.length() || active_key.find(letter) == std::string::npos)
                {
                    invalid_char = user_phrase.at(i);
                    success = false;
                    break;
                }
                if (position <= active_key.length())
                {
                    success = true;
                }
            }
            if (success)
            {
                user_phrase = encrypt_decrypt(user_phrase, active_key, user_phrase, active_chars);
                running = false;
            }
            if (success == false)
            {
                {
                    print_messages::print_char_not_in_key();
                    num_of_passes = 0;
                    break;
                }
            }
        }
        if (num_of_passes == 1)
        {
            std::cout << "\n*1 decryption pass complete*" << std::endl;
            print_messages::print_decrypt_success();

        }
        if (num_of_passes > 1)
        {
            std::cout << "\n*" << num_of_passes << " decryption passes complete*" << std::endl;
            print_messages::print_decrypt_success();
        }
    }
}

//Clears the user_phrase string
void clear_phrase()
{
    std::string user_selection{};
    std::cout << "\nAre you sure you would like to clear your stored phrase?" << std::endl;
    std::cout << "\nIf yes press 'Y' or press 'N' to return to the menu : ";
    user_selection = valid_char("yYnN");
    clear();
    if (user_selection == "y" || user_selection == "Y")
    {
        user_phrase = {};
        std::cout << "\n--------------------------------------------" << std::endl;
        std::cout << "||           cleared successfully!        ||" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
    }
}

//Processes all user inputs until valid quit key is detected
void application::process_user_inputs()
{
    std::string user_selection{};
    bool running{ true };
    while (running)
    {
        if (active_key.length() == 0)
        {
            active_key = random_key(char_list);
        }
        print_messages::print_menu();
        user_selection = valid_char("kKsSeEdDcCqQ");
        clear();
        while (running)
        {
            if (user_selection == "k" || user_selection == "K")
            {
                encryption_key();
                break;
            }
            if (user_selection == "s" || user_selection == "S")
            {
                store_user_phrase();
                break;
            }
            if (!user_phrase.empty() && user_selection == "e" || !user_phrase.empty() && user_selection == "E")
            {
                encrypt_phrase();
                break;
            }
            if (user_phrase.empty() && user_selection == "e" || user_phrase.empty() && user_selection == "E")
            {
                print_messages::print_no_phrase();
                break;
            }
            if (!user_phrase.empty() && user_selection == "d" || !user_phrase.empty() && user_selection == "D")
            {
                decrypt_phrase();
                break;
            }
            if (user_phrase.empty() && user_selection == "d" || user_phrase.empty() && user_selection == "D")
            {
                print_messages::print_no_phrase();
                break;
            }
            if (user_selection == "c" || user_selection == "C")
            {
                clear_phrase();
                break;
            }
            if (user_selection == "q" || user_selection == "Q")
            {
                running = false;
            }
        }
    }
}