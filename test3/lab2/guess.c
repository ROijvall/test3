#include <stdlib.h>
#include "utils.h"
#include <stdio.h>

int main(void)
{
  char buf[255];
  int T = random() % 1024;
  char *N = ask_question_string("Vad heter du?\n", buf, 255);
  int G = 1;
  printf("Du %s, jag tänker på ett tal kan du gissa vilket?", N);
  for(; G <= 15; ++G)
  {
    int c = ask_question_int("");
    if (c == T)
    {
      puts("Bingo!");
      printf("Det tog %s %d gissningar att komma fram till %d\n", N, G, T);
      return 0;
    }
    else
    {
      if (c > T)
      {
        puts("För stort!");
      }
      else
      {
        puts("För litet");
      }
    }
  }
  printf("Nu har du slut på gissningar! Jag tänkte på %d\n", T);
  return 0;
}
 


