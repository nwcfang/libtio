/**
 * @file   test_utf.c
 * @author Egorov N.V. <egorov@rti-mints.ru>
 * @date   Mon Oct 11 18:07:05 2010
 * 
 * @brief  Тест работы со строками в формате utf-8
 * 
 * 
 */

#include <utf.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    char* tst = "Амбивалентный";
    char* tst2 = "Test Проверка";
    long l=0;
    long i;
    if ( utf_strlen(tst)!=13)
    {
        printf("Длинна строки \"%s\" %zd utf: %zd\n", tst, strlen(tst), utf_strlen(tst));
        return -1;
    }
    if (utf_strlen(tst2)!=13)
    {
        printf("Длинна строки \"%s\" %zd utf: %zd\n", tst2, strlen(tst2), utf_strlen(tst2));
        return -1;
    }
    l=utf_strlen(tst);
    for ( i=0; i<l; i++)
    {
        puts(utf_stroffset(tst, i));
    }

    return 0;
}
