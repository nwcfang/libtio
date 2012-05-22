/**
 * @file   finish.c
 * @author Egorov N.V. <egorov@rti-mints.ru>
 * @date   Thu Sep  9 12:48:06 2010
 * 
 * @brief  Реализация функция завершения для библиотеки 
 *
 * 
 * 
 */
#include <stdlib.h>
#include <stdio.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <tioinit.h>

#include <finish_msg.h>


extern char *selfname;

static size_t finish_count = 3;

void tioFinish(size_t num)
{
    if(num >= finish_count)
    {
        num = finish_count;
    }
    tioFree();
    fprintf(stdout, finish_messages[num], selfname);
    free(selfname);
    exit(num);
}
