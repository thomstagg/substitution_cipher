#pragma once

#include <string>

class console_out
{
public:
	console_out(std::string* user_phrase_string, std::string* active_key_string, char* invalid_char);

	void print_no_phrase();
	void print_clear_success();
	void print_phrase_already_stored();
	void print_store_phrase_success();
	void print_encrypt_key_menu();
	void print_encrypt_success();
	void print_decrypt_success();
	void print_char_not_in_key();
	void print_current_key();
	void print_menu();

private:
	std::string* user_phrase_;
	std::string* active_key_;
	char* invalid_char_;
};
