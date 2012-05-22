/**
 * @file   longto.h
 * @author Egorov N.V. <egorov@rti-mints.ru>
 * @date   Tue Aug 24 17:18:07 2010
 * 
 * @brief  
 * 
 * 
 */


#ifndef _LONG_TO_H
#define _LONG_TO_H

/** 
 * Функция преобразования целого числа obj в строку шеснадцетиричного
 * буквы в верхнем регистре формата с занесением в буфер out длинны
 * bl.
 * 
 * @return NULL при недостаточном количестве места в буфере 
 */
inline char* longtoHEX(long obj, char* out, size_t bl);

/** 
 * Функция преобразования целого числа obj в строку шеснадцетиричного
 * буквы в нижнем регистре формата с занесением в буфер out длинны
 * bl.
 * 
 * @return NULL при недостаточном количестве места в буфере 
 */
inline char* longtohex(long obj, char* out, size_t bl);

/** 
 * Функция преобразования целого числа obj в строку восьмиричной с
 * занесением в буфер out длинны bl.
 * 
 * @return NULL при недостаточном количестве места в буфере 
 */
char* longtooct(long obj, char* out, size_t bl);

/** 
 * Функция преобразования целого числа obj в строку десятичной формы с
 * занесением в буфер out длинны bl.
 * 
 * @return NULL при недостаточном количестве места в буфере 
 */
char* longtodec(long obj, char *out, size_t bl);

#endif _LONG_TO_H
