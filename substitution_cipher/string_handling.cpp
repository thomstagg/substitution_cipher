#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include "print_messages.h"
#include "user_input_handling.h"
#include "string_handling.h"

//Variables initialized
std::string string_handling::default_chars{ "!@#$%^&*()_+-={}[]:;',.<>/?|`~abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890" };
std::string string_handling::char_list_string = default_chars;
std::string string_handling::active_chars_string = default_chars;
std::string string_handling::active_key_string{};
std::string string_handling::user_phrase_string{};
char string_handling::invalid_char{};

//Generates random key using characters in active_chars
 std::string return_random_key(std::string input_string)
{
    std::string chars{};
    chars = std::move(input_string);
    std::random_device random;
    std::mt19937 twist(random());
    std::shuffle(chars.begin(), chars.end(), twist);
    return chars;
}

//Sets active_key_string to the randomly generated key from return_random_key
void string_handling::random_key()
{
    active_key_string = return_random_key(char_list_string);
}

//Gets words from user to be stored in the user_phrase string
void string_handling::store_user_phrase()
{
    if (user_phrase_string.length() > 0)
    {
        std::cout << "\n--------------------------------------------" << std::endl;
        std::cout << "||             A word or phrase           ||" << std::endl;
        std::cout << "||            is already stored!          ||" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
    }
    if (user_phrase_string.length() == 0)
    {
        bool running{ true };
        while (running)
        {
            std::cout << "Enter the word or phrase you would like to be encrypted or decrypted" << std::endl;
            std::cout << "\nYour Phrase: ";
            user_input_handling::pause();
            std::string get_user_phrase{};
            std::getline(std::cin, user_phrase_string);
            user_input_handling::clear();
            if (user_phrase_string.length() > 0)
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
void string_handling::encryption_key()
{
    bool running{ true };
    while (running)
    {
        std::string user_selection{};
        print_messages::print_current_key();
        std::cout << "\nWould you like to generate a new key or enter an existing one?" << std::endl;
        std::cout << "\nEnter 'Y' to proceed or 'N' to keep the current key and return to the menu: ";
        user_selection = user_input_handling::valid_char("yYnN");
        if (user_selection == "y" || user_selection == "Y")
        {
            user_input_handling::clear();
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
            user_selection = user_input_handling::valid_char("12");
            if (user_selection == "1")
            {
                user_input_handling::clear();
                random_key();
                std::cout << "New key generated successfully!" << std::endl;
                print_messages::print_current_key();
                std::cout << "\nPress 'Y' to continue: ";
                user_selection = user_input_handling::valid_char("yYnN");
                if (user_selection == "y" || user_selection == "Y")
                {
                    user_input_handling::clear();
                    break;
                }
            }
            if (user_selection == "2")
            {
                user_input_handling::clear();
                std::cout << "Enter your encryption key below" << std::endl;
                std::cout << "\nYour key: ";
                user_input_handling::pause();
                std::getline(std::cin, active_key_string);
                user_input_handling::clear();
                std::cout << "Encryption key updated successfully!";
                print_messages::print_current_key();
                std::cout << "\nPress 'Y' to continue: ";
                user_selection = user_input_handling::valid_char("yYnN");
                if (user_selection == "y" || user_selection == "Y")
                {
                    user_input_handling::clear();
                    break;
                }
            }
        }
        user_input_handling::clear();
        running = false;
    }
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

//Encrypts user phrase
void string_handling::encrypt_phrase()
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
        std::string user_selection = user_input_handling::valid_char("yYnN");
        if (user_selection == "n" || user_selection == "N")
        {
            running = false;
        }
        if (user_selection == "y" || user_selection == "Y")
        {
            user_input_handling::clear();
            std::cout << "\nEnter the number of encryption passes you would like: ";
            int num_of_passes = user_input_handling::valid_num(100);
            user_input_handling::clear();
            for (int x{ 0 }; x < num_of_passes; ++x)
            {
                bool success{ false };
                for (size_t i{ 0 }; i < user_phrase_string.length(); ++i)
                {
                    const size_t position = active_chars_string.find(user_phrase_string.at(i));
                    if (position > active_chars_string.length())
                    {
                        invalid_char = user_phrase_string.at(i);
                        success = false;
                    }
                    if (i != std::string::npos && position <= active_chars_string.length())
                    {
                        success = true;
                    }
                }
                if (success)
                {
                    active_chars_string = encrypt_decrypt(active_chars_string, char_list_string, active_key_string, active_key_string);
                    user_phrase_string = encrypt_decrypt(user_phrase_string, active_chars_string, user_phrase_string, active_key_string);
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
void string_handling::decrypt_phrase()
{
    bool running{ true };
    while (running)
    {
        bool success{ false };
        print_messages::print_current_key();
        std::cout << "\nEnter the number of decryption passes you would like: ";
        int num_of_passes = user_input_handling::valid_num(100);
        user_input_handling::clear();
        active_chars_string = encrypt_decrypt(active_chars_string, char_list_string, active_key_string, active_key_string);
        for (int x{ 0 }; x < num_of_passes; ++x)
        {
            for (size_t i{ 0 }; i < user_phrase_string.length(); ++i)
            {
                const size_t position = active_key_string.find(user_phrase_string.at(i));
                const char letter = user_phrase_string.at(i);
                if (position > active_key_string.length() || active_key_string.find(letter) == std::string::npos)
                {
                    invalid_char = user_phrase_string.at(i);
                    success = false;
                    break;
                }
                if (position <= active_key_string.length())
                {
                    success = true;
                }
            }
            if (success)
            {
                user_phrase_string = encrypt_decrypt(user_phrase_string, active_key_string, user_phrase_string, active_chars_string);
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
void string_handling::clear_phrase()
{
    std::string user_selection{};
    std::cout << "\nAre you sure you would like to clear your stored phrase?" << std::endl;
    std::cout << "\nIf yes press 'Y' or press 'N' to return to the menu : ";
    user_selection = user_input_handling::valid_char("yYnN");
    user_input_handling::clear();
    if (user_selection == "y" || user_selection == "Y")
    {
        user_phrase_string = "";
        std::cout << "\n--------------------------------------------" << std::endl;
        std::cout << "||           cleared successfully!        ||" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
    }
}