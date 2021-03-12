#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <gmodule.h>

typedef struct
{
  gunichar *unistr;
  size_t start;
  size_t hyphen;
  size_t end;
} shuffle_info;

void shuffle_array(shuffle_info *shuffle)
{
  for (size_t i = shuffle->start; i < shuffle->end; ++i)
  {
    size_t new_pos = i + (rand() / (RAND_MAX / (shuffle->end - i) + 1));
    gunichar temp = shuffle->unistr[new_pos];
    shuffle->unistr[new_pos] = shuffle->unistr[i];
    shuffle->unistr[i] = temp;
  }
}

size_t find_hyphen(shuffle_info *shuffle)
{
  gunichar hyphen = g_utf8_to_ucs4("-", -1, NULL, NULL, NULL)[0];
  for (size_t i = shuffle->start; i < shuffle->end; ++i)
  {
    if (shuffle->unistr[i] == hyphen)
    {
      return i;
    }
  }
  return 0;
}

void scan_stdin()
{
  char *word_ptr = NULL;

  while (fscanf(stdin, "%ms", &word_ptr) != EOF)
  {
    /* Use fix width ucs4 encoding */
    glong str_items = 0;
    gunichar *ucs8_str = g_utf8_to_ucs4(word_ptr, -1, NULL, &str_items, NULL);
    g_assert(ucs8_str != NULL);

    if (g_unichar_ispunct(ucs8_str[str_items - 1]))
    {
      --str_items; /* Do not shuffle punctuation at the end of string */
    }

    shuffle_info word_shuffle = {
        .unistr = ucs8_str,
        .start = 1,
        .hyphen = 0,
        .end = str_items};

    word_shuffle.hyphen = find_hyphen(&word_shuffle);

    if (word_shuffle.hyphen == 0)
    {
      shuffle_array(&word_shuffle);
    }
    else
    {
      shuffle_info first_part_shuffle = word_shuffle;
      first_part_shuffle.end = word_shuffle.hyphen;
      shuffle_array(&first_part_shuffle);

      shuffle_info second_part_shuffle = word_shuffle;
      second_part_shuffle.start = word_shuffle.hyphen + 2;
      shuffle_array(&second_part_shuffle);
    }

    printf("%s ", g_ucs4_to_utf8(ucs8_str, -1, NULL, NULL, NULL));
    free(word_ptr);
    g_free(ucs8_str);
    word_ptr = NULL;
  };
  printf("\n");
}

int main(int argc, char **argv)
{
  /* Set time random seed */
  srand(time(NULL));
  scan_stdin();
  return 0;
}
