#include <ocr_engine.h>

#define MIN_VALUE(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)));

int levenshtein_distance(std::string& str_1, std::string& str_2)
{
    unsigned int length_str_1, length_str_2, x, y, last_diag, old_diag;

    length_str_1 = str_1.size();
    length_str_2 = str_2.size();

    unsigned int* column = new unsigned int[length_str_1 + 1];
    for (y = 1; y <= length_str_1; ++y)
        column[y] = y;

    for (x = 1; x <= length_str_2; ++x)
    {
        column[0] = x;

        for (y = 1, last_diag = x - 1; y <= length_str_1; ++y)
        {
            old_diag = column[y];
            column[y] = MIN_VALUE(column[y] + 1, column[y - 1] + 1, last_diag + (tolower(str_1[y - 1]) == tolower(str_2[x - 1]) ? 0 : 1));
            last_diag = old_diag;
        }
    }

    return(column[length_str_1]);
}

bool is_same_str(std::string origin_str, std::string& tkn, int max_distance)
{
    int distance = levenshtein_distance(origin_str, tkn);

    if (origin_str.size() <= 4)
        max_distance = 1;

    if (distance <= max_distance)
        return true;
    else
        return false;
}