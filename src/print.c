/**
 * @file    print.c
 * @author  Gennady Sazonov <sazonov_g@rti-mints.ru>
 * @date    2010-09-15
 *
 * @brief    В файле содержаться функции вывода.
 *
 */
#include  <stdio.h>
#include  <stdarg.h>
#include  <string.h>

#include  <tio.h>
#include  <tiooutput.h>

int tioPrint( const char* message )
{
    if( 0 > fprintf( stdout, "(II): %s", message ) )
        return (TEFAIL);
    return 0;
}

int tioPrintF( const char* template, ... )
{
    va_list ap;
    int res = 0;

    va_start( ap, template );
    res = uniformstroutput(MESSAGE, template, ap);
    va_end( ap );

    return res;
}

