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

void CompositeChars(char hour,char minute,char second,char*setTime,char*str)
{		
	unsigned char S_hour[4],S_minute[4],S_second[4],temp[4];
	unsigned char i;
	if(hour>9)	
		itoa(hour,S_hour);	
	else
	{	
		itoa(hour,S_hour);	
		strcpy(temp,S_hour);
		strcpy(S_hour,"0");
		strcat(S_hour,temp);
		
	}

	if(minute>9)	
		itoa(minute,S_minute);	
	else
	{	
		itoa(minute,S_minute);	
		strcpy(temp,S_minute);
		strcpy(S_minute,"0");
		strcat(S_minute,temp);
		
	}
	if(second>9)	
		itoa(second,S_second);	
	else
	{	
		itoa(second,S_second);	
		strcpy(temp,S_second);
		strcpy(S_second,"0");
		strcat(S_second,temp);		
	}

	strcpy(str,setTime);
	strcat(str,S_hour);
	strcat(str,":");
	strcat(str,S_minute);
	strcat(str,":");
	strcat(str,S_second);

	for(i=0;str[i]!='\0';i++)
	{
		if(str[i]=='s')
		{
			i++;
			str[i]='\0';
			break;
		}
	}
	
}