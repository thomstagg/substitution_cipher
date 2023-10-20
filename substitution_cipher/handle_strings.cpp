#include "handle_strings.h"
#include "console_out.h"
#include "handle_console.h"
#include <string>
#include <iostream>
#include <random>
#include <algorithm>

handle_strings::handle_strings()
= default;

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
    active_key_ = return_random_key(char_list_);
    active_chars_ = char_list_;
}

//Returns user phrase for use in app
std::string handle_strings::return_user_phrase()
{
    std::string user_phrase = user_phrase_;
    return user_phrase;
}

//Generates a new key or allows the entry of an existing one
void handle_strings::encryption_key()
{
    bool running{ true };
    while (running)
    {
        console_out console_out;
        handle_console handle_console;
        std::string user_selection{};
        console_out.print_encrypt_key_menu(active_key_);
        user_selection = handle_console.valid_char("123");
        if (user_selection == "1")
        {
            handle_console.clear();
            key_init();
            console_out.message("key_gen_success");
            console_out.print_current_key(active_key_, 1);
            console_out.message("y_continue");
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
            console_out.message("enter_encrypt_key");
            handle_console.pause();
            std::getline(std::cin, active_key_);
            handle_console.clear();
            console_out.message("key_updated_success");
            console_out.print_current_key(active_key_, 2);
            console_out.message("y_continue");
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
    console_out console_out;
    if (user_phrase_.length() > 0)
    {
        console_out.message("phrase_already_stored");
    }
    if (user_phrase_.length() == 0)
    {
        handle_console handle_console;
        bool running{ true };
        while (running)
        {
            console_out.message("enter_phrase");
            handle_console.pause();
            std::getline(std::cin, user_phrase_);
            handle_console.clear();
            if (user_phrase_.length() >= 1)
            {
                console_out.message("store_phrase_success");
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
    	console_out console_out;
        std::string user_selection{};
        console_out.print_current_key(active_key_, 1);
        console_out.message("yes_no");
        user_selection = handle_console.valid_char("yYnN");
        if (user_selection == "n" || user_selection == "N")
        {
            running = false;
        }
        if (user_selection == "y" || user_selection == "Y")
        {
            int num_of_passes{};
            console_out.message("encrypt_pass_num");
            num_of_passes = handle_console.valid_num(100);
            handle_console.clear();
            for (int x{ 0 }; x < num_of_passes; ++x)
            {
                std::string user_phrase = user_phrase_;
                bool success{ false };
                for (size_t i{ 0 }; i < user_phrase.length(); ++i)
                {
                    const size_t position = active_chars_.find(user_phrase.at(i));
                    if (position > active_chars_.length())
                    {
                        invalid_char_ = user_phrase.at(i);
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
                    char_list_, active_key_, active_key_);
                    user_phrase_ = encrypt_decrypt(user_phrase_,
                    active_chars_, user_phrase_, active_key_);
                    running = false;
                }
                else
                {
                    console_out.print_char_not_in_key(invalid_char_);
                    num_of_passes = 0;
                    running = false;
                }
            }
            console_out.print_encrypt_success(num_of_passes);
        }
    }
}

//Decrypts user phrase
void handle_strings::decrypt()
{
    bool running{ true };
    while (running)
    {
        handle_console handle_console;
        console_out console_out;
        bool success{ false };
        int num_of_passes{};
        console_out.print_current_key(active_key_, 2);
        console_out.message("decrypt_pass_num");
        num_of_passes = handle_console.valid_num(100);
        handle_console.clear();
        active_chars_ = encrypt_decrypt(active_chars_, char_list_,
        active_key_, active_key_);
        std::string user_phrase = user_phrase_;
        for (int x{ 0 }; x < num_of_passes; ++x)
        {
            for (size_t i{ 0 }; i < user_phrase.length(); ++i)
            {
                std::string active_key = active_key_;
                const size_t position = active_key.find(user_phrase.at(i));
                const char letter = user_phrase.at(i);
                if (position > active_key.length() || active_key.find(letter) == std::string::npos)
                {
                    invalid_char_ = user_phrase.at(i);
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
                user_phrase_ = encrypt_decrypt(user_phrase_, active_key_,
                user_phrase_, active_chars_);
                running = false;
            }
            if (success == false)
            {
                {
                    console_out.print_char_not_in_key(invalid_char_);
                    num_of_passes = 0;
                    running = false;
                }
            }
        }
        console_out.print_decrypt_success(num_of_passes);
    }
}

//Clears the user_phrase string
void handle_strings::clear_phrase()
{
    handle_console handle_console;
    console_out console_out;
    std::string user_selection{};
    console_out.message("clear_phrase");
    console_out.message("yes_no");
	user_selection = handle_console.valid_char("yYnN");
    handle_console.clear();
    if (user_selection == "y" || user_selection == "Y")
    {
        user_phrase_ = "";
        console_out.message("clear_success");
    }
}