/**
 *
 * @file    tioTableBegin.c
 * @author  Gusev M.S. 
 * @date    2011-02-25
 *
 * @brief   Набор функций для табличного вывода данных
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include <tio.h> 

#define WIDTH 120

typedef struct cell     /*list*/ 
{
    void **s;           /*Массив указателей на неизвестный тип данных*/ 
    struct cell *n;     /*Указатель на следующий элемент списка*/ 
} cl;

struct inform
{
    char **cap;         /*Шапка*/
    int countLetter;    /*Колличество символов в строке*/
    int countColum;     /*Колличество столбцов*/
    int *bufType;      /*Буфер с типам данных для каждого столбца*/
    cl *head, *ptr;      /*Список данных*/ 
};


int tabRow( void **strings, int *bufType, int countColum, int lenColCon );

int capMap( int countColum, char **cap, int lenColCon );

int drawLine( int lenColCon );

/*Table initialization*/
void* tioTableBegin( const char* format,  ... )
{
    va_list ap;
    int i;
    int jj; 
    int j;
    struct inform *datTab;
    void *extPointer;

    va_start( ap, format );

    /*Allocating memory for datTab structure*/
    if( (datTab = (struct inform*) calloc( 1, sizeof(struct inform)) ) == NULL )
    {
        fprintf( stderr, "\nError \n" );
        return NULL;
    }

    /*Count the number of columns in a table and calculate the maximum length of the column.*/
    datTab->countColum = 1;
    for( i = 0; format[i] != '\0'; ++i )
    {
        ++ datTab->countLetter;
        if( (format[i] == '&') && ((format[i+1]) != '&'))
            ++ datTab->countColum;
        else if( (format[i] == '&') && ((format[i+1]) == '&'))
            ++ i;
    }

    printf("Count of letter %d.\nCount of colum %d.\n", datTab->countLetter,
            datTab->countColum );

    /*Allocating memory for cap*/
    if( (datTab->cap = (char**) calloc(datTab->countColum , sizeof(char*))) != NULL )
    {
        for( i = 0; i < datTab->countColum ; ++ i)
        {
            if( (datTab->cap[i] = (char*) calloc(datTab->countLetter + 1, sizeof(char))) == NULL )
            {
                printf(" error datTab->cap[%d][]\n",i);
                return NULL;
            }
        }
    }
    else
    {
        printf("\nerror\n");
        return NULL;
    }


    /*Allocating memory for datTab->bufType*/
    if( (datTab->bufType = (int*) calloc(datTab->countColum, sizeof(int))) == NULL )
    {
        printf("\nerror *datTab->bufType\n");
        return NULL;
    }

    printf("\n");

    /*Allocating memory for pointer to the head of list*/ 
    if( (datTab->head = (cl *) malloc( sizeof(cl))) == NULL )
    {
        printf("\nError ptr\n");
        return NULL;
    }

    datTab->ptr = datTab->head;
    datTab->ptr->n = NULL;

    /*Allocating memory for ptr->s*/    
    if( (datTab->ptr->s = (void **) calloc(datTab->countColum, sizeof(void *))) == NULL )
    {
        printf("\nError ptr->s\n");
        return NULL;
    } 

    /*Writing data types to the buffer*/
    printf ("Data types: ");
    for ( i = 0; i < datTab->countColum; ++ i )
    {
        datTab->bufType[i] = va_arg(ap, int);
        printf("%d ", datTab->bufType[i]);
    }

    printf("\n");


    /*Set colum's name*/
    jj = 0;
    for( i = 0; i < datTab->countColum; ++ i )
    {
        j = 0;
        while(1)
        {
            if(format[jj] == '\0')
                break;
            if((format[jj] == '&') && (format[jj+1] != '&'))
                break;
            datTab->cap[i][j] = format[jj];
            if((format[jj] == '&') && (format[jj+1] == '&'))
                ++jj;
            ++ j;
            ++ jj;
            
        }
        ++jj;

    }

    /*Print colum's name*/
    for( i = 0; i < datTab->countColum; ++i )
    {
        printf("%s", datTab->cap[i]);
        printf("\n");
    }

    va_end( ap );

    extPointer = (void *) datTab;
    return extPointer;
}

/*RECORDING DATA IN TABLE*/ 
void *tioTableRecord( void *td, ...  )
{
    va_list ap;
    struct inform *datTab;
    int i;
    char ch;
    double dbd;
    long ln;
    char* strn;
    void *extPointer;


    va_start( ap, td );
    
    datTab = (struct inform *) td;

    for( i = 0; i < datTab->countColum; ++ i )
    {
        switch( datTab->bufType[i] )
        {
        case 1:
            ch = (char) va_arg( ap, int);
            datTab->ptr->s[i] = calloc(1, sizeof(char));
            *(char *)datTab->ptr->s[i] =  ch;
            printf("char %c /added\n", *(char *)datTab->ptr->s[i]);
            break;
        case 2:
            dbd =  va_arg( ap, double);

            datTab->ptr->s[i] = malloc(sizeof(double));
            *(double *)datTab->ptr->s[i] = dbd;
            printf("double %f /added\n", *(double *)datTab->ptr->s[i]);

            break;
        case 3:
            ln =  va_arg( ap, long);
            datTab->ptr->s[i] = calloc(1, sizeof(long));
            *(long *)datTab->ptr->s[i] = ln;
            printf("long %ld /added\n", *(long *)datTab->ptr->s[i]);
            break;
        case 4:
            strn = va_arg( ap, char *);
            datTab->ptr->s[i]=(char *)calloc(strlen(strn) + 1, sizeof(char));  
            strcpy ((char *)datTab->ptr->s[i],strn);
            printf("string %s /added\n",  (char *) datTab->ptr->s[i]);
            break;
        default:
            printf("Неправельный параметр функции tioTableRecord!\n");
            return NULL;
        }
    }

    /*ALLOCATING MEMORY FOR THE HEAD POINTER OF LIST*/
    if( (datTab->ptr->n = (cl*) malloc(sizeof(cl))) == NULL )
    {
        printf("Error\n");
        return NULL;
    }
    datTab->ptr = datTab->ptr->n;
    datTab->ptr->n = NULL;

    /*ALLOCATIONG MEMORY FOR THE POINTER OF ptr->s*/
    if( (datTab->ptr->s = (void **) calloc(datTab->countColum, sizeof(void *))) == NULL )
    {
        printf("\nError ptr->s\n");
        return NULL;
    }

    va_end(ap);

    //extPointer = (void *) datTab;
    td = ( void * ) datTab;

    return td;

}


/*Table's output*/ 
int tioTableEnd( void *td )
{
    struct inform *datTab;
     
    int i;                          /*Counter*/ 
    int lenColCon;                  /*Cell width*/ 
    void *next;     
    int *masType;                   /*For type of cap*/ 
    datTab = (struct inform *) td;
    
    datTab->ptr = datTab->head;
    /*printf("string in End = %s\n", (char*)datTab->ptr->s[3]);*/

    /*Calculate the column width depending on the number of*/  
    lenColCon = WIDTH / datTab->countColum;   
    printf("Размер колонки = %d\n", lenColCon);
    
    if( (masType = (int *) malloc(datTab->countColum * sizeof(int))) == NULL)
    {
        printf("ERROR!");
        exit(EXIT_FAILURE);
    }

    /*Draw line*/ 
    drawLine(lenColCon); 
    
    for( i = 0; i < datTab->countColum; ++ i )
    {
        masType[i] = 4;
    }
    /*Display cap*/
    tabRow( (void *)datTab->cap, masType, datTab->countColum, lenColCon); 
    
    /*Draw line*/
    drawLine(lenColCon);
    
    while( datTab->ptr->n != NULL )
    {

        /*Print table row*/ 
        tabRow( datTab->ptr->s, datTab->bufType, datTab->countColum, lenColCon );

        /*Jump to the new cell*/ 
        datTab->ptr = datTab->ptr->n;
        /*Draw line*/
        drawLine(lenColCon);
    }
    
    /*Free masType*/
    free(masType);
    /*Free data*/
    for( i = 0; i < datTab->countColum; ++ i )
        free(datTab->cap[i]);
    free( datTab->cap );

    /*Free bufTab*/
    free(datTab->bufType);

    /*Free ptr->s*/ 
    datTab->ptr = datTab->head;
    do 
    {     
        next = (void *) datTab->ptr->n;
        for( i = 0; i < datTab->countColum; ++ i )
        {
            if(datTab->ptr->n != NULL)
                free(datTab->ptr->s[i]);
        }
        free(datTab->ptr->s);
        free(datTab->ptr);
        datTab->ptr = (cl *) next;
    } while (datTab->ptr != NULL);

    /*Free datTab*/
    free(datTab);

    return 0;
}

/*LOCAL FUNCTION*/ 

/*Table row*/ 
int tabRow( void **strings, int *bufType, int countColum, int lenColCon )
{
    char ***data;                   /*Pointer of the table's data*/
    int *colStr;                    /*Array of extra lines*/ 
    int i;
    int j;
    int max = 0;
    int extraCounter;               /*Extra lines counter*/ 
    int offset;                     /*Offset counter*/ 
    int strCounter;

    /*Allocating memory for colStr*/ 
    if( (colStr = (int *) malloc(countColum * sizeof(int))) == NULL )
    {
        printf("ERROR!");
        exit(EXIT_FAILURE);
    }

    /*Calculation number of extra lines of the array*/ 
    for( i = 0; i < countColum; ++ i )
    {
        colStr[i] = strlen( (char *)strings[i] ) / lenColCon; 
        if(max < colStr[i])
            max = colStr[i];
    }

    /*Allocating memory for data*/ 
    if((data = (char ***) malloc (countColum * sizeof(char **))) == NULL)
    {
        printf("ERROR!\n");
        exit(EXIT_FAILURE);
    }
    for( i = 0; i < countColum; ++ i )
    {
        if((data[i] = (char **) malloc ((max + 1) * sizeof(char *))) == NULL)
        {
            printf("ERROR!\n");
            exit(EXIT_FAILURE);
        }       
        else
        {
            for (j = 0; j < (max + 1); ++ j)
            {
                if((data[i][j] = (char *) malloc (lenColCon * sizeof(char))) == NULL)
                {
                    printf("ERROR!\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    /*Partition line*/ 
    for(i = 0; i < countColum; ++ i)
    {
        switch( bufType[i] )
        {
        case 1:
            sprintf( data[i][0], "%c",*(char *) strings[i]);
            offset = strlen(data[i][0]);
            /*Insert spaces*/
            for( offset; offset < (lenColCon - 1); ++ offset)
                data[i][0][offset] = ' ';
            /*Insert spaces*/
            for(extraCounter = 1; extraCounter < (max + 1); ++ extraCounter)
                for( offset = 0; offset < (lenColCon - 1); ++ offset )
                    data[i][extraCounter][offset] = ' ';           
            break;
        case 2:
            sprintf( data[i][0], "%.2f",*(double *) strings[i]);
            offset = strlen(data[i][0]);
            /*Insert spaces*/
            for( offset; offset < (lenColCon - 1); ++ offset)
                data[i][0][offset] = ' ';
            /*Insert spaces*/
            for(extraCounter = 1; extraCounter < (max + 1); ++ extraCounter)
                for( offset = 0; offset < (lenColCon - 1); ++ offset )
                    data[i][extraCounter][offset] = ' '; 
            /*printf("90 string in End = %s\n", (char*)strings[3]);*/
            break;
        case 3:
            sprintf( data[i][0], "%ld",*(long *) strings[i]);
            offset = strlen(data[i][0]);
            /*Insert spaces*/
            for( offset; offset < (lenColCon - 1); ++ offset)
                data[i][0][offset] = ' ';
            /*Insert spaces*/
            for(extraCounter = 1; extraCounter < (max + 1); ++ extraCounter)
                for( offset = 0; offset < (lenColCon - 1); ++ offset )
                    data[i][extraCounter][offset] = ' ';
            break;
        case 4:
            for( extraCounter = 0; extraCounter <= colStr[i]; ++ extraCounter )
            {
                j = extraCounter * (lenColCon - 1);
                for( offset = 0;
                        ((offset != (lenColCon - 1)) && (((char *)strings[i])[j] != '\0' )); ++ offset, ++ j)
                {
                    data[i][extraCounter][offset] = ((char *)strings[i])[j]; 
                }
                /*Insert spaces*/
                for( offset; offset < (lenColCon - 1); ++ offset)
                    data[i][extraCounter][offset] = ' ';
            }
            /*Insert spaces*/
            for(extraCounter = colStr[i] + 1; extraCounter < (max + 1); ++ extraCounter )
                for( offset = 0; offset < (lenColCon - 1); ++ offset )
                    data[i][extraCounter][offset] = ' ';
            break;
        default:
            printf("ERROR!");
            exit(EXIT_FAILURE);
        }
        
    
    }

    /*Print row*/
        for( strCounter = 0; strCounter < (max + 1); ++ strCounter  )
        {
            for( i = 0; i < countColum; ++ i )
                printf("|%s", data[i][strCounter]);    
            printf("|\n");
        } 

    /*FREE */
    for( i = 0; i < countColum; ++ i )
    {
        for( j = 0; j < colStr[i]; ++ j )
        {
            free(data[i][j]);
        }
        free(data[i]);
    }
    free(data);

    free(colStr);
    
    return 0;

}

/*Display cap*/ 
int capMap( int countColum, char **cap, int lenColCon )
{
    int i;
    int j;
    int tmp;
    for(i = 0; i < countColum; ++ i )
    {
        printf( "|%s", cap[i] );
        tmp = lenColCon - strlen(cap[i]);
        for( j = 0; j < tmp - 1; ++ j )
            printf( " " );
    }
    printf( "|\n");
    
    return 0;
}

/*Draw line function*/
int drawLine( int lenColCon )
{
    int i;
    for( i = 0; i < WIDTH; ++ i )   /*Need correct WIDTH*/ 
    {
        if((i % lenColCon) == 0)
            printf("+");
        else
            printf("-");
    }
    printf( "+\n" );

    return 0;
}
