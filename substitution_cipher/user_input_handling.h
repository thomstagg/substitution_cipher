#pragma once

#include<iostream>
#include <string>

class user_input_handling
{
public:
	void process_user_inputs();
	void pause();

	int valid_num(const int input_max_number);
	std::string valid_char(const std::string& input_valid_character);
};

extern user_input_handling* user_input_handling_main;