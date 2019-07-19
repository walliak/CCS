#include <string.h>
#include "lcd.h"
#include "CompositeChars.h"

 void reverse(char *s)
{
  int c;
  char *t; 
  for (t = s + (strlen(s) - 1); s < t; s++, t-- )
  {
    c = *s;
    *s = *t;
    *t = c;
  }
}

// Êý×Ö×ª³É×Ö·û´®
 void itoa(int n, char *s)
{
  int sign;
  char *t = s;
  if ((sign = n) < 0)
    n = -n; 
  do
  {
    *s++ = n % 10 + '0';
  } 
  while ((n /= 10) >0); 
  if (sign < 0)
    *s++ = '-'; 
  *s = '\0';  
  reverse(t);
}
