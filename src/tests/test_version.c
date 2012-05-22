/**
 * @file   test_version.c
 * @author Egorov N.V. <egorov@rti-mints.ru>
 * @date   Fri Sep 17 17:17:35 2010
 * 
 * @brief  проверка работы системы версий библиотеки
 * 
 * 
 */

#include <tio.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    printf("Version %s, revision %ld\n", tioGetVersionString(), tioGetVersion());
    return 0;
}
