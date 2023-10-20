#pragma once
#include <string>

class console_out
{
public:
	console_out();

	void print_no_phrase();
	void print_phrase_already_stored();
	void print_store_phrase_success();
	void print_encrypt_key_menu(const std::string& active_key);
	void print_encrypt_success(int& num_of_passes);
	void print_decrypt_success(int& num_of_passes);
	void print_char_not_in_key(const char& invalid_char);
	void print_current_key(const std::string& active_key, int option);
	void print_clear_success();
	void print_menu(const std::string& user_phrase);
};
