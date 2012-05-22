/**
 * @file   test_basetioGetDefC.c
 * @author Malov V.A. <malov@rti-mints.ru>
 * @date   Wed Aug 18 12:56:07 2010
 *
 * @brief Тестирование функци получения входных параметров для функции
 * получения строки
 */

#include <stdio.h>
#include <tio.h>
#include <tioerror.h>

const char* args[]  =
{
    __FILE__,
    "--short=mark",
    "-b",
    "--integer=10",
    "--overflow=512",
    "--EXP-int=73829023E2",
    "--exp-int=32789e2",
    "--HEX-int=0xFF",
    "--hex-int=FF",
    "--float-long=5.568E1",
    "--float-short=-3.77e0"
};

tio_param mypar [] = {
    {"b","BOOL","Булевое значение"},
    {"short:","SRT", "Короткая строка"},
    {"integer:","INT", "Целое число"},
    {"EXP-int:","EXP","Целое число в виде экспоненты"},
    {"exp-int:","exp","Целое число в виде экспоненты"},
    {"HEX-int:","HEX-int","Целое число в шестнадцатеричном представлении"},
    {"hex-int:","hex-int","Целое число в шестнадцатеричном представлении"},
    {"overflow:","OVER", "Целое число с переполнение"},
    {"float-long:","FLTL", "Длинное число с плавающей точкой"},
    {"float-short:","FLTSH", "Короткое число с плавающей точкой"},
    {"blank:","BLANK", "Ключ без значения"},
    {NULL, NULL, NULL}
};

int main(int argc, char** argv)
{
    tioInit("test", "Программа простого тестирования",mypar, 11, args);

    if(tioGetDefC("INT",77) != 10)
    {
        puts("Wrong returned value for INT\nOr couldn't be found value for INT");
        tioFinish(TOFAIL);
    }
    if(tioGetError() != TESUC)
    {
        puts("Wrong returned error for INT (MUST BE TESUC)");
        tioFinish(TOFAIL);
    }
    if(tioGetDefC("OVER",77) != 77)
    {
        puts("Could't be found overflow for OVER");
        tioFinish(TOFAIL);
    }
    if(tioGetError() != TEINCTYPE)
    {
        puts("Wrong returned error for OVER (MUST BE TEICNTYPE)");
        tioFinish(TOFAIL);
    }
    if(tioGetDefC("FLTL",77) != 77)
    {
        puts("Wrong returned value for FLTL");
        tioFinish(TOFAIL);
    }
    if(tioGetError() != TEINCTYPE)
    {
        puts("Wrong returned error for FLTL");
        tioFinish(TOFAIL);
    }
    if(tioGetDefC("FLTSH",77) != 77)
    {
        puts("Wrong returned value for FLTSH");
        tioFinish(TOFAIL);
    }
    if(tioGetError() != TEINCTYPE)
    {
        puts("Wrong returned error for FLTSH");
        tioFinish(TOFAIL);
    }
    if(tioGetDefC("HEX-int",77) != 77)
    {
        puts("Wrong returned value for HEX-int");
        return(-1);
    }
    if(tioGetError() != TEINCTYPE)
    {
        puts("Wrong returned error for HEX-int");
        return(-1);
    }
    if(tioGetDefC("hex-int",77) != 77)
    {
        puts("Wrong returned value for hex-int");
        return(-1);
    }
    if(tioGetError() != TEINCTYPE)
    {
        puts("Wrong returned error for hex-int");
        return(-1);
    }
    if(tioGetDefC("EXP",77) != 77)
    {
        puts("Wrong returned value for EXP");
        return(-1);
    }
    if(tioGetError() != TEINCTYPE)
    {
        puts("Wrong returned error for EXP (MUST BE TESUC)");
        return(-1);
    }
    if(tioGetDefC("exp",77) != 77)
    {
        puts("Wrong returned value for exp");
        return(-1);
    }
    if(tioGetError() != TEINCTYPE)
    {
        puts("Wrong returned error for exp (MUST BE TESUC)");
        return(-1);
    }
    if(tioGetDefC("SRT",77) != 77)
    {
        puts("Wrong returned value for SRT");
        return(-1);
    }
    if(tioGetError() != TEINCTYPE)
    {
        puts("Wrong returned error for SRT");
        return(-1);
    }
    if(tioGetDefC("SELF",77) != 77)
    {
        puts("Was founded value for (unregistered) SELF");
        return(-1);
    }
    if(tioGetError() != TENOPAR)
    {
        puts("Wrong returned error for (unregistered) SELF");
        return(-1);
    }
    if(tioGetDefC("BOOL",77) != 1)
    {
        puts("Wrong returned value for BOOL");
        return(-1);
    }
    if(tioGetError() != TESUC)
    {
        puts("Wrong returned error for BOOL");
        return(-1);
    }
    if(tioGetDefC("BLANK",77) != 77)
    {
        puts("We haven't value for key BLANK");
        tioFinish(TOFAIL);
    }
    if(tioGetError() != TENOTSET)
    {
        puts("Wrong returned error for BLANK (MUST BE TENOTSET)");
        tioFinish(TOFAIL);
    }
    tioFinish(TOPASS);
    return 0;
}
