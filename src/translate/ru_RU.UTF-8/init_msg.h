/**
 * @file   init_msg.h
 * @author Egorov N.V. <egorov@rti-mints.ru>
 * @date   Wed Sep 15 16:50:37 2010
 * 
 * @brief  Текстовые сообщения для init.c
 * 
 * 
 */


#ifndef _INIT_TRANS_H
#define _INIT_TRANS_H

#define INIT_UNKNOWN_PARAM "Неизвестный параметр %s\n"
#define INIT_KEY_WITHOUT_PARAM "Ключ %s без параметра, хотя параметр ожидается\n"
#define INIT_KEY_WITHOUT_PARAM2 "Ключ %c без параметра, хотя параметр ожидается\n"
#define INIT_UNKNOWN_KEY "Неизвестный ключ %s\n"
#define INIT_UNKNOWN_KEY2 "Неизвестный ключ -%c\n"
#define INIT_TO_MUCH_ARGUMENTS "Слишком большое количество аргументов\n"
#define INIT_INIT_FAIL "Сбой при инициализации системы работы с ошибками"
#define INIT_MEMORY_ERROR "Ошибка памяти\n"
#define INIT_INIT_PARAM_ERROR "Ошибка при инициализации библиотеки - не верно заданы" \
    "параметры инициализации\n"
#define INIT_VERSION_INFO "Программа %s версия %s\n"
#define INIT_RUN_MSG "[RUN]: Запуск %s\n"
#define INIT_READ_PARAM_ERROR "Ошибка чтения параметров при иницализации библиотеки\n"
#define INIT_REASSING_KEYS_ERROR1 "Ошибка чтения параметров: Ошибка времени выполнения"


#endif
