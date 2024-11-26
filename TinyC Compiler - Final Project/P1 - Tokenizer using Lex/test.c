// TEST FILE FOR TESTING TINY-C LEXICAL ANALYZER

/* ======================================================
    TEST FILE : GROUP - 54
    -------------------------
    TUHIN MONDAL (22CS10087)
    DIGANTA MANDAL (22CS30062)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>
// TEST FILE FOR TESTING TINY-C LEXICAL ANALYZER

/* ======================================================
    TEST FILE : GROUP - 54
    -------------------------
    TUHIN MONDAL (22CS10087)
    DIGANTA MANDAL (22CS30062)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

int global_var = 45;

int main()
{
  auto int a = 10;
  static float b = 3.14;
  const char c = 'X';
  volatile int v = 100;
  unsigned int u = 1;
  short s = -1;
  long l = 9999999;

  unsigned long cf = 100;
  typedef struct
  {
    int x;
    int y;
  } Point;

  struct Student
  {
    char name[50];
    int roll_no;
  };

  union Data
  {
    int i;
    float f;
    char str[20];
  } data;

  Point p1 = {1, 2};
  struct Student stud1 = {"Nihut", 10087};
  struct Student stud2 = {"Atnagid", 30062};
  data.i = 10;

  double complex_num = 5.1234E3;
  if (a > b && u || v != 0)
  {
    for (int i = 0; i < 10; i++)
    {
      a += i;
    }
  }
  else if (a == b)
  {
    goto label;
  }
  else
  {
    do
    {
      a--;
    } while (a > 0);
  }

label:
  switch (a)
  {
  case 1:
    break;
  case 2:
    break;
  default:
    return 0;
  }

  double x = (double)a;
  extern int external_var;
  register int fast_var = 50;
  size_t size = sizeof(stud1);
  printf("Size of struct Student: %zu\n", size);

  int *ptr = &a;
  a = (b + c) * s - u / l;
  b++;
  b--;
  cf <<= 1;
  a &= (1 << 5);
  u |= 64;
  a ^= 45;
  cf %= 2;
  a = ~a;

  a = (a > 0) ? 1 : 0;
  int comp = !(a == b) && (s <= l);
  printf("Result: %d\n", a);
  printf("Result: %d\n", b);
  printf("Result: %d\n", c);
  printf("Result: %d\n", v);
  *ptr = 20;

  return 0;
}

int global_var = 45;

int main() 
{
  auto int a = 10;
  static float b = 3.14;
  const char c = 'X';
  volatile int v = 100;
  unsigned int u = 1;
  short s = -1;
  long l = 9999999;

  unsigned long cf = 100;
  typedef struct {
    int x;
    int y;
  } Point;

  struct Student {
    char name[50];
    int roll_no;
  };

  union Data {
    int i;
    float f;
    char str[20];
  } data;

  Point p1 = {1, 2};
  struct Student stud1 = {"Nihut", 10087};
  struct Student stud2 = {"Atnagid", 30062};
  data.i = 10;

  double complex_num = 5.1234E3;
  if (a > b && u || v != 0) {
    for (int i = 0; i < 10; i++) {
      a += i;
    }
  } else if (a == b) {
    goto label;
  } else {
    do {
      a--;
    } while (a > 0);
  }

label:
  switch (a) {
  case 1:
    break;
  case 2:
    break;
  default:
    return 0; 
  }

  double x = (double)a;
  extern int external_var;
  register int fast_var = 50;
  size_t size = sizeof(stud1);
  printf("Size of struct Student: %zu\n", size);

  int *ptr = &a;
  a = (b + c) * s - u / l;
  b++;
  b--;
  cf <<= 1;
  a &= (1 << 5);
  u |= 64;
  a ^= 45;
  cf %= 2;
  a = ~a;

  a = (a > 0) ? 1 : 0;
  int comp = !(a == b) && (s <= l);
  printf("Result: %d\n", a);
  printf("Result: %d\n", b);
  printf("Result: %d\n", c);
  printf("Result: %d\n", v);
  *ptr = 20;

  return 0;
}

