/**
 * @file   test_output.c
 * @author Egorov N.V. <egorov@rti-mints.ru>
 * @date   Mon Oct 11 18:07:42 2010
 * 
 * @brief  Тест функций вывода ошибок
 * 
 * 
 */
#include  <stdio.h>

#include  <tio.h>
#include  <tiowerror.h>

int main( int argc, char *argv[] )
{
    char* str= "This is string!";
    long dig = 123;
    double dbl = 11.5434;

    char* fullStr = "Символ = %c число %d с плавающей: %e, ещё раз: %f, 100 в"
        " окт: %o, строка: %x в хексе: %x, в ХЕКСЕ: %X %%THe end.\n";

    tioErrorInit();

    tioErrorF( "%s\n","26767683687684376876348768638768372686387687638763874687364876384768764387"
        "jddhkjhfkjdhkjherw;jhl;kjelskjlkjelkjlkjefl;sj;lkej;lkj;lej;lkjelkfsjljeflkjlkjesflkjlke"
        "jkjdlksjlkjejlkjdlkjlkdjyiu63e8763876982pojlkhjlkewyp9ub oiuro;icnj8p2[oicnpoi2poi2p3ipo"
        "i2309878yrhjewhiouyfipdhlu3rpo8u7093kpojkfd09iupjrepwu09ufeoij09fueoijoifeu980j32oiy87y9"
        "jddhkjhfkjdhkjherw;jhl;kjelskjlkjelkjlkjefl;sj;lkej;lkj;lej;lkjelkfsjljeflkjlkjesflkjlke");
    tioErrorF( fullStr, 'Y', 128, dbl,
            dbl, 100, str, dig, dig );

    tioErrorF( fullStr, 'Z', 129, dbl,
            dbl, 100, str, dig, dig );

    tioErrorFree();
    return 0;
}
