/**
 *
 * @file    test_help.c
 * @author  Gusev M.S. 
 * @date    2011-06-25
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
    char* mas5[] = { NULL };

    tio_param_rec p[SIZE] = {
        {
            "List",
            mas,
            "kd",
            "List information about the FILEs (the current directory by default).  Sort entries alphabetically if none of -cftuvSUX nor --sort. Mandatory arguments to long options are mandatory for short options too.",
            NULL,
            0
        },
        {
            "IP",
            mas1,
            NULL,
            "show / manipulate routing, devices, policy routing and tunnels",
            NULL,
            1
        },
        {
            "Check",
            mas2,
            "sS",
            "sort lines of text files",
            NULL,
            "a"
        },
        {
            "File",
            mas3,
            NULL,
            "determine file type",
            NULL,
            1
        },
        {
            "Tab",
            NULL,
            "t",
            "table view",
            NULL,
            1
        }
    };

    if( tioHelp( msg, name, p, SIZE ) )
        return 1;

    return 0;
}
