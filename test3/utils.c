#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>


typedef union
{
  int i;
  float f;
  char *s;
} answer_t;

typedef bool(*check_func)(char *);
typedef answer_t(*convert_func)(char *);

bool not_empty(char *str)
{
  return strlen(str) > 0;
}

answer_t ask_question(char *question, check_func check, convert_func convert)
{
  int buf_siz = 255;
  char buf[buf_siz];
  answer_t answer;
  int a = 0;
  do
   {
    printf("%s\n", question);
    a = read_string(buf, buf_siz);
   }
  while (a < 1 && (!(check(buf)))); 
  answer = convert(buf);
  return answer;               
}

char *ask_question_string2(char *question)
{
  answer_t answer = ask_question(question, not_empty, (convert_func) strdup);
  return answer.s;
}

int ask_question_int(char *question)
{
  int result = 0;
  int conversions = 0;
  do
    {
      printf("%s\n", question);
      conversions = scanf("%d", &result);
        int c;
        do
          {
            c = getchar();
          }
        while (c != '\n' && c != EOF);
        putchar('\n');
    }
  while (conversions < 1);
  return result;
}

int ask_question_int2 (char *question)
{
  answer_t answer = ask_question(question, is_number, (convert_func) atoi);
  return answer.i;
}


int read_string(char *buf, int buf_siz)
{ 
  int i = 0;
  int c;
  do
    {
      c = getchar();
      if (c != '\n' && c != EOF)
      {
        buf[i] = c;
        i = i + 1;
      }
      else
      {
        i = i + 1;
        buf[i] = '\0';
        return i - 1;
      }
    }
  while (i <= (buf_siz - 1));
  int k;
      do
      {
        k = getchar();
      }
      while (k !='\n' && k != EOF);
      buf[i] = '\0';
      return i - 1;
}

char *ask_question_string(char *question, char *buf, int buf_siz)
{
  int c;
  do
      {
        printf("%s\n", question);
        c = read_string(buf, buf_siz);
      }  
  while (c == 0); 
  return strdup(buf);
}

bool is_number(char *str)
{
    int str_length = strlen(str);
    for (int i = 0; i < str_length; ++i)
    {
      char element = (str)[i];
      if  (!(isdigit(element) || (element == '-' && i == 0 && str_length > 1)))
      {
        return false;
      }      
    }
    return true;
}
/*
int main(void)
{
  int buf_siz = 255;
  int read = 0; 
  char buf[buf_siz];

  puts("Läs in en sträng:");
  read = read_string(buf, buf_siz);
  printf("'%s' (%d tecken)\n", buf, read);

  puts("Läs in en sträng till:");
  read = read_string(buf, buf_siz);
  printf("'%s' (%d tecken)\n", buf, read);

  return 0;
  
  }
*/

 
int main(void)
{
  //int buf_siz = 255;
  char *question = "hur gammal är du?";
  char *question2 = "vad heter du?";
  char *test2 = "a1";
  char *test3 = "1a";
  // char buf[buf_siz];
  char *str;
  bool test = is_number(test2);
  bool test4 = is_number(test3);
  printf("a1 is %d, 1a is %d", test, test4);
  str = ask_question_string2(question2);
  printf("Hej %s!\n", str);
  int str2 = ask_question_int2(question);
  printf("Du är %d gammal!\n", str2);
  return 0;
}

/*
int main(void)
{
  int tal;

  tal = ask_question_int("Första talet:");
  printf("Du skrev '%d'\n", tal);

  tal = ask_question_int("Andra talet:");
  printf("Du skrev '%d'\n", tal);

  return 0;
}
*/

