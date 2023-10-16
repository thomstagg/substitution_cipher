#include "application.h"
#include <iostream>


int main()
{
	std::cout << "\nWelcome to the Substitution Cipher" << std::endl;
	application::process_user_inputs();
	std::cout << "\nGoodbye!" << std::endl;
	std::cout << std::endl;
	return 0;
}