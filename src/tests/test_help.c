/**
 *
 * @file    test_help.c
 * @author  Gennady Sazonov <sazonov_g@rti-mints.ru>
 * @date    2010-06-25
 *
 * @brief    Тест для проверки вывода функции помощи.
 *
 */

#include  <tioinit.h>

#define SIZE 5

int tioHelp( const char* help_msg, const char* progName,
        const tio_param_rec par[], const size_t sz );


int main( int argc, char *argv[] )
{
    const char* msg = "Проверка описания программы.";
    const char* name = "Test";

    char* mas[] = { "--list", "--ls", "--lst", NULL };
    char* mas1[] = { "--ip", "--adress", NULL };
    char* mas2[] = { "--sort", NULL };
    char* mas3[] = { "--file", "--fl", NULL };
//    char* mas5[] = { NULL };

    tio_param_rec p[SIZE] = {
        {
            "List",
            mas,
            "kd",
            "Выводит информацию списком",
            NULL,
            0
        },
        {
            "IP",
            mas1,
            NULL,
            "Указать IP адресс. А ещё этот ключ делает бла-бла-бла. После чего по новой бла-бла-бла. И третий раз для теста бла-бла-бла.",
            NULL,
            1
        },
        {
            "Check",
            mas2,
            "sS",
            "Сортировка даннах",
            NULL,
            "a"
        },
        {
            "File",
            mas3,
            NULL,
            "Сортировка данных",
            NULL,
            1
        },
        {
            "Tab",
            NULL,
            "t",
            "В табличном виде",
            NULL,
            1
        }
    };

    if( tioHelp( msg, name, p, SIZE ) )
        return 1;

    return 0;
}
