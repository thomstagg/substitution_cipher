#include "print_messages.h"
#include "application.h"

#include <iostream>
#include <string>
#include <random>

//Prints no phrase stored warning
void print_messages::print_no_phrase()
{
    std::cout << "\n--------------------------------------------" << std::endl;
    std::cout << "||                 Whoops!                ||" << std::endl;
    std::cout << "||            No phrase stored            ||" << std::endl;
    std::cout << "||          please enter a phrase         ||" << std::endl;
    std::cout << "||             using option 'S'           ||" << std::endl;
    std::cout << "||              and try again             ||" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
}

//Prints encryption success message
void print_messages::print_encrypt_success()
{
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "||             Phrase encrypted           ||" << std::endl;
    std::cout << "||               successfully!            ||" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
}

//Prints decryption success message
void print_messages::print_decrypt_success()
{
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "||             Phrase decrypted           ||" << std::endl;
    std::cout << "||               successfully!            ||" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
}

//Prints character not found in key message
void print_messages::print_char_not_in_key()
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
void print_messages::print_current_key()
{
    std::cout << "\nThe current encryption key is" << std::endl;
    std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << active_key << std::endl;
    std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
}

//Prints Menu to console
void print_messages::print_menu()
{
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
    active_chars = char_list;
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