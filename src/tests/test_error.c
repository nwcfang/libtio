/**
 * @file   test_error.c
 * @author Gusev M.S.
 * @date   2012-09-07
 * 
 * @brief  Тестирование функцкций обработки ошибок 
 * 
 * @todo Необходимо проверить многопоточный режим
 */


#include <tioerror.h>
#include <tiowerror.h>

#include <pthread.h>

#include <stdio.h>


int error_msg=1;
int succes_msg=0;


void* testfunc(void* A)
{
    char* a;
    if (!A)
        pthread_exit((void*)&error_msg);
    a = (char*)A;

    
    if (tioGetError())
    {
        fprintf(stderr,"%s: Ну нет еще ошибок\n", a);
        pthread_exit((void*)&error_msg);
        return &error_msg;
    }
    tioSetErrorNum(10);
    if (10!=tioGetError())
    {
        fprintf(stderr,"%s: Не верно возвращен код ошибки\n", a);
        pthread_exit((void*)&error_msg);
        return &error_msg;
    }
    tioSetErrorNum(0);
    tioSetErrorNum(10);
    tioSetErrorNum(11);
    if(11!=tioGetError())
    {
        fprintf(stderr,"%s, Не правильное чтение при задании двух кодов ошибок подряд\n", a);
        pthread_exit((void*)&error_msg);
        return &error_msg;
    }
    if(tioGetError())
    {
        fprintf(stderr, "%s:Повторное получение ошибки провалилось\n", a);
        pthread_exit((void*)&error_msg);
        return &error_msg;
    }
    pthread_exit((void*)&succes_msg);
    return NULL;
}

typedef struct 
{
    pthread_t id;
    char*     name;
} test_thread;


int main(int argc, char** argv)
{
    test_thread *i;
    test_thread threads[] = {
        {0, "first"},
        {0, "second"},
        {0, "therd"},
        {0, "forth"},
        {0, NULL}
    };
    void *p;

    if (!tioSetErrorNum(100))
    {
        fputs("Неверная реакция на установку значения до инициализации", stderr);
        return -1;
    }

    tioErrorInit();    
    for ( i = threads; i->name; ++i )
    {
        //(out) id, param (default), function (thread main), arg (thread main)  
        if (pthread_create(&(((test_thread*)i)->id), NULL, testfunc, i->name))
            return -1;
    }
    if (tioGetError())
    {
        puts("Ну нет еще ошибок");
	//        return -1;
    }
    tioSetErrorNum(10);
    if (10!=tioGetError())
    {
        puts("Не верно возвращен код ошибки");
	//        return -1;
    }
    tioSetErrorNum(0);
    tioSetErrorNum(10);
    tioSetErrorNum(11);
    if(11!=tioGetError())
    {
        puts("Не правильное чтение при задании двух кодов ошибок подряд");
	//        return -1;
    }
    if(tioGetError())
    {
        puts("Повторное получение ошибки провалилось");
	//        return -1;
    }
    for ( i = threads; i->name; ++i )
    {
        pthread_join(i->id, &p);
        if ( p == &error_msg )
        {
            puts("Joining error");
            return -1;
        }
    }
    tioErrorFree();
            
    return 0;
}
