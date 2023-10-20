#pragma once
#include <string>

class app
{
public:
	app();
	void init();
private:
	std::string user_phrase_;
	std::string active_key_;
	char invalid_char_;
};
