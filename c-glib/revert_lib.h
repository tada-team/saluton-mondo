#include <gmodule.h>

typedef struct
{
    gunichar *unistr;
    size_t start;
    size_t hyphen;
    size_t end;
} shuffle_info;

void shuffle_array(shuffle_info *shuffle);

char *shuffle_word(char *word);

void scan_stdin();
