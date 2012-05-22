/**
 * @file   test_all_out.c
 * @author Egorov N.V. <egorov@rti-mints.ru>
 * @date   Thu Sep 30 16:09:24 2010
 * 
 * @brief  Тестирование всех возможных функций вывода
 * 
 * 
 */


#include <tio.h>

tio_param params[] = {
    { NULL, NULL, NULL }
};

int main(int argc, char** argv)
{
    tioInit("1.0.0", "Программа тестирующая все возможные системы вывыода",
            params, argc, argv);

    tioPrint("Hello my darling\n");
    tioPrintF("This %s is %d-st test for me\n", "programm", (long)1);
    tioWarning("I think It\'s rather prety\n");
    tioWarningF("I %s it well be usefull\n", "programm");
    tioDebug("Thow it can be useless as much\n");
    tioDebugF("%s", "And even dangerous\n");
    tioError("But i think it weel be great\n");
    tioErrorF("It\'s over %X\n", 9000);

    tioFinish(TOPASS);
    return 0;
}
