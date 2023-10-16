#pragma once

#include <iostream>

class print_messages
{
public:
	static void print_no_phrase();
	static void print_encrypt_success();
	static void print_decrypt_success();
	static void print_char_not_in_key();
	static void print_current_key();
	static void print_menu();
};