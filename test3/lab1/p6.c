#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool is_number (char *str)
{
  int c = strlen(str);
  for (int i = 0; i < c; ++i)
    {
      char k = str[i];
      if (!(isdigit(k) || (k == '-' && i == 0 && c > 1)))
      {
        return false;
      }
    }
  return c > 0;
}

int main(int argc, char **argv)
{
  if (argc > 1 && is_number(argv[1]))
    {
      printf("%s is a number\n", argv[1]);
    }
  else
    {
      if (argc > 1)
        {
          printf("%s is not a number\n", argv[1]);
        }
      else
        {
          printf("Please provide a command line argument!\n");
        }
    }
}
