/**
 * @file   test_tioInit.c
 * @author Gusev M.S <gpinok@gmail.com>
 * @date   01.09.12
 * @brief  Тест для проверки функции tioInit
 */


#include <stdio.h>
#include <string.h>
#include <tio.h>
#include <tioerror.h>


int main()
{
    int argc = 13;
    char buff[100] = {0} ;
    const char* argv[]  =
    {
        "self",
        "--short=mark",
        "--shortmy=",
        "markmy",
        "-f",
        "20",
        "--integer",
        "=10",
        "--myp",
        "=",
        "FOO",
        "-bk73",
        "unnamedKey"
    };


   tio_param mypar [] = {
       {"b","BOOL","Булевое значение"},
       {"shortmy:", "SRTM", "Это моя короткая строка"},
       {"short:","SRT", "Короткая строка"},
       {"integer:","INT", "Целое число"},
       {"i:", "INT" , NULL},
       {"f:", "FOO","The foo param"},
       {"k:", "KU", "Ther program to something"},
       {"myparam0","MP0", "Это очень длинный коммент от khenara"},
       {"myp:", "MP", "1909"},
       {"is-it-true","IITRTYRYTRTYRYRY", "I think it\'s true"},
       {"T","TEST", "TEST OF FOO"},
       {NULL, NULL, NULL}
   };

    puts("Test start");
    tioInit("alpha", "This is test", mypar, argc, argv);

    if (tioGetS("SRT", buff, 100))
    {
        fputs("Fail to get SRT",stderr);
        return -1;
    }
    if(strcmp(buff,"mark"))
    {
        fprintf(stderr,"Get %s while must be mark", buff);
        return -1;
    }
    if (tioGetS("SRTM", buff, 100))
    {
        fprintf(stderr, "Fail to get SRTM - Error 0x%X\n",tioGetError());
        
        return -1;
    }
    if(strcmp(buff,"markmy"))
    {
        fprintf(stderr,"Get %s while must be markmy\n", buff);
        return -1;
    }
    if (tioGetS("INT", buff, 100) ||strcmp(buff,"10"))
    {
        fprintf(stderr,"Get %s in INT while must be 10\n", buff);
        return -1;
    }
    if (tioGetS("FOO", buff, 100) ||strcmp(buff,"20"))
    {
        fprintf(stderr,"Get %s in FOO while must be 20\n", buff);
        return -1;
    }
    if (tioGetS("MP", buff, 100) ||strcmp(buff,"FOO"))
    {
        fprintf(stderr,"Get %s in MP while must be FOO\n", buff);
        return -1;
    }
    if (tioGetS("KU", buff, 100) || strcmp(buff,"73"))
    {
        fprintf(stderr,"Get %s in KU while must be 73\n", buff);
        return -1;
    }

    printf( "unnamedKey is %s\n", tio_argv[0] ); 

    if( strcmp( tio_argv[0], "unnamedKey" ) )
    {
        tioFinish(1);
        return -1;
    }
    tioFinish(0);
    return 0;
}
