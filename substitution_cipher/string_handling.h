#pragma once

#include <string>

class string_handling
{
public:
	void random_key();
	void store_user_phrase();
	void encryption_key();
	void encrypt_phrase();
	void decrypt_phrase();
	void clear_phrase();

	std::string default_chars{ "!@#$%^&*()_+-={}[]:;',.<>/?|`~abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890" };
	std::string char_list_string = default_chars;
	std::string active_chars_string = default_chars;
	std::string active_key_string;
	std::string user_phrase_string;
	char invalid_char;
};

extern string_handling* string_handling_main;