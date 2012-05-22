/**
 * @file   tiogetparam.h
 * @author Malov V.A. <malov@rti-mints.ru>
 * @date   Tue Jun 15 14:50:40 2010
 *
 * @brief Реализация семейства функций tioGet* и tioGetDef* 
 * для получения параметров
 */
#include <tio.h>
#include <tioerror.h>
#include <tioinit.h>
#include <string.h>
#include <tiowerror.h>
#include <math.h>

#ifdef HAVE_CONFIG_H
  #include <config.h>
#endif //HAVE_CONFIG_H

#define TRUE  1
#define FALSE 0

#define BASE_CONVERT 10

tio_param_rec* getnextval(tio_param_rec* val);
int write_val_in_buff(char* val, char *buff, size_t buff_len);
int write_bool_in_buff(char* Bool, char* buff, size_t buff_len);

struct _strBool
{
    char *sTrue;
    char *sFalse;
} strBool = {"TRUE","FALSE"};

static inline long retbool(const char* str)
{
    if (str == NULL)
    {
        return (FALSE);
    }
    else
    {
        return (TRUE);
    }
}

int tioGetS(const char* name, char* buff, const size_t buff_len)
{
	int cnt = 1;
	tio_param_rec *curr_tio_param = Tio_params;
    
	if (buff == NULL)
	{
		tioSetErrorNum(TEINVAL);
		return(TEINVAL);
	}
	else if (!buff_len)
	{
		tioSetErrorNum(TENES);
		return (TENES);
	}
    while(cnt <= Tio_params_sz)
    {
        int result = strcmp(name,curr_tio_param->name);
        if (result == 0)
        {
            if (curr_tio_param->has_key)
            {
                if (curr_tio_param->val != NULL)
                {
                    char *curr_val = curr_tio_param->val;
                    size_t vallen = strlen(curr_val);
                    if ((vallen+1) <= buff_len)
                    {
                        strcpy(buff,curr_val);
                        tioSetErrorNum(TESUC);
                        return (TESUC);
                    }
                    else
                    {
                        strncpy(buff,curr_val,buff_len-1);
                        char *setoff = (buff + buff_len - 1);
                        *setoff = '\0';
                        tioSetErrorNum(TENES);
                        return (TENES);
                    }
                }
                else 
                {
                    tioSetErrorNum(TENOTSET);
                    return (TENOTSET);
                }
            }
            else 
            {
                if (curr_tio_param->val != NULL)
                {
                    size_t strval = strlen(strBool.sTrue);
                    if (strval+1 <= buff_len)
                    {
                        strcpy(buff,strBool.sTrue);
                        tioSetErrorNum(TESUC);
                        return (TESUC);
                    }
                    else
                    {
                        tioSetErrorNum(TENES);
                        return (TENES);
                    }
                }
                else 
                {
                    size_t strval = strlen(strBool.sFalse);
                    if (strval+1 <= buff_len)
                    {
                        strcpy(buff,strBool.sFalse);
                        tioSetErrorNum(TESUC);
                        return (TESUC);
                    }
                    else
                    {
                        tioSetErrorNum(TENES);
                        return (TENES);
                    }
                }
            }
        }
        curr_tio_param++;
        cnt++;
    }
    tioSetErrorNum(TENOPAR);
    return (TENOPAR);
	//*******************************
}

int tioGetDefS(const char* name, const char* Default, char* buff, const size_t buff_len)
{
	int cnt = 1;
	tio_param_rec *curr_tio_param = Tio_params;

	if (buff == NULL)
	{
		tioSetErrorNum(TEINVAL);
		return(TEINVAL);
	}
	else if (!buff_len)
	{
		tioSetErrorNum(TENES);
		return (TENES);
	}
    while(cnt <= Tio_params_sz)
    {
        int result = strcmp(name,curr_tio_param->name);
        if (result == 0)
        {
            if (curr_tio_param->has_key)
            {
                if(curr_tio_param->val != NULL)
                {
                    char *curr_val = curr_tio_param->val;
                    size_t vallen = strlen(curr_val);
                    if ((vallen+1) <= buff_len)
                    {
                        strcpy(buff,curr_val);
                        tioSetErrorNum(TESUC);
                        return (EXIT_SUCCESS);
                    }
                    else
                    {
                        strncpy(buff,curr_val,buff_len-1);
                        char *setoff = (buff + buff_len - 1);
                        *setoff = '\0';
                        tioSetErrorNum(TENES);
                        return (TENES);
                    }
                }
                else
                {
                    tioSetErrorNum(TENOTSET);
                    size_t vallen = strlen(Default);
                    if((vallen+1) <= buff_len)
                    {
                        strcpy(buff,Default);
                    }
                    return (TENOTSET);
                }
            }
            else
            {
                if (curr_tio_param->val != NULL)
                {
                    size_t strval = strlen(strBool.sTrue);
                    if (strval+1 <= buff_len)
                    {
                        strcpy(buff,strBool.sTrue);
                        tioSetErrorNum(TESUC);
                        return (TESUC);
                    }
                    else
                    {
                        tioSetErrorNum(TENES);
                        return (TENES);
                    }
                }
                else
                {
                    size_t strval = strlen(strBool.sFalse);
                    if (strval+1 <= buff_len)
                    {
                        strcpy(buff,strBool.sFalse);
                        tioSetErrorNum(TESUC);
                        return (TESUC);
                    }
                    else
                    {
                        tioSetErrorNum(TENES);
                        return (TENES);
                    }
                }
            }
        }
        curr_tio_param++;
        cnt++;
    }
    size_t vallen = strlen(Default);
    if((vallen+1) <= buff_len)
    {
        strcpy(buff,Default);
    }
    tioSetErrorNum(TENOPAR);
    return (TENOPAR);
}

long tioGetL(const char* name)
{
	int cnt = 1;
	tio_param_rec *curr_tio_param = Tio_params;
    
    while(cnt <= Tio_params_sz)
    {
        int rescmp = strcmp(name,curr_tio_param->name);
        if (rescmp == 0)
        {
            long result;
            if (curr_tio_param->has_key)
            {
                if(curr_tio_param->val != NULL)
                {
                    char* endptr;
                    result = strtol(curr_tio_param->val,&endptr,BASE_CONVERT);
                    if (!strcmp(endptr,""))
                    {
                        if (result == LONG_MAX || result == LONG_MIN)
                        {
                            tioSetErrorNum(TEINCTYPE);
                            return (LONG_MAX);
                        }
                        else
                        {
                            tioSetErrorNum(TESUC);
                            return (result);
                        }
                    }
                    else
                    {
                        tioSetErrorNum(TEINCTYPE);
                        return (LONG_MAX);
                    }
                }
                else
                {
                    tioSetErrorNum(TENOTSET);
                    return (LONG_MAX);
                }
            }
            else 
            {
                result = retbool(curr_tio_param->val);
                tioSetErrorNum(TESUC);
                return(result);
            }
        }
        curr_tio_param++;
        cnt++;
    }
    tioSetErrorNum(TENOPAR);
    return (LONG_MAX);
}

long tioGetDefL(const char* name, const long Default)
{
    int cnt = 1;
    tio_param_rec *curr_tio_param = Tio_params;
    
    while(cnt <= Tio_params_sz)
    {
        int rescmp = strcmp(name,curr_tio_param->name);
        if (rescmp == 0)
        {
            long result;
            if (curr_tio_param->has_key)
            {
                if(curr_tio_param->val != NULL)
                {
                    char* endptr;
                    result = strtol(curr_tio_param->val,&endptr,BASE_CONVERT);
                    if (!strcmp(endptr,""))
                    {
                        if (result == LONG_MAX || result == LONG_MIN)
                        {
                            tioSetErrorNum(TEINCTYPE);
                            return (Default);
                        }
                        else
                        {
                            tioSetErrorNum(TESUC);
                            return (result);
                        }
                    }
                    else
                    {
                        tioSetErrorNum(TEINCTYPE);
                        return (Default);
                    }
                }
                else
                {
                    tioSetErrorNum(TENOTSET);
                    return (Default);
                }
            }
            else
            {
                result = retbool(curr_tio_param->val);
                tioSetErrorNum(TESUC);
                return(result);
            }
        }
        curr_tio_param++;
        cnt++;
    }
    tioSetErrorNum(TENOPAR);
    return (Default);
}

double tioGetD(const char* name)
{
	int cnt = 1;
	tio_param_rec *curr_tio_param = Tio_params;
    
    while(cnt <= Tio_params_sz)
    {
        int result = strcmp(name,curr_tio_param->name);
        if (result == 0)
        {
            double result;
            if (curr_tio_param->has_key)
            {
                if(curr_tio_param->val != NULL)
                {
                    char* endptr;
                    result = strtod(curr_tio_param->val,&endptr);
                    
                    if (!strcmp(endptr,""))
                    {
                        if ((result == HUGE_VAL) || (result == -HUGE_VAL))
                        {
                            tioSetErrorNum(TEINCTYPE);
                            return (DBL_MAX);
                        }
                        else
                        {
                            tioSetErrorNum(TESUC);
                            return (result);
                        }
                    }
                    else
                    {
                        tioSetErrorNum(TEINCTYPE);
                        return (DBL_MAX);
                    }
                }
                else
                {
                    tioSetErrorNum(TENOTSET);
                    return (DBL_MAX);
                }
            }
            else
            {
                result = (double)retbool(curr_tio_param->val);
                tioSetErrorNum(TESUC);
                return(result);
            }
        }
        curr_tio_param++;
        cnt++;
    }
    tioSetErrorNum(TENOPAR);
    return (DBL_MAX);
}

double tioGetDefD(const char* name, const double Default)
{
	int cnt = 1;
	tio_param_rec *curr_tio_param = Tio_params;

    while(cnt <= Tio_params_sz)
    {
        int result = strcmp(name,curr_tio_param->name);
        if (result == 0)
        {
            double result;
            if (curr_tio_param->has_key)
            {
                if(curr_tio_param->val != NULL)
                {
                    char* endptr;
                    result = strtod(curr_tio_param->val,&endptr);
                    
                    if (!strcmp(endptr,""))
                    {
                        if ((result == HUGE_VAL) || (result == -HUGE_VAL))
                        {
                            tioSetErrorNum(TEINCTYPE);
                            return (Default);
                        }
                        else
                        {
                            tioSetErrorNum(TESUC);
                            return (result);
                        }
                    }
                    else
                    {
                        tioSetErrorNum(TEINCTYPE);
                        return (Default);
                    }
                }
                else
                {
                    tioSetErrorNum(TENOTSET);
                    return (Default);
                }
            }
            else
            {
                result = (double)retbool(curr_tio_param->val);
                tioSetErrorNum(TESUC);
                return(result);
            }
        }
        curr_tio_param++;
        cnt++;
    }
    tioSetErrorNum(TENOPAR);
    return (Default);
}

unsigned char tioGetC(const char* name)
{
	int cnt = 1;
	tio_param_rec *curr_tio_param = Tio_params;

		while(cnt <= Tio_params_sz)
		{
			int rescmp = strcmp(name,curr_tio_param->name);
			if (rescmp == 0)
			{
				long result;
				if (curr_tio_param->has_key)
				{
					if(curr_tio_param->val != NULL)
					{
						char* endptr;
						result = strtol(curr_tio_param->val,&endptr,BASE_CONVERT);
						if (!strcmp(endptr,""))
						{
                            if (result >= 0 && result < UCHAR_MAX)
                            {
                                tioSetErrorNum(TESUC);
                                return(result);
                            }
                            else
                            {
                                tioSetErrorNum(TEINCTYPE);
                                return (UCHAR_MAX);
                            }
						}
						else
						{
							tioSetErrorNum(TEINCTYPE);
							return (UCHAR_MAX);
						}
					}
					else
					{
						tioSetErrorNum(TENOTSET);
						return (UCHAR_MAX);
					}
				}
				else
				{
					result = retbool(curr_tio_param->val);
					tioSetErrorNum(TESUC);
					return(result);
				}
			}
			curr_tio_param++;
			cnt++;
		}
		tioSetErrorNum(TENOPAR);
		return (UCHAR_MAX);
}

unsigned char tioGetDefC(const char* name, const unsigned char Default)
{
	int cnt = 1;
	tio_param_rec *curr_tio_param = Tio_params;

		while(cnt <= Tio_params_sz)
		{
			int rescmp = strcmp(name,curr_tio_param->name);
			if (rescmp == 0)
			{
				long result;
				if (curr_tio_param->has_key)
				{
					if(curr_tio_param->val != NULL)
					{
						char* endptr;
						result = strtol(curr_tio_param->val,&endptr,BASE_CONVERT);
						if (!strcmp(endptr,""))
						{
                            if (result >= 0 && result < UCHAR_MAX)
                            {
                                tioSetErrorNum(TESUC);
                                return(result);
                            }
                            else
                            {
                                tioSetErrorNum(TEINCTYPE);
                                return (Default);
                            }
						}
						else
						{
							tioSetErrorNum(TEINCTYPE);
							return (Default);
						}
					}
					else
					{
						tioSetErrorNum(TENOTSET);
						return (Default);
					}
				}
				else
				{
					result = retbool(curr_tio_param->val);
					tioSetErrorNum(TESUC);
					return(result);
				}
			}
			curr_tio_param++;
			cnt++;
		}
		tioSetErrorNum(TENOPAR);
		return (Default);
}

tio_param_rec* getnextval(tio_param_rec* val)
{
    static int cnt_sz = 0;
    if(val == NULL || (++val) == NULL)
    {
    return(NULL);
    }
    else if(cnt_sz < Tio_params_sz)
    {
    cnt_sz++;
    return(val);
    }
    else
    {
    return(NULL);
    }
}

int write_val_in_buff(char* val, char *buff, size_t buff_len)
{
    if (buff == NULL)
    {
        tioSetErrorNum(TEINVAL);
        return(TEINVAL);
    }
    else if (!buff_len)
    {
        tioSetErrorNum(TENES);
        return(TENES);
    }

    if(strlen(val)+1 <= buff_len)
    {
        strcpy(buff,val);
        tioSetErrorNum(TESUC);
        return(TESUC);
    }
    else
    {
        strncpy(buff,val,buff_len-1);
        char *setoff = (buff + buff_len - 1);
        *setoff = '\0';
        tioSetErrorNum(TENES);
        return(TENES);
    }
}
int write_bool_in_buff(char* Bool, char* buff, size_t buff_len)
{
	if (buff == NULL)
	{
		tioSetErrorNum(TEINVAL);
		return(TEINVAL);
	}
	else if (!buff_len)
	{
		tioSetErrorNum(TENES);
		return(TENES);
	}

	if (strlen(Bool)+1 <= buff_len)
	{
		strcpy(buff, Bool);
		tioSetErrorNum(TESUC);
		return(TESUC);
	}
	else
	{
		tioSetErrorNum(TENES);
		return (TENES);
	}
}
