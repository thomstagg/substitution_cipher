#pragma once
#include <string>

class handle_strings
{
public:
	handle_strings(std::string* user_phrase_string, std::string* active_key_string, char* invalid_char);

	void store_user_phrase();
	void key_init();
	void encryption_key();
	void encrypt();
	void decrypt();
	void clear_phrase();

private:
	
	std::string char_list_ = R"raw(!@#$%^&*()_+-={}[]:;',.<>/?|`~abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890\")raw";
	std::string active_chars_;

	std::string* user_phrase_;
	std::string* active_key_;
	char* invalid_char_{};
};
