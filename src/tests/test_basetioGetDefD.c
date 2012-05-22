/**
 * @file   test_basetioGetDefD.c
 * @author Malov V.A. <malov@rti-mints.ru>
 * @date   Wed Aug 18 12:56:07 2010
 * @brief Тестирование функци получения входных параметров для функции
 * получения строки
 */

#include <stdio.h>
#include <tio.h>
#include <tioerror.h>
#include <math.h>

#define EPSILON 0.00000001

const char* args[]  =
{
    __FILE__,
    "--short=mark",
    "-b",
    "--integer=10",
    "--EXP-int=73829023E2",
	"--exp-int=32789e2",
	"--HEX-int=0xFF",
	"--hex-int=FF",
    "--float-long=0.563282391371238E1",
    "--float-short=-0.736477e0",
    "--double=5.37128436193748"
};

tio_param mypar [] = {
    {"b","BOOL","Булевое значение"},
    {"short:","SRT", "Короткая строка"},
    {"integer:","INT", "Целое число"},
	{"EXP-int:","EXP","Целое число в виде экспоненты"},
	{"exp-int:","exp","Целое число в виде экспоненты"},
	{"HEX-int:","HEX-int","Целое число в шестнадцатеричном представлении"},
	{"hex-int:","hex-int","Целое число в шестнадцатеричном представлении"},
    {"float-long:","FLTL", "Длинное число с плавающей точкой"},
    {"float-short:","FLTSH", "Короткое число с плавающей точкой"},
    {"double:","DBL", "Вещественное число с плавающей точкой"},
    {"blank:","BLANK", "Ключ без значения"},
    {NULL, NULL, NULL}
};

int main(int argc, char** argv)
{
    tioInit("test", "Программа простого тестирования",mypar, 11, args);
        if(tioGetDefD("DBL", 0.533) != 5.37128436193748)
        {
            puts("Wrong returned value for DBL\nOr couldn't be found value for DBL");
            tioFinish(TOFAIL);
        }
        if(tioGetError() != TESUC)
        {
			puts("Wrong returned error for DBL (MUST BE TESUC)");
			tioFinish(TOFAIL);
        }
		if(tioGetDefD("INT", 0.533) != 10.0)
		{
			puts("Wrong returned value for INT\nOr couldn't be found value for INT");
			tioFinish(TOFAIL);
		}
		if(tioGetError() != TESUC)
		{
			puts("Wrong returned error for INT (MUST BE TESUC)");
			tioFinish(TOFAIL);
		}
        double tmp = tioGetDefD("FLTL", 0.533);
		if(fabs(tmp - 0.563282391371238E1) > EPSILON)
		{
			puts("Wrong returned value for FLTL");
			tioFinish(TOFAIL);
		}
		if(tioGetError() != TESUC)
		{
			puts("Wrong returned error for FLTL");
			tioFinish(TOFAIL);
		}
		if(tioGetDefD("FLTSH", 0.533) != -0.736477e0)
		{
			puts("Wrong returned value for FLTSH");
			tioFinish(TOFAIL);
		}
		if(tioGetError() != TESUC)
		{
			puts("Wrong returned error for FLTSH");
			tioFinish(TOFAIL);
		}
		if(tioGetDefD("HEX-int", 0.533) != 0xFF)
		{
			puts("Wrong returned value for HEX-int");
			tioFinish(TOFAIL);
		}
		if(tioGetError() != TESUC)
		{
			puts("Wrong returned error for HEX-int");
			tioFinish(TOFAIL);
		}
		if(tioGetDefD("hex-int", 0.533) != 0.533)
		{
			puts("Wrong returned value for hex-int");
			tioFinish(TOFAIL);
		}
		if(tioGetError() != TEINCTYPE)
		{
			puts("Wrong returned error for hex-int");
			tioFinish(TOFAIL);
		}
		if(tioGetDefD("EXP", 0.533) != 73829023E2)
		{
			puts("Wrong returned value for EXP");
			tioFinish(TOFAIL);
		}
		if(tioGetError() != TESUC)
		{
			puts("Wrong returned error for EXP (MUST BE TESUC)");
			tioFinish(TOFAIL);
		}
		if(tioGetDefD("exp", 0.533) != 32789e2)
		{
			puts("Wrong returned value for exp");
			tioFinish(TOFAIL);
		}
		if(tioGetError() != TESUC)
		{
			puts("Wrong returned error for exp (MUST BE TESUC)");
			tioFinish(TOFAIL);
		}
		if(tioGetDefD("SRT", 0.533) != 0.533)
		{
			puts("Wrong returned value for SRT");
			tioFinish(TOFAIL);
		}
		if(tioGetError() != TEINCTYPE)
		{
			puts("Wrong returned error for SRT");
			tioFinish(TOFAIL);
		}
		if(tioGetDefD("SELF", 0.533) != 0.533)
		{
			puts("Was founded value for (unregistered) SELF");
			tioFinish(TOFAIL);
		}
		if(tioGetError() != TENOPAR)
		{
			puts("Wrong returned error for (unregistered) SELF");
			tioFinish(TOFAIL);
		}
		if(tioGetDefD("BOOL", 0.533) != 1)
		{
			puts("Wrong returned value for BOOL");
			tioFinish(TOFAIL);
		}
		if(tioGetError() != TESUC)
		{
			puts("Wrong returned error for BOOL");
			tioFinish(TOFAIL);
		}
        if(tioGetDefD("BLANK", 0.533) != 0.533)
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
