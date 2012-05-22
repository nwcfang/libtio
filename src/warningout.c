/**
 * @file   warningout.c
 * @author Egorov N.V. <egorov@rti-mints.ru>
 * @date   Thu Sep 30 15:52:07 2010
 * 
 * @brief  Вывод предупрежденией в поток вывода 
 * 
 * 
 */

#include <stdio.h>
#include <stdarg.h>

#include <tiooutput.h>
#include <tio.h>


int tioWarning(const char* message)
{
    if ( 0 > fprintf(stderr, "(WW): %s", message))
        return (TEFAIL);
    return 0;
}

int tioWarningF(const char* format, ... )
{
    va_list ap;
    int res;

    va_start( ap, format );
    res = uniformstroutput(WARNING, format, ap);
    va_end( ap );
    return res;
}
