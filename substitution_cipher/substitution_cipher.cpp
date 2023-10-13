#include <iostream>
#include <string>
#include <limits>
#include <random>
#include <algorithm>

//Stores User Phrase
std::string user_phrase;

//Valid menu options
std::string valid_menu_option{};

//Valid number
int valid_number{};

//Cipher Strings
std::string active_chars{ "!@#$%^&*()_+-={}[]:;',.<>/?|`~abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890" };
std::string active_key{};

//Generates random key using characters in active_chars
std::string random_key()
{
    std::string chars = active_chars;

    std::random_device random;
    std::mt19937 twist(random());

    std::shuffle(chars.begin(), chars.end(), twist);

    return chars;
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
std::string valid_char()
{
    std::string valid_options{};
    valid_options = valid_menu_option;

    std::string input{};
    std::cin >> input;
    while (input.size() != 1 || valid_options.find(input) == std::string::npos)
    {
        std::cin.clear();
        std::cout << "\nInput invalid, please enter a valid character : ";
        std::cin >> input;
    }
    return input;
}

//checks for valid number
int valid_num()
{
    int valid_num_max{};
    valid_num_max = valid_number;
    int input{};
    std::cin >> input;
    while (std::cin.fail() || input >= valid_num_max)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nInput invalid, please enter a valid number below 100: ";
        std::cin >> input;
    }
    return input;
}

//Prints Menu to console
void print_menu()
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
	if(user_phrase.length() == 0)
	{
        bool running{ true };
        while (running)
        {
            std::cout << "Enter the word or phrase you would like to be encrypted or decrypted" << std::endl;
            std::cout << "Your Phrase: ";
            pause();
            std::getline(std::cin, user_phrase);
            clear();
            if(user_phrase.length() > 0)
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
    while(running)
    {
        std::string user_selection{};
	    std::cout << "The current encryption key is" << std::endl;
        std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
        std::cout << active_key << std::endl;
        std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
        std::cout << "\nWould you like to generate a new key or enter an existing one?" << std::endl;
    	std::cout << "\nEnter 'Y' to proceed or 'N' to keep the current key and return to the menu: ";
        valid_menu_option = "yYnN";
        user_selection = valid_char();
        if (user_selection == "y" || user_selection == "Y")
        {
            clear();
            valid_menu_option = "12";
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
            user_selection = valid_char();
            if(user_selection == "1")
            {
                clear();
                active_key = random_key();
                std::cout << "Your new key is" << std::endl;
                std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
                std::cout << active_key << std::endl;
                std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
                std::cout << "Press 'Y' to continue: ";
                valid_menu_option = "yYnN";
                user_selection = valid_char();
                if (user_selection == "y" || user_selection == "Y")
                {
                    clear();
                    break;
                }
            }
            if (user_selection == "2")
            {
                clear();
	            std::cout << " Enter your encryption key below" << std::endl;
                std::cout << "\nYour key: ";
                pause();
                std::getline(std::cin, active_key);
                clear();
                std::cout << "Your key is now" << std::endl;
                std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
                std::cout << active_key << std::endl;
                std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
                std::cout << "\nPress 'Y' to continue: ";
                valid_menu_option = "yYnN";
                user_selection = valid_char();
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
    char invalid_char{};
    valid_number = 100;
    std::cout << "\n--------------------------------------------" << std::endl;
    std::cout << "||               *IMPORTANT*              ||" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "Your current encryption key is" << std::endl;
    std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << active_key << std::endl;
    std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "\nNote this down and keep it safe. Without this key future decryption will be impossible!" << std::endl;
    std::cout << "\nEnter the number of encryption passes you would like: ";
    int num_of_passes = valid_num();
    clear();
    for (int x {0}; x < num_of_passes; ++x)
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
            for (size_t i{ 0 }; i < user_phrase.length(); ++i)
            {
                const size_t position = active_chars.find(user_phrase.at(i));
                if (i != std::string::npos)
                {
                    user_phrase.at(i) = active_key.at(position);
                }
            }
        }
        else
        {
            std::cout << "\n--------------------------------------------" << std::endl;
            std::cout << "||                 Whoops!                ||" << std::endl;
            std::cout << "||        Encryption not possible as      ||" << std::endl;
            std::cout << "||  the character " << invalid_char << " was not found in key! ||" << std::endl;
            std::cout << "||        please clear stored phrase      ||" << std::endl;
            std::cout << "||              and try again             ||" << std::endl;
            std::cout << "--------------------------------------------" << std::endl;
            num_of_passes = 0;
            break;
        }
    }
    if (num_of_passes == 1)
    {
	    std::cout << "*1 encryption pass complete*" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "||             Phrase encrypted           ||" << std::endl;
        std::cout << "||               successfully!            ||" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
    }
    if(num_of_passes > 1)
    {
	    std::cout << "\n*" << num_of_passes << " encryption passes complete*" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "||             Phrase encrypted           ||" << std::endl;
        std::cout << "||               successfully!            ||" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
    }
}

//Decrypts user phrase
void decrypt_phrase()
{
    valid_number = 100;
    bool success{ false };
    char invalid_char{};
    std::cout << "\nEnter the number of decryption passes you would like: ";
    int num_of_passes = valid_num();
    clear();
    for (int x{ 0 }; x < num_of_passes; ++x)
    {
        for (size_t i { 0 }; i < user_phrase.length(); ++i)
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
            for (size_t i{ 0 }; i < user_phrase.length(); ++i)
            {
                const size_t position = active_key.find(user_phrase.at(i));
                if (i != std::string::npos)
                {
                    user_phrase.at(i) = active_chars.at(position);
                }
            }
        }
        if (success == false)
        {
            {
                std::cout << "\n--------------------------------------------" << std::endl;
                std::cout << "||                 Whoops!                ||" << std::endl;
                std::cout << "||        Decryption not possible as      ||" << std::endl;
                std::cout << "||  the character " << invalid_char << " was not found in key! ||" << std::endl;
                std::cout << "||        please clear stored phrase      ||" << std::endl;
                std::cout << "||              and try again             ||" << std::endl;
                std::cout << "--------------------------------------------" << std::endl;
                num_of_passes = 0;
                break;
            }
        }
    }
    if (num_of_passes == 1)
    {
        std::cout << "\n*1 decryption pass complete*" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "||             Phrase decrypted           ||" << std::endl;
        std::cout << "||               successfully!            ||" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
    }
    if (num_of_passes > 1)
    {
        std::cout << "\n*" << num_of_passes << " decryption passes complete*" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "||             Phrase decrypted           ||" << std::endl;
        std::cout << "||               successfully!            ||" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
    }
}

//Clears the user_phrase string
void clear_phrase()
{
    std::string user_selection{};
    std::cout << "\nAre you sure you would like to clear your stored phrase?" << std::endl;
    std::cout << "\nIf yes press 'Y' or press 'N' to return to the menu : ";
    valid_menu_option = "yYnN";
    user_selection = valid_char();
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
void process_user_inputs()
{
    std::string user_selection{};
    bool running{ true };
    while (running)
    {
        print_menu();
        valid_number = 0;
        valid_menu_option = "kKsSeEdDcCqQ";
        user_selection = valid_char();
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
            if (!user_phrase.empty() && user_selection == "e" || user_selection == "E")
            {
                encrypt_phrase();
                break;
            }
            if (user_phrase.empty() && user_selection == "e" || user_selection == "E")
            {
                std::cout << "\n--------------------------------------------" << std::endl;
                std::cout << "||                 Whoops!                ||" << std::endl;
                std::cout << "||            No phrase stored            ||" << std::endl;
                std::cout << "||          please enter a phrase         ||" << std::endl;
                std::cout << "||             using option 'S'           ||" << std::endl;
                std::cout << "||              and try again             ||" << std::endl;
                std::cout << "--------------------------------------------" << std::endl;
                break;
            }
            if (!user_phrase.empty() && user_selection == "d" || user_selection == "D")
            {
                decrypt_phrase();
                break;
            }
            if (user_phrase.empty() && user_selection == "d" || user_selection == "D")
            {
                std::cout << "\n--------------------------------------------" << std::endl;
                std::cout << "||                 Whoops!                ||" << std::endl;
                std::cout << "||            No phrase stored            ||" << std::endl;
                std::cout << "||          please enter a phrase         ||" << std::endl;
                std::cout << "||             using option 'S'           ||" << std::endl;
                std::cout << "||              and try again             ||" << std::endl;
                std::cout << "--------------------------------------------" << std::endl;
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

int main()
{
    active_key = random_key();
    std::cout << "\nWelcome to the Substitution Cipher" << std::endl;
    process_user_inputs();
    std::cout << "\nGoodbye!" << std::endl;
	std::cout << std::endl;
	return 0;
}