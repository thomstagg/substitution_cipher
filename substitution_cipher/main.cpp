#include "string_handling.h"
#include "user_input_handling.h"

string_handling* string_handling_main = new string_handling();
user_input_handling* user_input_handling_main = new user_input_handling();

int main()
{
	string_handling_main->random_key();
	user_input_handling_main->process_user_inputs();
	return 0;
}