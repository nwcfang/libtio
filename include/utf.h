/**
 * @file   utf.h
 * @author Egorov N.V. <egorov@rti-mints.ru>
 * @date   Wed Jul  7 15:14:23 2010
 * 
 * @brief  
 * 
 * 
 */

#include <stdlib.h>


#ifndef _UTF_H
#define _UTF_H

/** 
 * Определение строки симвлов кодированной 
 *
 * Возвращает длинну строки учитывая возможность того что строка
 * является строкой UTF-8 символов
 * 
 * @param obj указатель на строку
 * 
 * @return длинну строки печетаемых символов.
 */
size_t utf_strlen(const char* obj);


/** 
 * Поиск  адресса n-го го символа в строке
 * 
 * @param obj Начало строки
 *
 * @param symbnum Номер символа в строке.
 * 
 * @return Адресс символа в строке или адрес завершающего нуля если
 * запрошен символ за пределами строки
 */
char* utf_stroffset(const char* obj, const size_t symbnum);

#endif //_UTF_H
