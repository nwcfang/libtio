/**
 * @file   uof.c
 * @author Egorov N.V. <egorov@rti-mints.ru>
 * @date   Wed Sep 29 18:04:02 2010
 * 
 * @brief Реализация функции унифицированного вывода 
 *
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

#include <tioerror.h>
#include <tiowerror.h>
#include <tiooutput.h>

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#define PREFIXLEN 5
#define MINLEN    100;


#ifdef USE_VSPRINTF

/** 
 * \breif Функция формирования буфера для вывода (вспомогательная)
 *
 * Унифицироавниая функция производящая переформатирование строки в
 * соотвествии с заданой строкой форматированияи передоваемой в строке
 * форматирования и списком аргументов переланным через список аргументов.
 * 
 * @param buff буфер вывода сообщения.
 * @param buff_len Длинна буфера вывода
 * @param format Строка форматирования
 * @param args  Список аргументов
 * 
 * @return 0 в случае успеха и код ошибки в противном
 * случае. Используемые коды ошибок: ENOMEM, TEINVAL, TENES
 *
 * \see tioGetError()
 */

static int uof(char* buff, size_t buff_len, const char* format, va_list args)
{

    size_t tformatl = 0;
    char  *tformat  = NULL;
    const char  *p = format;
    char  *v = NULL;
    size_t res;
    
    for (; *p!='\0'; ++p)
        if (*p == '%')
            ++tformatl;
    tformatl += strlen(format) +10;
    if (!(tformat=malloc(tformatl)))
    {
        tioSetErrorNum(ENOMEM);
        return ENOMEM;
    }
    for(v=tformat, p=format; (*p)!='\0'; ++p, ++v)
    {
        *v = *p;

        if(*p == '%')
        {
            ++p, ++v;
            switch (*p) 
            {
            case 'c':
            case 's':
            case 'e':
            case 'f':
            case '%':
                *v=*p;
                break;
            case 'i':
            case 'd':
            case 'X':
            case 'x':
            case 'o':
                *(v++)='l';
                *v=*p;
                break;
            case '\0':
            default:
                free(tformat);
                tioSetErrorNum(TEINVAL);
                return TEINVAL;
            }
        }
    }
    *v = '\0';
    res=vsnprintf(buff, buff_len, tformat, args);
    free(tformat);
    if (res>=buff_len)
    {
        tioSetErrorNum(TENES);
        return TENES;
    }
    return 0;
}


/** 
 * @breif Функция осуществляет формирования вывода в зависимости от
 * типа текстового сообщения 
 * 
 * @param type Тип сообщения 
 *
 * @param format Форматированная в соответствии с документацией
 * библиотеки строка вывода
 *
 * @param args список аргументов строки вывода
 * 
 * @return 0 в случае успешного завершения и код ошибки в противном случае
 */
int uniformstroutput(enum msgtype type, const char* format, va_list args)
{
    size_t bl = 0;
    int flag = TENES;
    char *buff = NULL;
    FILE *out;
    char *prefix;
    char  *err = "(EE):";
    char  *inf = "(II):";
    char  *warn = "(WW):";
    char  *dbg = "(DD):";

    switch (type) 
    {
    case ERROR:
        prefix = err;
        out = stderr;
        break;
    case DEBUG:
        prefix = dbg;
        out = stderr;
        break;
    case WARNING:
        prefix = warn;
        out = stdout;
        break;
    case MESSAGE:
        prefix = inf;
        out = stdout;
        break;
    default:
        tioSetErrorNum(TEINVAL);
        return TEINVAL;
    }

    bl = strlen(format) * 2 + MINLEN;
    while (flag == TENES)
    {
        bl *= 2;
        if(buff) free(buff);
        if (!(buff = malloc(bl)))
        {
            tioSetErrorNum(TEFAIL);
            return TEFAIL;
        }
        strcpy(buff, prefix);
        flag = uof(buff+PREFIXLEN , bl - PREFIXLEN - 1, format, args);
    }
    if ( flag )
    {
        free(buff);
        tioSetErrorNum (flag);
        return flag;
    }
    fputs(buff, out);
    free(buff);
    return 0;
} 

#else // USE_VSPRINTF
#error "This part not emplemanted yet compile with vsprintf enable."
#endif // USE_VSPRINTF
