#pragma once

#include <string>
#include <vector>

class string_handling
{
public:
	static void random_key();
	static void store_user_phrase();
	static void encryption_key();
	static void encrypt_phrase();
	static void decrypt_phrase();
	static void clear_phrase();

	static std::vector<char> stored_string;
	static std::string default_chars;
	static std::string char_list_string;
	static std::string active_chars_string;
	static std::string active_key_string;
	static std::string user_phrase_string;
	static char invalid_char;
};