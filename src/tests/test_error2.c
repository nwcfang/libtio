/**
 * @file   test_error2.c
 * @author Egorov N.V. <egorov@rti-mints.ru>
 * @date   Mon Aug  2 15:16:29 2010
 * 
 * @brief Полный тетс многопоточных сообщений об ошибках внутри
 * библиотеке
 * 
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <compare.h>
#include <tioerror.h>
#include <tiowerror.h>


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


int main(int argc, char** argv)
{
    pthread_t id;
    char *name = "Child";
    void* p;
    tioErrorInit();
    
    if(pthread_create(&id, NULL, testfunc, name))
        return -1;
    pthread_join(id, &p);
    return 0;
    
}
