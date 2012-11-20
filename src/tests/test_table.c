#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <tio.h>

#define MSRTLEN 500/*Максимальная длина строки с названиями колонок*/

/*Тест функция */

int main( )
{
    FILE *in;
    void *td;
    double doub_test = 23.7; 
    long   long_test = 33;
    char *string = "char&st&&ring&double&string";
    char c_test = 'f' ; 
    char *s_test = "Animated by Ryan Woodward";
    char *s_test2 = "The essence of COM is a language-neutral way of implementing objects that can be used in environments";
    char *s_test4 = "An advantage of COM+";

    printf("Cap string\n");
    
    printf("Call \"tioTableBegin\".\n");
    td = tioTableBegin( string, TIOCHAR, TIOSTRING, TIODOUBLE, TIOSTRING);

    /*Вызов функции заполнения таблицы*/
    printf("\nCall \"tioTableRecord\".\n");
    td = tioTableRecord( td, 'r', s_test4, doub_test, s_test );
    c_test = 'g' ; doub_test = 43.9 ;long_test = 43 ;
    td = tioTableRecord( td, 'e', s_test4, doub_test, s_test2 );
    /*Вызов завершающей функции*/
    printf("\nCall \"tioTableEnd\".\n");


    tioTableEnd( td );

    return 0;

}
