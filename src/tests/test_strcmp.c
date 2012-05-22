/**
 * @file   test_strcmp.c
 * @author Egorov N.V. <egorov@rti-mints.ru>
 * @date   Mon Jul  5 16:33:17 2010
 * 
 * @brief Проверка на правильную работу сравнения строки.
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char** argv)
{
    char* a="--tio-foo";
    char* b="--tio-football";
    
    if (strcmp(b,a)>0)
        return 0;
    else
        return -1;
}
