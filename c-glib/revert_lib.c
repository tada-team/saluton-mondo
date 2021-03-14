#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <gmodule.h>
#include "revert_lib.h"

void shuffle_array(shuffle_info *shuffle)
{
    if (shuffle->start >= shuffle->end)
    {
        return;
    }

    for (size_t i = shuffle->start; i < shuffle->end; ++i)
    {
        size_t new_pos = i + (rand() / (RAND_MAX / (shuffle->end - i) + 1));
        gunichar temp = shuffle->unistr[new_pos];
        shuffle->unistr[new_pos] = shuffle->unistr[i];
        shuffle->unistr[i] = temp;
    }
}

size_t find_separator(shuffle_info *shuffle)
{
    gunichar *hyphen = g_utf8_to_ucs4("-", -1, NULL, NULL, NULL);
    for (size_t i = shuffle->start; i < shuffle->end; ++i)
    {
        if (shuffle->unistr[i] == hyphen[0] || g_unichar_isspace(shuffle->unistr[i]))
        {
            return i;
        }
    }
    g_free(hyphen);
    return 0;
}

char *shuffle_word(char *word)
{
    /* Use fix width ucs4 encoding */
    glong str_items = 0;
    gunichar *ucs8_str = g_utf8_to_ucs4(word, -1, NULL, &str_items, NULL);
    g_assert(ucs8_str != NULL);

    if (g_unichar_ispunct(ucs8_str[str_items - 1]))
    {
        --str_items; /* Do not shuffle punctuation at the end of string */
    }
    --str_items; /* Do not sort last character */

    shuffle_info word_shuffle = {
        .unistr = ucs8_str,
        .start = 1,
        .separator = 0,
        .end = str_items};

    if (str_items > 1)
    {
        word_shuffle.separator = find_separator(&word_shuffle);

        if (word_shuffle.separator == 0)
        {
            shuffle_array(&word_shuffle);
        }
        else
        {
            shuffle_info first_part_shuffle = word_shuffle;
            first_part_shuffle.end = word_shuffle.separator - 1;
            shuffle_array(&first_part_shuffle);

            shuffle_info second_part_shuffle = word_shuffle;
            second_part_shuffle.start = word_shuffle.separator + 2;
            shuffle_array(&second_part_shuffle);
        }
    }

    char *shuffled_utf8_str = g_ucs4_to_utf8(ucs8_str, -1, NULL, NULL, NULL);
    g_free(ucs8_str);
    return shuffled_utf8_str;
}

void scan_stdin()
{
    char word_ptr[1000] = {0};

    while (fscanf(stdin, "%1000s", word_ptr) != EOF)
    {
        char *shuffled_word = shuffle_word(word_ptr);
        printf("%s ", shuffled_word);
        g_free(shuffled_word);
    };
    printf("\n");
}
