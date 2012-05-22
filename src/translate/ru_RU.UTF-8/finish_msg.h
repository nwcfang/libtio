/**
 * @file   finish_msg.h
 * @author Egorov N.V. <egorov@rti-mints.ru>
 * @date   Wed Sep 15 17:23:36 2010
 * 
 * @brief  Текстовые сообщения для finish.c
 * 
 * 
 */


#ifndef _FINISH_MSG_H
#define _FINISH_MSG_H

typedef char* strg;

static strg  finish_messages[] = {
    "[PASS]: %s : Тест пройден успешно\n",
    "[FAIL]: %s : Тест провален\n",
    "[FAIL]: %s : Не выполнены условия запуска теста\n",
    "[FAIL]: %s : Внутрення ошибка библиотеки\n"
};

#endif
