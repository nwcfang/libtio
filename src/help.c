/**
 * @file    help.c
 * @author  Gusev M.S. 
 * @date    2011-06-21
 *
 * @brief    В файле содержаться функции вывода помощи на экран.
 *
 */
#include  <stdio.h>
#include  <string.h>
#include  <tioinit.h>
#include  <utf.h>

#include <help_msg.h>

#define MAX_TAB 4
#define MAX_DES 50
#define SIZE    100

int tioHelp( const char* help_msg, const char* progName,
        const tio_param_rec par[], const size_t sz )
{
    printf( HELP_USAGE, progName );
    puts( help_msg );

    int idx, i;
    int nolong = 0;
    size_t lskeys;
    int counter;
    for( idx = 0 ; idx < sz ; ++idx )
    {
        counter = MAX_TAB;
        // Вывод короткого ключа
        if( par[idx].skeys )
        {
            if( !par[idx].keys )
                nolong = 1;
            else nolong = 0;
            lskeys = strlen( par[idx].skeys );

            for( i = 0; i < lskeys-1 ; ++i )
            {
                printf( " -%c,", par[idx].skeys[i] );
            }
            // Если нет длинных ключей то ставим последний короткий
            if( nolong )
                printf( " -%c", par[idx].skeys[lskeys-1] );
            else
                printf( " -%c,", par[idx].skeys[lskeys-1] );
            counter -= lskeys / 2;
        }

        // Вывод длинных ключей
        if( !nolong)
        {
            for( i = 0; par[idx].keys[i]; ++i )
            {
                if( par[idx].keys[i+1] )
                    printf( " %s,", par[idx].keys[i] );
                else
                    printf( " %s", par[idx].keys[i] );
                --counter;
            }
        }

        //Если нужен для данного ключа параметр
        if( par[idx].has_key )
        {
            printf(HELP_PARAM);
            counter -= 2;
        }
        for( i = 0; i <= counter; ++i )
            printf("\t");

        // Разбор параметра описания ключей
        size_t lenDes = utf_strlen( par[idx].description ); //длина описания
        char buf[SIZE];     // буфер для текста входящего в одну строку
        char* headStr = par[idx].description;
        char* endStr;
        int size;
        if( lenDes > MAX_DES )
        {
            do {
                endStr = utf_stroffset( headStr, MAX_DES );
                size = (int)( endStr - headStr );
                strncpy( buf, headStr, size );
                buf[size] = '\0';
                if( headStr == par[idx].description ) // если начало описания
                {
                    printf( "%s\n", buf );
                } else
                {
                    printf( "\t\t\t\t%s\n", buf );
                }
                headStr = endStr;
                lenDes = utf_strlen( headStr );
            } while( lenDes > MAX_DES );
            endStr = utf_stroffset( headStr, MAX_DES );
            size = (int)(endStr - headStr);
            strncpy( buf, headStr, size );
            buf[size] = '\0';
            printf( "\t\t\t\t%s\n", buf );
        }
        else
        {
            printf( "%s\n", par[idx].description );
        }
    }

    return 0;
}
