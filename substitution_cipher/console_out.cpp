#include "console_out.h"
#include <iostream>

console_out::console_out()
= default;

//Prints no phrase stored warning
void console_out::print_no_phrase()
{
    std::cout << "\n--------------------------------------------" << std::endl;
    std::cout << "||                 Whoops!                ||" << std::endl;
    std::cout << "||            No phrase stored            ||" << std::endl;
    std::cout << "||          please enter a phrase         ||" << std::endl;
    std::cout << "||             using option 'S'           ||" << std::endl;
    std::cout << "||              and try again             ||" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
}

//Prints phrase already stored message
void console_out::print_phrase_already_stored()
{
    std::cout << "\n--------------------------------------------" << std::endl;
    std::cout << "||             A word or phrase           ||" << std::endl;
    std::cout << "||            is already stored!          ||" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
}

//Prints store phrase successful message
void console_out::print_store_phrase_success()
{
    std::cout << "\n--------------------------------------------" << std::endl;
    std::cout << "||                 Phrase                 ||" << std::endl;
    std::cout << "||           stored successfully!         ||" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
}

//Prints encryption key menu
void console_out::print_encrypt_key_menu(const std::string& active_key)
{
    print_current_key(active_key, 2);
    std::cout << "\nPlease choose from the following options" << std::endl;
    std::cout << "\n--------------------------------------------" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "||                                        ||" << std::endl;
    std::cout << "||       1 - Generate New Key             ||" << std::endl;
    std::cout << "||       2 - Enter existing key           ||" << std::endl;
    std::cout << "||       3 - Cancel                       ||" << std::endl;
    std::cout << "||                                        ||" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "\nEnter your choice: ";
}

//Prints encryption success message
void console_out::print_encrypt_success(int& num_of_passes)
{
    if (num_of_passes == 1)
    {
        std::cout << "*1 encryption pass complete*" << std::endl;
    }
    if (num_of_passes > 1)
    {
        std::cout << "\n*" << num_of_passes << " encryption passes complete*" << std::endl;
    }
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "||             Phrase encrypted           ||" << std::endl;
    std::cout << "||               successfully!            ||" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
}

//Prints decryption success message
void console_out::print_decrypt_success(int& num_of_passes)
{
    if (num_of_passes == 1)
    {
        std::cout << "\n*1 decryption pass complete*" << std::endl;
    }
    if (num_of_passes > 1)
    {
        std::cout << "\n*" << num_of_passes << " decryption passes complete*" << std::endl;
    }
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "||             Phrase decrypted           ||" << std::endl;
    std::cout << "||               successfully!            ||" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
}

//Prints character not found in key message
void console_out::print_char_not_in_key(const char& invalid_char)
{
    std::cout << "\n--------------------------------------------" << std::endl;
    std::cout << "||                 Whoops!                ||" << std::endl;
    std::cout << "||        Encryption not possible as      ||" << std::endl;
    std::cout << "||  the character " << invalid_char << " was not found in key! ||" << std::endl;
    std::cout << "||        please clear stored phrase      ||" << std::endl;
    std::cout << "||              and try again             ||" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
}

//Prints current encryption key
void console_out::print_current_key(const std::string& active_key, int option)
{
    if (option == 1)
    {
        std::cout << "\n--------------------------------------------" << std::endl;
        std::cout << "||               *IMPORTANT*              ||" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "\nThe current encryption key is" << std::endl;
        std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
        std::cout << active_key << std::endl;
        std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
        std::cout << "\nNote this key down and keep it safe. Without this key future decryption will be near impossible!" << std::endl;
    }
    if (option == 2)
    {
        std::cout << "\nThe current encryption key is" << std::endl;
        std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
        std::cout << active_key << std::endl;
        std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
    }
}

//Prints console cleared successfully message
void console_out::print_clear_success()
{
    std::cout << "\n--------------------------------------------" << std::endl;
    std::cout << "||           cleared successfully!        ||" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
}


//Prints Menu to console
void console_out::print_menu(const std::string& user_phrase)
{
    std::cout << "\nWelcome to the Substitution Cipher" << std::endl;
    if (user_phrase.length() == 0)
    {
        std::cout << "\n--------------------------------------------" << std::endl;
        std::cout << "You currently have no phrase stored" << std::endl;
        std::cout << "Enter a word or phrase using option 'S'" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
    }
    else
    {
        std::cout << "\n--------------------------------------------" << std::endl;
        std::cout << "Stored Phrase : " << user_phrase << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
    }
    std::cout << "\nPlease choose from the following options" << std::endl;
    std::cout << "\n--------------------------------------------" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "||                                        ||" << std::endl;
    std::cout << "||       S - Enter a phrase               ||" << std::endl;
    std::cout << "||       K - View/change Encrypt Key      ||" << std::endl;
    std::cout << "||       E - Encrypt Phrase               ||" << std::endl;
    std::cout << "||       D - Decrypt Phrase               ||" << std::endl;
    std::cout << "||       C - Clear Phrase                 ||" << std::endl;
    std::cout << "||       Q - Quit program                 ||" << std::endl;
    std::cout << "||                                        ||" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "\nEnter your choice: ";
}