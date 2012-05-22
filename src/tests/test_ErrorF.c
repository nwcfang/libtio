/**
 *
 * @file    test_ErrorF.c
 * @author  Gennady Sazonov <sazonov_g@rti-mints.ru>
 * @date    2010-09-08
 *
 * @brief    Тест для проверки функции вывода ошибок с параметрами 
 *
 */

#include  <tioinit.h>

int main( int argc, char *argv[] )
{
    char ch = 'X';
    char* str= "This is string!";
    long dig = 123;
    double dbl = 11.5434;

    tioErrorF("char = %c long = %d le = %e  float = %f. 100 in oct = %o. %s and"
            " h = %x, H = %X. Happy%% end!", ch, dig, dbl, dbl, 100, str,
            dig, dig );

    return 0;
}
