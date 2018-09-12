#include <stdio.h>
#include <string.h>
#include "utils.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
struct item_t
{
  char name[255];
  char description[255];
  int price;
  char shelf[8];
};
typedef struct item item_t;

int print_item (struct item_t *item)
{
  printf("Name: %s\n", item->name);
  printf("Description: %s\n", item->description);
  int kr = item->price / 100;
  int ore = item->price % 100;
  printf("Price: %d.%d\n", kr, ore);
  printf("Shelf: %s\n", item->shelf);
    return 0;
}

struct item_t make_item(char *name, char *descr, int price, char *shelf)
{
  struct item_t item;
  strcpy(item.name, name);
  strcpy(item.description, descr);
  item.price = price;
  strcpy(item.shelf, shelf);
  return item;
}

bool is_shelf(char *str)
{
  int str_length = strlen(str);
  for (int i = 0; i < str_length; ++i)
    {
      char element = str[i];
      if (!((!(isdigit(element)) && i == 0) || (isdigit(element) && i != 0)))
        {
          return false;
        }
    }
  return str_length > 0;
}

char *ask_question_shelf(char *question)
{
  answer_t answer = ask_question(question, is_shelf, (convert_func) strdup);
  return answer.s;
}

struct item_t input_item(void)
{
  char *name = ask_question_string("Ange namn");
  char *descr = ask_question_string("Ange beskrivning");
  int price = ask_question_int("Ange pris");
  char *shelf = ask_question_shelf("Ange hyllans nr");
  struct item_t item = make_item(name, descr, price, shelf);
  return item;
}
/*
int main (void)
{
  struct item_t test;
  strcpy( test.name, "Potatis");
  strcpy( test.description, "Gott");
  test.price = 101051;
  strcpy( test.shelf, "25A");
  print_item(&test);
  struct item_t testitem = input_item();
  print_item(&testitem);
    return 0;
  
  
}
*/

char *magick(char *array1, char *array2, char *array3, int array_length)
{
  char buf[255];
  int i = 0;
  int rnd = random() % array_length;
  buf[i] = array1[rnd];
  buf[i+1] = '-';
  int rnd2 = random() % array_length;
  buf[i+2] = array2[rnd2];
  buf[i+3] = ' ';
  int rnd3 = random() % array_length;
  buf[i+4] = array3[rnd3];
  buf[i+5] = '\0';
  return strdup(buf);
}

//int main(int argc, char *argv[])
int main(void)
{
  char *array1[] = { "Laser",        "Polka",    "Extra" }; //LÄGG TILL
  char *array2[] = { "förnicklad",   "smakande", "ordinär" }; //LÄGG TILL
  char *array3[] = { "skruvdragare", "kola",     "uppgift" }; //LÄGG TILL
  char *str = magick(*array1, *array2, *array3, 3);
  printf("Strängen blev %s", str);
  return 0;
}

  /*
  if (argc < 2)
    {
      printf("Usage: %s number\n", argv[0]);
    }
  else
    {
      struct item_t db[16]; //Array med plats för 16 varor
      int db_siz = 0; //Antalet varor i arrayen just nu

      int items = atoi(argv[1]); //Antalet varor som skall skapas

      if (items > 0 && items <= 16)
        {
          for (int i = 0; i < items; ++i)
            {
              //Läs in en vara, lägg till den i arrayen, öka storleksräknaren
              struct item_t item = input_item();
              db[db_siz] = item;
              ++db_siz;
            }
        }
      else
        {
          puts("Sorry, must have [1-16] items in database.");
          return 1; //Avslutar programmet!
        }
      for (int i = db_siz; i < 16; ++i)
        {
          char *name = magick(array1, array2, array3, 3); //TODO lägg till storlek
          char *desc = magick(array1, array2, array3, 3); //TODO lägg till storlek
          int price = random() % 200000;
          char shelf[] = { random() % ('Z'-'A') + 'A',
                           random() % 10 + '0',
                           random() % 10 + '0',
                           '\0' };
          struct item_t item = make_item(name, desc, price, shelf);

          db[db_siz] = item;
          ++db_siz;
        }
      for (int i = 0; i < db_siz; ++i)
        {
          print_item(&db[i]);
        }
      
    }
  return 0;
}
*/
