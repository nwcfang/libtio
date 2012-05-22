/**
 * @file    output.c
 * @author  Gennady Sazonov <sazonov_g@rti-mints.ru>
 * @date    2010-09-27
 *
 * @brief    Реализаия общих функций разбора строк для вывода.
 *
 */

#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <stdarg.h>

#include  <tioerror.h>
#include  <tiowerror.h>
#include  <tiooutput.h>

#define     SIZE_BUF    100      // Размер временного буфера

int parseFormat( char* resStr, const char* formStr, const va_list* list )
{
    int fIdx = 0;
    int resIdx = 0;

    char    c, *str;
    long    lng;
    double  dbl;

    int err;    // номер ошибки
    char buf[SIZE_BUF];
    size_t fLth = strlen( formStr );

    while( fIdx < fLth )
    {
        if( formStr[fIdx] == '%' )
        {
            ++fIdx;
            switch ( formStr[fIdx] )
            {
                case 'c' :
                    c = (char)va_arg( *(list), int );
                    resStr[resIdx++] = c;
                    break;
                case 'd' :
                case 'i' :
                    lng = va_arg( *(list), long );
                    sprintf( buf, "%ld", lng );
                    if( (err = catAndGo( resStr, buf, &resIdx)) != 0 )
                        return tioSetErrorNum( err );
                    break;
                case 'e' :
                    dbl = va_arg( *(list), double );
                    sprintf( buf, "%e", dbl );
                    if( (err = catAndGo( resStr, buf, &resIdx)) != 0 )
                        return tioSetErrorNum( err );
                    break;
                case 'f' :
                    dbl = va_arg( *(list), double );
                    sprintf( buf, "%f", dbl );
                    if( (err = catAndGo( resStr, buf, &resIdx)) != 0 )
                        return tioSetErrorNum( err );
                    break;
                case 'o' :
                    lng = va_arg( *(list), long );
                    sprintf( buf, "%lo", lng );
                    if( (err = catAndGo(resStr, buf, &resIdx )) != 0 )
                        return tioSetErrorNum( err );
                    break;
                case 's' :
                    str = va_arg( *(list), char* );
                    if( (err = catAndGo( resStr, str, &resIdx )) != 0 )
                        return tioSetErrorNum( err );
                    break;
                case 'x' :
                    lng = va_arg( *(list), long );
                    sprintf( buf, "%lx", lng );
                    if( (err = catAndGo( resStr, buf, &resIdx )) != 0 )
                        return tioSetErrorNum( err );
                    break;
                case 'X' :
                    lng = va_arg( *(list), long );
                    sprintf( buf, "%lX", lng );
                    if( (err = catAndGo( resStr, buf, &resIdx )) != 0 )
                        return tioSetErrorNum( err );
                    break;
                case '%' :
                    resStr[resIdx++] = formStr[fIdx];
                    break;
                default :
                    return TEFAIL;
                    break;
            }
        } else
        {
            resStr[resIdx++] = formStr[fIdx];
        }
        ++fIdx;
    }

    return 0;
}

int numOccur( const char* formStr, size_t len )
{
    int occur =0;
    size_t idx = 0;

    while( idx < len )
    {
        if(  formStr[idx] == '%' )
            formStr[idx+1] != '%' ? ++occur : ++idx;
        ++idx;
    }

    return occur;
}

int catAndGo( char* str, char* buf, int* itr )
{
    size_t len = strlen( buf );

    strcat( str, buf );

    (*itr) += len;

    return 0;
}

