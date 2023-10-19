#pragma once

class print_messages
{
public:
	void clear();
	void print_no_phrase();
	void print_encrypt_success();
	void print_decrypt_success();
	void print_char_not_in_key();
	void print_current_key();
	void print_menu();
};

extern print_messages* print_messages_main;