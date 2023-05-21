#include <cmd_engine.h>

std::tuple<uint64_t, bool, std::string> time_format(const std::string& input)
{
    uint64_t sec = 0;
    std::string description;

    bool syntax_ok = true;
    bool is_short = false;
    bool is_worked = true;

    for (int i = 0; i < input.size(); i++)
    {
        int c = tolower(input[i]);

        if ('0' <= c && c <= '9')
        {
            uint64_t value = 0;

            while (i < input.size() && '0' <= input[i] && input[i] <= '9')
            {
                value = value * 10 + (input[i] - '0');
                i++;
            }

            if (i < input.size())
            {
                switch (input[i])
                {
                case 'd': sec += value * 86400; break;
                case 'h': sec += value * 3600; break;
                case 'm': sec += value * 60; break;
                case 's': sec += value; break;
                default: syntax_ok = false; break;
                }
            }
            else
                sec += value * 60;
        }
        else if (i + 1 < input.size())
        {
            if (c == 'd' && input[i + 1] == ' ') i++;
            else if (c == 'h' && input[i + 1] == ' ') i++;
            else if (c == 'm' && input[i + 1] == ' ') i++;
            else if (c == 's' && input[i + 1] == ' ') i++;
            else syntax_ok = false;
        }
        else
            syntax_ok = false;

        if (sec < 10)
            is_short = true;
    }

    if (!syntax_ok)
    {
        description = "Wrong time format!";
        is_worked = false;
    }
    else
    {
        if (is_short)
        {
            description = "Time too short! Timeout should be at least `10 seconds`";
            is_worked = false;
        }
    }

    return { sec, is_worked, description };
}