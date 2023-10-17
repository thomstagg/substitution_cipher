#pragma once

#include <string>

extern std::string char_list;
extern std::string active_chars;
extern std::string active_key;
extern std::string user_phrase;
extern char invalid_char;

class string_handling
{
public:
	static void init_active_chars();
	static void random_key();
	static void store_user_phrase();
	static void encryption_key();
	static void encrypt_phrase();
	static void decrypt_phrase();
	static void clear_phrase();
};
