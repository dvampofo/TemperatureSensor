/* gcc -ansi -Wall -pedantic temp.c -o temp
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "ifttt.h"
#define PATH_MAX 50

extern int ifttt(char* , char* , char* , char* );
int main(int argc,char *argv[])
{
    char *ret, *s1;
    char holdval[10];
    int len,newTemp,oldTemp,absTemp;
    FILE *fp;
    char path[PATH_MAX];
/*    if(argc > 3)
    {
        printf("Please enter only one argument");
        return 1;
    }
    printf("%d\n", argc);
    printf("%s", argv[1]);
*/
oldTemp = -10;
while(1)
{  
    fp = fopen("/sys/bus/w1/devices/28-021312eefeaa/w1_slave", "r");
    
    if (fp == NULL)
    {   
        printf("temperature sensor cannot be found");
        return 2;
    }   

    while (fgets(path, PATH_MAX, fp) != NULL)
    {   
        printf("%s", path);
        ret = strpbrk(path, "Yes");
        if(ret)
                {
                        printf("Sensor working, will print the temp\n");
                }
    
    }   
    
    len = strlen(path)- 6;
    s1 = path+len;
/* printf("%d\n",len);
printf("%s\n",s1); */
strcpy(holdval,s1);
newTemp = atoi(holdval);

printf("this is the old value %d\n", oldTemp);
printf("this is the new value %d\n\n", newTemp);

fclose(fp);
if((newTemp < 0 && oldTemp > 0))
{
	printf("we see a change 20 \n");
	oldTemp = newTemp;
}
if((newTemp > 0 && oldTemp < 0))
{
	 printf("we see a change 10\n");
	oldTemp = newTemp;
	ifttt("https://maker.ifttt.com/trigger/AlarmTriggerd3/with/key/uQayuY3amwBonQr7RGtpk", "Temp", "is", "changing");
}
if(oldTemp > 0 && newTemp > 0)
{
	
	absTemp = abs(oldTemp - newTemp);
	printf("both of them are positive\n");
	if(absTemp >= 1000)
	{
		printf("Change in temp, both were positive\n");
	}
}
else
{
	absTemp = abs(abs(oldTemp)-abs(newTemp));
	printf("both are negative\n");
	if(absTemp >= 1000)
        {
                printf("Change in temp, both were negative\n");
        }
}


}
/*
    printf("%c\n",path[len]);
    printf("%c\n",path[len+1]);
    printf("%c\n",path[len+2]);
    printf("%c\n",path[len+3]);
    printf("%c\n",path[len+4]);
*/
/*
    currentChar = path[len];
   val = atof(currentChar);
   val = val *10;
   currentChar = path[len
*/

return 0;
}




