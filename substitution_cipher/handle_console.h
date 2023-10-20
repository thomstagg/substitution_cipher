#pragma once
#include <string>

class handle_console
{
public:
	handle_console();

	void clear();
	void pause();

	int valid_num(const int input_max_number);
	std::string valid_char(const std::string& input_valid_character);
};