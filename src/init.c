/* Copyright (C) 2010 by РТИ им. Минтса */
/**
 * @file   init.c
 * @author Egorov N.V. <egorov@rti-mints.ru>
 * @date   Fri Jun 18 14:34:34 2010
 * 
 * @brief Реализация инициализации библиотеки и внутренних переменных
 * библиотеки
 * 
 * 
 */

#include <errno.h>
#include <string.h>
#include <stdio.h>

#include <tioinit.h>
#include <tioerror.h>
#include <tiowerror.h>
#include <tio.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <init_msg.h>

#define MAXARGS 100

char *tio_argv[MAXARGS] = {0};

char *selfname = NULL;


char *True="True";
char *False="False";

tio_param      TIOPARAMNULL = { NULL, NULL, NULL };
tio_param_rec *Tio_params = NULL;
size_t         Tio_params_sz = 0;

tio_key_string *longkeys = NULL; /**< Временный массив коротких ключей
                                  * ( используется для поиска ) */
tio_key_string *shortkeys = NULL; /**< Временный массив длинных ключей
                                   * (используется для поиска) */


tio_lib_state tio_self_state [] = {
    {"--tio-debug", 0, TIODEBUG, NULL  },
    {"--tio-file" , 0, TIOFILETAR, NULL},
    { NULL, 0, 0, NULL }
};


/// Проверяет является-ли tio_param нулевым
static inline int is_paramNULL(const tio_param* obj)
{
    if ( obj->description == NULL &&
         obj->name == NULL &&
         obj->key == NULL )
        return 1;
    return 0;
}

/// Сортировка параметров по имени
static int tio_params_sort(tio_param *obj)
{
    tio_param *i, *j, k;

    for ( i = obj; !is_paramNULL(i); ++i)
        for ( j = i+1; !is_paramNULL(j); ++j)
        {
            if ( strcmp(i->name, j->name) > 0 )
            {
                k=*i;
                *i=*j;
                *j=k;
            }
        }
    return 0;
}

/** 
 * Создание копии строки. 
 *
 * Память из под строки заием необходимо освободить вызовом free
 * 
 * @return  Указатель на новую строку или NULL в случае ошибки
 */
static char* newstring(const char* obj)
{
    size_t sz = strlen(obj);
    char *ret;
    if (!obj)
        return NULL;
    ret = malloc(sz+1);
    if(!ret)
        return NULL;
    strcpy(ret, obj);
    return ret;
}


/** 
 * Преобразование ключей в полную форму и первичный разбор на длинные
 * и короткие.
 *
 * @param obj Массив ключей - изменяется во время работы.
 *
 * @param sz  Колличество ключей
 * 
 * @return 0 при упешном выполнени или код ошибки в противном случае.
 */
static int decode_keys(tio_key_string *obj, size_t sz)
{
    size_t i, ll;
    char buff[TIOMAXKEY+3];
    if (!obj)
        return EINVAL;
    
    for ( i = 0; i < sz; ++i)
    {
        ll = strlen(obj[i].str);
        if (!ll || ll > TIOMAXKEY)
            return EINVAL;
        if( 1 == ll )
        {
            obj[i].symb=obj[i].str[0];
            free(obj[i].str);
            obj[i].str=NULL;
            obj[i].per->has_key = 0;
        }
        else if ( 2 == ll)
        {
            if (obj[i].str[0]=='-')
            {
                buff[0] = buff[1] = '-';
                buff[2] = obj[i].str[1];
                buff[3] = '\0';
                obj[i].per->has_key = 0;
                if (!(obj[i].str = newstring(buff)))
                    return ENOMEM;
                obj[i].symb='\0';
            }
            else if (obj[i].str[1] == ':')
            {
                obj[i].symb = obj[i].str[0];
                free(obj[i].str);
                obj[i].str = NULL;
                obj[i].per->has_key = 1;
            }
            else
            {
                buff[0]=buff[1] = '-';
                buff[2] = '\0';
                strcpy(buff+2, obj[i].str);
                obj[i].per->has_key=0;
                obj[i].symb='\0';
                free(obj[i].str);
                if (!(obj[i].str = newstring(buff)))
                    return ENOMEM;
            }
        }
        else
        {
            obj[i].symb='\0';
            buff[0] = buff[1] = '-';
            if (3 == ll && obj[i].str[0]=='-' && obj[i].str[2]==':')
            {
                buff[2] = obj[i].str[1];
                buff[3] = '\0';
                obj[i].per->has_key = 1;
                free(obj[i].str);
                if (!(obj[i].str = newstring(buff)))
                    return ENOMEM;
            }
            else 
            {
                if (obj[i].str[ll-1] == ':')
                {
                    obj[i].per->has_key=1;
                    obj[i].str[ll-1] = '\0';
                }
                else
                    obj[i].per->has_key=0;
                strcpy(buff + 2, obj[i].str);
                free(obj[i].str);
                if (!(obj[i].str=newstring(buff)))
                    return ENOMEM;
            }
        }
    }
    return 0;
}


/** 
 * Сортировка длинных ключей в порядке который позволяет при прямом
 * переборе от младшего индеса к старшему исключить что более короткий
 * ключ перекроет более длинный
 * 
 * @param[in,out] obj Массив подвергающийся сортировки.
 * 
 * @return 0 в случае успеха и неноль при ошибке.
 */
static int sortkeys(tio_key_string *obj)
{
    tio_key_string t, *j, *p = obj;
    
    for(; p->per; ++p)
        for( j = p; j->per; ++j)
        {
            if(!j->str)
                return EINVAL;
            if(strcmp(p->str, j->str)<0)
            {
                t=*j;
                *j=*p;
                *p=t;
            }
        }
    return 0;
}



/** 
 * Разделение на длинные и короткие ключи 
 * 
 * Производит заполнение массивов shortkeys longkeys терминируя их
 * записью содержащей в поле per значение NULL. Записи str в longkey
 * заполнются строками размещенными в heap и должны быть высвобождены
 * при помощи вызова free  по окончании использования. 
 *
 * Внимание строки из массива obj не должны быть освобождены так как
 * они будут использованы при при работе с shortkeys и longkeys и
 * будут освобождены при завершении работы с библиотекой.
 *
 * @param obj Исходный массив данных
 *
 * @param sz Колличество элементов входного массива
 * 
 * @return 0 в случае успеха и ненулевое значение при ошибке
 */
static int splitkeys( tio_key_string *obj, const size_t sz)
{
  size_t lng = 0;
  size_t srt = 0;
  tio_key_string *i, *j, *k;
  tio_key_string *last = (tio_key_string*)(obj + sz);

  for ( i = obj; i < last ; ++i)
    {
      if (i->symb == '\0')
	++lng;
      else 
	++srt;
    }
  ++srt, ++lng;
  if (!(shortkeys=(tio_key_string*)malloc((srt+1)*sizeof(tio_key_string))))
    return errno;
  if(!(longkeys=(tio_key_string*)malloc((1+lng)*sizeof(tio_key_string))))
    return errno;

  for ( i = obj, j = shortkeys, k = longkeys; i < last; ++i)
  {
      if (i->symb =='\0')
      {
          *k=*i;
          ++k;
      }
      else if(i->str == NULL)
      {
          *j=*i;
          ++j;
      }
  }
  j->per = NULL;
  k->per = NULL;
  return 0;
}

/** 
 * Связывание расшифрованных ключей и параметров.
 * 
 * Функция производит обратное связывание заполняя полей keys и skeys
 *
 * @param keys Сгруперованный массив структур tio_key_string в котором
 * если два элемента ссылаются на родительский элемент а межу ними не
 * можеты быть элемента сылающегося на не а.
 *
 * @param ksz  Длинна массива keys
 *
 * @return Код ошибки при провале или ноль в случае успеха.
 */
static int reassing_keys(tio_key_string *keys, size_t ksz)
{
    tio_key_string *i, *last = keys + ksz;
    tio_param_rec **mas, *ptr = NULL;
    size_t *shrtk;
    size_t *longk;
    size_t cnts = 0;
    size_t cntl = 0;
    size_t offset = 0;
    
    
    if (!(shrtk=malloc(sizeof(size_t)*(Tio_params_sz+1))))
        return errno;
    if(!(longk=malloc(sizeof(size_t)*(Tio_params_sz+1))))
    {
        int err = errno;
        free(shrtk);
        errno = err;
        return err;
    }
    if(!(mas = malloc(sizeof(tio_param_rec*)*Tio_params_sz)))
    {
        int err = errno;
        free(shrtk);
        free(longk);
        errno = err;
        return err;
    }
    ptr = keys->per;
    for ( i = keys; i < last; ++i )
    {
        if (i->per != ptr )
        {
            shrtk[offset]=cnts;
            longk[offset]=cntl;
            mas[offset]=ptr;
            cntl=cnts=0;
            ++offset;
            ptr=i->per;
        }
        if (i->str != NULL)
            ++cntl;
        else if (i->symb != '\0')
            ++cnts;
        else
        {
            free(shrtk);
            free(longk);
            fputs(INIT_REASSING_KEYS_ERROR1, stderr);
            return -1;
        }
    }
    shrtk[offset]=cnts;
    longk[offset]=cntl;
    mas[offset]=ptr;
    for ( offset = 0 ; offset < Tio_params_sz; ++offset)
    {
        Tio_params[offset].val = NULL;
        if (longk[offset]==0)
            Tio_params[offset].keys=NULL;
        else
            if(!(Tio_params[offset].keys=malloc(sizeof(char*)*(longk[offset]+1))))
            {
                free(shrtk);
                free(longk);
                return ENOMEM;
            }
        if(shrtk[offset]==0)
            Tio_params[offset].skeys=NULL;
        else
            if(!(Tio_params[offset].skeys=malloc(shrtk[offset]+1)))
            {
                free(shrtk);
                free(longk);
                return ENOMEM;
            }
    }
    cntl = cnts = 0;
    ptr = keys->per;
    for ( i = keys; i < last ; i++ )
    {
        if (i->per != ptr)
        {
            if (ptr->keys != NULL)
                ptr->keys[cntl]=NULL;
            if(ptr->skeys != NULL)
                ptr->skeys[cnts]='\0';
            cntl=cnts=0;
            ptr=i->per;
        }
        if (i->str != NULL)
            ptr->keys[cntl++] = i->str;
        else
            ptr->skeys[cnts++] = i->symb;
    }
    free(mas);
    free(shrtk);
    free(longk);
    return 0;
}




/** 
 * Разбор введеных параметров, перенос из входной структуры в
 * tio_param_rec с преобразованием записи в естественный вид ключа и
 * группировкой по имени параметра.
 * 
 * @param params Список пораметров переданых а tioInit.
 * 
 * @return 0 при успешном завершении и ненулевое значение в противном
 * случае.
 */
int tio_decode_params(tio_param *params)
{
  tio_param *i;
  tio_param_rec *j;
  tio_key_string *keys, *k;
  size_t cnt = 0;
  size_t fsz = 0;

//  if ( (!params) || is_paramNULL(params) )
  if ( (!params) )
    return EINVAL;
  if (is_paramNULL(params))
      return 0;
  tio_params_sort(params);
  


  for( i = params; !is_paramNULL(i); ++i, ++fsz)
    if(i->description) cnt++;


  if ( !(Tio_params = malloc(sizeof(tio_param_rec)*cnt)))
    return ENOMEM;
  Tio_params_sz = cnt;
  if (!(keys = malloc(sizeof(tio_key_string)*(fsz+1))))
    {
      free(Tio_params);
      return ENOMEM;
    }

  Tio_params[0].name=newstring(params->name);
  for ( i = params, j = Tio_params, k=keys; !is_paramNULL(i); i++, ++k )
  {
      if ( j->name == NULL || strcmp(j->name, i->name))
      {
          ++j;
          j->name=newstring(i->name);
      }
      k->str = newstring(i->key);
      if (i->description)
          if (!(j->description = newstring(i->description)))
              return ENOMEM;
      k->per = j;
  }
  // Связали ключи с именами удалив лишние имена - теперь есть два
  // массива - массив имен и массив строк
  if (decode_keys(keys, fsz))
      return ENOMEM;
  if (splitkeys(keys, fsz))
       return ENOMEM;
  if  (reassing_keys(keys, fsz))
       return ENOMEM;
  if(sortkeys(longkeys))
      return ENOMEM;
  free(keys);
  return 0;
}




/** 
 * Фцнкуия извлечения параметров библиотеки из переданных программепараметров
 * 
 * @param argc Количество параметров передаваемых функции
 *
 * @param argv Массив параметров для обработки
 * 
 * @param[out] cnt Колличество оставшихся элементов
 * 
 * @return Массив строк с параметрами не подпадающими под шаблоню Все
 * эти строки должны быть освобожден вызовом free, как и сам массив
 * строк.
 */
static char** extrude_tio(const int argc, const char** argv, int* cnt )
{
    char** ptr;
    tio_simple_chain *par=NULL;
    tio_lib_state *p = tio_self_state;
    tio_simple_chain *tp = NULL;
    int i;

    *cnt = 0;
    for (i=0; i<argc; i++)
    {
        if (!strncmp("--tio-", argv[i], 6))
        {
            for ( p = tio_self_state; p->key != NULL; ++p)
            {
                size_t len = strlen(p->key);
                if ( !strncmp(p->key, argv[i], len))
                {
                    p->set=1;
                    if (argv[i][len]=='=')
                    {
                        if(argv[i][len+1]!='\0')
                            p->value = newstring(argv[i]+len+1);
                        else if (++i < argc )
                            p->value = newstring(argv[i]);
                        else
                        {
                            errno=EINVAL;
                            return NULL;
                        }
                    }
                    else if (i+1 < argc && argv[i+1][0]=='=')
                    {
                        if (argv[++i][1]=='\0')
                        {
                            if (i+1 < argc ) 
                                p->value = newstring(argv[++i]);
                            else
                            {
                                errno=EINVAL;
                                return NULL;
                            }
                        }
                        else 
                            p->value = newstring(argv[i]+1);
                    }
                    if (i==argc)
                    {
                        p->value = NULL;
                    }
                }
            
            }
        }
        else
        {
            tp = NULL;
            if (!(tp = malloc(sizeof(tio_simple_chain))))
             
                return NULL;
            tp->val = newstring(argv[i]);
            tp->next = par;
            par = tp;
            ++(*cnt);
        }
    }
//    for (tp=par, *cnt=0; tp!=NULL; tp = tp->next, ++(*cnt));
    if (!(ptr = malloc(sizeof(char*)* *cnt)))
          return NULL;
    for (i = *cnt,  tp = par; i>0;)
    {
        
        ptr[--i] = tp->val;
        par = tp;
        tp = tp->next;
        free(par);
    }
    errno=0;
    return ptr;

}



static int extractparams(int start, int argc, char** argv)
{
    size_t i;
    size_t cnt=0;
    tio_simple_chain *ptr;
    tio_simple_chain *pt;
    tio_key_string *p;
    
    for (i=start; i < argc; i++)
    {
        if (argv[i][0]=='-')
        {
            if (argv[i][1]=='-')
            {
                for (p=longkeys; p->per != NULL; ++p)
                {
                    size_t k=strlen(p->str);
                    if (!strncmp(p->str, argv[i], k))
                    {
                        if (!(p->per->has_key) && strlen(argv[i])!=k)
                            fprintf(stderr, INIT_UNKNOWN_PARAM, argv[i]);
                        else if(p->per->has_key)
                        {
                            if (argv[i][k]=='=')
                            {
                                if (strlen(argv[i])>k+1)
                                    p->per->val=newstring(argv[i]+k+1);
                                else
                                    p->per->val=newstring(argv[++i]);
                            }
                            else if (argc - i > 1 && argv[i+1][0]=='=')
                            {
                                if (argv[++i][1]=='\0')
                                    p->per->val=newstring(argv[++i]);
                                else
                                    p->per->val=newstring(argv[i]+1);
                            }
                            else
                            {
                                fprintf(stderr, 
                                        INIT_KEY_WITHOUT_PARAM,
                                        argv[i]);
                                return -1;
                            }
                        }
                        else
                            p->per->val=True;
                        break;
                    }
                }
                if (p->per==NULL)
                {
                    fprintf(stderr, INIT_UNKNOWN_KEY, argv[i]);
                }
            }
            else
            {
                int j, sz = strlen(argv[i]);
                int brk = 0;
                for (j=1; !brk && j<sz; ++j)
                {
                    for(p=shortkeys; p->per!=NULL; ++p)
                    {
                        if(p->symb == argv[i][j])
                        {
                            if(p->per->has_key)
                            {
                                if (argv[i][j+1]!='\0')
                                    p->per->val = newstring(argv[i]+j+1);
                                else
                                {
                                    ++i;
                                    if (i < argc)
                                        p->per->val = newstring(argv[i]);
                                    else
                                    {
                                        fprintf(stderr,
                                                INIT_KEY_WITHOUT_PARAM2,
                                                argv[i-1][j]);
                                        return -1;
                                    }
                                }
                                
                                brk=1;
                                break;
                            }
                            else
                            {
                                p->per->val = True;
                                break;
                            }
                        }
                        if (p->per==NULL)
                            fprintf(stderr, INIT_UNKNOWN_KEY2, argv[i][j]);
                    }
                }
            }
        }
        else // argv[i][0]=='-'
        {
            if(!(pt=malloc(sizeof(tio_simple_chain))))
                return -1;
            pt->next = ptr;
            ptr=pt;
            pt->val = argv[i];
            cnt++;
        }
    }
//  Обратный ход - сбор неиспользованных параметров;
    if (cnt>=MAXARGS)
    {
        fprintf(stderr,INIT_TO_MUCH_ARGUMENTS);
        return -1;
    }
    for (i = cnt; i>0;)
    {
        tio_argv[--i]=pt->val;
        pt=pt->next;
        free(ptr);
        ptr=pt;
    }
    return 0;
}


int tioInit(const char* version, const char* help,
            const tio_param param[], const int argc, const char* argv[] )
{
    char **mass;
    int cnt, i;
    int res;
    int *ptr=&cnt;
    tio_param *tmpar;
    
    if((res = tioErrorInit()))
    {
        fputs(INIT_INIT_FAIL, stderr);
#ifdef INITRETURN
        return res;
#else
        exit(res);
#endif
    }
    for(cnt=0;!is_paramNULL(param+cnt);++cnt);
    if(!(tmpar=malloc(sizeof(tio_param)*(++cnt))))
    {
        
        fputs(INIT_MEMORY_ERROR, stderr);
#ifdef INITRETURN
        return TEEPICFAILL;
#else
        exit(TEEPICFAIL);
#endif        
    }
    memcpy(tmpar, param, sizeof(tio_param) * cnt);
    
    if (!version || !help || !argv  || !(argc > 0) || tio_decode_params(tmpar))
    {
        fputs(INIT_INIT_PARAM_ERROR, stderr);
#ifdef INITRETURN
        return EINVAL;;
#else        
        exit(EINVAL);
#endif
    }

    for(i=1; i<argc; ++i)
    {
        if (!strcmp(argv[i], "--help"))
        {
            tioHelp(help, argv[0], Tio_params, Tio_params_sz);
            exit(0);
        }
        if(!(strcmp(argv[i], "--version")))
        {
            printf(INIT_VERSION_INFO, argv[0],  version);
            exit(0);
        }
    }

    selfname = newstring(argv[0]);
    fprintf(stdout, INIT_RUN_MSG, argv[0]);

    if(!(mass = extrude_tio(argc-1, argv + 1, ptr))&&errno)
    {
        puts(strerror(errno));
        fputs(INIT_MEMORY_ERROR, stderr);
#ifdef INITRETURN
        return TEFAIL;;
#else        
        exit(TEFAIL);
#endif
    }

    if (extractparams(0, cnt, mass))
    {
#ifndef NDEBUG
        fputs(INIT_READ_PARAM_ERROR, stderr);
#endif
#ifdef INITRETURN
        return TEFAIL;;
#else        
        exit(TEFAIL);
#endif
    }
    for (i = 0; i< cnt; ++i)
        free(mass[i]);
    free(mass);
    free(tmpar);

    return 0;
}

/** 
 * Функция освобождения ресчурсов выделенных при запуске библиотеки
 * 
 */
void tioFree()
{

    tio_key_string *p;
    size_t i;
    
    tioErrorFree();
    
    if(longkeys)
        for ( p = longkeys; p->per != NULL; ++p )
            free(p->str);
    for (i=0 ; i < Tio_params_sz; ++i)
    {
        if (Tio_params[i].keys) 
            free(Tio_params[i].keys);
        if(Tio_params[i].skeys)
            free(Tio_params[i].skeys);
        if(Tio_params[i].has_key && Tio_params[i].val)
            free(Tio_params[i].val);
        free(Tio_params[i].name);
        free(Tio_params[i].description);
    }
    if (Tio_params) 
        free(Tio_params);
    if(longkeys)
        free(longkeys);
    if(shortkeys)
        free(shortkeys);

}
