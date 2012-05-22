/**
 * @file   version.c
 * @author Egorov N.V. <egorov@rti-mints.ru>
 * @date   Fri Sep 17 17:10:32 2010
 * 
 * @brief  Функции для работы с версонолизацией
 * 
 * 
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

//#define VERSTR #VERSIONSTR

static  char *versionstr=VERSIONSTR;

long tioGetVersion(void )
{
    return VERSION;
}

char* tioGetVersionString(void )
{
    return versionstr;
}
