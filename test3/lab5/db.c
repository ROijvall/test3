#include <stdio.h>
#include <string.h>
#include "utils.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
struct item
{
  char name[255];
  char description[255];
  int price;
  char shelf[8];
};
typedef struct item item_t;

int print_item (item_t *item)
{
  printf("Name: %s\n", item->name);
  printf("Description: %s\n", item->description);
  int kr = item->price / 100;
  int ore = item->price % 100;
  printf("Price: %d.%d\n", kr, ore);
  printf("Shelf: %s\n", item->shelf);
    return 0;
}

item_t make_item(char *name, char *descr, int price, char *shelf)
{
  item_t item;
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
  return str_length > 1;
}

char *ask_question_shelf(char *question)
{
  answer_t answer = ask_question(question, is_shelf, (convert_func) strdup);
  return answer.s;
}

item_t input_item(void)
{
  char *name = ask_question_string("Ange namn");
  char *descr = ask_question_string("Ange beskrivning");
  int price = ask_question_int("Ange pris");
  char *shelf = ask_question_shelf("Ange hyllans nr");
  item_t item = make_item(name, descr, price, shelf);
  return item;
}


char *magick(char *array1[], char *array2[], char *array3[], int array_length)
{
  char buf[255];
  int rnd = random() % array_length;
  strcpy(buf, array1[rnd]);
  strcat(buf, "-");
  int rnd2 = random() % array_length;
  strcat(buf, array2[rnd2]);
  strcat(buf, " ");
  int rnd3 = random() % array_length;
  strcat(buf, array3[rnd3]);
  strcat(buf, "\0");
  return strdup(buf);
}

void list_db(item_t *items, int no_items)
{
    for (int i = 0; i < no_items; ++i)
      {
        printf("%d. %s\n", i+1, items[i].name);
      }
      
}

item_t *edit_db(item_t *db, int db_siz)
{
  while(true)
    {
    int answer = ask_question_int("Vilken vara vill du ändra på?");
    if (answer > 0 && answer <= db_siz)
      {
        item_t *olditem = &db[answer-1];
        print_item(olditem);
        item_t newitem = input_item();
        db[answer-1] = newitem;
        return db;
      }
    else
      {
        puts("Ta ett nummer som är större än 0 och inte större än databasens index!");
      }
    }
}
bool in_menu(char *elem)
{
  char *acc_chars = ("LlTtRrGgHhAa");
  int len = strlen(acc_chars);
  if (strlen(elem) == 1)
    {
    for (int i = 0; i < len; ++i)
      {
        if (elem[0] == acc_chars[i])
          { 
            return true;
          }
      }
    }
  return false;
}

item_t *remove_item_from_db(item_t *db, int *db_siz)
{
  while(true)
    {
      int answer = ask_question_int("Vilken vara vill du ta bort?");
      if (answer > 0 && answer <= *db_siz)
        {
          for (int i = answer; i <= *db_siz; ++i)
            {
              db[i-1] = db[i];
            }
          *db_siz = *(db_siz - 1);
        }
      else
        {
          puts("Valet kan inte vara under 0 eller totala mängden varor");
        }
      return db;
    }
}

item_t *add_item_to_db(item_t *db, int db_siz)
{
  db[db_siz] = input_item();
  return db;
}

void print_menu()
{
  puts("[L]ägga till en vara");
  puts("[T]a bort en vara");
  puts("[R]edigera en vara");
  puts("Ån[g]ra senaste ändringen"); 
  puts("Lista [h]ela varukatalogen");
  puts("[A]vsluta");
}

char ask_question_menu(char *question)
{
  print_menu();
  answer_t answer = ask_question(question, in_menu, (convert_func) strdup);
  char *str = answer.s;
  char elem = str[0];
  elem = toupper(elem);
  return elem;
}          
int event_loop()
{
  item_t db[16];
  int db_siz = 0;
  while (true)
    {
      char elem = ask_question_menu("\nVad vill du göra?");
      if (elem == 'L')
        {
          add_item_to_db(db, db_siz);
          db_siz = (db_siz + 1);
          puts("");
        }
      if (elem == 'T')
        {
          remove_item_from_db(db, &db_siz);
  
        }
      if (elem == 'R')
        {
          edit_db(db, db_siz);
        }
      if (elem == 'G')
        {
          puts("Not yet implemented\n");
        }
      if (elem == 'H')
        {
          list_db(db, db_siz);
          puts("");
        }
      if (elem == 'A')
        {
          return 0;
        }
    }
}
int main(void)
{
  event_loop();
  return 0;
}

/*
int main(int argc, char *argv[])
{
  char *array1[] = { "Laser",        "Polka",    "Extra" }; //LÄGG TILL
  char *array2[] = { "förnicklad",   "smakande", "ordinär" }; //LÄGG TILL
  char *array3[] = { "skruvdragare", "kola",     "uppgift" }; //LÄGG TILL
  
  if (argc < 2)
    {
      printf("Usage: %s number\n", argv[0]);
    }
  else
    {
      item_t db[16]; //Array med plats för 16 varor
      int db_siz = 0; //Antalet varor i arrayen just nu

      int items = atoi(argv[1]); //Antalet varor som skall skapas

      if (items > 0 && items <= 16)
        {
          for (int i = 0; i < items; ++i)
            {
              //Läs in en vara, lägg till den i arrayen, öka storleksräknaren
              item_t item = input_item();
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
          item_t item = make_item(name, desc, price, shelf);

          db[db_siz] = item;
          ++db_siz;
        }
      list_db(db, db_siz);
      edit_db(db, db_siz);
      list_db(db, db_siz);
    } 
  return 0;
}
*/
