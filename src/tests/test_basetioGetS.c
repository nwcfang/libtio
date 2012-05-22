/**
 * @file   test_basetioGetS.c
 * @author Malov V.A. <malov@rti-mints.ru>
 * @date   Wed Aug 18 12:56:07 2010
 * @brief Тестирование функци получения входных параметров для функции
 * получения строки
 */

#include <stdio.h>
#include <string.h>
#include <tio.h>
#include <tioerror.h>

const char* args[]  =
{
    "self",
    "--long-string=asdgfjhgshgjhgsjdhgjhgdshgjhsgdhgjsdgjhgsdhgjhgsdjhgjhsdgjhgjsdjsdhgjgdjsg",
    "--short=mark",
    "-b"
};

char buff[40];

tio_param mypar [] = {
    {"b","BOOL","Булевое значение"},
    {"long-string:", "LSTR", "Длинная строка"},
    {"short:","SRT", "Короткая строка"},
    {"blank:","BLANK", "Значение без ключа"},
    {NULL, NULL, NULL}
};

int main(int argc, char** argv)
{

    tioInit("test", "Программа простого тестирования",mypar, 4, args);
    if(tioGetS("LSTR", buff, 10)!=TENES || tioGetError() != TENES)
    {
        puts("No correct answer for LSTR question");
        tioFinish(TOFAIL);
    }
    if (strlen(buff)!=9)
    {
        puts("Buffer fill error");
        tioFinish(TOFAIL);
    }
    if (tioGetS("SRT",buff,40)!=TESUC || tioGetError() != TESUC)
    {
        puts("No answer for SRT question");
        tioFinish(TOFAIL);
    }
    if (strcmp(buff,"mark"))
    {
        puts("Wrong key value");
        tioFinish(TOFAIL);
    }

    if(tioGetS("foo", buff, 10)!=TENOPAR || tioGetError() != TENOPAR)
    {
        puts("found unexisting parametr");
        tioFinish(TOFAIL);
    }
    if (tioGetS("BOOL", buff, 40))
    {
        puts("No answer for BOOL question");
        tioFinish(TOFAIL);
    }
    puts(buff);
    if(tioGetS("BOOL", NULL, 10)!=TEINVAL || tioGetError() != TEINVAL)
    {
        puts("Accepting NULL buffer -What the hell ]:->");
        tioFinish(TOFAIL);
    }
    if(tioGetS("LSTR", buff, 0)!=TENES || tioGetError() != TENES)
    {
        puts("Wrong reaction on zero lenght buffer");
        tioFinish(TOFAIL);
    }
    if(tioGetS("BLANK",buff,40) != TENOTSET)
    {
        puts("We haven't value for key BLANK");
        tioFinish(TOFAIL);
        return (-1);
    }
    if(tioGetError() != TENOTSET)
    {
        puts("Wrong returned error for BLANK (MUST BE TENOTSET)");
        tioFinish(TOFAIL);
        return (-1);
    }
    tioFinish(TOPASS);
    return 0;
}
