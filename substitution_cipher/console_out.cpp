#include "console_out.h"
#include <iostream>

console_out::console_out()
= default;

void console_out::message(std::string message_choice)
{
    if(message_choice == "welcome_message")
    {
        std::cout << "\nWelcome to the Substitution Cipher" << std::endl;
        message_choice = "";
    }
	if(message_choice == "no_phrase")
	{
        std::cout << "\n--------------------------------------------" << std::endl;
        std::cout << "||                 Whoops!                ||" << std::endl;
        std::cout << "||            No phrase stored            ||" << std::endl;
        std::cout << "||          please enter a phrase         ||" << std::endl;
        std::cout << "||             using option 'S'           ||" << std::endl;
        std::cout << "||              and try again             ||" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        message_choice = "";
	}
    if(message_choice == "phrase_already_stored")
    {
        std::cout << "\n--------------------------------------------" << std::endl;
        std::cout << "||             A word or phrase           ||" << std::endl;
        std::cout << "||            is already stored!          ||" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        message_choice = "";
    }
    if(message_choice == "store_phrase_success")
    {
        std::cout << "\n--------------------------------------------" << std::endl;
        std::cout << "||                 Phrase                 ||" << std::endl;
        std::cout << "||           stored successfully!         ||" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        message_choice = "";
    }
    if(message_choice == "clear_success")
    {
        std::cout << "\n--------------------------------------------" << std::endl;
        std::cout << "||           cleared successfully!        ||" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        message_choice = "";
    }
    if (message_choice == "key_gen_success")
    {
        std::cout << "New key generated successfully!" << std::endl;
        message_choice = "";
    }
    if(message_choice == "y_continue")
    {
        std::cout << "\nPress 'Y' to continue: ";
        message_choice = "";
    }
    if(message_choice == "yes_no")
    {
        std::cout << "\nWhen ready to proceed press 'Y' or to cancel press 'N': ";
        message_choice = "";
    }
    if(message_choice == "enter_encrypt_key")
    {
        std::cout << "Enter your encryption key below" << std::endl;
        std::cout << "\nYour key: ";
        message_choice = "";
    }
    if(message_choice == "key_updated_success")
    {
        std::cout << "Encryption key updated successfully!" << std::endl;
        message_choice = "";
    }
    if(message_choice == "enter_phrase")
    {
        std::cout << "Enter the word or phrase you would like to be encrypted or decrypted" << std::endl;
        std::cout << "\nYour Phrase: ";
        message_choice = "";
    }
    if(message_choice == "encrypt_pass_num")
    {
        std::cout << "\nEnter the number of encryption passes you would like: ";
        message_choice = "";
    }
    if(message_choice == "decrypt_pass_num")
    {
        std::cout << "\nEnter the number of decryption passes you would like: ";
        message_choice = "";
    }
    if(message_choice == "clear_phrase")
    {
        std::cout << "\nAre you sure you would like to clear your stored phrase?" << std::endl;
        message_choice = "";
    }
    else if(message_choice.length() >= 1)
    {
        std::cout << "*******DEBUG INCORRECT STRING INPUT INTO FUNCTION********" << std::endl;
        message_choice = "";
    }
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

//Prints Menu to console
void console_out::print_menu(const std::string& user_phrase)
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