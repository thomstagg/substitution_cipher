#include "handle_strings.h"
#include "console_out.h"
#include "handle_console.h"
#include <string>
#include <iostream>
#include <random>
#include <algorithm>

handle_strings::handle_strings(std::string* user_phrase_string, std::string* active_key_string, char* invalid_char):
    user_phrase_(user_phrase_string),
    active_key_(active_key_string),
	invalid_char_(invalid_char)
{
}

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

//Encrypts or decrypts input string
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

//Sets active_key_string to the randomly generated key from return_random_key
void handle_strings::key_init()
{
    *active_key_ = return_random_key(char_list_);
    active_chars_ = char_list_;
}

void handle_strings::encryption_key()
{
    bool running{ true };
    while (running)
    {
        console_out console_out(user_phrase_, active_key_, invalid_char_);
        handle_console handle_console;
        std::string user_selection{};
        console_out.print_encrypt_key_menu();
        user_selection = handle_console.valid_char("123");
        if (user_selection == "1")
        {
            handle_console.clear();
            key_init();
            std::cout << "New key generated successfully!" << std::endl;
            console_out.print_current_key();
            std::cout << "\nPress 'Y' to continue: ";
            user_selection = handle_console.valid_char("yYnN");
            if (user_selection == "y" || user_selection == "Y")
            {
                handle_console.clear();
                running = false;
            }
        }
        if (user_selection == "2")
        {
            handle_console.clear();
            std::cout << "Enter your encryption key below" << std::endl;
            std::cout << "\nYour key: ";
            handle_console.pause();
            std::getline(std::cin, *active_key_);
            handle_console.clear();
            std::cout << "Encryption key updated successfully!";
            console_out.print_current_key();
            std::cout << "\nPress 'Y' to continue: ";
            user_selection = handle_console.valid_char("yYnN");
            if (user_selection == "y" || user_selection == "Y")
            {
                handle_console.clear();
                running = false;
            }
        }
        if (user_selection == "3")
        {
            handle_console.clear();
            running = false;
        }
    }
}

//Gets words from user to be stored in the user_phrase string
void handle_strings::store_user_phrase()
{
    console_out console_out(user_phrase_, active_key_, invalid_char_);
    const std::string user_phrase = *user_phrase_;
    if (user_phrase.length() > 0)
    {
        console_out.print_phrase_already_stored();
    }
    if (user_phrase.length() == 0)
    {
        handle_console handle_console;
        bool running{ true };
        while (running)
        {
            
            std::cout << "Enter the word or phrase you would like to be encrypted or decrypted" << std::endl;
            std::cout << "\nYour Phrase: ";
            handle_console.pause();
            std::getline(std::cin, *user_phrase_);
            handle_console.clear();
            if (user_phrase_)
            {
                console_out.print_store_phrase_success();
                running = false;
            }
        }
    }
}

//Encrypts user phrase
void handle_strings::encrypt()
{
    bool running{ true };
    while (running)
    {
        handle_console handle_console;
    	console_out console_out(user_phrase_, active_key_, invalid_char_);
        console_out.print_current_key();
        std::cout << "\nWhen ready to proceed press 'Y' or to cancel press 'N': ";
        std::string user_selection = handle_console.valid_char("yYnN");
        if (user_selection == "n" || user_selection == "N")
        {
            running = false;
        }
        if (user_selection == "y" || user_selection == "Y")
        {
            std::cout << "\nEnter the number of encryption passes you would like: ";
            int num_of_passes = handle_console.valid_num(100);
            handle_console.clear();
            for (int x{ 0 }; x < num_of_passes; ++x)
            {
                std::string user_phrase = *user_phrase_;
                bool success{ false };
                for (size_t i{ 0 }; i < user_phrase.length(); ++i)
                {
                    const size_t position = active_chars_.find(user_phrase.at(i));
                    if (position > active_chars_.length())
                    {
                        *invalid_char_ = user_phrase.at(i);
                        success = false;
                    }
                    if (i != std::string::npos && position <= active_chars_.length())
                    {
                        success = true;
                    }
                }
                if (success)
                {
                    active_chars_ = encrypt_decrypt(active_chars_,
                    char_list_, *active_key_, *active_key_);
                    *user_phrase_ = encrypt_decrypt(*user_phrase_,
                    active_chars_, *user_phrase_, *active_key_);
                    running = false;
                }
                else
                {
                    console_out.print_char_not_in_key();
                    num_of_passes = 0;
                    running = false;
                }
            }
            if (num_of_passes == 1)
            {
                std::cout << "*1 encryption pass complete*" << std::endl;
                console_out.print_encrypt_success();
            }
            if (num_of_passes > 1)
            {
                std::cout << "\n*" << num_of_passes << " encryption passes complete*" << std::endl;
                console_out.print_encrypt_success();
            }
        }
    }
}

//Decrypts user phrase
void handle_strings::decrypt()
{
    bool running{ true };
    while (running)
    {
        console_out console_out(user_phrase_, active_key_, invalid_char_);
        bool success{ false };
        console_out.print_current_key();
        std::cout << "\nEnter the number of decryption passes you would like: ";
        handle_console handle_console;
        int num_of_passes = handle_console.valid_num(100);
        handle_console.clear();
        active_chars_ = encrypt_decrypt(active_chars_, char_list_,
        *active_key_, *active_key_);
        std::string user_phrase = *user_phrase_;
        for (int x{ 0 }; x < num_of_passes; ++x)
        {
            for (size_t i{ 0 }; i < user_phrase.length(); ++i)
            {
                std::string active_key = *active_key_;
                const size_t position = active_key.find(user_phrase.at(i));
                const char letter = user_phrase.at(i);
                if (position > active_key.length() || active_key.find(letter) == std::string::npos)
                {
                    *invalid_char_ = user_phrase.at(i);
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
                *user_phrase_ = encrypt_decrypt(*user_phrase_, *active_key_,
                *user_phrase_, active_chars_);
                running = false;
            }
            if (success == false)
            {
                {
                    console_out.print_char_not_in_key();
                    num_of_passes = 0;
                    running = false;
                }
            }
        }
        if (num_of_passes == 1)
        {
            std::cout << "\n*1 decryption pass complete*" << std::endl;
            console_out.print_decrypt_success();
        }
        if (num_of_passes > 1)
        {
            std::cout << "\n*" << num_of_passes << " decryption passes complete*" << std::endl;
            console_out.print_decrypt_success();
        }
    }
}

//Clears the user_phrase string
void handle_strings::clear_phrase()
{
    console_out console_out(user_phrase_, active_key_, invalid_char_);
    std::string user_selection{};
    std::cout << "\nAre you sure you would like to clear your stored phrase?" << std::endl;
    std::cout << "\nIf yes press 'Y' or press 'N' to return to the menu : ";
    handle_console handle_console;
    user_selection = handle_console.valid_char("yYnN");
    handle_console.clear();
    if (user_selection == "y" || user_selection == "Y")
    {
        *user_phrase_ = "";
        console_out.print_clear_success();
    }
}