/**
 * @file   test_basetioGetL.c
 * @author Malov V.A. <malov@rti-mints.ru>
 * @date   Wed Aug 18 12:56:07 2010
 * @brief Тестирование функци получения входных параметров для функции
 * получения строки
 */

#include <stdio.h>
#include <tio.h>
#include <tioerror.h>

const char* args[]  =
{
    "self",
    "--short=mark",
    "-b",
    "--integer=10",
    "--overflow=3728710371937173929347492103473472043729349027430103820392830374829387203429042034204720",
    "--EXP-int=73829023E2",
    "--exp-int=32789e2",
    "--HEX-int=0xFF",
    "--hex-int=FF",
    "--float-long=0.56328239137123810238E1",
    "--float-short=-0.736477e0",
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
    {"blank:","BLANK", "Ключ без установленного значения"},
    {NULL, NULL, NULL}
};

int main(int argc, char** argv)
{
	

    tioInit("test", "Программа простого тестирования",mypar, 11, args);
		if(tioGetL("INT") != 10)
		{
			puts("Wrong returned value for INT\nOr couldn't be found value for INT");
			tioFinish(TOFAIL);
		}
		if(tioGetError() != TESUC)
		{
			puts("Wrong returned error for INT (MUST BE TESUC)");
			tioFinish(TOFAIL);
		}
		if(tioGetL("OVER") != LONG_MAX)
		{
			puts("Could't be found overflow for OVER");
			tioFinish(TOFAIL);
		}
		if(tioGetError() != TEINCTYPE)
		{
			puts("Wrong returned error for OVER (MUST BE TEICNTYPE)");
			tioFinish(TOFAIL);
		}
		if(tioGetL("FLTL") != LONG_MAX)
		{
			puts("Wrong returned value for FLTL");
			tioFinish(TOFAIL);
		}
		if(tioGetError() != TEINCTYPE)
		{
			puts("Wrong returned error for FLTL");
			tioFinish(TOFAIL);
		}
		if(tioGetL("FLTSH") != LONG_MAX)
		{
			puts("Wrong returned value for FLTSH");
			tioFinish(TOFAIL);
		}
		if(tioGetError() != TEINCTYPE)
		{
			puts("Wrong returned error for FLTSH");
			tioFinish(TOFAIL);
		}
		if(tioGetL("HEX-int") != LONG_MAX)
		{
			puts("Wrong returned value for HEX-int");
		}
		if(tioGetError() != TEINCTYPE)
		{
			puts("Wrong returned error for HEX-int");
		}
		if(tioGetL("hex-int") != LONG_MAX)
		{
			puts("Wrong returned value for hex-int");
		}
		if(tioGetError() != TEINCTYPE)
		{
			puts("Wrong returned error for hex-int");
		}
		if(tioGetL("EXP") != LONG_MAX)
		{
			puts("Wrong returned value for EXP");
		}
		if(tioGetError() != TEINCTYPE)
		{
			puts("Wrong returned error for EXP (MUST BE TESUC)");
		}
		if(tioGetL("exp") != LONG_MAX)
		{
			puts("Wrong returned value for exp");
		}
		if(tioGetError() != TEINCTYPE)
		{
			puts("Wrong returned error for exp (MUST BE TESUC)");
		}
		if(tioGetL("SRT") != LONG_MAX)
		{
			puts("Wrong returned value for SRT");
		}
		if(tioGetError() != TEINCTYPE)
		{
			puts("Wrong returned error for SRT");
		}
		if(tioGetL("SELF") != LONG_MAX)
		{
			puts("Was founded value for (unregistered) SELF");
		}
		if(tioGetError() != TENOPAR)
		{
			puts("Wrong returned error for (unregistered) SELF");
		}
		if(tioGetL("BOOL") != 1)
		{
			puts("Wrong returned value for BOOL");
		}
		if(tioGetError() != TESUC)
		{
			puts("Wrong returned error for BOOL");
		}
        if(tioGetL("BLANK") != LONG_MAX)
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
