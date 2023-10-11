#include <iostream>
#include <string>

//Stores User Phrase
std::string user_phrase{};

//Cipher Strings
std::string alphabet{ " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890" };
std::string key{ "!XZ$%W@B=J?Q&YV_K6U1MPCIASRxzn#webg@hq3y2tkfu4mpciasrN-G+)(*D^/" };

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

//checks for valid response
std::string valid_menu_choice()
{
    std::string const valid_options("sSeEdDcCqQ");
    std::string input{};

    std::cin >> input;
    while (input.size() != 1 || valid_options.find(input) == std::string::npos)
    {
        std::cin.clear();
        std::cout << "\nInput invalid, please enter a valid menu selection : ";
        std::cin >> input;
    }
    return input;
}

//checks for valid response
std::string valid_continue()
{
    std::string const valid_options("yYnN");
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

//Prints Menu to console
void print_menu()
{
    if (user_phrase.length() == 0)
    {
        std::cout << "\n--------------------------------------------" << std::endl;
	    std::cout << "You currently have no phrase stored" << std::endl;
    }
    else
    {
        std::cout << "\n--------------------------------------------" << std::endl;
        std::cout << "Stored Phrase : " << user_phrase << std::endl;
    }
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "||                                        ||" << std::endl;
    std::cout << "||           S - Enter a phrase           ||" << std::endl;
    std::cout << "||           E - Encrypt Phrase           ||" << std::endl;
    std::cout << "||           D - Decrypt Phrase           ||" << std::endl;
    std::cout << "||           C - Clear list               ||" << std::endl;
    std::cout << "||           Q - Quit program             ||" << std::endl;
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
	        std::cout << "Enter the words or phrase you would like to be encrypted or decrypted: ";
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

//Encrypts user phrase
void encrypt_phrase()
{
    bool success{ false };
    for (size_t i{ 0 }; i < user_phrase.length(); ++i)
    {
        const size_t position = alphabet.find(user_phrase.at(i));
        if(i != std::string::npos && position <=62)
        {
            user_phrase.at(i) = key.at(position);
            success = true;
        }
    }
    if(success)
    {
        std::cout << "\n--------------------------------------------" << std::endl;
        std::cout << "||             Phrase encrypted           ||" << std::endl;
        std::cout << "||               successfully!            ||" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
    }
    else
    {
        std::cout << "\n--------------------------------------------" << std::endl;
        std::cout << "||                 WARNING!               ||" << std::endl;
        std::cout << "||          Encryption of symbols         ||" << std::endl;
        std::cout << "||               not possible!            ||" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
    }
}

//Decrypts user phrase
void decrypt_phrase()
{
    for (size_t i{ 0 }; i < user_phrase.length(); ++i)
    {
        const size_t position = key.find(user_phrase.at(i));
        if (i != std::string::npos)
        {
            user_phrase.at(i) = alphabet.at(position);
        }
    }
    std::cout << "\n--------------------------------------------" << std::endl;
    std::cout << "||             Phrase decrypted           ||" << std::endl;
    std::cout << "||               successfully!            ||" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
}

//Clears the user_phrase string
void clear_phrase()
{
    std::string user_selection{};
    std::cout << "\nAre you sure you would like to clear your stored phrase?" << std::endl;
    std::cout << "\nIf yes press 'Y' or press 'N' to return to the menu : ";
    user_selection = valid_continue();
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
        user_selection = valid_menu_choice();
        clear();
        while (running)
        {
            if (user_selection == "s" || user_selection == "S")
            {
                store_user_phrase();
                break;
            }
            if (user_selection == "e" || user_selection == "E")
            {
                encrypt_phrase();
                break;
            }
            if (user_selection == "d" || user_selection == "D")
            {
                decrypt_phrase();
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
    std::cout << "\nWelcome to the Substitution Cipher" << std::endl;
    process_user_inputs();
    std::cout << "\nGoodbye!" << std::endl;
	std::cout << std::endl;
	return 0;
}
