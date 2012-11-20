/**
 *
 * @file   test_error.c
 * @author Gusev M.S.
 * @date   2012-09-07
 * 
 * @brief  Функцкция обработки ошибок 
 * 
 */


#include <tioerror.h>
#include <tiowerror.h>

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <compare.h>


typedef struct _errdeque
{
    pthread_t id;   //дескриптор потока 
    int error;
    struct _errdeque *next;
    struct _errdeque *prev;
} errdeque;

static pthread_mutex_t errlock = PTHREAD_MUTEX_INITIALIZER;

static errdeque *starterr = NULL;
static errdeque *enderr   = NULL;


int tioErrorInit(void)
{
    errdeque* obj = NULL;

    pthread_mutex_lock(&errlock);
    if (starterr || enderr)
    {
#ifndef NDEBUG
        fputs("Internal pointers for deque already initializated", stderr);
#endif
        pthread_mutex_unlock(&errlock);
        return TEINTMC;
    }
    if(!(obj=malloc(sizeof(errdeque))))
    {
#ifndef NDEBUG
        fprintf(stderr,"Memory error at %s:%d\n", __FILE__, __LINE__);
#endif
        return TEEPICFAIL;
    }
    obj->next = obj->prev = NULL;
    obj->error = 0;
    obj->id = pthread_self();
    starterr = enderr = obj;
    pthread_mutex_unlock(&errlock);
    return 0;
}


void tioErrorFree(void)
{
    errdeque *fr, *iter = starterr;

    pthread_mutex_lock(&errlock);
    while (iter)
    {
        fr = iter;
        iter = iter->next;
        free(fr);
    }
    starterr = enderr = NULL;
    pthread_mutex_unlock(&errlock);
}

//==================================================================
int tioSetErrorNum(int num)
{

    //typedef struct _errdeque
    //{
        //pthread_t id;   //дескриптор потока 
        //int error;
        //struct _errdeque *next;
        //struct _errdeque *prev;
    //} errdeque;
    
    errdeque *iter, *obj;
    pthread_t thread;

    thread = pthread_self();    
    pthread_mutex_lock(&errlock);
    if ( !starterr || !enderr )
    {
#ifndef NDEBUG
        fputs("Attempt to set error befor error initialization or after error free\n", \
            stderr);
#endif
        pthread_mutex_unlock(&errlock);
        return TEINTMC;
    }


    if (cmppthread_t(&(((errdeque*)enderr)->id), &thread) > 0)
    {
        if (!(obj=malloc(sizeof(errdeque))))
        {
#ifndef NDEBUG
            fprintf(stderr, "Memory error at %s:%d\n", __FILE__, __LINE__);
#endif
            pthread_mutex_unlock(&errlock);
            return TEEPICFAIL;
        }
        // сохраняем код новой ошибки и id потока
        obj->prev = enderr;
        obj->next = NULL;
        enderr->next = obj;
        obj->error = num;
        obj->id = thread;
        enderr = obj;
    }
    for (iter=starterr; iter != NULL; iter = iter->next)
    {
        long long res;
        if (!(res = cmppthread_t(&(((errdeque*)iter)->id), &thread)))
        {
            iter->error = num;
            break;
        }

        if(res < 0)
        {
            if(!(obj = malloc(sizeof(errdeque))))
            {
#ifndef NDEBUG
                fprintf(stderr, "Memory error at %s:%d\n", __FILE__, __LINE__);
#endif
                pthread_mutex_unlock(&errlock);
                return TEEPICFAIL;
            }
            if ( iter == starterr )
                starterr = obj;
            obj->next = iter;
            obj->prev = iter->prev;
            obj->id = thread;
            obj->error = num;
            if(iter->prev)
                iter->prev->next = obj;
            iter->prev = obj;
            break;
        }
    }
    pthread_mutex_unlock(&errlock);
    return 0;
}

int tioGetError()
{
    errdeque *iter;
    pthread_t id = pthread_self(); //берет id своего потока 
    int result = 0;

    pthread_mutex_lock(&errlock);
    if( !starterr || !enderr)
    {
#ifndef NDEBUG
        fputs("Attemp to use uninitializate error deque\n", stderr);
#endif
        return TEEPICFAIL;
    }
    if (cmppthread_t(&(((errdeque*)enderr)->id), &id)>0)
    {
        pthread_mutex_unlock(&errlock);
        return 0;
    }
    for (iter=starterr; iter != NULL; iter = iter->next)
    {
        long long res;
        if(!(res=cmppthread_t(&(((errdeque*)iter)->id), &id)))
        {
            result = iter->error;
            iter->error = 0;
            break;
        }
        if (res<0)
        {
            result = 0;
            break;
        }
    }
    pthread_mutex_unlock(&errlock);
    return result;
}
