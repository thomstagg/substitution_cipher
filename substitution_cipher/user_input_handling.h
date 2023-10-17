#pragma once

#include<iostream>
#include <string>

class user_input_handling
{
public:
	static void process_user_inputs();
	static void pause();
	static void clear();

	static int valid_num(const int input_max_number);
	static std::string valid_char(const std::string& input_valid_character);
};