/**
 * @file   utf.c
 * @author Egorov N.V. <egorov@rti-mints.ru>
 * @date   Wed Jul  7 14:54:08 2010
 * 
 * @brief Набор функция для операций со стоками - включая разбиения
 * сторк, получение смещений и так-далее
 * 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


#ifdef HAVE_CONFIG_H
  #include <config.h>
#endif //HAVE_CONFIG_H

#define HASSUB 0x80
#define UMASK  0xC0



static inline int utf_len(const char* symb)
{

    if (!(*symb & HASSUB))
    {
        return 1;
    }
    else if ( (((symb[0]<< 1)&UMASK)==HASSUB) && (symb[1]&UMASK)==HASSUB )
    {
        return 2;
    }
    else if ( (((symb[0]<< 2)&UMASK)==HASSUB) && ((symb[1] & UMASK)==HASSUB) && ((symb[2] & UMASK)==HASSUB))
        return 3;
    else if ( (((symb[0]<< 3)&UMASK)==HASSUB)  && ((symb[1] & UMASK)==HASSUB) &&            \
             ((symb[2] & UMASK)==HASSUB) &&((symb[3] & UMASK)==HASSUB))
        return 4;
    else if ((((symb[0]<< 4)&UMASK)==HASSUB) &&  ((symb[1] & UMASK)==HASSUB) && ((symb[2] & UMASK)==HASSUB) && \
             ((symb[3] & UMASK)==HASSUB) && ((symb[4] & UMASK)==HASSUB))
        return 5;
//    else if (!((*symb)<<6)) Временно удалено так как такого не быовает
//        return 6;
    return 1;
}

size_t utf_strlen(const char* obj)
{
    size_t cnt = 0, i=0;

    while(obj[i]!='\0')
        i+=utf_len(obj+i), ++cnt;

    return cnt;
}

char* utf_stroffset(char* obj, const size_t symbnum)
{
    size_t i=0, cnt = 0;
    
    while(obj[i]!='\0' && cnt < symbnum)
    {
        i+=utf_len(obj+i), ++cnt;
    }

    return (obj + i);
}
