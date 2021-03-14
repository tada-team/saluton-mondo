#include <stdlib.h>
#include <time.h>
#include "revert_lib.h"

int main()
{
  /* Set time random seed */
  srand(time(NULL));
  scan_stdin();
  return 0;
}
