/**
 * @file   errorout.c
 * @author Egorov N.V. <egorov@rti-mints.ru>
 * @date   Mon Aug 30 14:42:46 2010
 * 
 * @brief Реализация базовых функций вывода сообщений об ошибках.
 * 
 * 
 */


#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <stdarg.h>


#include  <tio.h>
#include  <tioerror.h>
#include  <tiowerror.h>

#include  <config.h>
#include  <tiooutput.h>


#ifdef USE_VSPRINTF

int tioError( const char* content)
{
    if ( 0 > fprintf(stderr, "(EE): %s", content))
        return (TEFAIL);
    return 0;
}

int tioErrorF( const char* format, ... )
{
    va_list ap;
    int res;

    va_start( ap, format );
    res = uniformstroutput(ERROR, format, ap);
    va_end( ap );
    return res;
}

#else // USE_VSPRINTF
#error "This part not emplemanted yet compile with vsprintf enable."
#endif

int tioDie(int status, const char* msg)
{
    if (msg) 
        tioError(msg);
    if ( ! status  )
        status = TOTESTNOTSTART;
    tioFinish(status);
    return 0;
}
