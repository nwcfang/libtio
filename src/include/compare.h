/**
 * @file   compare.h
 * @author Egorov N.V. <khenarghot@gmail.com>
 * @date   Fri Jul 30 17:01:22 2010
 * 
 * @brief  
 * 
 * 
 */


#ifndef _COMPARE_H
#define _COMPARE_H

/** 
 * Функция сравения произвольных типов данных
 * 
 * 
 * @todo Избавиться
 */
int cmpfoo(void* a, void* b, size_t sz);

/** 
 * Сравнение двух переменных типа pthread_t
 * 
 * 
 * @return 0 если значения равны, 1 если a < b и -1 если b < a
 */
int cmppthread_t(pthread_t *a, pthread_t *b);
#endif
