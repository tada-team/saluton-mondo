#include <gmodule.h>
#include "revert_lib.h"
#include <stdlib.h>

void run_test(char *input_str, char *expect_str)
{
    char *shuffled_str = shuffle_word(input_str);
    g_assert_cmpstr(shuffled_str, ==, expect_str);
    g_free(shuffled_str);
}

int main()
{
    srand(0);

    run_test("а", "а");
    run_test("бы", "бы");
    run_test("это", "это");
    run_test("это!", "это!");
    run_test("что-то", "что-то");
    run_test("123456789", "178463259");
    run_test("каокй-то", "кокай-то");
    run_test("удивительное рядом!", "уеоиьндтилве родям!");

    return 0;
}