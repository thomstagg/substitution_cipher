#include "app.h"
#include "handle_strings.h"
#include "console_out.h"
#include "handle_console.h"

app::app()
= default;

void app::init()
{
    handle_strings handle_strings;
    console_out console_out;
    handle_strings.key_init();
    std::string user_selection{};
    bool running{ true };
    while (running)
    {
        handle_console handle_console;
        std::string user_phrase = handle_strings.return_user_phrase();
        console_out.print_menu(user_phrase);
        user_selection = handle_console.valid_char("sSkKeEdDcCqQ");
        handle_console.clear();
        while (running)
        {
            if (user_selection == "s" || user_selection == "S")
            {
                handle_strings.store_user_phrase();
                break;
            }
            if (user_selection == "k" || user_selection == "K")
            {
                handle_strings.encryption_key();
                break;
            }
            if (!user_phrase.empty() && user_selection == "e"
                || !user_phrase.empty() && user_selection == "E")
            {
                handle_strings.encrypt();
                break;
            }
            if (user_phrase.empty() && user_selection == "e"
                || user_phrase.empty() && user_selection == "E")
            {
                console_out.print_no_phrase();
                break;
            }
            if (!user_phrase.empty() && user_selection == "d"
                || !user_phrase.empty() && user_selection == "D")
            {
                handle_strings.decrypt();
                break;
            }
            if (user_phrase.empty() && user_selection == "d"
                || user_phrase.empty() && user_selection == "D")
            {
                console_out.print_no_phrase();
                break;
            }
            if (user_selection == "c" || user_selection == "C")
            {
                handle_strings.clear_phrase();
                break;
            }
            if (user_selection == "q" || user_selection == "Q")
            {
                running = false;
            }
        }
    }
}