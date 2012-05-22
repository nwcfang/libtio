/**
 * @author Egorov N.V. <egorov@rti-mints.ru>
 * @date   Wed Sep 15 17:23:36 2010
 * 
 */


#ifndef _FINISH_MSG_H
#define _FINISH_MSG_H

typedef char* strg;

static strg  finish_messages[] = {
    "[PASS]: %s : Sucsessfull pass\n",
    "[FAIL]: %s : Testing fail\n",
    "[FAIL]: %s : Wrong test enviroment due start\n",
    "[FAIL]: %s : Internal library error\n"
};

#endif
