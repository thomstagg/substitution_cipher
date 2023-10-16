#pragma once

#include <iostream>
#include <string>

extern std::string char_list;
extern std::string active_chars;
extern std::string active_key;
extern std::string user_phrase;
extern char invalid_char;

class application
{
public:
	static void process_user_inputs();
};