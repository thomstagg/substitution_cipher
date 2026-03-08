#include "handle_strings.h"
#include "console_out.h"
#include "handle_console.h"
#include <string>
#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <numeric>

handle_strings::handle_strings()
= default;

std::vector<size_t> shuffle_indices_; // permutation for reversible shuffle
size_t shuffle_seed_{};               // user-chosen seed for shuffling

std::vector<size_t> handle_strings::generate_permutation(size_t length, size_t seed)
{
    std::vector<size_t> indices(length);
    std::iota(indices.begin(), indices.end(), 0);

    std::mt19937 gen(seed);
    std::shuffle(indices.begin(), indices.end(), gen);

    return indices;
}

// Apply a permutation to a string
std::string handle_strings::apply_permutation(const std::string& input, const std::vector<size_t>& perm)
{
    std::string output(input.size(), '\0');
    for (size_t i = 0; i < perm.size(); ++i)
    {
        output[i] = input[perm[i]];
    }
    return output;
}

// Reverse a permutation
std::string handle_strings::reverse_permutation(const std::string& input, const std::vector<size_t>& perm)
{
    std::string output(input.size(), '\0');
    for (size_t i = 0; i < perm.size(); ++i)
    {
        output[perm[i]] = input[i];
    }
    return output;
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

// Shuffle user_phrase_ deterministically using a seed
void handle_strings::shuffle_phrase()
{
    std::vector<size_t> indices(user_phrase_.size());
    std::iota(indices.begin(), indices.end(), 0); // 0,1,2,...

    std::mt19937 gen(shuffle_seed_);
    std::shuffle(indices.begin(), indices.end(), gen);

    std::string shuffled = user_phrase_;
    for (size_t i = 0; i < indices.size(); ++i)
        shuffled[i] = user_phrase_[indices[i]];

    user_phrase_ = shuffled;
    shuffle_indices_ = indices;
}

void handle_strings::unshuffle_phrase()
{
    std::string original = user_phrase_;
    for (size_t i = 0; i < shuffle_indices_.size(); ++i)
        original[shuffle_indices_[i]] = user_phrase_[i];

    user_phrase_ = original;
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
    handle_console handle_console;
    console_out console_out;

    console_out.print_current_key(active_key_, 1);
    console_out.message("yes_no");
    std::string user_selection = handle_console.valid_char("yYnN");
    if (user_selection == "n" || user_selection == "N") return;

    if (user_selection == "y" || user_selection == "Y")
    {
        // Number of encryption passes
        console_out.message("encrypt_pass_num");
        int num_of_passes = handle_console.valid_num(100);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // User chooses seed
        console_out.message("enter_random_seed");
        shuffle_seed_ = handle_console.valid_num(1000000);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Generate deterministic permutation
        shuffle_indices_ = generate_permutation(user_phrase_.size(), shuffle_seed_);

        // Apply permutation
        user_phrase_ = apply_permutation(user_phrase_, shuffle_indices_);

        // --- Encryption loop ---
        bool success = true;
        for (int x = 0; x < num_of_passes; ++x)
        {
            for (size_t i = 0; i < user_phrase_.length(); ++i)
            {
                if (active_chars_.find(user_phrase_[i]) == std::string::npos)
                {
                    invalid_char_ = user_phrase_[i];
                    success = false;
                    break;
                }
            }

            if (!success)
            {
                console_out.print_char_not_in_key(invalid_char_);
                break;
            }

            active_chars_ = encrypt_decrypt(active_chars_, char_list_, active_key_, active_key_);
            user_phrase_ = encrypt_decrypt(user_phrase_, active_chars_, user_phrase_, active_key_);
        }

        if (success)
            console_out.print_encrypt_success(num_of_passes);
    }
}

//Decrypts user phrase
void handle_strings::decrypt()
{
    handle_console handle_console;
    console_out console_out;

    console_out.print_current_key(active_key_, 2);

    // Number of decryption passes
    console_out.message("decrypt_pass_num");
    int num_of_passes = handle_console.valid_num(100);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // User enters the same seed
    console_out.message("enter_random_seed");
    shuffle_seed_ = handle_console.valid_num(1000000);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Recreate the same permutation
    shuffle_indices_ = generate_permutation(user_phrase_.size(), shuffle_seed_);

    // --- Decryption loop ---
    bool success = true;
    for (int x = 0; x < num_of_passes; ++x)
    {
        for (size_t i = 0; i < user_phrase_.length(); ++i)
        {
            if (active_key_.find(user_phrase_[i]) == std::string::npos)
            {
                invalid_char_ = user_phrase_[i];
                success = false;
                break;
            }
        }

        if (!success)
        {
            console_out.print_char_not_in_key(invalid_char_);
            break;
        }

        user_phrase_ = encrypt_decrypt(user_phrase_, active_key_, user_phrase_, active_chars_);
    }

    if (success)
        user_phrase_ = reverse_permutation(user_phrase_, shuffle_indices_);

    console_out.print_decrypt_success(num_of_passes);
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