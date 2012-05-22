/**
 * @file   test_longto.c
 * @author Egorov N.V. <egorov@rti-mints.ru>
 * @date   Tue Aug 24 16:00:00 2010
 * 
 * @brief  Тестирование функций преоброзования строк
 * 
 * 
 */



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <config.h>

#ifndef USE_VSPRINTF
#define asstring(x) #x

static inline char* longtoHEX(long obj, char* out, size_t bl);

static inline char* longtohex(long obj, char* out, size_t bl);

char* longtooct(long obj, char* out, size_t bl);

char* longtodec(long obj, char *out, size_t bl);



int main(int argc, char** argv)
{

    char buff[200];

    if (strcmp(longtoHEX(0xFFE, buff, 200), asstring(FFE)))
    {
        puts(buff);
        return -1;
    }
    if (strcmp(longtohex(0xad14e, buff, 200), "ad14e"))
    {
        puts("longtohex failure");
        puts(buff);
        return -1;
    }
    if(strcmp(longtooct(0674, buff, 200), "674"))
    {
        puts("longtooct failure");
        puts(buff);
        return -1;
    }

    if(!longtodec(1256789, buff, 200))
    {
        puts("Failure longtodec");
        return -1;
    }
    if(strcmp(longtodec(1256789, buff, 200), "1256789"))
    {
        puts("longtodec failure");
        puts(buff);
        return -1;
    }
    return 0;
}
#else
int main (int argc, char** argv)
{
    return 0;
}
#endif
